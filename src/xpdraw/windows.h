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
} xpd_win_t;

// TODO: Documentation
void xpd_win_new(xpd_win_t* inWindow, int width, int height);
void xpd_win_set_cb(xpd_win_t* inWindow, XPLMHandleMouseClick_f mouseHandler, XPLMDrawWindow_f drawHandler, XPLMHandleMouseWheel_f mouseWheelHandler, XPLMHandleKey_f keyHandler, XPLMHandleCursor_f cursorHandler);
void xpd_win_create(xpd_win_t* inWindow, const char* title, int winLeft = 50, int winDown = 150);
void xpd_win_resize_lims(xpd_win_t* inWindow, int minWidth, int minHeight, int maxWidth, int maxHeight);

#endif