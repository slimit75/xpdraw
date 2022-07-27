#pragma once

#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "xpdraw.h"

namespace xpdraw::fonts {
    struct font {
        FT_Face face;
        texture texCache[256][256];
    };

    void initFonts();
    void loadFont(FT_Face *font, std::string filename);
    void drawText(FT_Face face, std::string textString, float x, float y, int size, int align, xpdraw::color color);
}