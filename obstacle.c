#include "obstacle.h"
#include "grid.h"
#include "graphics.h"
#include <stdlib.h>

void drawObstacles(const Obstacle *obs, int numObstacles, int rows, int cols) 
{
    for (int i = 0; i < numObstacles; i++) 
    {
        int cx, cy;
        getTileCenter(obs[i].row, obs[i].col, &cx, &cy, rows, cols);
        setColour(black);
        fillRect(cx-25, cy-25, obs[i].size * 48, obs[i].size * 48); // Each cell is 50x50 with 3 pixel margin so that it looks like a obstacle and not black fill
    }
}


// Fill all area outside octagon with boundary obstacles
void fillAreaOutsideOctagon(Obstacle *obs, int *numObstacles, int rows, int cols) 
{
    int i = 0; //counting no. of obstacles
    
    for (int r = 0; r < rows; r++) 
    {
        for (int c = 0; c < cols; c++) 
        {
            if (!isInsideOctagon(r, c, rows, cols)) 
            {
                if (i < MAX_OBSTACLES) 
                {
                    obs[i].row = r;
                    obs[i].col = c;
                    obs[i].size = 1;
                    i++; 
                }
            }
        }
    }
    
    *numObstacles = i;
}

// Place random obstacles inside octagon
void placeObstaclesInsideOctagon(Obstacle *obs, int *numObstacles, int rows, int cols,
                                const Marker *markers, int numMarkers) {
    
    // Calculate center of octagon
    int centerRow = rows / 2;
    int centerCol = cols / 2;
    
    // Place 4-5 obstacles inside the playable area for more challenge
    int minObstaclesInsideOctagon = 4;
    int numToPlace = minObstaclesInsideOctagon + rand() % 2;
    
    for (int i = 0; i < numToPlace; i++) {
        if (*numObstacles >= MAX_OBSTACLES)
            break;
        
        int valid = 1;
        while (valid) {
            int r = rand() % rows;
            int c = rand() % cols;
            
            // Must be inside octagon
            if (!isInsideOctagon(r, c, rows, cols))
                continue;
            
            // obs must not be at center---> robot drop location
            if (r == centerRow && c == centerCol)
                continue;
            
            // Check if it overlaps with markers
            int overlap = 0;
            for (int m = 0; m < numMarkers; m++) {
                if (markers[m].alive && markers[m].row == r && markers[m].col == c)
                    overlap = 1;
            }            
            for (int o = 0; o < *numObstacles; o++) {
                if (obs[o].row == r && obs[o].col == c)
                    overlap = 1;
            }
            
            // If no overlap, place obstacle
            if (!overlap) {
                obs[*numObstacles].row = r;
                obs[*numObstacles].col = c;
                obs[*numObstacles].size = 1;
                (*numObstacles)++;
                valid = 0;
            }
        }
    }
}



//----------Stage 2,3,4---------//
// Randomly places obstacles, not overlapping markers, not overlapping prior obstacles, not in corners
void placeRandomObstacles(Obstacle *obs, int *numObstacles, int rows, int cols, const Marker *markers, int numMarkers) 
{
    *numObstacles = 2 + rand() % 4;
    for (int i = 0; i < *numObstacles; i++) 
    {
        int valid = 1;
        obs[i].size = 1;
        while (valid) 
        {
            int r = rand() % rows;
            int c = rand() % cols;

            int overlap = 0;
            for (int m = 0; m < numMarkers; m++)
                if (markers[m].alive && markers[m].row == r && markers[m].col == c)
                    overlap = 1;
            if ((r == 0 || r == rows-1) && (c == 0 || c == cols-1)) overlap = 1;
            for (int o = 0; o < i; o++)
                if (obs[o].row == r && obs[o].col == c) overlap = 1;
            if (!overlap) 
            {
                obs[i].row = r;
                obs[i].col = c;
                valid = 0;
            }
        }
    }
}