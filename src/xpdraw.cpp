#include <GL/gl.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "xpdraw/xpdraw.h"

using namespace std;

int anchor_x = 0;
int anchor_y = 0;

namespace xpdraw {
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
    
    void drawRect(int left, int bottom, int width, int height, xpdraw::color color, int borderSize, xpdraw::color borderColor) {
        if (borderSize == -1) {
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

    void drawLine(int start_x, int start_y, int end_x, int end_y, int thickness, xpdraw::color color) {
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

    void drawTexture(xpdraw::texture texture, int left, int bottom, int width, int height, xpdraw::color color) {
        glColor4f(color.red, color.green, color.blue, color.alpha);

        if (width == -1) {
            width = texture.width;
        }
        if (height == -1) {
            height = texture.height;
        }
        
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
    }

    void drawFlippedTexture(xpdraw::texture texture, int left, int bottom, int width, int height, xpdraw::color color) {
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
    }

    void drawRotatedTexture(xpdraw::texture texture, float angle, float left, float bottom, float width, float height, float rx, float ry, xpdraw::color color) {
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

        int width, height, nrChannels;
        unsigned char* texDat = stbi_load(filename.c_str(), &width, &height, &nrChannels, 4);

        if (texDat == NULL) {
            throw("Failed to load texture: %s!", filename.c_str());

            return { 0, 0, 0 };
        }
        
        // Return texture
        xpdraw::texture return_value;
        return_value = loadBuffer(texDat, width, height, GL_RGBA);
        stbi_image_free(texDat);

        return return_value;
    }
}