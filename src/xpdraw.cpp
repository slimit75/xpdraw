#if LIN or __MINGW32__
	#include <GL/gl.h>
#elif __GNUC__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "xpdraw/xpdraw.h"

int anchor_x = 0;
int anchor_y = 0;

namespace xpdraw {
    void loadBuffer(xpdraw::texture* texture, void* buffer, int width, int height, GLenum format) {
        texture->width = width;
        texture->height = height;

        glGenTextures(1, &texture->gl_texture);
        glBindTexture(GL_TEXTURE_2D, texture->gl_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, format, texture->width, texture->height, 0, format, GL_UNSIGNED_BYTE, buffer);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
    void setAnchor(int newAnchor_x, int newAnchor_y) {
        anchor_x = newAnchor_x;
        anchor_y = newAnchor_y;
    }
#pragma clang diagnostic pop
    
    void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, xpdraw::color color) {
        glColor4f(color.red, color.green, color.blue, color.alpha);

        glBegin(GL_TRIANGLES);
        glVertex2i(x1 + anchor_x, y1 + anchor_y);
        glVertex2i(x2 + anchor_x, y2 + anchor_y);
        glVertex2i(x3 + anchor_x, y3 + anchor_y);
        glEnd();
    }

    void drawRect(int left, int bottom, int width, int height, xpdraw::color color, int borderSize, xpdraw::color borderColor) {
        if (borderSize == -1) {
            glColor4f(color.red, color.green, color.blue, color.alpha);

            const int x1 = anchor_x + left;
            const int y1 = anchor_y + bottom;
            const int x2 = x1 + width;
            const int y2 = y1 + height;
            glBegin(GL_QUADS);
            glVertex2i(x1, y1);
            glVertex2i(x1, y2);
            glVertex2i(x2, y2);
            glVertex2i(x2, y1);
            glEnd();
        }
        else {
            drawRect(left, bottom, width, height, color);
            drawRect(left, bottom, borderSize, height, borderColor);
            drawRect(left + width - borderSize, bottom, borderSize, height, borderColor);
            drawRect(left, bottom + height - borderSize, width, borderSize, borderColor);
            drawRect(left, bottom, width, borderSize, borderColor);
        }
    }

    void drawQuad(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, xpdraw::color color) {
        glColor4f(color.red, color.green, color.blue, color.alpha);

        glBegin(GL_QUADS);
        glVertex2i(x1 + anchor_x, y1 + anchor_y);
        glVertex2i(x2 + anchor_x, y2 + anchor_y);
        glVertex2i(x3 + anchor_x, y3 + anchor_y);
        glVertex2i(x4 + anchor_x, y4 + anchor_y);
        glEnd();
    }

    void drawLine(int start_x, int start_y, int end_x, int end_y, xpdraw::color color, int thickness) {
        glColor4f(color.red, color.green, color.blue, color.alpha);

        const int x1 = start_x + anchor_x;
        const int y1 = start_y + anchor_y;
        const int x2 = end_x + anchor_x;
        const int y2 = end_y + anchor_y;

        glLineWidth(thickness);
        glBegin(GL_LINES);
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);
        glEnd();
    }

    void drawTexture(xpdraw::texture* texture, int left, int bottom, int width, int height, xpdraw::color color) {
        glColor4f(color.red, color.green, color.blue, color.alpha);

        if (width == 0) {
          width = texture->width;
        }
        if (height == 0) {
          height = texture->height;
        }

        const int x1 = anchor_x + left;
        const int y1 = anchor_y + bottom;
        const int x2 = x1 + width;
        const int y2 = y1 + height;

        glBindTexture(GL_TEXTURE_2D, texture->gl_texture);
        glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);
        glTexCoord2i(0, 1);
        glVertex2i(x1, y1);
        glTexCoord2i(0, 0);
        glVertex2i(x1, y2);
        glTexCoord2i(1, 0);
        glVertex2i(x2, y2);
        glTexCoord2i(1, 1);
        glVertex2i(x2, y1);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void drawRotatedTexture(xpdraw::texture* texture, float angle, float left, float bottom, float width, float height, float rx, float ry, xpdraw::color color) {
        glColor4f(color.red, color.green, color.blue, color.alpha);

        rx = left + rx;
        ry = bottom + ry;

        const float x1 = left - rx;
        const float y1 = bottom - ry;
        const float x2 = x1 + width;
        const float y2 = y1 + height;

        glBindTexture(GL_TEXTURE_2D, texture->gl_texture);
        glEnable(GL_TEXTURE_2D);

        glPushMatrix();
        glTranslatef(rx + anchor_x, ry + anchor_y, 0);
        glRotatef(360 - angle, 0, 0, 1);
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
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void loadTexture(xpdraw::texture* texture, const char* filename) {
        // Get a buffer from the passed file
        int width, height, nrChannels; // Do we need to store nrChannels?
        unsigned char* texDat = stbi_load(filename, &width, &height, &nrChannels, 4);

        // Load the buffer into an xpd texture
        if (texDat != nullptr) {
            loadBuffer(texture, texDat, width, height, GL_RGBA);
            stbi_image_free(texDat);
        }
        else {
          // TODO: Alert about this error without crashing the entire sim
        }
    }
}