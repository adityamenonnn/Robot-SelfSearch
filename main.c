#include "graphics.h"
#include "grid.h"
#include "robot.h"
#include "marker.h"
#include "obstacle.h"
#include "layers.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define GRID_SIZE 15


void runcircular() 
{
    int rows = GRID_SIZE;
    int cols = GRID_SIZE;
    
    int tile_size = 50;
    int width = cols * tile_size, height = rows * tile_size;
    setWindowSize(width + 100, height + 100);

    // Boundary obstacles fill area outside octagon
    Obstacle obstacles[MAX_OBSTACLES];
    int numObstacles = 0;
    fillAreaOutsideOctagon(obstacles, &numObstacles, rows, cols);

    // Markers spawn only inside octagonal playable area
    Marker markers[MAX_MARKERS];
    int numMarkers = 0;
    setMarkersRandomPositionInOctagon(markers, &numMarkers, rows, cols);

    // Interior obstacles inside octagon
    placeObstaclesInsideOctagon(obstacles, &numObstacles, rows, cols, markers, numMarkers);

    // Robot starts inside octagon
    Robot robot;
    setRobotRandomPositionInOctagon(&robot, rows, cols, markers, numMarkers, obstacles, numObstacles);

    clear();
    drawBackgroundLayer(rows, cols, obstacles, numObstacles, markers, numMarkers);
    drawForegroundLayer(&robot, rows, cols);
    sleep(500);

    // Collect ALL markers, avoid ALL obstacles, drop at center
    animateRobotPickupAndDropDFS(&robot, markers, numMarkers, obstacles, numObstacles, rows, cols);

    sleep(2000);
}


int main() 
{
    srand((unsigned int)time(NULL));
    
    setWindowSize(500, 300);
    clear();
    drawString("Welcome", 50, 50);
    drawString("This is the STAGE 5 - Circular Arena", 50, 80);
    sleep(2000);
    runcircular();

    return 0;
}