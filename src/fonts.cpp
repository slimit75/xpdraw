#include <ft2build.h>
#include FT_FREETYPE_H

#include "xpdraw/fonts.h"
#include "xpdraw/xpdraw.h"

int lastRight = 0;
int lastGlyphWidth = 0;

struct faceCache {
    xpdraw::texture bitmap;
    FT_Glyph_Metrics metrics;
    bool loaded = false;
};

FT_Library ft;
std::map<std::string, std::map<int, std::map<char, faceCache>>> cache;

namespace xpdraw::fonts {
    void Face::init(std::string filename) {
        FT_New_Face(ft, filename.c_str(), 0, &ftFace);
        path = filename;
    }

    void Face::add(int size, char letter) {
        if (cache[path][size][letter].loaded == false) {
            FT_Set_Pixel_Sizes(ftFace, 0, size * 1.5);
            FT_Load_Char(ftFace, letter, FT_LOAD_RENDER);

            cache[path][size][letter].bitmap = loadBuffer(ftFace->glyph->bitmap.buffer, ftFace->glyph->bitmap.width, ftFace->glyph->bitmap.rows, GL_ALPHA);
            cache[path][size][letter].metrics = ftFace->glyph->metrics;
            cache[path][size][letter].loaded = true;
        }
    }

    FT_Glyph_Metrics Face::getMetrics(int size, char letter) {
        return cache[path][size][letter].metrics;
    }

    texture Face::getTexture(int size, char letter) {
        return cache[path][size][letter].bitmap;
    }

    void initFonts() {
        FT_Init_FreeType(&ft);
    }

    void drawText(Face font, std::string text, int x, int y, int size, int align, xpdraw::color textColor) {
        glColor4f(textColor.red, textColor.green, textColor.blue, textColor.alpha);

        int width = 0;
        int charSpacing = 0;

        // Calculate the length of the string before drawing it
        for(const char *p = text.c_str(); *p; p++) {
            font.add(size, p[0]); // Automatically cache char if it isn't already cached

            width += (font.getMetrics(size, p[0]).horiAdvance) / 64;
        }

        if (align == ALIGN_CENTER) {
            x -= (width / 2);
        }
        else if (align == ALIGN_RIGHT) {
            x -= width;
        }

        // Render text using cached data
        for(const char *p = text.c_str(); *p; p++) {
            int y_offset = (((font.getMetrics(size, p[0]).horiBearingY) / 64) - (font.getMetrics(size, p[0]).height) / 64);
            texture image = font.getTexture(size, p[0]);
            drawFlippedTexture(image, x + ((font.getMetrics(size, p[0]).horiBearingX) / 64), y + y_offset, image.width, image.height, textColor);
            x += ((font.getMetrics(size, p[0]).horiAdvance) / 64);
        }
    }
}