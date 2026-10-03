# Point #

Point of this project is educate how to works 3D graphic.
This project be intresting to people, who wants learn how it works on practice.

# Architecture #

This project divided by modules:
1. math and matrix module.
2. graphic module.

## Matrix ##

We have two size of matrix - 4x4 and 1x4, and functions who works with them.
Naming of this functions must be like structure:
    [destination_operand]_[source_operand]_[prefix][operation]

Prefix may be:
- e - elements, operation will be done per-elements
- v - vector, input operands will be not erased
- m - math, operation will be math correct

## Graphic ##

Graphic module contains several structures, whitch contains graphic data:
1. graphic_state - contains general data, neccesary to render image:
```C
typedef struct {
    float screen_dst;           // distance to screen in 3D space
    float fov_x, fov_y;         // Field of view in radians

    uint32_t* pixels;           // pixel array
    uint32_t width, height;     // width and height 

    mat4x4 *transform;          // transform matrix
    mat1x4 *translate;          // translate matrix

    void (*vertex_shader)(polygon *input, polygon *output, mat4x4 *transform, mat1x4 *translate);   // vertex shader
    uint32_t (*pixel_shader)(mat1x4* input, mat1x4* position, mat1x4* normal);                      // pixel shader
} graphic_state;
```
    
2. thread_worker - contains data using to render polygon. Neccesary to use multi-threading in future:
```C
typedef struct {
    graphic_state *screen;      // pointer to general data

    mat1x4 *colors;             // array same size as pixel array, contains color

    polygon *start, *end;       // contains pointer to start and end polygon
} thread_worker;
```

3. polygon - contains polygon data:
```C
typedef struct {
    mat4x4 vertex;                  // contains three vertex of polygon
    mat1x4 color1, color2, color3;  // contains color of each vertex
} polygon;
```

# TODO #
1. Create more examples
2. Rewrite some code on Assembler to optimize
3. Add multi threading