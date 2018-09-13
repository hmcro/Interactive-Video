#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // there is a run script that copies the contents of the /bin/data/ folder
    // into the /Resources/data/ folder every time we run the project
    // so we must tell oF to load from the correct folder
    ofSetDataPathRoot("../Resources/data/");

    // load all video urls into array
    videos[0].load("Attractor.mp4");
    videos[1].load("End1.mp4");
    videos[2].load("Meeting1.mp4");
    videos[3].load("Questions1.mp4");
    videos[4].load("Questions2.mp4");
    videos[5].load("Questions3.mp4");
    videos[6].load("Questions4.mp4");
    videos[7].load("Reflection1.mp4");
    videos[8].load("Reflection2.mp4");
    videos[9].load("Tour1.mp4");
    videos[10].load("Tour2.mp4");
    videos[11].load("Tour3.mp4");
    videos[12].load("Welcome1.mp4");
    videos[13].load("Welcome2.mp4");
    
    // tell the attractor to play on loop
    videos[0].setLoopState(OF_LOOP_NORMAL);
    
    // tell the normla video to play once
    videos[1].setLoopState(OF_LOOP_NONE);
    
    // start playing the attractor video immediately
    playVideo(0);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    updateVideo();

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    
    drawVideo();
    
    string str = "ATTRACTOR TOGGLE";
    str += "\n\nA = attractor video";
    str += "\nB = welcome video";
    str += "\nF = fullscreen";
    str += "\nS = scale mode";
    if (videoMaxScale) {
        str += " (max)";
    }
    else {
        str += " (with borders)";
    }
    
    ofDrawBitmapString(str, 50, 50);

}

//--------------------------------------------------------------
void ofApp::playVideo(int n){
    
    // stop any existing video
    if (videoPointer) {
        videoPointer->stop();
    }
    
    // switch to the new video using a pointer
    videoPointer = &videos[n];
    
    // set to starting frame
    videoPointer->setPosition(0);
    
    // start playing from the beginning
    videoPointer->play();
    
}

//--------------------------------------------------------------
void ofApp::updateVideo(){
    
    // check if the video has finished
    // the attractor doesn't trigger this because of it's loopState
    // so it's only when normal videos stop
    if ( videoPointer->getIsMovieDone() ) {
        cout << "video finished\n";        
        // play the attractor
        playVideo(0);
    }
    
    videoPointer->update();
    
}

//--------------------------------------------------------------
void ofApp::drawVideo(){
    
    ofPushMatrix();
    
    // convert width and height to floats so we can use decimals
    float screenWidth = ofGetWidth();
    float screenHeight = ofGetHeight();
    float screenRatio = screenWidth / screenHeight;
    
    // check the screen ratio and stretch the width or the height
    if (screenRatio >= hdVideoRatio) {
        
        // wider
        
        if (videoMaxScale) {
            // draw the video in the absolute center and without borders
            float newHeight = screenWidth/hdVideoRatio;
            videoPointer->draw(0, (screenHeight-newHeight)/2, screenWidth, newHeight);
        }
        else {
            float newWidth = screenHeight*hdVideoRatio;
            videoPointer->draw((screenWidth-newWidth)/2, 0, newWidth, screenHeight);
        }
        
    }
    else {
        
        // taller
        
        if (videoMaxScale) {
            // draw the video in the absolute center and without borders
            float newWidth = screenHeight*hdVideoRatio;
            videoPointer->draw((screenWidth-newWidth)/2, 0, newWidth, screenHeight);
        }
        else {
            float newHeight = screenWidth/hdVideoRatio;
            videoPointer->draw(0, (screenHeight-newHeight)/2, screenWidth, newHeight);
        }
        
    }
    
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if (key == 'a') {
        playVideo(0);
    }
    else if (key == 'b') {
        playVideo(1);
    }
    else if (key == 'f') {
        ofToggleFullscreen();
    }
    else if (key == 's') {
        videoMaxScale = !videoMaxScale;
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}
