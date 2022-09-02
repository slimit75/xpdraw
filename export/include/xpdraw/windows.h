#ifndef XPDRAW_WINDOWS_H
#define XPDRAW_WINDOWS_H

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

            /**
             * @brief Draw function that is called to render the window. Define this!!!
             * 
             */
            XPLMDrawWindow_f drawFunc;

            /**
             * @brief Function to handle mouse clicks; if you need this, make sure to define it
             * 
             */
            XPLMHandleMouseClick_f mouseFunc;

            /**
             * @brief Function to handle scroll wheels; if you need this, make sure to define it
             * 
             */
            XPLMHandleMouseWheel_f wheelFunc;

            /**
             * @brief Function to handle key presses; if you need this, make sure to define it
             * 
             */
            XPLMHandleKey_f keyFunc;

            /**
             * @brief Function to handle mouse cursors; if you need this, make sure to define it
             * 
             */
            XPLMHandleCursor_f cursorFunc;

            /**
             * @brief Creates a new window with the specified width and height
             * 
             * @param newWidth Width of new window
             * @param newHeight Height of new window
             */
            void initWindow(int newWidth, int newHeight);

            /**
             * @brief Starts drawing a window with the specified title.
             * 
             * @param title Title of window
             * @param winLeft X location of window relative to X-Plane window; defaults to 50
             * @param winDown Y location of window relative to X-PLane window; defaults to 150
             */
            void createWindow(std::string title, int winLeft = 50, int winDown = 150);

            /**
             * @brief Define resize limits for the newly created window
             * 
             * @param minWidth Minimum width of window
             * @param minHeight Minimum height of window
             * @param maxWidth Maximum width of window
             * @param maxHeight Maximum height of window
             */
            void setResizeLimits(int minWidth, int minHeight, int maxWidth, int maxHeight);
    };
}

#endif