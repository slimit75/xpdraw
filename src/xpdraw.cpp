#include "xpdraw.h"

#include <filesystem>

#if LIN
	#include <GL/gl.h>
#elif __GNUC__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

#include <XPLMPlugin.h>
#include <XPLMUtilities.h>
#include <math.h>

#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

/*
    Drawing functions to simplify OpenGL
*/

using namespace std;
using namespace std::filesystem;
using std::filesystem::current_path;

int anchor_x = 0;
int anchor_y = 0;
int lastRight = 0;
int lastGlyphWidth = 0;
xpdraw::texture charBitmapCache[256][256];

FT_Library ft;

namespace xpdraw {
    namespace tools {
        string findPluginPath() {
            XPLMEnableFeature("XPLM_USE_NATIVE_PATHS", 1);

            char pluginPathChar[256];
            XPLMGetPluginInfo(XPLMGetMyID(), NULL, pluginPathChar, NULL, NULL);
            string pluginPath = pluginPathChar;
            pluginPath.erase(pluginPath.end() - 10, pluginPath.end());

            return pluginPath;
        }

        string findXPlanePath() {
            XPLMEnableFeature("XPLM_USE_NATIVE_PATHS", 1);

            char xplanePath[512];
            XPLMGetSystemPath(xplanePath);
            string xpPath = xplanePath;
            
            return xpPath;
        }
    }
    
    namespace fonts {
        void initFT() {
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
                    x = lastRight + 1.3;
                }
            }
        }
    }

    xpdraw::texture loadBuffer(void* buffer, int width, int height, GLenum format) {
        GLuint tex;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, buffer);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        xpdraw::texture return_value;
        return_value.gl_texture = tex;
        return_value.width = width;
        return_value.height = height;

        return return_value;
    }

    void setAnchor(int newAnchor_x, int newAnchor_y) {
        anchor_x = newAnchor_x;
        anchor_y = newAnchor_y;
    }
    
    void drawRect(int left, int bottom, int width, int height, xpdraw::color color = { 1, 1, 1, 1 }) {
        glColor4f(color.red, color.green, color.blue, color.alpha);

        int x1 = anchor_x + left;
        int y1 = anchor_y + bottom;
        int x2 = x1 + width;
        int y2 = y1 + height;
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex2f(x1, y1);
        glTexCoord2f(0, 1);
        glVertex2f(x1, y2);
        glTexCoord2f(1, 1);
        glVertex2f(x2, y2);
        glTexCoord2f(1, 0);
        glVertex2f(x2, y1);
        glEnd();
    }

    void drawQuad(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, xpdraw::color color = { 1, 1, 1, 1 }) {
        glColor4f(color.red, color.green, color.blue, color.alpha);

        x1 += anchor_x;
        y1 += anchor_y;
        x2 += anchor_x;
        y2 += anchor_y;
        x3 += anchor_x;
        y3 += anchor_y;
        x4 += anchor_x;
        y4 += anchor_y;
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex2f(x1, y1);
        glTexCoord2f(0, 1);
        glVertex2f(x2, y2);
        glTexCoord2f(1, 1);
        glVertex2f(x3, y3);
        glTexCoord2f(1, 0);
        glVertex2f(x4, y4);
        glEnd();
    }

    void drawRectBorder(int left, int bottom, int width, int height, xpdraw::color color = { 1, 1, 1, 1 }, int borderSize, xpdraw::color borderColor = { 1, 1, 1, 1 }) {
        drawRect(left, bottom, width, height, color);
        drawRect(left, bottom, borderSize, height, borderColor);
        drawRect(left + width - borderSize, bottom, borderSize, height, borderColor);
        drawRect(left, bottom + height - borderSize, width, borderSize, borderColor);
        drawRect(left, bottom, width, borderSize, borderColor);
    }

    void drawLine(int start_x, int start_y, int end_x, int end_y, xpdraw::color color = { 1, 1, 1, 1 }) {
        glColor4f(color.red, color.green, color.blue, color.alpha);

        int x1 = start_x + anchor_x;
        int y1 = start_y + anchor_y;
        int x2 = end_x + anchor_x;
        int y2 = end_y + anchor_y;
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    }

    void drawLine(int start_x, int start_y, int end_x, int end_y, xpdraw::color color = { 1, 1, 1, 1 }, int thickness) {
        glColor4f(color.red, color.green, color.blue, color.alpha);

        int x1 = start_x + anchor_x;
        int y1 = start_y + anchor_y;
        int x2 = end_x + anchor_x;
        int y2 = end_y + anchor_y;

        glLineWidth(thickness);
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    }

    void drawTexture(xpdraw::texture texture, int left, int bottom, xpdraw::color color = { 1, 1, 1, 1 }) {
        glColor4f(color.red, color.green, color.blue, color.alpha);

        int x1 = anchor_x + left;
        int y1 = anchor_y + bottom;
        int x2 = x1 + texture.width;
        int y2 = y1 + texture.height;

        glBindTexture(GL_TEXTURE_2D, texture.gl_texture);
        glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex2f(x1, y1);
        glTexCoord2f(0, 1);
        glVertex2f(x1, y2);
        glTexCoord2f(1, 1);
        glVertex2f(x2, y2);
        glTexCoord2f(1, 0);
        glVertex2f(x2, y1);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        lastRight = x2 - anchor_x;
    }

    void drawTexture(xpdraw::texture texture, int left, int bottom, int width, int height, xpdraw::color color = { 1, 1, 1, 1 }) {
        glColor4f(color.red, color.green, color.blue, color.alpha);

        int x1 = anchor_x + left;
        int y1 = anchor_y + bottom;
        int x2 = x1 + width;
        int y2 = y1 + height;

        glBindTexture(GL_TEXTURE_2D, texture.gl_texture);
        glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex2f(x1, y1);
        glTexCoord2f(0, 1);
        glVertex2f(x1, y2);
        glTexCoord2f(1, 1);
        glVertex2f(x2, y2);
        glTexCoord2f(1, 0);
        glVertex2f(x2, y1);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        lastRight = x2 - anchor_x;
    }

    void drawFlippedTexture(xpdraw::texture texture, int left, int bottom, int width, int height, xpdraw::color color = { 1, 1, 1, 1 }) {
        glColor4f(color.red, color.green, color.blue, color.alpha);

        int x1 = anchor_x + left;
        int y1 = anchor_y + bottom;
        int x2 = x1 + width;
        int y2 = y1 + height;

        glBindTexture(GL_TEXTURE_2D, texture.gl_texture);
        glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 1);
        glVertex2f(x1, y1);
        glTexCoord2f(0, 0);
        glVertex2f(x1, y2);
        glTexCoord2f(1, 0);
        glVertex2f(x2, y2);
        glTexCoord2f(1, 1);
        glVertex2f(x2, y1);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        lastRight = x2 - anchor_x;
    }

    void drawRotatedTexture(xpdraw::texture texture, float angle, float left, float bottom, float width, float height, float rx, float ry, xpdraw::color color = { 1, 1, 1, 1 }) {
        glColor4f(color.red, color.green, color.blue, color.alpha);

        rx = left + rx;
        ry = bottom + ry;

        float x1 = left - rx;
        float y1 = bottom - ry;
        float x2 = x1 + width;
        float y2 = y1 + height;

        angle = 360 - angle;

        glBindTexture(GL_TEXTURE_2D, texture.gl_texture);
        glEnable(GL_TEXTURE_2D);

        glPushMatrix();

        glTranslatef(rx + anchor_x, ry + anchor_y, 0);
        glRotatef(angle, 0, 0, 1);

        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex2f(x1, y1);
        glTexCoord2f(0, 1);
        glVertex2f(x1, y2);
        glTexCoord2f(1, 1);
        glVertex2f(x2, y2);
        glTexCoord2f(1, 0);
        glVertex2f(x2, y1);
        glEnd();

        glPopMatrix();

        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    xpdraw::texture loadTexture(string filename) {
        stbi_set_flip_vertically_on_load(true);

        string filePath = xpdraw::tools::findPluginPath() += filename;

        int width, height, nrChannels;
        unsigned char* texDat = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 4);

        if (texDat == NULL) {
            throw("Failed to load texture: %s!", filePath.c_str());

            return { 0, 0, 0 };
        }
        
        // Return texture
        xpdraw::texture return_value;
        return_value = loadBuffer(texDat, width, height, GL_RGBA);
        stbi_image_free(texDat);

        return return_value;
    }
}