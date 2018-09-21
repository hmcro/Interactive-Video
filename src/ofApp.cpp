#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // there is a run script that copies the contents of the /bin/data/ folder
    // into the /Resources/data/ folder every time we run the project
    // so we must tell oF to load from the correct folder
    ofSetDataPathRoot("../Resources/data/");
    
    // set the colour
    orange1.setHex(0xE9501E);
    orange2.setHex(0xAF2C00);
    
    // load the GFX
    logo.load("hmcro-logo.svg");
    person.load("person-icon.svg");
    
    // load the audio
    ding.load("91926__corsica-s__ding.wav");

    // load all video urls into array
    videos[0].load("Attractor.mov");
    videos[1].load("Welcome1.mov");
    videos[2].load("Welcome2.mov");
    videos[3].load("Tour1.mov");
    videos[4].load("Tour2.mov");
    videos[5].load("Tour3.mov");
    videos[6].load("Questions1.mov");
    videos[7].load("Questions2.mov");
    videos[8].load("Questions3.mov");
    videos[9].load("Questions4.mov");
    videos[10].load("Meeting1.mov");
    videos[11].load("Reflection1.mov");
    videos[12].load("Reflection2.mov");
    videos[13].load("End.mov");
    videos[14].load("Detected.mov");
    
    // tell all the videos to only play once
    for(int i = 0; i < VIDEOS_LENGTH; i++) {
        videos[i].setLoopState(OF_LOOP_NONE);
    }
    
    // BUT tell the attractor to play on looping
    videos[0].setLoopState(OF_LOOP_NORMAL);
    
    // start playing the attractor video immediately
    playVideo(0);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // update the sound playing system:
    ofSoundUpdate();
    
    // check if the video has finished
    // the attractor doesn't trigger this because of it's loopState
    // so it's only when normal videos stop
    if ( videos[nPlaying].getIsMovieDone() ) {
        cout << "video finished, nPlaying(" << nPlaying << ")" << endl;

        // are there any more videos to play?
        if ( nPlaying >= SEQUENCE_LENGTH-1 ) {

            // play the attractor
            playVideo(0);

            isSequencePlaying = false;
        }
        else {

            // increase the nPlaying number to the next video in the array
            nPlaying++;

            playVideo( sequence[nPlaying] );
        }

    }

    videos[nPlaying].update();
    
    if (isVisitorAnimating) {
        float timer = ofGetElapsedTimef() - visitorStartTime;
        
        // check and stop the timer
        if (timer >= 6) {
            cout << "stop the timer" << endl;
            isVisitorAnimating = false;
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    
    // convert width and height to floats so we can use decimals
    float screenWidth = ofGetWidth();
    float screenHeight = ofGetHeight();
    float screenRatio = screenWidth / screenHeight;
    
    // check the screen ratio and stretch the width or the height
    if (screenRatio >= hdVideoRatio) {
        
        // wider
        
        float newWidth = screenHeight*hdVideoRatio;
        videos[nPlaying].draw((screenWidth-newWidth)/2, 0, newWidth, screenHeight);
        drawGFX((screenWidth-newWidth)/2, 0, newWidth, screenHeight);
        
        if (showControls) {
            drawDebugInfo((screenWidth-newWidth)/2, 0, newWidth, screenHeight);
        }
        
    }
    else {
        
        // taller
        
        float newHeight = screenWidth/hdVideoRatio;
        videos[nPlaying].draw(0, (screenHeight-newHeight)/2, screenWidth, newHeight);
        drawGFX(0, (screenHeight-newHeight)/2, screenWidth, newHeight);
        
        if (showControls) {
            drawDebugInfo(0, (screenHeight-newHeight)/2, screenWidth, newHeight);
        }
        
    }

}


//--------------------------------------------------------------
void ofApp::drawGFX(float x, float y, float w, float h){
    
    float scale = w / 1920.0f;
    
    // draw the line
    ofDrawLine( x+(w*gfxPaddingX), y+h-(logo.getHeight()*scale)-((h*gfxPaddingY)*2),
               w-(w*gfxPaddingX), y+h-(logo.getHeight()*scale)-((h*gfxPaddingY)*2) );
    
    // move to bottom of screen to draw logo
    ofPushMatrix();
    ofTranslate(x+(w*gfxPaddingX), y+h-(logo.getHeight()*scale)-(h*gfxPaddingY));
    
    // draw the logo at the correct scale
    ofScale(scale, scale);
    
    // draw the logo
    logo.draw();
    
    ofPopMatrix();
    
    
    
    // move to bottom of screen to draw logo
    ofPushMatrix();
    ofTranslate(w-(w*gfxPaddingX), y+h-(logo.getHeight()*scale)-((person.getHeight()*scale)/2));
    
    // create an iterator that points to the first element
    vector<string>::iterator it = visitors.begin();
    
    // loop through, increasing to next element until the end is reached
    for(; it != visitors.end(); ++it){
        // draw the people icons
        ofTranslate(-(person.getWidth()*scale), 0);
        
        // scale the icon to the right size
        ofPushMatrix();
        ofScale(scale, scale);
        person.draw();
        ofPopMatrix();
        
        ofTranslate(-5, 0);
    }
    
    if (isVisitorAnimating) {
        // nudge up a little and draw the string
        ofTranslate((person.getWidth()*scale)/2+5, -50);
        ofDrawBitmapStringHighlight("Citizen #" + visitors.back() + " detected", -110, 0, orange2);
        
        ofPushStyle();
        ofSetColor(orange2);
        ofDrawLine(0, 0, 0, 50);
        ofPopStyle();
    }
    
    
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void ofApp::drawDebugInfo(int x, int y, int w, int h){
    
    string str = "VIDEO SEQUENCER";
    str += "\n\nA = attractor video";
    str += "\nF = fullscreen";
    str += "\n+ = Add 1 visitor";
    str += "\n- = Remove 1 visitor";
    str += "\n\nisPlayingSequence: " + ofToString(isSequencePlaying);
    str += "\nSequence: ";
    
    // output the sequence order and highlight the new video position
    for(int i = 0; i < SEQUENCE_LENGTH; i++) {
        if (i == nPlaying) {
            str += "[";
        }
        str += ofToString(sequence[i]);
        if (i == nPlaying) {
            str += "]";
        }
        if (i < SEQUENCE_LENGTH-1) {
            str += ",";
        }
    }
    
    str += "\nVisitors: " + ofToString(visitors.size());
    
    ofDrawBitmapString(str, x+(w*gfxPaddingX), y+(w*gfxPaddingX));
}

//--------------------------------------------------------------
void ofApp::generateVideoSequence(){
    cout << "generateVideoSequence" << endl;
    
    // create a new sequence randomly and replace current sequence
    sequence[0] = 14; // detected
    sequence[1] = round( ofRandom(1, 2) ); // welcome
    sequence[2] = round( ofRandom(3, 5) ); // tour
    sequence[3] = round( ofRandom(6, 9) ); // question
    sequence[4] = 10; // meeting
    sequence[5] = round( ofRandom(11, 12) ); // reflection
    sequence[6] = 13; // end
    
    // reset the playhead so the next video will be the first in the sequence
    nPlaying = 0;
}

//--------------------------------------------------------------
void ofApp::playVideo(int n){
    
    // stop any existing video
    videos[nPlaying].stop();
    
    // set to starting frame
    videos[nPlaying].setPosition(0);
    
    // start playing from the beginning
    videos[nPlaying].play();
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if (key == 'a') {
        
        isSequencePlaying = false;
        playVideo(0);
        
    }
    else if (key == 'f') {
        
        ofToggleFullscreen();
        
    }
    
    else if (key == '+') {
        
        addVisitor();
        
    }
    
    else if (key == '-') {
        
        removeVisitor();
        
    }
    
    else if (key == ' ') {
        
        // toggle the controls top left
        showControls = !showControls;
        
    }
    
}

//--------------------------------------------------------------
void ofApp::addVisitor(){
    
    if (visitors.size() < MAX_VISITORS) {
        
        // add random ID to the vector
        string id = "";
        id += getRandomChar();
        id += getRandomChar();
        id += ofToString( rand() % 9 + 1 );
        id += ofToString( rand() % 9 + 1 );
        id += ofToString( rand() % 9 + 1 );
        id += ofToString( rand() % 9 + 1 );
        id += ofToString( visitors.size() % 10 );
        id += getRandomChar();
        
        visitors.push_back( id );
        
        // play the audio sound
        ding.play();
        
        // start the timer to show/hide the id
        visitorStartTime = ofGetElapsedTimef();
        isVisitorAnimating = true;
        
        if (!isSequencePlaying) {
            
            // regenerate a new video sequence
            generateVideoSequence();
            
            // play the first video in the sequence
            playVideo(sequence[nPlaying]);
            
            isSequencePlaying = true;
        }
        
    }
    
}

//--------------------------------------------------------------
void ofApp::removeVisitor(){
    
    if (visitors.size() > 0) {
        
        // erase the last element in the vector
        visitors.pop_back();
        
        // play the audio sound
        ding.play();
        
        // check and hide the id if everyone's left
        if ( visitors.size() == 0 ) {
            isVisitorAnimating = false;
        }
        
    }
    
}


//--------------------------------------------------------------
char ofApp::getRandomChar(){
    
    return rand() % 26 + 'A';
} 

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}
