#ifndef MARKER_H
#define MARKER_H

#define MAX_MARKERS 10

typedef struct {
    int row;
    int col;
    int alive;
} Marker;

void drawMarkers(const Marker *markers, int numMarkers, int rows, int cols);
void setMarkersRandomPositionInOctagon(Marker *markers, int *numMarkers, int rows, int cols);
void findCenter(int from_row, int from_col, int rows, int cols, int *corner_row, int *corner_col);

//-------STAGE 2,3,4-------//
void setMarkersRandomPosition(Marker *markers, int *numMarkers, int rows, int cols);
#endif