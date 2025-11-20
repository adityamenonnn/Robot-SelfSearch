#include "graphics.h"
#include "grid.h"
#include <stdlib.h>
#include <math.h>

// Draw grid os each tile size of 50x50
void drawGrid(int rows, int cols) {
    int x = 50; 
    int y = 50;
    int tile_size = 50;
    int width = cols * tile_size, height = rows * tile_size;
    setColour(red);

    //DARK RED BORDER
    drawRect(x + 1, y + 1, width - 2, height - 2);
    drawRect(x + 2, y + 2, width - 4, height - 4);
    drawRect(x, y, width, height);

    setColour(black);
    for (int c = 1; c < cols; c++)
        drawLine(x + c * tile_size, y, x + c * tile_size, y + height);
    for (int r = 1; r < rows; r++)
        drawLine(x, y + r * tile_size, x + width, y + r * tile_size);
}
// Used to place robot & markers in the center of a tile
void getTileCenter(int row, int col, int *center_x, int *center_y, int rows, int cols) {
    int tile_size = 50, x = 50, y = 50;
    *center_x = x + col * tile_size + tile_size / 2;
    *center_y = y + row * tile_size + tile_size / 2;
}

// Check if tile is inside octagonal playable area 
int isInsideOctagon(int row, int col, int rows, int cols) 
{
    // Center of the grid --> (7,7) for 15x15
    int centerRow = rows / 2; 
    int centerCol = cols / 2;
    
    int distRow = abs(row - centerRow);
    int distCol = abs(col - centerCol);
    
    int maxDist;
    if (rows < cols) 
    {
        maxDist = rows / 2 - 2;
    } 
    else 
    {
        maxDist = cols / 2 - 2;
    }
    int cutSize = maxDist / 3;
    
    if (distRow > maxDist || distCol > maxDist)
        return 0;
    
    if (distRow + distCol > maxDist + cutSize)
        return 0;
    
    return 1;
}