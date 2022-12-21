#ifndef XPDRAW_H
#define XPDRAW_H

#if LIN or __MINGW32__
	#include <GL/gl.h>
#elif __GNUC__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

#include <string>

#define XPD_COLOR_WHITE { 1, 1, 1, 1 }
#define XPD_COLOR_BLACK { 0, 0, 0, 1 }
#define XPD_RGB(r, g, b) { r/255.0f, g/255.0f, b/255.0f, 1 }
#define XPD_RGBA(r, g, b, a) { r/255.0f, g/255.0f, b/255.0f, a }

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

    /**
     * @brief Loads an OpenGL buffer and converts it into a xpdraw texture
     *
     * @param texture Pointer to the xpdraw texture
     * @param buffer Buffer to load
     * @param width Width of buffer
     * @param height Height of buffer
     * @param format Format of buffer
     */
    void loadBuffer(xpdraw::texture* texture, void* buffer, int width, int height, GLenum format);

    /**
     * @brief Sets the position of the 'anchor'. All future calls will be relative to this location if defined.
     * 
     * @param newAnchor_x Lateral position of the anchor
     * @param newAnchor_y Vertical position of the anchor
     */
    void setAnchor(int newAnchor_x, int newAnchor_y);

    /**
     * @brief Draw a triangle with the specified points
     * 
     * @param x1 Lateral position of first point
     * @param y1 Vertical position of first point
     * @param x2 Lateral position of second point
     * @param y2 Vertical position of second point
     * @param x3 Lateral position of third point
     * @param y3 Vertical position of third point
     * @param color Color of the triangle; defaults to white
     */
    void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, xpdraw::color color = XPD_COLOR_WHITE);

    /**
     * @brief Draw a rectangle with the specified parameters
     * 
     * @param left X position of the rectangle 
     * @param bottom Y position of the rectangle
     * @param width Width of the rectangle
     * @param height Height of the rectangle
     * @param color Color of the rectangle; defaults to white
     * @param borderSize Border size of the rectangle if needed; not shown by default
     * @param borderColor Color of the rectangle border (if shown); defaults to white
     */
    void drawRect(int left, int bottom, int width, int height, xpdraw::color color = XPD_COLOR_WHITE, int borderSize = -1, xpdraw::color borderColor = XPD_COLOR_WHITE);
    
    /**
     * @brief Draw a quad with the specified points
     * 
     * @param x1 Lateral position of the first point
     * @param y1 Vertical position of the first point
     * @param x2 Lateral position of the second point
     * @param y2 Vertical position of the second point
     * @param x3 Lateral position of the third point
     * @param y3 Vertical position of the third point
     * @param x4 Lateral position of the fourth point
     * @param y4 Vertical position of the fourth point
     * @param color Color of the quad; defaults to white
     */
    void drawQuad(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, xpdraw::color color = XPD_COLOR_WHITE);

    /**
     * @brief Draw a line
     * 
     * @param start_x X position of the starting point
     * @param start_y Y position of the starting point
     * @param end_x X position of the ending point
     * @param end_y Y position of the ending point
     * @param color Color of the line; defaults to white
     * @param thickness Thickness of the line; defaults to 1
     */
    void drawLine(int start_x, int start_y, int end_x, int end_y, xpdraw::color color = XPD_COLOR_WHITE, int thickness = 1);

    /**
     * @brief Draw a mirrored version of a texture; used by xpdraw::fonts
     * 
     * @param texture Texture to draw
     * @param left X position of the texture
     * @param bottom Y position of the texture
     * @param width Width of the drawn texture; defaults to the texture's width
     * @param height Height of the drawn texture; defaults to the texture's height
     * @param color Color of the texture; defaults to white
     */
    void drawTexture(xpdraw::texture* texture, int left, int bottom, int width = 0, int height = 0, xpdraw::color color = XPD_COLOR_WHITE);

    /**
     * @brief Draw a rotated texture
     * 
     * @param texture Texture to draw
     * @param angle Angle to draw the texture at
     * @param left X position of the texture
     * @param bottom Y position of the texture
     * @param width Width of the drawn texture; defaults to the texture's width
     * @param height Height of the drawn texture; defaults to the texture's height
     * @param rx X anchor to rotate around relative to the texture
     * @param ry Y anchor to rotate around relative to the texture
     * @param color Color of the texture; defaults to white
     */
    void drawRotatedTexture(xpdraw::texture* texture, float angle, float left, float bottom, float width, float height, float rx, float ry, xpdraw::color color = XPD_COLOR_WHITE);
    
    /**
     * @brief Load a texture
     *
     * @param texture Pointer to the xpdraw texture
     * @param filename File path to load
     */
    void loadTexture(xpdraw::texture* texture, std::string filename);
}

#endif