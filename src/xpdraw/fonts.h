/*
 * fonts.h - Font handler & renderer
 * Copyright 2024 Ian Ward
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/
#ifndef XPDRAW_FONTS_H
#define XPDRAW_FONTS_H

#include <limits.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "xpdraw.h"

#ifdef __cplusplus
extern "C" {
#endif

#define XPD_CHAR_MAX (CHAR_MAX - CHAR_MIN)

typedef enum {
	xpdAlignLeft,
	xpdAlignCenter,
	xpdAlignRight
} xpd_text_align_t;

typedef struct {
	FT_Glyph_Metrics metrics;
	xpd_texture_t bitmap;
} xpd_font_cache_t;

typedef struct {
	int size;
	char letter;
	xpd_font_cache_t data;
} xpd_font_letter_t;

typedef struct {
	FT_Face ftFace;
	xpd_font_letter_t letters[XPD_CHAR_MAX];
	int letters_idx;
} xpd_font_face_t;

static const FT_Glyph_Metrics xpd_metrics_empty = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0
};

/**
 * @brief Load a new font
 *
 * @param font Pointer to the font we are loading
 * @param path File path to load from
 */
void xpd_font_load(xpd_font_face_t *font, const char *path);

/**
 * @brief Returns the length of a string.
 *
 * @param font Font to use
 * @param text Text to get the length of
 * @param size Size of the font to use
 * @return int
 */
int xpd_text_length(xpd_font_face_t *font, const char *text, int size);

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
void xpd_text_draw(xpd_font_face_t *font, const char *text, int x, int y, int size, xpd_text_align_t align,
				   xpd_color_t color);

#ifdef __cplusplus
}
#endif

#endif
