#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"
#include "ofxDatGui.h"
#include "WindowManager.h"

class ofApp : public ofBaseApp{

	public:
        ofApp(int _appIndex) : ofBaseApp() {
            appIndex = _appIndex;
        };
        int appIndex;
    
        ofxSyphonClient syphonClient;
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
    
        void serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg);
        void serverUpdated(ofxSyphonServerDirectoryEventArgs &args);
        void serverRetired(ofxSyphonServerDirectoryEventArgs &arg);

        ofxSyphonServerDirectory dir;
        vector<string> syphonServers;
        int dirIdx;
        void setSyphonServerByIndex(int idx);
            
        vector<string> monitorDescriptions;
        void setMonitorByIndex(int index);
    
        vector<ofxSyphonServerDescription> getSortedServers(vector<ofxSyphonServerDescription> servers);
    
        void resetGui();
        ofxDatGui *gui;
        ofxDatGuiDropdown* syphonDropdown;
        ofxDatGuiDropdown* monitorsDropdown;
        ofxDatGuiToggle* fullScreenToggle;
    
        bool isFullScreen;
        bool isShowGui;
    
        void onSyphonDropdownEvent(ofxDatGuiDropdownEvent e);
        void onMonitorsDropdownEvent(ofxDatGuiDropdownEvent e);
        void onFullScreenToggleEvent(ofxDatGuiToggleEvent e);
		
};
