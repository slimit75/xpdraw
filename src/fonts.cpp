#include "xpdraw/fonts.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

bool fontsInit = false;
FT_Library ft;

namespace xpdraw::fonts {
    void loadFont(face* font, const char* filename) {
        if (!fontsInit) {
            FT_Init_FreeType(&ft);
            fontsInit = true;
        }

        FT_New_Face(ft, filename, 0, &font->ftFace);
        font->path = filename;
    }

    void addToCache(face* font, int size, char letter) {
        if (!font->cache[size][letter].loaded) {
            FT_Set_Pixel_Sizes(font->ftFace, 0, size * 1.5);
            FT_Load_Char(font->ftFace, letter, FT_LOAD_RENDER);

            loadBuffer(&font->cache[size][letter].bitmap, font->ftFace->glyph->bitmap.buffer, font->ftFace->glyph->bitmap.width, font->ftFace->glyph->bitmap.rows, GL_ALPHA);
            font->cache[size][letter].metrics = font->ftFace->glyph->metrics;
            font->cache[size][letter].loaded = true;
        }
    }

    inline FT_Glyph_Metrics getMetrics(face* font, int size, char letter) {
        addToCache(font, size, letter); // Automatically cache char if it isn't already cached

        return font->cache[size][letter].metrics;
    }

    inline texture* getCharTexture(face* font, int size, char letter) {
        addToCache(font, size, letter); // Automatically cache char if it isn't already cached

        return &font->cache[size][letter].bitmap;
    }

    int getLength(face* font, std::string text, const int size) {
        int width = 0;

        // Calculate the length of the string before drawing it
        for (int i = 0; i < text.length(); i++) {
            if (i == (text.length() - 1)) {
               width += (getMetrics(font, size, text[i]).width + getMetrics(font, size, text[i]).horiBearingX) / 64;
            }
            else {
                width += (getMetrics(font, size, text[i]).horiAdvance) / 64;
            }
        }

        return width;
    }

    void drawText(face* font, std::string text, int x, int y, int size, textAlignment align, xpdraw::color textColor) {
        glColor4f(textColor.red, textColor.green, textColor.blue, textColor.alpha);

        // Handle text alignment
        if (align == xpdAlignCenter) {
            x -= (getLength(font, text, size) / 2);
        }
        else if (align == xpdAlignRight) {
            x -= getLength(font, text, size);
        }

        // Draw each character
        for (char character : text) {
            // Calculate offset from the passed y value
            int y_offset = (getMetrics(font, size, character).horiBearingY / 64) - (getMetrics(font, size, character).height / 64);

            // Fetch & draw texture
            texture* image = getCharTexture(font, size, character);
            drawTexture(image, x + (getMetrics(font, size, character).horiBearingX / 64), y + y_offset, image->width, image->height, textColor);

            // Advance to the next character
            x += getMetrics(font, size, character).horiAdvance / 64;
        }
    }
}
#pragma clang diagnostic pop