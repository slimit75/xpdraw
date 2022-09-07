#ifndef XPDRAW_TOOLS_H
#define XPDRAW_TOOLS_H

#include <string>
#include "xpdraw.h"

#define XPOLD 10; // Represents X-Plane 10 and below.
#define XP11 11;
#define XP12 12;

namespace xpdraw::tools {
    /**
     * @brief Returns the plugin's current path. Forces XPLM_USE_NATIVE_PATHS to true!
     * 
     * @return std::string 
     */
    std::string findPluginPath();

    /**
     * @brief Returns the X-Plane instance's path. Forces XPLM_USE_NATIVE_PATHS to true!
     * 
     * @return std::string 
     */
    std::string findXPlanePath();

    /**
     * @brief Returns what major X-Plane version is running
     * 
     * @return Can either return XPOLD (XP10 and below), XP11 or XP12
     */
    int getXPlaneVersion();
}

#endif