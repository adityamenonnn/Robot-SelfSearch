#include "graphics.h"
#include <math.h>

// Returns 1 if (row, col) is inside the central circular region
int isInCircle(int row, int col, int center_row, int center_col, int radius) {
    int dx = row - center_row;
    int dy = col - center_col;
    return dx * dx + dy * dy <= radius * radius;
}

// Draws a grid, with obstacles outside a center circle of specified radius
void drawCircularArena(int rows, int cols, int tile_size, int playable_radius) {
    int win_width = cols * tile_size + 40;
    int win_height = rows * tile_size + 40;
    setWindowSize(win_width, win_height);

    int start_x = 20, start_y = 20;
    int center_row = rows / 2;
    int center_col = cols / 2;

    // Draw thick red boundary rectangle
    setColour(red);
    drawRect(start_x - 5, start_y - 5, cols * tile_size + 10, rows * tile_size + 10);

    // Draw grid squares and obstacles
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int x = start_x + c * tile_size;
            int y = start_y + r * tile_size;
            setColour(black);
            drawRect(x, y, tile_size, tile_size); // grid
            if (!isInCircle(r, c, center_row, center_col, playable_radius)) {
                setColour(black);
                fillRect(x + 2, y + 2, tile_size - 4, tile_size - 4); // obstacle
            }
        }
    }
}

