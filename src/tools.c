#include "xpdraw/tools.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <XPLMPlugin.h>
#include <XPLMUtilities.h>

int xpVersion = -1;
char xpPath[512];
char pluginPath[512];
char str3[512];

char *xpd_tools_constr(const char *str1, const char *str2) {
	strcpy(str3, str1);
	strncat(str3, str2, sizeof(str3) - strlen(str3) - 1);
	return str3;
}

char *xpd_tools_plugin_fp() {
	XPLMEnableFeature("XPLM_USE_NATIVE_PATHS", 1);

	if (strlen(pluginPath) == 0) {
		XPLMGetPluginInfo(XPLMGetMyID(), NULL, pluginPath, NULL, NULL);
		pluginPath[strlen(pluginPath) - 10] = '\0';
	}

	return pluginPath;
}

char *xpd_tools_xp_fp() {
	XPLMEnableFeature("XPLM_USE_NATIVE_PATHS", 1);

	if (strlen(xpPath) == 0) {
		XPLMGetSystemPath(xpPath);
	}

	return xpPath;
}

int xpd_tools_xp_ver() {
	if (xpVersion == -1) {
		XPLMGetVersions(&xpVersion, NULL, NULL);
		xpVersion = xpVersion / 1000;
	}
	return xpVersion;
}

void xpd_assert(int exp, char *msg) {
	if (!exp) {
		char str[256];
		sprintf(str, "xpdraw: %s \n", msg);
		XPLMDebugString(str);
		abort();
	}
}
