#pragma once

#include <XPLMDisplay.h>
#include <string>

namespace xpdraw {
    class Window {
        public:
            XPLMCreateWindow_t params;
            XPLMWindowID windowID;
            int texNum;
            unsigned char* buffer;
            int width;
            int height;

            XPLMDrawWindow_f drawFunc;
            XPLMHandleMouseClick_f mouseFunc;
            XPLMHandleMouseWheel_f wheelFunc;
            XPLMHandleKey_f keyFunc;
            XPLMHandleCursor_f cursorFunc;

            void initWindow(int newWidth, int newHeight);
            void setDrawFunc(XPLMDrawWindow_f newDrawFunc);
            void createWindow(std::string title, int winLeft = 50, int winDown = 150);
            void setResizeLimits(int minWidth, int minHeight, int maxWidth, int maxHeight);
    };
}