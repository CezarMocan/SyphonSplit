//
//  WindowManager.h
//  EITSOG-SyphonClient
//
//  Created by Cezar Mocan on 1/20/22.
//

#ifndef WindowManager_h
#define WindowManager_h

#include "ofMain.h"
#include "ofAppGLFWWindow.h"
#include "GLFW/glfw3.h"

#define MAX_WINDOWS 5

using namespace std;

struct MonitorProps {
    int x, y, width, height;
};


class WindowManager {
public:
    static ofGLFWWindowSettings windowSettings[MAX_WINDOWS];
    static shared_ptr<ofAppBaseWindow> window[MAX_WINDOWS];
    
    
    static int monitorCount;
    static GLFWmonitor** monitors;
    
    static vector<MonitorProps> monitorProps;
};

#endif /* WindowManager_h */
