#include "xpdraw/tools.h"

#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <XPLMPlugin.h>
#include <XPLMUtilities.h>

int xp_ver = -1;
char xp_path[512];
char *plugin_path;
char str3[512];

char *xpd_tools_constr(const char *str1, const char *str2) {
	strcpy(str3, str1);
	strncat(str3, str2, sizeof(str3) - strlen(str3) - 1);
	return str3;
}

char *xpd_tools_plugin_fp() {
	XPLMEnableFeature("XPLM_USE_NATIVE_PATHS", 1);

	if (!plugin_path) {
		plugin_path = malloc(sizeof(char) * 512);
		XPLMGetPluginInfo(XPLMGetMyID(), nullptr, plugin_path, nullptr, nullptr);
		strcpy(plugin_path, dirname(dirname(plugin_path)));
		strncat(plugin_path, "/", sizeof(plugin_path) - strlen(plugin_path) - 1);
	}

	return plugin_path;
}

char *xpd_tools_xp_fp() {
	XPLMEnableFeature("XPLM_USE_NATIVE_PATHS", 1);

	if (strlen(xp_path) == 0) {
		XPLMGetSystemPath(xp_path);
	}

	return xp_path;
}

int xpd_tools_xp_ver() {
	if (xp_ver == -1) {
		XPLMGetVersions(&xp_ver, nullptr, nullptr);
		xp_ver = xp_ver / 1000;
	}
	return xp_ver;
}

void xpd_assert(int exp, char *msg) {
	if (!exp) {
		char str[256];
		sprintf(str, "xpdraw: %s \n", msg);
		XPLMDebugString(str);
		assert(exp);
	}
}
