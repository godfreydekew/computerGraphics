# Dragon Curve

## Description
This project visualizes the **Dragon Curve**, a fractal generated through iterative transformations. The program uses OpenGL and GLUT to render the fractal with color gradients and interactive features.

## Features
- **Dynamic Iterations**: Adjust the number of iterations to control the fractal's complexity.
- **Rotation**: Rotate the fractal clockwise or counterclockwise.
- **Scaling**: Zoom in and out of the fractal for detailed views.
- **Color Gradient**: Points on the curve are rendered with a gradient from red to blue.

## Controls
- **`+`**: Increase the number of iterations.
- **`-`**: Decrease the number of iterations.
- **`R`/`r`**: Rotate the fractal clockwise or counterclockwise.
- **`S`/`s`**: Zoom in or out.
- **`ESC`**: Exit the program.

## Dependencies
- OpenGL
- GLUT (FreeGLUT recommended)

## Compilation
To compile the program, use the following command:
```bash
g++ -o dragon_curve dragon_curve.cpp -lGL -lGLU -lglut
