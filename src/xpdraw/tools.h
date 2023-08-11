/*
 * tools.h - Minor tools/functions
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
#ifndef XPDRAW_TOOLS_H
#define XPDRAW_TOOLS_H

#include <string>
#include <cstring>
#include "xpdraw.h"

namespace xpdraw::tools {
	/**
	 * @brief Concentrate two C strings into one
	 *
	 * @param str1
	 * @param str2
	 * @return char*
	 */
	static char* constr(const char *str1, const char *str2) {
		char str3[256];
		strcpy(str3, str1);
		return strncat(str3, str2, sizeof(str3) - strlen(str3) - 1);
	}

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
	 * @return int
	 */
	int getXPlaneVersion();
}

#endif