#ifndef PAINT_H
#define PAINT_H

void drawPoint(int x, int y, int color, int width);
void drawLine(int x1, int y1, int x2, int y2, int color, int width);
void drawRect(int x1, int y1, int x2, int y2, int color, int width, int fill);
void drawCircle(int x1, int y1, int r);
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color, int width, int fill);
void drawMem(int x1, int y1, char* data, int height, int width);

#endif
