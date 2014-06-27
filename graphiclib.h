/*Daniel Ramos Miola 438340
  Giulianno Raphael Sbrugnera 408093
  Igor Felipe Ferreira Ceridório 408611
  Rafael Paschoal Giordano 408298*/

/* graphiclib.h */

#ifndef __graphiclib_h__
#define __graphiclib_h__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <X11/Xlib.h>

/*Point data structure*/

typedef struct Point{
	float x, y, z;
} point;

/*Color data structure*/

typedef struct RGB {
	float r, g, b;
}RGB;

typedef struct HSV {
	float h, s, v;
}HSV;

/*Objects data structure*/

typedef struct Node{
	point ptList;  //coordinates of the point
	point ptListN; //point normalized
	point ptListD; //point discrete
	struct Node *next;
}node;

typedef node *list;

/*Functions prototypes*/
//void multMatrix(float matrizA[][3], int matrizB[][1], int* matrizC);

int startList(list *p_l);
int emptyList(list *p_l);
void addEndList(list *p_l, point *pt, point *maxXYZ, point *minXYZ, point *viewPortXYZ, int option);
void freeList(list *p_l);
void showList(list *p_l);
void printListBresenham(list *p_l, char *input, point *viewPortXY);

void setUniverse(point *minXYZ, point *maxXYZ, int option);
void getUniverse(point *minXYZ, point *maxXYZ, int option);

void setValues(point *ptOne, point *ptTwo);
void getValues(point *ptOne, point *ptTwo);

void setViewPort(point *viewPortXY);
void getViewPort(point *viewPortXY);

void initMatrix(char *image, point *viewPortXY);

point sruToSrn(point *pt, point *maxXYZ, point *minXYZ, int option);
point srnToSrd(point *ptN, point *viewPortXY);
void getSrn(point *ptOneN, point *ptTwoN, int option);
void getSrd(point *ptOneD, point *ptTwoD);

void drawLine(char *input, point *ptOneD, point *ptTwoD, point *viewPortXY);
void bresenham(char *input, point *ptOneD, point *ptTwoD, point *viewPortXY);

//void translate(list *p_l);
//void rotate(list *p_l);
//void scale(list *p_l);
//void mirror(list *p_l);

void drawWindow(point *viewPortXY);
void drawWindowLine(point *viewPortXY, char *input);

void rgbTohsv(RGB rgb, HSV *hsv);
void hsvTorgb(HSV hsv, RGB *rgb);


#endif /* __graphiclib_h__ */