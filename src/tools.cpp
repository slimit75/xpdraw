#include "xpdraw/tools.h"
#include <XPLMUtilities.h>
#include <XPLMPlugin.h>

int xpVersion = -1;
char xpPath[512];
char pluginPath[512];

char *xpd_tools_plugin_fp() {
	XPLMEnableFeature("XPLM_USE_NATIVE_PATHS", 1);

	if (strlen(pluginPath) == 0) {
		XPLMGetPluginInfo(XPLMGetMyID(), nullptr, pluginPath, nullptr, nullptr);
		std::string pluginPathTemp = pluginPath;
		pluginPathTemp.erase(pluginPathTemp.end() - 10, pluginPathTemp.end());
		strcpy(pluginPath, pluginPathTemp.c_str());
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
		XPLMGetVersions(&xpVersion, nullptr, nullptr);
		xpVersion = xpVersion / 1000;
	}
	return xpVersion;
}
