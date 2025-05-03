#include "xpdraw/fonts.h"

#include <assert.h>

bool fonts_init = false;
FT_Library ft;

void xpd_font_load(xpd_font_face_t *font, const char *path) {
	if (fonts_init == false) {
		FT_Init_FreeType(&ft);
		fonts_init = true;
	}

	FT_New_Face(ft, path, 0, &font->ftFace);
	font->letters_idx = -1;
}

void xpd_font_cache(xpd_font_face_t *font, int size) {
	// Throw a fatal error if the font isn't properly loaded
	assert(font != NULL);
	assert(font->ftFace != NULL);

	if (font->letters[size][7].letter == 0u) { // Why 7???
		// Tell FreeType what font size we want
		FT_Set_Pixel_Sizes(font->ftFace, 0, (int)(size * 1.5));

		// Load data for each available character
		for (char i = CHAR_MIN; i <= CHAR_MAX; i++) {
			FT_Load_Char(font->ftFace, i, FT_LOAD_RENDER);

			font->letters[size][i].letter = i;
			font->letters[size][i].metrics = font->ftFace->glyph->metrics;

			xpd_load_buffer(&font->letters[size][i].bitmap, font->ftFace->glyph->bitmap.buffer,
							font->ftFace->glyph->bitmap.width, font->ftFace->glyph->bitmap.rows, GL_ALPHA);
		}
	}
}

int xpd_text_length(xpd_font_face_t *font, const char *text, const int size) {
	int width = 0;

	// Calculate the length of the string before drawing it
	for (int i = 0; i < strlen(text); i++) {
		FT_Glyph_Metrics text_metrics = font->letters[size][text[i]].metrics;
		if (i == strlen(text) - 1) {
			width += (int)((text_metrics.width + text_metrics.horiBearingX) / 64);
		}
		else {
			width += (int)(text_metrics.horiAdvance / 64);
		}
	}

	return width;
}

void xpd_text_draw(xpd_font_face_t *font, const char *text, int x, int y, int size, xpd_text_align_t align,
				   xpd_color_t textColor) {
	assert(font != NULL);

	xpd_font_cache(font, size);
	glColor4f(textColor.red, textColor.green, textColor.blue, textColor.alpha);

	// Handle text alignment
	if (align == XPD_ALIGN_C) {
		x -= xpd_text_length(font, text, size) / 2;
	}
	else if (align == XPD_ALIGN_R) {
		x -= xpd_text_length(font, text, size);
	}

	// Draw each character
	for (int i = 0; i < strlen(text); i++) {
		FT_Glyph_Metrics text_metrics = font->letters[size][text[i]].metrics;

		// Calculate offset from the passed y value
		int y_offset = (int)(text_metrics.horiBearingY / 64) - (int)(text_metrics.height / 64);

		// Fetch & draw texture
		xpd_texture_t image = font->letters[size][text[i]].bitmap;
		xpd_draw_texture(&image, x + (int)(text_metrics.horiBearingX / 64), y + y_offset, image.width, image.height,
						 textColor);

		// Advance to the next character
		x += (int)text_metrics.horiAdvance / 64;
	}
}
