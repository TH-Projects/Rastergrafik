#include <stdlib.h>
#include "macros.h"

void drawPixel(int x, int y , char data[PIC_SIDE_LEN][PIC_SIDE_LEN]){
    data[x][y] = '+';
}

void drawLine (int x0, int y0, int x1, int y1, char data[PIC_SIDE_LEN][PIC_SIDE_LEN])
{
    int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */

    for (;;){  /* loop */
        drawPixel (x0,y0,data);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
        if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
    }
}

void drawSquare(int startX, int startY,int squareSideLen,char data[PIC_SIDE_LEN][PIC_SIDE_LEN]){
    int stageOneX = startX + squareSideLen -1; //represents X value of top right corner
    int stageOneY = startY;
    int stageTwoX = stageOneX;
    int stageTwoY = stageOneY + squareSideLen -1; // represents Y value of bottom right corner
    int stageThreeX = stageTwoX - squareSideLen +1; // represents X value of bottom left corner
    int stageThreeY = stageTwoY;

    drawLine(startX,startY,stageOneX,stageOneY,data);
    drawLine(stageOneX,stageOneY,stageTwoX,stageTwoY,data);
    drawLine(stageTwoX,stageTwoY,stageThreeX,stageThreeY,data);
    drawLine(stageThreeX,stageThreeY,startX,startY,data);
}
