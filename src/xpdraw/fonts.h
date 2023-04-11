/*
 * fonts.h - Font handler & renderer
 * Copyright 2022 Ian Ward
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
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#ifndef XPDRAW_FONTS_H
#define XPDRAW_FONTS_H

#include "xpdraw.h"
#include <map>
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H

enum textAlignment { xpdAlignLeft, xpdAlignCenter, xpdAlignRight };

namespace xpdraw::fonts {
    struct charCache {
      xpdraw::texture bitmap;
      FT_Glyph_Metrics metrics;
      bool loaded = false;
    };

    struct face {
        FT_Face ftFace;
        const char* path;
        std::map<int, std::map<char, charCache>> cache;
    };

    /**
     * @brief Load a new font
     *
     * @param font Pointer to the font we are loading
     * @param filename File path to load from
     */
    void loadFont(face* font, std::string filename);

    /**
     * @brief Returns the length of a string.
     *
     * @param font Font to use
     * @param text Text to get the length of
     * @param size Size of the font to use
     * @return int
     */
    int getLength(face* font, std::string text, const int size);

    /**
     * @brief Function to draw text
     * 
     * @param font Current font in use
     * @param text Text to render
     * @param x Lateral position to draw at relative to anchor
     * @param y Vertical position to draw at relative to anchor
     * @param size Size of font face to use
     * @param align Alignment of the text relative to x
     * @param color Color of the text; defaults to white
     */
    void drawText(face* font, std::string text, int x, int y, int size, textAlignment align, color color = XPD_COLOR_WHITE);
}

#endif
#pragma clang diagnostic pop