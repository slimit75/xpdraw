# xpdraw
xpdraw is a library for X-Plane plugins which aims to simplify certain OpenGL and X-Plane functions. It is still in early development, and as a result, things are extremely likely to change.

If you do decide to use xpdraw in its current state, you **SHOULD NOT** use `xpdraw/fonts.h`. It is in the process of being overhauled and text rendering is currently disabled.

It should also be known that, in its current state, xpdraw crashes the sim with no hints whenever it runs into an error such as being unable to load a texture. This will be fixed in the future.

The include directory and static libraries are under the `export/` directory. 
Usage instructions will be added to a wiki as xpdraw becomes more complete.