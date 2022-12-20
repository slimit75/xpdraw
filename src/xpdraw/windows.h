#ifndef XPDRAW_WINDOWS_H
#define XPDRAW_WINDOWS_H

#include <XPLMDisplay.h>
#include <string>

namespace xpdraw::windows {
    struct window {
        XPLMCreateWindow_t params;
        XPLMWindowID windowID;
        int texNum;
        unsigned char* buffer;
        int width;
        int height;
    };

    // TODO: Documentation
    void newWindow(window* inWindow, int width, int height);
    void setCallbacks(window* inWindow, XPLMHandleMouseClick_f mouseHandler, XPLMDrawWindow_f drawHandler, XPLMHandleMouseWheel_f mouseWheelHandler, XPLMHandleKey_f keyHandler, XPLMHandleCursor_f cursorHandler);
    void createWindow(window* inWindow, std::string title, int winLeft = 50, int winDown = 150);
    void setResizeLimits(window* inWindow, int minWidth, int minHeight, int maxWidth, int maxHeight);
}

#endif