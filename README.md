# xpdraw
xpdraw is a library for X-Plane plugins which aims to simplify certain OpenGL and X-Plane functions. It is still in early development, and as a result, things are extremely likely to change.

**Note:** In its current state, xpdraw crashes the sim with no hints whenever it runs into an error such as being unable to load a texture. This will be fixed in the future.

As of December 14th, 2022, you can include xpdraw into your project by using the `add_subdirectory()` function in your `CMakeLists.txt`.