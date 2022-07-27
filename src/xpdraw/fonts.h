#pragma once

#include <string>
#include <vector>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "xpdraw.h"

namespace xpdraw {
    class Font {
        public:
            void load(std::string filename);
            texture getTexture(int size, char letter);
            FT_Face face;
            FT_Glyph_Metrics metrics;
            void cacheChar(int size, char letter);
            std::vector<std::vector<texture>> cache;
    };
}

namespace xpdraw::fonts {
    void initFonts();
    void drawText(Font font, std::string textString, float x, float y, int size, int align, color color = { 1, 1, 1, 1 });
}