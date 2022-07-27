# xpdraw
xpdraw is a library for X-Plane plugins which aims to simplify certain OpenGL and X-Plane functions. It is still in early development, and as a result, things are extremely likely to change.

If you do decide to use xpdraw in its current state, you **SHOULD NOT** use `xpdraw/fonts.h`. It:
- Will 100% be rewritten in the future
- Is effectively limited to one font face
- Does questionable things to calculate width of spaces
- Does even more questionable things to calculate position of any character that is Q or is outside of the 26 letters

Other known limitations of xpdraw as a whole include:
- If an error occurs, such as being unable to load a texture, X-Plane will crash without a hint in the log. 

The include directory and static libraries are under the `export/` directory. 
Usage instructions will be added to a wiki as xpdraw becomes more complete.