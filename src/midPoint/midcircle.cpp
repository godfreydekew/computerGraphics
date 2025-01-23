#include "Image.h"

void dup8(GrayscaleImage &im, int cx, int cy, int x, int y) {
    im(cx + x , cy + y) = 255;
    im(cx - x , cy - y) = 255;

    im(cx + y , cy + x) = 255;
    im(cx - y , cy - x) = 255;

    im(cx - x , cy + y) = 255;
    im(cx - y , cy + x) = 255;

    im(cx + x , cy - y) = 255;

    im(cx + y , cy - x) = 255;
   
}


void circle(GrayscaleImage &im, int cx, int cy, int r) {
    int x = r, y = 0;
    dup8(im, cx, cy, x, y);
    int rsq = r * r;

    while(x > y) {

        y++;
        int d1 = abs((x * x) + (y * y) - rsq);
        int d2 = abs((x - 1) * (x - 1) + (y*y) - rsq);

        if (d2 < d1) {
            x--;
        }
        dup8(im, cx, cy, x, y);
        std::cout << x << ", " <<y << std::endl;

    }

}

void line(GrayscaleImage &im, int x, int y,int cx, int cy, int col) {

    for(int i = -x; i <= x; i++){
        im(i + cx, y + cy) = col;
    }
}

void filled_circle(GrayscaleImage &im, int cx, int cy, int r, int col) {
    int x = r, y = 0;
    line(im, x, y, cx, cy, col);
    int rsq = r * r;

    while(x > y) {
        y++;
        int d1 = abs((x * x) + (y * y) - rsq);
        int d2 = abs((x - 1) * (x - 1) + (y*y) - rsq);

        if (d2 < d1) {
            x--;
        }
       
        line(im, x, y, cx, cy, col);
        line(im, x, -y, cx, cy, col);
        line(im, y, x, cx, cy, col);
        line(im, y, -x, cx, cy, col);

    }

}
int main(){
    GrayscaleImage im(250, 250);

    int cx = 100, cy = 100;
    im(cx, cy) = 255;
    // im(7, 6) = 255;
    int r = 30;

    // for(int r1 = 0; r1 <= r ; r1++) {
    //     circle(im, cx, cy, r1);
    // }
     circle(im, cx, cy, r);

    filled_circle(im, cx, cy, r, 255);
    im.Save("midcircle.png");

    return 0;
}