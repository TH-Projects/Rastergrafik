#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "macros.h"



void initData(char data[PIC_SIDE_LEN][PIC_SIDE_LEN]);
void drawSquare(int startX, int startY,int squareSideLen,char data[PIC_SIDE_LEN][PIC_SIDE_LEN]);
void calcSquareStartPositions(int squareStartPoints[], float matchingSideLen[]);
void calcSideLen(int picSize, float matchingSideLen[FIGURE_DEPTH]);
int createPPM( char data[PIC_SIDE_LEN][PIC_SIDE_LEN]);
/*
 *
 */
int main(int argc, char** argv){
    char data[PIC_SIDE_LEN][PIC_SIDE_LEN];
    int squareStartPoints[FIGURE_DEPTH];
    float matchingSideLen[FIGURE_DEPTH];
    calcSideLen(PIC_SIDE_LEN, matchingSideLen);
    calcSquareStartPositions(squareStartPoints,matchingSideLen);
    initData(data);
    for (int i = 0; i < FIGURE_DEPTH; ++i) {
        drawSquare((int)squareStartPoints[i],(int)squareStartPoints[i],matchingSideLen[i],data);
    }
    createPPM(data);
    return (EXIT_SUCCESS);
}

void initData(char data[PIC_SIDE_LEN][PIC_SIDE_LEN]){
    for (int i = 0; i < PIC_SIDE_LEN; ++i) {
        for (int j = 0; j < PIC_SIDE_LEN; ++j) {
            data[j][i] = ' ';
        }
    }
}

void calcSideLen(int picSize, float matchingSideLen[FIGURE_DEPTH]){
    float nextSideLen = (float)picSize;
    for (int i = 0; i < FIGURE_DEPTH; ++i) {
        matchingSideLen[i] = nextSideLen;
        nextSideLen = nextSideLen / 2;
    }
}

void calcSquareStartPositions(int squareStartPoints[FIGURE_DEPTH], float matchingSideLen[FIGURE_DEPTH]){
    /*  the distance on the diagonal to the next square is a quarter
     *  of the side length of the square before.
     *  Only one coordinate per point is needed due to their position on the diagonal
     */
    int nextStart = 0;
    for (int i = 0; i < FIGURE_DEPTH; i++) {
        if(i == 0){
            squareStartPoints[i] = 0; //drawing border square
            nextStart = round(matchingSideLen[i] /4);
        }else{
            squareStartPoints[i] = nextStart;
            nextStart = nextStart + round(matchingSideLen[i] / 4);
        }
    }
}

int createPPM( char data[PIC_SIDE_LEN][PIC_SIDE_LEN])
{
    FILE *p_file = fopen(FILENAME,"w");
    if (NULL != p_file)
    {
        fprintf (p_file, "P3\n %d %d\n 255\n", PIC_SIDE_LEN, PIC_SIDE_LEN);
        for(int i = 0 ; i < PIC_SIDE_LEN ; i++){
            for(int j = 0 ; j < PIC_SIDE_LEN ; j++){
                if(data[j][i] != ' ') fprintf(p_file," 255 255 255 ");
                else fprintf(p_file," 255 128 0 ");
            }
            fprintf(p_file,"\n");
        }
        fclose(p_file);
    }
}