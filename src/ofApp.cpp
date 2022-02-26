#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::setup() {
    ofSetDataPathRoot("../Resources/data");
    isShowGui = true;
    
    setMonitorByIndex(appIndex);
    
    stringstream ss;
    ss << "SyphonReceiver-" << appIndex;
    ofSetWindowTitle(ss.str());
    ofSetFrameRate(60);
    
    syphonClient.setup();
    dir.setup();
    
    //register for our directory's callbacks
    ofAddListener(dir.events.serverAnnounced, this, &ofApp::serverAnnounced);
    ofAddListener(dir.events.serverRetired, this, &ofApp::serverRetired);

    dirIdx = -1;
    
    if (dir.size() >= 2) {
        dirIdx = std::min(appIndex, dir.size() - 1);
        syphonClient.set(dir.getDescription(dirIdx));
    }
    
    gui = new ofxDatGui( 100, 100 );
    resetGui();
}

void ofApp::resetGui() {
    gui->clearGui();
    
    syphonServers.clear();
    for (int i = 0; i < dir.size(); i++) {
        syphonServers.push_back(dir.getDescription(i).serverName);
    }
    
    gui->addLabel("Select Syphon video stream to display in this window:");
    syphonDropdown = gui->addDropdown("Input video stream", syphonServers);
    syphonDropdown->onDropdownEvent(this, &ofApp::onSyphonDropdownEvent);
    
    monitorDescriptions.clear();
    for (int i = 0; i < WindowManager::monitorProps.size(); i++) {
        stringstream ss;
        ss << "Display #" << i << ": " << WindowManager::monitorProps[i].width << "x" << WindowManager::monitorProps[i].height << " @ (" << WindowManager::monitorProps[i].x << ", " << WindowManager::monitorProps[i].y << ")";
        
        monitorDescriptions.push_back(ss.str());
    }
    
    gui->addLabel("Select which monitor this window should display on:");
    monitorsDropdown = gui->addDropdown("Current Monitor", monitorDescriptions);
    monitorsDropdown->onDropdownEvent(this, &ofApp::onMonitorsDropdownEvent);
    
//    fullScreenToggle = gui->addToggle("Full screen");
//    fullScreenToggle->setChecked(true);
//    fullScreenToggle->onToggleEvent(this, &ofApp::onFullScreenToggleEvent);
    
    gui->addLabel("Press 'f' to toggle fullscreen.");
    gui->addLabel("Press 'h' to hide/show this GUI.");
}

void ofApp::onFullScreenToggleEvent(ofxDatGuiToggleEvent e) {
    WindowManager::window[appIndex]->setFullscreen(e.checked);
}

void ofApp::onSyphonDropdownEvent(ofxDatGuiDropdownEvent e) {
    setSyphonServerByIndex(e.child);
}

void ofApp::onMonitorsDropdownEvent(ofxDatGuiDropdownEvent e) {
    setMonitorByIndex(e.child);
}

void ofApp::serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg) {
    for( auto& dir : arg.servers ){
        ofLogNotice("ofxSyphonServerDirectory Server Announced")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
    }
        
    
    dirIdx = std::min(appIndex, dir.size() - 1);
    syphonClient.set(dir.getDescription(dirIdx));
    
    resetGui();
}

void ofApp::serverRetired(ofxSyphonServerDirectoryEventArgs &arg) {
    for( auto& dir : arg.servers ){
        ofLogNotice("ofxSyphonServerDirectory Server Updated")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
    }
    
    dirIdx = std::min(appIndex, dir.size() - 1);
    if (dirIdx >= 0)
        syphonClient.set(dir.getDescription(dirIdx));
    
    resetGui();
}

void ofApp::setSyphonServerByIndex(int idx) {
    if (dir.size() > 0)
    {
        dirIdx = idx;
        if(dirIdx > dir.size() - 1)
            dirIdx = 0;

        syphonClient.set(dir.getDescription(dirIdx));
        string serverName = syphonClient.getServerName();
        string appName = syphonClient.getApplicationName();

        if(serverName == ""){
            serverName = "null";
        }
        if(appName == ""){
            appName = "null";
        }
//        ofSetWindowTitle(serverName + ":" + appName);
    }
    else
    {
//        ofSetWindowTitle("No Server");
    }

}

void ofApp::setMonitorByIndex(int index) {
    int monitorIndex = std::min(index, (int)(WindowManager::monitorProps.size() - 1));
    if (monitorIndex < 0) return;
    
    WindowManager::windowSettings[appIndex].setSize(WindowManager::monitorProps[monitorIndex].width, WindowManager::monitorProps[monitorIndex].height);
    WindowManager::window[appIndex]->setWindowShape(WindowManager::monitorProps[monitorIndex].width, WindowManager::monitorProps[monitorIndex].height);
    WindowManager::window[appIndex]->setWindowPosition(WindowManager::monitorProps[monitorIndex].x, WindowManager::monitorProps[monitorIndex].y);
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    ofColor(255, 255, 255, 255);
    ofEnableAlphaBlending();
    
    
    syphonClient.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == 'h') {
        isShowGui = !isShowGui;
        gui->setVisible(isShowGui);
        gui->setEnabled(isShowGui);
        
        if (!isShowGui) ofHideCursor();
        else ofShowCursor();
    } else if (key == 'f') {
        WindowManager::window[appIndex]->toggleFullscreen();
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
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
