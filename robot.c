#include "robot.h"
#include "graphics.h"
#include "grid.h"
#include "marker.h"
#include "obstacle.h"
#include "layers.h"
#include <stdlib.h>
#include <math.h>

//compares robot pos with marker pos
int atMarker(const Robot *robot, const Marker *markers, int numMarkers) 
{
    for (int i = 0; i < numMarkers; i++) 
    {
        if (markers[i].alive && robot->row == markers[i].row && robot->col == markers[i].col) 
            return 1;
    }
    return 0;
}

//ChatGPT drawn robot as triangle
void drawRobot(int row, int col, int angle, int rows, int cols) 
{
    int cx, cy;
    getTileCenter(row, col, &cx, &cy, rows, cols);
    int sz = 20, px[3], py[3];
    for (int i = 0; i < 3; i++) 
    {
        double theta = (angle - i * 120) * M_PI / 180.0;
        px[i] = cx + (int)(sz * cos(theta));
        py[i] = cy + (int)(sz * sin(theta));
    }
    setColour(blue);
    fillPolygon(3, px, py);
}

// Place robot randomly only inside octagon
void setRobotRandomPositionInOctagon(Robot *robot, int rows, int cols, const Marker *markers, int numMarkers, const Obstacle *obstacles, int numObstacles) 
{
    while (1) 
    {
        //avoid edges next to the wall
        robot->row = 1 + rand() % (rows - 2); 
        robot->col = 1 + rand() % (cols - 2);
        
        // Must be inside octagon
        if (!isInsideOctagon(robot->row, robot->col, rows, cols))
            continue;
        
        //Checking if overlapping w markr/obs
        int overlap = 0;
        if (atMarker(robot, markers, numMarkers))
            overlap = 1;
        for (int i = 0; i < numObstacles; i++)
            if (obstacles[i].row == robot->row && obstacles[i].col == robot->col)
                overlap = 1;
        if (!overlap) 
        {
            //randomizing angle that is starts from
            int angles[4] = {0, 90, 180, 270};
            robot->angle = angles[rand() % 4];
            robot->markersHeld = 0;
            break;
        }
    }
}

void forward(Robot *robot, int rows, int cols, const Obstacle *obstacles, int numObstacles) 
{
    if (!canMoveForward(robot, rows, cols, obstacles, numObstacles)) return;
    if (robot->angle == 0)      robot->col++;
    else if (robot->angle == 90)  robot->row++;
    else if (robot->angle == 180) robot->col--;
    else if (robot->angle == 270) robot->row--;
}

void left(Robot *robot) 
{ 
    robot->angle = (robot->angle + 270) % 360;
}

void right(Robot *robot) 
{
     robot->angle = (robot->angle + 90) % 360; 
}

int canMoveForward(const Robot *robot, int rows, int cols, const Obstacle *obstacles, int numObstacles) 
{
    //Copy current pos
    int newrow = robot->row;
    int newcol = robot->col;
    
    //0=Right... Must inc col
    if (robot->angle == 0) newcol++;
    //90=Down... Must inc row
    else if (robot->angle == 90) newrow++;
    //180=Left... Must dec col
    else if (robot->angle == 180) newcol--;
    //270=Up... Must dec row
    else if (robot->angle == 270) newrow--;

    //Checking if it is out of bound
    if (newrow < 0 || newrow >= rows || newcol < 0 || newcol >= cols)
        return 0;
    //Checking if next pos has obstacle on it (must be blocked from movement)
    for (int i = 0; i < numObstacles; i++)
        if (newrow == obstacles[i].row && newcol == obstacles[i].col)
            return 0;
    return 1;
}

void pickUpMarker(Robot *robot, Marker *markers, int numMarkers) 
{
    if (atMarker(robot, markers, numMarkers)) 
    {
        for (int i = 0; i < numMarkers; i++) 
        {
            if (markers[i].alive && robot->row == markers[i].row && robot->col == markers[i].col) 
            {
                //Removing marker frm grid and inc robot's marker count
                robot->markersHeld++;
                markers[i].alive = 0;
            }
        }
    }
}

//Only called when robot reaches the center of the octagon
void dropMarker(Robot *robot, Marker *marker) 
{
    if (robot->markersHeld > 0) 
    {
        robot->markersHeld--;
        marker->row = robot->row;
        marker->col = robot->col;
        marker->alive = 1;
    }
}

int markerCount(const Robot *robot) 
{ 
    return robot->markersHeld; 
}

// Gets next position based on direction
static void getNextPosition(int direction, int curr_row, int curr_col, int *next_row, int *next_col)
{
    *next_row = curr_row;
    *next_col = curr_col;
    
    if (direction == 0) (*next_col)++;           // Right
    else if (direction == 90) (*next_row)++;      // Down
    else if (direction == 180) (*next_col)--;     // Left
    else if (direction == 270) (*next_row)--;     // Up
}

// ChecksValidity of future move
static int Viable(int row, int col, int rows, int cols, 
                       const Obstacle *obstacles, int numObstacles)
{
    // Check bounds
    if (row < 0 || row >= rows || col < 0 || col >= cols)
        return 0;
    
    // Check obstacles
    for (int i = 0; i < numObstacles; i++)
        if (row == obstacles[i].row && col == obstacles[i].col)
            return 0;
    
    return 1;
}

//  DFS 
static int dfsMove(Robot *robot, int goal_row, int goal_col, int rows, int cols,
                   const Obstacle *obstacles, int numObstacles, int **visited,
                   Marker *markers, int numMarkers) 
{
    clear();

    drawBackgroundLayer(rows, cols, obstacles, numObstacles, markers, numMarkers);
    drawForegroundLayer(robot, rows, cols);
    sleep(60);

    // If robot spawns at marker---> NOT POSSIBLE IN TESTS, BUT JUST IN CASE
    pickUpMarker(robot, markers, numMarkers);

    if (robot->row == goal_row && robot->col == goal_col) 
    {
        return 1;
    }
    
    visited[robot->row][robot->col] = 1;

    // Try all 4 directions without modifying robot state initially
    int directions[4] = {0, 90, 180, 270};
    
    for (int d = 0; d < 4; d++) 
    {
        int direction = directions[d];
        int nrow, ncol;
        
        // Calculate next position
        getNextPosition(direction, robot->row, robot->col, &nrow, &ncol);
        
        // Check if move is Viable and not visited
        if (Viable(nrow, ncol, rows, cols, obstacles, numObstacles) && 
            !visited[nrow][ncol])
        {
            // proper facing
            while (robot->angle != direction)
                right(robot);
            
            
            forward(robot, rows, cols, obstacles, numObstacles);
            
            // Recursive DFS call
            if (dfsMove(robot, goal_row, goal_col, rows, cols,
                        obstacles, numObstacles,
                        visited, markers, numMarkers))
                return 1;
            
            // -----Backtracking steps-----
            // Turn around 180 degrees
            right(robot);
            right(robot);
            
            // Move back to previous position
            forward(robot, rows, cols, obstacles, numObstacles);
            
            // Turn back to original direction
            right(robot);
            right(robot);
            
            // Unmark current cell so other paths can explore it
            visited[robot->row][robot->col] = 0;
        }
    }
    
    return 0;
}

void animateRobotPickupAndDropDFS(Robot *robot, Marker *markers, int numMarkers, 
                                 const Obstacle *obstacles, int numObstacles,
                                 int rows, int cols) 
{
    
    int totalMarkers = numMarkers;
    int done = 0;
    
    // Robot is UNAWARE about marker location
    for (int row = 0; row < rows && !done; row++) 
    {
        for (int col = 0; col < cols && !done; col++) 
        {
            
            // Skip tiles outside the octagon
            if (!isInsideOctagon(row, col, rows, cols))
                continue;
            
            // Count how many markers have been picked up so far
            int collected = 0;
            for (int i = 0; i < numMarkers; i++) 
            {
                if (!markers[i].alive) 
                {
                    collected++;
                }
            }
            
            // If all markers collected, exit exploration
            if (collected == totalMarkers) 
            {
                done = 1;
                break;
            }
            
            // Create fresh visited array for pathfinding to this tile
            int **explored = malloc(rows * sizeof(int*));
            for (int x = 0; x < rows; x++) 
                explored[x] = calloc(cols, sizeof(int));
            
            // Use DFS to navigate to this tile
            // If marker is here, it will be picked up automatically
            dfsMove(robot, row, col, rows, cols, obstacles, numObstacles, 
                    explored, markers, numMarkers);
            
            // Free allocated memory
            for (int x = 0; x < rows; x++) 
                free(explored[x]);
            free(explored);
        }
    }
    
    // All markers collected, now navigate to center to drop them
    int centerRow, centerCol;
    findCenter(robot->row, robot->col, rows, cols, &centerRow, &centerCol);

    // Create visited array for path to center
    int **visited = malloc(rows * sizeof(int*));
    for (int row = 0; row < rows; row++) 
        visited[row] = calloc(cols, sizeof(int));

    // Navigate to center using DFS
    dfsMove(robot, centerRow, centerCol, rows, cols,
            obstacles, numObstacles, visited, markers, numMarkers);

    // Drop all collected markers at the center
    for (int i = 0; i < numMarkers; i++) {
        if (!markers[i].alive) {
            dropMarker(robot, &markers[i]);
        }
    }

    // Free allocated memory
    for (int row = 0; row < rows; row++) 
        free(visited[row]);
    free(visited);

    // Display final state with all markers dropped
    clear();
    drawBackgroundLayer(rows, cols, obstacles, numObstacles, markers, numMarkers);
    drawForegroundLayer(robot, rows, cols);
}

//-------STAGE 2,3,4-------//

void setRobotRandomPosition(Robot *robot, int rows, int cols, const Marker *markers, int numMarkers, const Obstacle *obstacles, int numObstacles)
{
    while (1) {
        robot->row = 1 + rand() % (rows - 2);
        robot->col = 1 + rand() % (cols - 2);
        int clash = 0;
        if (atMarker(robot, markers, numMarkers))
            clash = 1;
        for (int i = 0; i < numObstacles; i++)
            if (obstacles[i].row == robot->row && obstacles[i].col == robot->col)
                clash = 1;
        if (!clash) {
            int angles[4] = {0, 90, 180, 270};
            robot->angle = angles[rand() % 4];
            robot->markersHeld = 0;
            break;
        }
    }
}

//Manhattan distance to find nearest marker
//NOT USED----> Used when the robot is aware of marker locations
int findNearestMarker(const Robot *robot, const Marker *markers, int numMarkers) 
{
    int min_dist = 6767;
    int nearest = -1; //Distance is non negative usuall-- -1 means no markr
    for (int i = 0; i < numMarkers; i++) 
    {
        if (markers[i].alive) 
        {
            int d = abs(robot->row - markers[i].row) + abs(robot->col - markers[i].col);
            if (d < min_dist) { min_dist = d; nearest = i; }
        }
    }
    return nearest;
}