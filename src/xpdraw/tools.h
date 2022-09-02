#ifndef XPDRAW_TOOLS_H
#define XPDRAW_TOOLS_H

#include <string>
#include "xpdraw.h"

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
}

#endif