#include <ft2build.h>
#include FT_FREETYPE_H

#include "xpdraw/fonts.h"
#include "xpdraw/xpdraw.h"

using namespace std;

int lastRight = 0;
int lastGlyphWidth = 0;

FT_Library ft;

struct faceCache {
    xpdraw::texture bitmap;
    FT_Glyph_Metrics metrics;
    bool loaded = false;
};

std::map<std::string, std::map<int, std::map<char, faceCache>>> cache;

namespace xpdraw::fonts {
    void Face::init(string filename) {
        FT_New_Face(ft, filename.c_str(), 0, &ftFace);
        path = filename;
    };

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
    };

    texture Face::getTexture(int size, char letter) {
        return cache[path][size][letter].bitmap;
    }

    void initFonts() {
        FT_Init_FreeType(&ft);
    }

    void drawText(Face font, string text, int x, int y, int size, int align, xpdraw::color textColor) {
        glColor4f(textColor.red, textColor.green, textColor.blue, textColor.alpha);

        /*
        int width = 0;

        // Attempt to calculate the length of the string *without* drawing it
        for(const char *p = text.c_str(); *p; p++) {
            // Cache char data if it isn't already.
            // font.add should automatically skip caching a letter if it already exists
            font.add(size, p[0]);

            width += font.getMetrics(size, p[0]).width;
        }

        if (align == ALIGN_CENTER) {
            x -= (width / 2);
        }
        else if (align == ALIGN_RIGHT) {
            x -= width;
        }

        // Render text using cached data
        for(const char *p = text.c_str(); *p; p++) {
            texture image = font.getTexture(size, p[0]);
            drawFlippedTexture(image, x, y, image.width, image.height, textColor);
            x += image.width;
        }
        */
    }
}