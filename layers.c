#include "layers.h"
#include "graphics.h"
#include "grid.h"

//Background layer: grid, obstacles, markers
//Foreground layer: robot

void drawBackgroundLayer(int rows, int cols, const Obstacle *obstacles, int numObstacles, const Marker *markers, int numMarkers) 
{
    drawGrid(rows, cols);
    drawObstacles(obstacles, numObstacles, rows, cols);
    drawMarkers(markers, numMarkers, rows, cols);
}

void drawForegroundLayer(const Robot *robot, int rows, int cols) 
{
    drawRobot(robot->row, robot->col, robot->angle, rows, cols);
}
