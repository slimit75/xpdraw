/*
 * windows.h - X-Plane window handler
 * Copyright 2023 Ian Ward
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/
#ifndef XPDRAW_WINDOWS_H
#define XPDRAW_WINDOWS_H

#include <XPLMDisplay.h>

typedef struct xpd_win {
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
} xpd_win_t;

/**
 * @brief Create a new window
 *
 * @param inWindow Window to create
 * @param width Width of the window's framebuffer
 * @param height Height of the window's framebuffer
 */
void xpd_win_new(xpd_win_t* inWindow, int width, int height);

/**
 * @brief Define callbacks for a window
 *
 * @param inWindow Window to update
 * @param mouseHandler Mouse click handler
 * @param drawHandler Render function
 * @param mouseWheelHandler Mouse wheel handler
 * @param keyHandler Keyboard handler
 * @param cursorHandler Cursor handler (render your own cursor?)
 */
void xpd_win_set_cb(xpd_win_t* inWindow, XPLMHandleMouseClick_f mouseHandler, XPLMDrawWindow_f drawHandler, XPLMHandleMouseWheel_f mouseWheelHandler, XPLMHandleKey_f keyHandler, XPLMHandleCursor_f cursorHandler);

/**
 * @brief Display a window created with xpd_win_new
 *
 * @param inWindow Window to start rendering
 * @param title Title of the window
 * @param winLeft Position of the left edge of the window
 * @param winDown Position of the bottom edge of the window
 */
void xpd_win_create(xpd_win_t* inWindow, const char* title, int winLeft = 50, int winDown = 150);

/**
 * @brief Set the minimum & maximum sizes of a window
 *
 * @param inWindow Window to update
 * @param minWidth New minimum width of the window
 * @param minHeight New minimum height of the window
 * @param maxWidth New maximum width of the window
 * @param maxHeight New maximum height of the window
 */
void xpd_win_resize_lims(xpd_win_t* inWindow, int minWidth, int minHeight, int maxWidth, int maxHeight);

#endif