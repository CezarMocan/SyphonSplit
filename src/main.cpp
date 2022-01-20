#include "ofMain.h"
#include "ofApp.h"
#include "WindowManager.h"

//========================================================================
int main( ){
    
    // Setting up 2 app windows
    for (int i = 0; i < 2; i++) {
        WindowManager::windowSettings[i].multiMonitorFullScreen = false;
        WindowManager::windowSettings[i].setGLVersion(3, 2);
        WindowManager::windowSettings[i].windowMode = OF_FULLSCREEN;
        if (i == 1) {
            WindowManager::windowSettings[i].shareContextWith = WindowManager::window[0];
        }

        WindowManager::window[i] = ofCreateWindow(WindowManager::windowSettings[i]);
    }

    // Getting positions and dimensions for all connected monitors
    WindowManager::monitors = glfwGetMonitors(&WindowManager::monitorCount);
    
    for (int i = 0; i < WindowManager::monitorCount; i++) {
        int xM, yM;
        glfwGetMonitorPos(WindowManager::monitors[i], &xM, &yM);
        const GLFWvidmode* desktopMode = glfwGetVideoMode(WindowManager::monitors[i]);
        WindowManager::monitorProps.push_back(MonitorProps{ xM, yM, desktopMode->width, desktopMode->height });
    }

    /*
    int xM1; int yM1;
    glfwGetMonitorPos(WindowManager::monitors[0], &xM1, &yM1); // We take the second monitor
    WindowManager::desktopMode1 = glfwGetVideoMode(WindowManager::monitors[0]);

    WindowManager::windowSettings1.setSize(WindowManager::desktopMode1->width, WindowManager::desktopMode1->height);
    WindowManager::window1->setWindowShape(WindowManager::desktopMode1->width, WindowManager::desktopMode1->height);
    WindowManager::window1->setWindowPosition(xM1, yM1);

    int xM2; int yM2;
    glfwGetMonitorPos(WindowManager::monitors[1], &xM2, &yM2); // We take the second monitor
    WindowManager::desktopMode2 = glfwGetVideoMode(WindowManager::monitors[1]);

    WindowManager::windowSettings2.setSize(WindowManager::desktopMode2->width, WindowManager::desktopMode2->height);
    WindowManager::window2->setWindowShape(WindowManager::desktopMode2->width, WindowManager::desktopMode2->height);
    WindowManager::window2->setWindowPosition(xM2, yM2);
     */
    
    cout << "Monitor count: " << WindowManager::monitorCount << endl;
    
    // Running two different instances of the app, for the two windows
    for (int i = 0; i < 2; i++) {
        shared_ptr<ofApp> mainApp(new ofApp(i));
        ofRunApp(WindowManager::window[i], mainApp);
    }
    ofRunMainLoop();
}
