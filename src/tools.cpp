#include <string>
#include <XPLMPlugin.h>
#include <XPLMUtilities.h>

#include "xpdraw/tools.h"

namespace xpdraw::tools {
    std::string findPluginPath() {
        XPLMEnableFeature("XPLM_USE_NATIVE_PATHS", 1);

        char pluginPathChar[256];
        XPLMGetPluginInfo(XPLMGetMyID(), NULL, pluginPathChar, NULL, NULL);
        std::string pluginPath = pluginPathChar;
        pluginPath.erase(pluginPath.end() - 10, pluginPath.end());

        return pluginPath;
    }

    std::string findXPlanePath() {
        XPLMEnableFeature("XPLM_USE_NATIVE_PATHS", 1);

        char xplanePath[512];
        XPLMGetSystemPath(xplanePath);
        std::string xpPath = xplanePath;
        
        return xpPath;
    }
}