#include "xpdraw/tools.h"
#include <XPLMUtilities.h>
#include <XPLMPlugin.h>

int xpVersion = -1;

std::string xpd_tools_plugin_fp() {
	XPLMEnableFeature("XPLM_USE_NATIVE_PATHS", 1);

	char pluginPathChar[256];
	XPLMGetPluginInfo(XPLMGetMyID(), nullptr, pluginPathChar, nullptr, nullptr);
	std::string pluginPath = pluginPathChar;
	pluginPath.erase(pluginPath.end() - 10, pluginPath.end());

	return pluginPath;
}

std::string xpd_tools_xp_fp() {
	XPLMEnableFeature("XPLM_USE_NATIVE_PATHS", 1);

	char xplanePath[512];
	XPLMGetSystemPath(xplanePath);
	std::string xpPath = xplanePath;

	return xpPath;
}

int xpd_tools_xp_ver() {
	if (xpVersion == -1) {
		XPLMGetVersions(&xpVersion, nullptr, nullptr);
		xpVersion = xpVersion / 1000;
	}
	return xpVersion;
}