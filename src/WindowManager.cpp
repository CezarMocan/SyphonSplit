//
//  WindowManager.cpp
//  EITSOG-SyphonClient
//
//  Created by Cezar Mocan on 1/20/22.
//

#include <stdio.h>
#include "WindowManager.h"

ofGLFWWindowSettings WindowManager::windowSettings[MAX_WINDOWS];
shared_ptr<ofAppBaseWindow> WindowManager::window[MAX_WINDOWS];

int WindowManager::monitorCount;
GLFWmonitor** WindowManager::monitors;

vector<MonitorProps> WindowManager::monitorProps;
