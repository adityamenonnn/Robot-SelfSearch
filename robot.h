#ifndef ROBOT_H
#define ROBOT_H
#include "marker.h"
#include "obstacle.h"

typedef struct {
    int row;
    int col;
    int angle;
    int markersHeld;
} Robot;

void drawRobot(int row, int col, int angle, int rows, int cols);
void setRobotRandomPositionInOctagon(Robot *robot, int rows, int cols, const Marker *markers, int numMarkers, const Obstacle *obstacles, int numObstacles);
void forward(Robot *robot, int rows, int cols, const Obstacle *obstacles, int numObstacles);
void left(Robot *robot);
void right(Robot *robot);
int canMoveForward(const Robot *robot, int rows, int cols, const Obstacle *obstacles, int numObstacles);
void pickUpMarker(Robot *robot, Marker *markers, int numMarkers);
void dropMarker(Robot *robot, Marker *marker);
int markerCount(const Robot *robot);
int atMarker(const Robot *robot, const Marker *markers, int numMarkers);
void animateRobotPickupAndDropDFS(Robot *robot, Marker *markers, int numMarkers, const Obstacle *obstacles, int numObstacles, int rows, int cols);

//-------STAGE 2,3,4-------//
void setRobotRandomPosition(Robot *robot, int rows, int cols, const Marker *markers, int numMarkers, const Obstacle *obstacles, int numObstacles);
int findNearestMarker(const Robot *robot, const Marker *markers, int numMarkers); //Not used as we expelore blindly

#endif