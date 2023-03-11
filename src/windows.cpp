#include <XPLMDisplay.h>

#include "xpdraw/windows.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
namespace xpdraw::windows {
    void newWindow(window* inWindow, int width, int height) {
        inWindow->width = width;
        inWindow->height = height;
        inWindow->buffer = new unsigned char[width * height * 4];

        inWindow->params.structSize = sizeof(inWindow->params);
        inWindow->params.visible = 1;
        inWindow->params.refcon = nullptr;
        inWindow->params.layer = xplm_WindowLayerFloatingWindows;
        inWindow->params.decorateAsFloatingWindow = xplm_WindowDecorationRoundRectangle;
    }

    void setCallbacks(window* inWindow, XPLMHandleMouseClick_f mouseHandler, XPLMDrawWindow_f drawHandler, XPLMHandleMouseWheel_f mouseWheelHandler, XPLMHandleKey_f keyHandler, XPLMHandleCursor_f cursorHandler) {
      inWindow->params.drawWindowFunc = drawHandler;
      inWindow->params.handleMouseClickFunc = mouseHandler;
      inWindow->params.handleRightClickFunc = mouseHandler;
      inWindow->params.handleMouseWheelFunc = mouseWheelHandler;
      inWindow->params.handleKeyFunc = keyHandler;
      inWindow->params.handleCursorFunc = cursorHandler;
    }

    void createWindow(window* inWindow, const char *title, int winLeft, int winDown) {
        int left, bottom, right, top;
        XPLMGetScreenBoundsGlobal(&left, &top, &right, &bottom);
        inWindow->params.left = left + winLeft;
        inWindow->params.bottom = bottom + winDown;
        inWindow->params.right = inWindow->params.left + inWindow->width - 20;
        inWindow->params.top = inWindow->params.bottom + inWindow->height - 20;
        inWindow->windowID = XPLMCreateWindowEx(&inWindow->params);
        
        XPLMSetWindowPositioningMode(inWindow->windowID, xplm_WindowPositionFree, -1);
        XPLMSetWindowTitle(inWindow->windowID, title);
    }

    void setResizeLimits(window* inWindow, int minWidth, int minHeight, int maxWidth, int maxHeight) {
        XPLMSetWindowResizingLimits(inWindow->windowID, minWidth - 20, minHeight - 20, maxWidth - 20, maxHeight - 20);
    }
}
#pragma clang diagnostic pop