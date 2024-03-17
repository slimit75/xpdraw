#include "xpdraw/fonts.h"

#include <assert.h>
#include <stdbool.h>
#include <XPLMUtilities.h>

bool fonts_init = false;
char str[255];
FT_Library ft;

void xpd_font_load(xpd_font_face_t *font, const char *path) {
	if (fonts_init == false) {
		FT_Init_FreeType(&ft);
		fonts_init = true;
	}

	FT_New_Face(ft, path, 0, &font->ftFace);
	font->letters_idx = -1;
}

void xpd_font_cache(xpd_font_face_t *font, int size, char letter) {
	// TODO: Does this need to be called as often as it currently is?
	bool not_loaded = true;

	if (font->ftFace == NULL) {
		assert("font->ftFace == NULL");
	}

	for (int i = 0; (i < XPD_CHAR_MAX) && (i <= font->letters_idx); i++) {
		if (font->letters[i].size == size && font->letters[i].letter == letter) {
			not_loaded = false;
			break;
		}
	}

	if (not_loaded == true) {
		FT_Set_Pixel_Sizes(font->ftFace, 0, (int)(size * 1.5));
		FT_Load_Char(font->ftFace, letter, FT_LOAD_RENDER);

		font->letters_idx++;
		font->letters[font->letters_idx].size         = size;
		font->letters[font->letters_idx].letter       = letter;
		font->letters[font->letters_idx].data.metrics = font->ftFace->glyph->metrics;

		xpd_load_buffer(&font->letters[font->letters_idx].data.bitmap, font->ftFace->glyph->bitmap.buffer,
						font->ftFace->glyph->bitmap.width, font->ftFace->glyph->bitmap.rows, GL_ALPHA);
	}
}

FT_Glyph_Metrics xpd_font_get_metrics(xpd_font_face_t *font, int size, char letter) {
	xpd_font_cache(font, size, letter); // Automatically cache char if it isn't already cached

	for (int i = 0; i < CHAR_MAX; i++) {
		if (font->letters[i].size == size && font->letters[i].letter == letter) {
			return font->letters[i].data.metrics;
		}
	}

	sprintf(str, "xpdraw: Unable to load metrics for font family %s at letter %c & size %i!\n",
			font->ftFace->family_name, letter, size);
	XPLMDebugString(str);
	return xpd_metrics_empty;
}

xpd_texture_t xpd_font_get_texture(xpd_font_face_t *font, int size, char letter) {
	xpd_font_cache(font, size, letter); // Automatically cache char if it isn't already cached

	for (int i = 0; i < CHAR_MAX; i++) {
		if (font->letters[i].size == size && font->letters[i].letter == letter) {
			return font->letters[i].data.bitmap;
		}
	}

	sprintf(str, "xpdraw: Unable to load texture for font family %s at letter %c & size %i!\n",
			font->ftFace->family_name, letter, size);
	XPLMDebugString(str);
	return xpd_texture_empty;
}

int xpd_text_length(xpd_font_face_t *font, const char *text, const int size) {
	int width = 0;

	// Calculate the length of the string before drawing it
	for (int i = 0; i < strlen(text); i++) {
		FT_Glyph_Metrics text_metrics = xpd_font_get_metrics(font, size, text[i]);
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
	glColor4f(textColor.red, textColor.green, textColor.blue, textColor.alpha);

	// Handle text alignment
	if (align == xpdAlignCenter) {
		x -= xpd_text_length(font, text, size) / 2;
	}
	else if (align == xpdAlignRight) {
		x -= xpd_text_length(font, text, size);
	}

	// Draw each character
	for (int i = 0; i < strlen(text); i++) {
		FT_Glyph_Metrics text_metrics = xpd_font_get_metrics(font, size, text[i]);

		// Calculate offset from the passed y value
		int y_offset = (text_metrics.horiBearingY / 64) - (text_metrics.height / 64);

		// Fetch & draw texture
		xpd_texture_t image = xpd_font_get_texture(font, size, text[i]);
		xpd_draw_texture(&image, x + (text_metrics.horiBearingX / 64), y + y_offset, image.width, image.height,
						 textColor);

		// Advance to the next character
		x += text_metrics.horiAdvance / 64;
	}
}
