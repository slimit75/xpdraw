#ifndef XPDRAW_FONTS_H
#define XPDRAW_FONTS_H

#include <map>
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "xpdraw.h"

enum textAlignment { xpdAlignLeft, xpdAlignCenter, xpdAlignRight };

namespace xpdraw::fonts {
    struct charCache {
      xpdraw::texture bitmap;
      FT_Glyph_Metrics metrics;
      bool loaded = false;
    };

    struct face {
        FT_Face ftFace;
        std::string path;
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