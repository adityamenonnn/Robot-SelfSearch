#ifndef GRID_H
#define GRID_H

void drawGrid(int rows, int cols);
void getTileCenter(int row, int col, int *center_x, int *center_y, int rows, int cols);
int isInsideOctagon(int row, int col, int rows, int cols);

#endif
