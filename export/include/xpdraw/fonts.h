#pragma once

#include <string>
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "xpdraw.h"

#define ALIGN_LEFT 1
#define ALIGN_CENTER 2
#define ALIGN_RIGHT 3

namespace xpdraw::fonts {
    class Face {
        public:
            FT_Face ftFace;
            std::string path;
            void init(std::string filename);
            void add(int size, char letter);
            FT_Glyph_Metrics getMetrics(int size, char letter);
            texture getTexture(int size, char letter);
    };

    void initFonts();
    void drawText(Face font, std::string text, int x, int y, int size, int align, color color = { 1, 1, 1, 1 });
}