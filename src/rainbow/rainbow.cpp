#include "Image.h"
#include <array>


void dup4(ColorImage &im,const RGBA &col, int cx, int cy, int x, int y) {
    im(cx - x , cy - y) = col;
    im(cx - y , cy - x) = col;
    im(cx + x , cy - y) = col;
    im(cx + y , cy - x) = col;
}
void circle(ColorImage &im,const RGBA &col, int cx, int cy, int r) {
    int x = r, y = 0;
    int rsq = r * r;
    dup4(im,col, cx, cy, x, y);

    while(x > y) {
        y++;
    
        int d1 = abs((x * x) + (y * y) - rsq);
        int d2 = abs((x - 1) * (x - 1) + (y*y) - rsq);

        if (d2 < d1) {
            x--;
        }

        dup4(im,col, cx, cy, x, y);
    }

}

void naive_circle_algorithm(ColorImage &im, int r1, int r2, const RGBA &col){
    int cx = 1000, xy = 1000;
    circle(im, col, cx,  xy, r1);

    for (int y = -r1; y <= r1; y++) {
        for (int x = -r1; x <= r1; x++) {
            if (x*x + y*y <= r1*r1 && x*x + y*y >= r2*r2) {
                if ( y <= 0  ) {
                    im(cx + x,xy + y) = col; 
                }
            }
        }
}
}


void draw_rainbow(ColorImage &im, int thickness){

    std::array<std::array<int, 4>, 7> colors{{
        {112, 54, 157, 255},//violet
        {75, 54, 157, 255},//indigo
        {72, 125, 231, 255},//blue
        {0, 188, 0, 255},//green
        {250, 235, 54, 255},//yellow
        {255, 165, 0, 255},//orange
        {232, 20, 22, 128}//red
    }};

    int outer_radius = 500;
    int inner_radius = outer_radius - thickness;

    for (const auto &col : colors){
        naive_circle_algorithm(im, outer_radius, inner_radius, RGBA(col[0], col[1],col[2]));
        outer_radius += thickness;
        inner_radius += thickness;
    }
}

int main(){
    ColorImage im(2000, 2000);

    int thickness = 20;
    draw_rainbow(im, thickness);

    im.Save("rainbow.png");
    return 0;
}
