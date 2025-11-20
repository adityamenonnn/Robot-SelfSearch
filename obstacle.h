#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "marker.h"
#define MAX_OBSTACLES 150 // Big number to fit array for all boundary obsatcles

typedef struct {
    int row;
    int col;
    int size;
} Obstacle;

void drawObstacles(const Obstacle *obs, int numObstacles, int rows, int cols);
void fillAreaOutsideOctagon(Obstacle *obs, int *numObstacles, int rows, int cols);
void placeObstaclesInsideOctagon(Obstacle *obs, int *numObstacles, int rows, int cols, const Marker *markers, int numMarkers);

//-------STAGE 2,3,4-------//
void placeRandomObstacles(Obstacle *obs, int *numObstacles, int rows, int cols, const Marker *markers, int numMarkers);

#endif