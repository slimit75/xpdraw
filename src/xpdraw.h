#pragma once

#if LIN
	#include <GL/gl.h>
#elif __GNUC__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

#include <string>
#include <vector>

/*
    Drawing functions to simplify OpenGL
*/

#define ALIGN_LEFT 1
#define ALIGN_CENTER 2
#define ALIGN_RIGHT 3

namespace xpdraw {
    struct texture {
        GLuint gl_texture;
        int width;
        int height;
    };

    struct color {
        float red;
        float green;
        float blue;
        float alpha = 1;
    };

    struct font {
        texture cache[256][256];
    };

    namespace tools {
        std::string findPluginPath();
        std::string findXPlanePath();
    }

    /*
    namespace fonts {
        void initFonts();
        void loadFont(FT_Face *font, std::string filename);
        void drawText(FT_Face face, std::string textString, float x, float y, int size, int align, xpdraw::color color);
    }
    */

    xpdraw::texture loadBuffer(void* buffer, int width, int height, GLenum format);
    void setAnchor(int newAnchor_x, int newAnchor_y);
    void drawRect(int left, int bottom, int width, int height, xpdraw::color color = { 1, 1, 1, 1 });
    void drawRectBorder(int left, int bottom, int width, int height, xpdraw::color color = { 1, 1, 1, 1 }, int borderSize, xpdraw::color borderColor = { 1, 1, 1, 1 });
    void drawQuad(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, xpdraw::color color = { 1, 1, 1, 1 });
    void drawLine(int start_x, int start_y, int end_x, int end_y, xpdraw::color color = { 1, 1, 1, 1 });
    void drawLine(int start_x, int start_y, int end_x, int end_y, xpdraw::color color = { 1, 1, 1, 1 }, int thickness);
    void drawTexture(xpdraw::texture texture, int left, int bottom, xpdraw::color color = { 1, 1, 1, 1 });
    void drawTexture(xpdraw::texture texture, int left, int bottom, int width, int height, xpdraw::color color = { 1, 1, 1, 1 });
    void drawRotatedTexture(xpdraw::texture texture, float angle, float left, float bottom, float width, float height, float rx, float ry, xpdraw::color color = { 1, 1, 1, 1 });
    xpdraw::texture loadTexture(std::string filename);
}