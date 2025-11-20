---------Description--------- 
In this program, a triangular robot searches the octagonal(circular) region to collect markers while avoiding obstacles. The robot searches the arena with the Depth-First-Search algoirhtm and picks up any and all markers it encounters. At the end, to display knowledge of Stage 4 of the coursework, it navigated to the center of the grid and then drops it.

---------Features of the project--------- 
-15x15 grid with red outer border.
-Boundary is filled by obstacles to create a octagonal playable region. 
-Obstacles and markers are randomly placed within the octagonal playable region.
-Robot searches for the markers in stage 5 WITHOUT the knowledge of the marker location. 
-DFS Pathfinding. 
-Collection and dropoff of markers.

---------Running and compiling the program--------- 
gcc -o C_Coursework main.c grid.c robot.c marker.c obstacle.c layers.c graphics.c -lm ./C_Coursework | java -jar drawapp-4.5.jar

---------Plagiarism--------- 
-Deciding whether to use DFS or BFS - https://stackoverflow.com/questions/20192445/which-procedure-we-can-use-for-maze-exploration-bfs-or-dfs

-AI also helped me decide how to use helper functinons in the DFS code

Sonnet-4.5 code

void drawRobot(int row, int col, int angle, int rows, int cols) { int cx, cy; getTileCenter(row, col, &cx, &cy, rows, cols); int sz = 20, px[3], py[3]; for (int i = 0; i < 3; i++) { double theta = (angle - i * 120) * M_PI / 180.0; px[i] = cx + (int)(sz * cos(theta)); py[i] = cy + (int)(sz * sin(theta)); } setColour(blue); fillPolygon(3, px, py); }

int isInsideOctagon(int row, int col, int rows, int cols) // LLM Generated Code { int centerRow = rows / 2; int centerCol = cols / 2; int distRow = abs(row - centerRow); int distCol = abs(col - centerCol); int maxDist; if (rows < cols) {maxDist = rows / 2 - 2;} else {maxDist = cols / 2 - 2;} int cutSize = maxDist / 3; if (distRow > maxDist || distCol > maxDist) return 0; if (distRow + distCol > maxDist + cutSize) return 0; return 1; }
