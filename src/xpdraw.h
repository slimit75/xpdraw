#pragma once

#if LIN
	#include <GL/gl.h>
#elif __GNUC__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

#include <string>

/*
    Drawing functions to simplify OpenGL
*/

#define ALIGN_LEFT 1
#define ALIGN_CENTER 2
#define ALIGN_RIGHT 3

struct sd_texture {
    GLuint gl_texture;
    int width;
    int height;
};

struct sd_color {
    float red;
    float green;
    float blue;
    float alpha;
};

std::string findPluginPath();
std::string findXPlanePath();

namespace simdraw {
    void initFT();
    void setAnchor(int newAnchor_x, int newAnchor_y);
    void drawRect(int left, int bottom, int width, int height, sd_color color);
    void drawRectBorder(int left, int bottom, int width, int height, sd_color color, int borderSize, sd_color borderColor);
    void drawQuad(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, sd_color color);
    void drawLine(int start_x, int start_y, int end_x, int end_y, sd_color color);
    void drawLine(int start_x, int start_y, int end_x, int end_y, sd_color color, int thickness);
    void drawTexture(sd_texture texture, int left, int bottom, int width, int height, sd_color color);
    void drawRotatedTexture(sd_texture texture, float angle, float left, float bottom, float width, float height, float rx, float ry, sd_color color);
    sd_texture loadTexture(std::string filename);
    void loadFont(FT_Face *font, std::string filename);
    void drawText(FT_Face face, std::string textString, float x, float y, int size, int align, sd_color color);
    sd_texture loadBuffer(void* buffer, int width, int height, GLenum format);
}