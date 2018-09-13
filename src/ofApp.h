#pragma once

#include "ofMain.h"

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
    
        // use these functions to start each new video
        // we don't access the array of videos directly
        void playVideo(int n);
        void updateVideo();
        void drawVideo();
    
        // fixed ratio that we compare against to resize & scale the video
        const float hdVideoRatio = 1.777;
    
        // do we scale the video to the max size and fill the screen
        bool videoMaxScale = false;
    
        // array of all the video files
        ofVideoPlayer videos[14];
    
        // Pointer to ofVideoPlayer
        ofVideoPlayer *videoPointer;
    
};
