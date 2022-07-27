#include <XPLMDisplay.h>
#include <XPLMGraphics.h>
#include <GL/gl.h>
#include "xpdraw/windows.h"

using namespace xpdraw::windows;

void Window::initWindow(int newWidth, int newHeight) {
    buffer = new unsigned char[newWidth * newHeight * 4];
    width = newWidth;
    height = newHeight;
};

void Window::createWindow(std::string title, int winLeft, int winDown, int minScale, int maxScale) {
    params.structSize = sizeof(params);
    params.visible = 1;
    params.drawWindowFunc = drawFunc;
    params.handleMouseClickFunc = mouseFunc;
    params.handleRightClickFunc = mouseFunc;
    params.handleMouseWheelFunc = wheelFunc;
    params.handleKeyFunc = keyFunc;
    params.handleCursorFunc = cursorFunc;
    params.refcon = NULL;
    params.layer = xplm_WindowLayerFloatingWindows;
    params.decorateAsFloatingWindow = xplm_WindowDecorationRoundRectangle;

    int left, bottom, right, top;
    XPLMGetScreenBoundsGlobal(&left, &top, &right, &bottom);
    params.left = left + winLeft;
    params.bottom = bottom + winDown;
    params.right = params.left + width - 20;
    params.top = params.bottom + height - 20;
    
    windowID = XPLMCreateWindowEx(&params);
    
    XPLMSetWindowPositioningMode(windowID, xplm_WindowPositionFree, -1);
    XPLMSetWindowResizingLimits(windowID, (width * minScale) - 20, (height * minScale) - 20, (width * minScale) - 20, (height * minScale) - 20);
    XPLMSetWindowTitle(windowID, "MD302 Left Display");
};