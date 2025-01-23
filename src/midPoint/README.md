# Circle and Line Drawing using GrayscaleImage

## Description
This project demonstrates drawing geometric shapes, such as circles and filled circles, on a grayscale image using simple algorithms. It includes utility functions to draw lines, circles, and filled circles with customizable parameters.

## Features
- **Circle Drawing**: Draws a circle with a specified radius and center.
- **Filled Circle**: Fills a circle with a given color.
- **Line Drawing**: Draws horizontal lines to assist in filling shapes.
- **Custom Grayscale Image Manipulation**: Uses the `GrayscaleImage` class for pixel manipulation and image saving.

## Functions
### `void dup8(GrayscaleImage &im, int cx, int cy, int x, int y)`
Mirrors points across eight octants to draw symmetrical parts of a circle.

### `void circle(GrayscaleImage &im, int cx, int cy, int r)`
Draws a circle centered at `(cx, cy)` with radius `r` using a midpoint-based algorithm.

### `void line(GrayscaleImage &im, int x, int y, int cx, int cy, int col)`
Draws a horizontal line centered at `(cx, cy)` with length `2x`.

### `void filled_circle(GrayscaleImage &im, int cx, int cy, int r, int col)`
Draws and fills a circle with color `col` using horizontal lines for each row.

## Usage
### Dependencies
Ensure the `Image.h` header file and its implementation for the `GrayscaleImage` class are included in your project. The `GrayscaleImage` class should provide:
- Pixel manipulation via `operator()`.
- Saving functionality using `Save(filename)`.

### Compilation
To compile the program:
```bash
g++ -o circle_filled circle_filled.cpp -l png
