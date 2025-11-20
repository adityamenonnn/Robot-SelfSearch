#include "marker.h"
#include "graphics.h"
#include "grid.h"
#include <stdlib.h>


void drawMarkers(const Marker *markers, int numMarkers, int rows, int cols) 
{
    for (int i = 0; i < numMarkers; i++) 
    {
        if (markers[i].alive) 
        {
            int cx, cy;
            getTileCenter(markers[i].row, markers[i].col, &cx, &cy, rows, cols);
            setColour(darkgray);
            fillOval(cx-11, cy-11, 22, 22);
        }
    }
}


// Place markers randomly only inside playable octagonal area
void setMarkersRandomPositionInOctagon(Marker *markers, int *numMarkers, int rows, int cols) 
{
    *numMarkers = 2 + rand() % 4; // Min 2, max 5 markers
    int placed = 0;
    
    for (int i = 0; i < *numMarkers; i++) 
    {
        int valid = 1;  // Start as valid
        while (valid) 
        {
            markers[placed].row = rand() % rows;
            markers[placed].col = rand() % cols;

            // Only place inside octagon
            if (!isInsideOctagon(markers[placed].row, markers[placed].col, rows, cols)) {
                valid = 1;  // Keep trying
                continue;
            }
          
            // Not overlapping previous markers
            valid = 1;
            for (int j = 0; j < placed; j++) {
                if (markers[j].row == markers[placed].row && markers[j].col == markers[placed].col) {
                    valid = 1;  // Keep trying
                    break;
                }
            }

            if (valid) {
                markers[placed].alive = 1;
                placed++;
                valid = 0;  //Leave loop
            }
        }
    }
    
    *numMarkers = placed;
}

// For drop location: find closest corner (or center for octagon)
void findCenter(int from_row, int from_col, int rows, int cols, int *corner_row, int *corner_col) 
{
    // For octagon, drop at center
    *corner_row = rows / 2;
    *corner_col = cols / 2;
}


//-------STAGE 2,3,4-------//

// Fill array with random markers, never in corners, never overlapping
void setMarkersRandomPosition(Marker *markers, int *numMarkers, int rows, int cols)
{
    *numMarkers = 2 + rand() % 4;
    for (int i = 0; i < *numMarkers; i++) 
    {
        int valid = 0;
        while (!valid) 
        {
            markers[i].row = rand() % rows;
            markers[i].col = rand() % cols;

            if ((markers[i].row == 0 || markers[i].row == rows-1) &&
                (markers[i].col == 0 || markers[i].col == cols-1)) continue;
          
            valid = 1;
            for (int j = 0; j < i; j++)
                if (markers[j].row == markers[i].row && markers[j].col == markers[i].col)
                    valid = 0;

            markers[i].alive = valid;
        }
    }
}
// Find nearest corner for stage 4
void NearestCorner(int from_row, int from_col, int rows, int cols, int *corner_row, int *corner_col) 
{
   int corners[4][2] = { {0,0},{0,cols-1},{rows-1,0},{rows-1,cols-1} };
   int min_dist = rows + cols, best = 0;
   for (int i = 0; i < 4; i++) 
   {
       int d = abs(from_row - corners[i][0]) + abs(from_col - corners[i][1]);
       if (d < min_dist) { min_dist = d; best = i; }
   }
   *corner_row = corners[best][0];
   *corner_col = corners[best][1];
}




