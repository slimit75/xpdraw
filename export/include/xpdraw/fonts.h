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
            std::string path; // File path that this font was loaded from

            /**
             * @brief Load a new face
             * 
             * @param filename File path to load
             */
            void init(std::string filename);

            /**
             * @brief Adds a character to the cache
             * 
             * @param size Size of the character to cache
             * @param letter Character to cache
             */
            void add(int size, char letter);

            /**
             * @brief Return a characters metrics
             * 
             * @param size Size of character to fetch
             * @param letter Character to fetch
             * @return FT_Glyph_Metrics 
             */
            FT_Glyph_Metrics getMetrics(int size, char letter);

            /**
             * @brief Return a characters texture
             * 
             * @param size Size of character to fetch
             * @param letter Character to fetch
             * @return texture 
             */
            texture getTexture(int size, char letter);
    };

    /**
     * @brief Initalize freetype
     * 
     */
    void initFonts(); 

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
    void drawText(Face font, std::string text, int x, int y, int size, int align, color color = { 1, 1, 1, 1 });
}