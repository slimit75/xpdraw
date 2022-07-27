#include <ft2build.h>
#include FT_FREETYPE_H

#include "xpdraw/fonts.h"
#include "xpdraw/xpdraw.h"

using namespace std;

int lastRight = 0;
int lastGlyphWidth = 0;

FT_Library ft;

namespace xpdraw {
    void Font::load(string filename) {
        if(FT_New_Face(ft, filename.c_str(), 0, &face)) {
            throw("Error loading font!");
        }
    };

    void Font::cacheChar(int size, char letter) {
        FT_Set_Pixel_Sizes(face, 0, size);
        FT_GlyphSlot g = face->glyph;
        FT_Load_Char(face, letter, FT_LOAD_RENDER);

        vector<texture> temp = cache[size];
        temp.assign(letter - '0', loadBuffer(face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows, GL_ALPHA));
        cache.assign(size, temp);
    }
}

namespace xpdraw::fonts {
    void initFonts() {
        if (FT_Init_FreeType(&ft)) {
            throw("Error initializing FreeType library!");
        }
    }

    void drawText(xpdraw::Font font, string textString, float x, float y, int size, int align, xpdraw::color textColor) {
        /*
        glColor4f(textColor.red, textColor.green, textColor.blue, textColor.alpha);

        const char* text = textString.c_str();
        FT_Set_Pixel_Sizes(font.face, 0, size * 1.5);
        const char *p;
        FT_GlyphSlot g = font.face->glyph;
        float width = 0;

        // Attempt to calculate the length of the string *without* drawing it
        for(p = text; *p; p++) {
            // Cache char data if it isn't already
            if (!font.cache[size][p[0] - '0'].gl_texture) {
                font.cacheChar(size, p[0]);
            }

            if (isspace(p[0])) {
                width = width + lastGlyphWidth + 1.3;
            }
            else {
                lastGlyphWidth = font.cache[size][p[0] - '0'].width;
                width = width + lastGlyphWidth + 1.3;
            }
        }
        width = width - 1.3;

        if (align == ALIGN_CENTER) {
            x = x - (width / 2);
        }
        else if (align == ALIGN_RIGHT) {
            x = x - width;
        }

        // Render text using cached data
        for(p = text; *p; p++) {
            int y_offset;
            if (p[0] == 'Q') {
                y_offset = size / -6.5;
            }
            else if (p[0] == '-') {
                y_offset = size / 3;
            }
            else if (p[0] == '.') {
                x += 3;
                width += 6;
            }
            else {
                y_offset = 0;
            }

            if (isspace(p[0])) {
                x = lastRight + lastGlyphWidth + 2.6;
            }
            else {
                texture image = font.cache[size][p[0] - '0'];
                drawFlippedTexture(image, x, y + y_offset, image.width, image.height, textColor);
                lastGlyphWidth = image.width;
                lastRight = x + image.width;
                x = lastRight + 1.3;
            }
        }
        */
    }
}