#include <ft2build.h>
#include FT_FREETYPE_H

#include "xpdraw/fonts.h"
#include "xpdraw/xpdraw.h"

using namespace std;

int lastRight = 0;
int lastGlyphWidth = 0;
xpdraw::texture charBitmapCache[256][256];

FT_Library ft;

namespace xpdraw::fonts {
    void initFonts() {
        if (FT_Init_FreeType(&ft)) {
            throw("Error initializing FreeType library!");
        }
    }

    void cacheChar(FT_Face face, int size, char character) {
        FT_Set_Pixel_Sizes(face, 0, size * 1.5);
        FT_GlyphSlot g = face->glyph;
        FT_Load_Char(face, character, FT_LOAD_RENDER);
        charBitmapCache[size][character - '0'] = loadBuffer(g->bitmap.buffer, g->bitmap.width, g->bitmap.rows, GL_ALPHA);
    }

    void loadFont(FT_Face *font, string filename) {
        // Get file locations
        string filePath = filename;

        if(FT_New_Face(ft, filePath.c_str(), 0, font)) {
            throw("Error loading font!");
        }
    }

    void drawText(FT_Face face, string textString, float x, float y, int size, int align, xpdraw::color color = { 1, 1, 1, 1 }) {
        glColor4f(color.red, color.green, color.blue, color.alpha);

        const char* text = textString.c_str();
        FT_Set_Pixel_Sizes(face, 0, size * 1.5);
        const char *p;
        FT_GlyphSlot g = face->glyph;
        float width = 0;

        // Attempt to calculate the length of the string *without* drawing it
        for(p = text; *p; p++) {
            // Cache char data if it isn't already
            if (!charBitmapCache[size][p[0] - '0'].gl_texture) {
                cacheChar(face, size, p[0]);
            }

            // Windows is completely stupid and does NOT load the metrics when told to load METRICS ONLY!!!!!!!
            if (isspace(p[0])) {
                width = width + lastGlyphWidth + 1.3;
            }
            else {
                lastGlyphWidth = charBitmapCache[size][p[0] - '0'].width;
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
                xpdraw::texture image = charBitmapCache[size][p[0] - '0'];
                xpdraw::drawFlippedTexture(image, x, y + y_offset, image.width, image.height, color);
                lastGlyphWidth = image.width;
                lastRight = x + image.width;
                x = lastRight + 1.3;
            }
        }
    }
}