#pragma once

#include "ofMain.h"
#include "ofxSvg.h"

#define VIDEOS_LENGTH 14
#define SEQUENCE_LENGTH 6
#define MAX_VISITORS 40

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        //
        // VIDEO RENDER STUFF
        //
    
        // use these functions to start each new video
        // we don't access the array of videos directly
        void playVideo(int n);
        void drawVideo(int x, int y, int w, int h);
    
        // fixed ratio that we compare against to resize & scale the video
        const float hdVideoRatio = 1.777;
    
        // array of all the video files
        ofVideoPlayer videos[VIDEOS_LENGTH];
    
        // Pointer to ofVideoPlayer
        ofVideoPlayer *videoPointer;
    
        //
        // VIDEO SEQUENCE STUFF
        //
    
        // use these functions to regenerate a list of videos to play
        void generateVideoSequence();
    
        // Array to hold the generated video sequence
        // each number represents a video from the video array
        int sequence[SEQUENCE_LENGTH];
    
        // int to remember which video we're playing
        int nPlaying;
    
        //
        // GFX STUFF
        //
    
        void drawDebugInfo(int x, int y, int w, int h);
        void drawGFX(float x, float y, float w, float h);
    
        // padding to space things away from the edge of the screen (percent)
        const float gfxPaddingX = 0.055;
        const float gfxPaddingY = 0.02;
    
        // logo
        ofxSVG logo;
        ofxSVG person;
    
        // audio
        ofSoundPlayer  ding;
    
        // flag to show/hide the debug controls and keyboard shortcuts
        bool showControls = true;
    
        //
        // INTERACTIVE STUFF
        //
    
        // vector to hold the unique ids for every visitor
        vector<string> visitors;
    
        void addVisitor();
        void removeVisitor();
};
