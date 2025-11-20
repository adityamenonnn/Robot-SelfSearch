#ifndef LAYERS_H
#define LAYERS_H
#include "marker.h"
#include "obstacle.h"
#include "robot.h"

void drawBackgroundLayer(int rows, int cols, const Obstacle *obstacles, int numObstacles, const Marker *markers, int numMarkers);
void drawForegroundLayer(const Robot *robot, int rows, int cols);

#endif