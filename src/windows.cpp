#include "xpdraw/windows.h"
#include <XPLMDisplay.h>

void xpd_win_new(xpd_win_t* inWindow, int width, int height) {
	inWindow->width = width;
	inWindow->height = height;
	inWindow->buffer = new unsigned char[width * height * 4];
}

void xpd_win_set_cb(xpd_win_t* inWindow, XPLMHandleMouseClick_f mouseHandler, XPLMDrawWindow_f drawHandler, XPLMHandleMouseWheel_f mouseWheelHandler, XPLMHandleKey_f keyHandler, XPLMHandleCursor_f cursorHandler) {
	inWindow->drawFunc = drawHandler;
	inWindow->mouseFunc = mouseHandler;
	inWindow->wheelFunc = mouseWheelHandler;
	inWindow->keyFunc = keyHandler;
	inWindow->cursorFunc = cursorHandler;
}

void xpd_win_create(xpd_win_t* inWindow, const char *title, int winLeft, int winDown) {
	inWindow->params.structSize = sizeof(inWindow->params);
	inWindow->params.visible = 1;
	inWindow->params.drawWindowFunc = inWindow->drawFunc;
	inWindow->params.handleMouseClickFunc = inWindow->mouseFunc;
	inWindow->params.handleRightClickFunc = inWindow->mouseFunc;
	inWindow->params.handleMouseWheelFunc = inWindow->wheelFunc;
	inWindow->params.handleKeyFunc = inWindow->keyFunc;
	inWindow->params.handleCursorFunc = inWindow->cursorFunc;
	inWindow->params.refcon = nullptr;
	inWindow->params.layer = xplm_WindowLayerFloatingWindows;
	inWindow->params.decorateAsFloatingWindow = xplm_WindowDecorationRoundRectangle;

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

void xpd_win_resize_lims(xpd_win_t* inWindow, int minWidth, int minHeight, int maxWidth, int maxHeight) {
	XPLMSetWindowResizingLimits(inWindow->windowID, minWidth - 20, minHeight - 20, maxWidth - 20, maxHeight - 20);
}