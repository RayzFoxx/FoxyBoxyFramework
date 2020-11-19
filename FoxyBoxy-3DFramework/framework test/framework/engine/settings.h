#ifndef _SETTINGS_H_
#define  _SETTINGS_H_

// window size
float SCR_WIDTH = 640;
float SCR_HEIGHT = 480;

float fov = 90.0;
float deltaTime = 0.0;
static float oldTime = 0.0;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

char windowName[] = "FoxyBoxy-GLframework";

#endif //  _SETTINGS_H_
