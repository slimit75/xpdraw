#include "xpdraw/fonts.h"

bool fontsInit = false;
FT_Library ft;

void xpd_font_load(xpd_font_face_t* font, const char* filename) {
	if (!fontsInit) {
		FT_Init_FreeType(&ft);
		fontsInit = true;
	}

	FT_New_Face(ft, filename, 0, &font->ftFace);
	font->path = filename;
}

void xpd_font_cache(xpd_font_face_t* font, int size, char letter) {
	if (!font->cache[size][letter].loaded) {
		FT_Set_Pixel_Sizes(font->ftFace, 0, size * 1.5);
		FT_Load_Char(font->ftFace, letter, FT_LOAD_RENDER);

		xpd_load_buffer(&font->cache[size][letter].bitmap, font->ftFace->glyph->bitmap.buffer, font->ftFace->glyph->bitmap.width, font->ftFace->glyph->bitmap.rows, GL_ALPHA);
		font->cache[size][letter].metrics = font->ftFace->glyph->metrics;
		font->cache[size][letter].loaded = true;
	}
}

inline FT_Glyph_Metrics xpd_font_get_metrics(xpd_font_face_t* font, int size, char letter) {
	xpd_font_cache(font, size, letter); // Automatically cache char if it isn't already cached

	return font->cache[size][letter].metrics;
}

inline xpd_texture_t* xpd_font_get_texture(xpd_font_face_t* font, int size, char letter) {
	xpd_font_cache(font, size, letter); // Automatically cache char if it isn't already cached

	return &font->cache[size][letter].bitmap;
}

int xpd_text_length(xpd_font_face_t* font, std::string text, const int size) {
	int width = 0;

	// Calculate the length of the string before drawing it
	for (int i = 0; i < text.length(); i++) {
		if (i == (text.length() - 1)) {
			width += (xpd_font_get_metrics(font, size, text[i]).width + xpd_font_get_metrics(font, size, text[i]).horiBearingX) / 64;
		}
		else {
			width += (xpd_font_get_metrics(font, size, text[i]).horiAdvance) / 64;
		}
	}

	return width;
}

void xpd_text_draw(xpd_font_face_t* font, std::string text, int x, int y, int size, xpd_text_align_t align, xpd_color_t textColor) {
	glColor4f(textColor.red, textColor.green, textColor.blue, textColor.alpha);

	// Handle text alignment
	if (align == xpdAlignCenter) {
		x -= (xpd_text_length(font, text, size) / 2);
	}
	else if (align == xpdAlignRight) {
		x -= xpd_text_length(font, text, size);
	}

	// Draw each character
	for (char character : text) {
		// Calculate offset from the passed y value
		int y_offset = (xpd_font_get_metrics(font, size, character).horiBearingY / 64) - (xpd_font_get_metrics(font, size,
		                                                                                                       character).height / 64);

		// Fetch & draw texture
		xpd_texture_t* image = xpd_font_get_texture(font, size, character);
		xpd_draw_texture(image, x + (xpd_font_get_metrics(font, size, character).horiBearingX / 64), y + y_offset, image->width, image->height, textColor);

		// Advance to the next character
		x += xpd_font_get_metrics(font, size, character).horiAdvance / 64;
	}
}