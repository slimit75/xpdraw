#include <XPLMDisplay.h>
#include <XPLMGraphics.h>

#if LIN or __MINGW32__
	#include <GL/gl.h>
#elif __GNUC__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

#include "xpdraw/windows.h"

using namespace xpdraw;

void Window::initWindow(int newWidth, int newHeight) {
    buffer = new unsigned char[newWidth * newHeight * 4];
    width = newWidth;
    height = newHeight;
};

void Window::createWindow(std::string title, int winLeft, int winDown) {
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
    XPLMSetWindowTitle(windowID, title.c_str());
};

void Window::setResizeLimits(int minWidth, int minHeight, int maxWidth, int maxHeight) {
    XPLMSetWindowResizingLimits(windowID, minWidth - 20, minHeight - 20, maxWidth - 20, maxHeight - 20);
};