#include "MazeGenerator.h"
#include "Utility.h"

// Get adjacent tiles that are 2 tiles away, does not matter if they're walls
// 2 Tiles away because 1 tile away represents the walls of the maze
std::vector<std::pair<int, int>> MazeGenerator::getMazeNeighbors(Grid &grid, int xPos, int yPos) {
    std::vector<std::pair<int, int>> result;
    for (int x = -2; x <= 2; x += 2) {
        for (int y = -2; y <= 2; y += 2) {
            if (std::abs(x) == std::abs(y)) continue;
            if (x + xPos < 0 || y + yPos < 0 || x + xPos >= grid.getWidth() || y + yPos >= grid.getHeight()) continue;
            //if (visited[y + yPos][x + xPos] == true) continue;
            result.push_back(std::make_pair(x + xPos, y + yPos));
        }
    }
    return result;
}
std::vector<std::pair<int, int>> MazeGenerator::getMazeNeighbors(Grid &grid, std::pair<int, int> vertex) {
    return getMazeNeighbors(grid, vertex.first, vertex.second);
}

// Generate a maze using a randomized prim's algorithm, each step is animated
void MazeGenerator::generateAnimated(sf::RenderWindow *window, Grid &grid, int msDelay, int size, int xOffset, int yOffset) {
    int height = grid.getHeight();
    int width = grid.getWidth();

    bool **visited = new bool*[height];

    // fill the grid up with walls
    for (int y = 0; y < height; ++y) {
        visited[y] = new bool[width];
        for (int x = 0; x < width; ++x) {
            grid.getTileAt(x, y).setWall(true);
            visited[y][x] = false;
        }
    }

    // randomized prim's algorithm
    std::vector<std::pair<int, int>> frontier;
    // choose a random cell, mark it as visited, and add it to the vector
    int randX = rand() % width;
    int randY = rand() % height;
    std::pair<int, int> cell = std::make_pair(randX, randY);
    frontier.push_back(cell);

    // while there are cells on the vector
    while (!frontier.empty()) {

        // pick a cell off the vector (a random cell)
        std::random_shuffle(frontier.begin(), frontier.end());
        cell = frontier.back();
        frontier.pop_back();
        int x = cell.first;
        int y = cell.second;
        if (visited[y][x]) continue;
        grid.getTileAt(x, y).setWall(false); // hard to explain, but necessary

                                        // add its neighbors to the vector
        bool wallDowned = false; // keeps track of whether a wall has been knocked down
        std::vector<std::pair<int, int>> neighbors = getMazeNeighbors(grid, cell);
        std::random_shuffle(neighbors.begin(), neighbors.end()); // I want a random neighbor
        for (auto it = neighbors.begin(), end = neighbors.end(); it != end; ++it) {
            int neighX = it->first;
            int neighY = it->second;

            if (visited[neighY][neighX]) { // only knocks down a wall if it's connected to a visited cell (makes the maze have a sol.)
                if (!wallDowned) { // only want to knock down 1 wall
                    Tile &tileInBetween = grid.getTileAt(((x + neighX) / 2), ((y + neighY) / 2));
                    // knock down a wall between it and a neighbor
                    tileInBetween.setWall(false);
                    wallDowned = true;
                }
            } else frontier.push_back(*it); // add its unvisited neighbors to the frontier
        }
        std::unique(frontier.begin(), frontier.end()); // removes duplicates

                                                        // mark that cell visited
        visited[y][x] = true;
        std::vector<sf::RectangleShape> tiles = gridToRects(&grid, size, xOffset, yOffset);

        if (window == nullptr) continue;

        drawRects(*window, tiles);
        window->display();
        sf::sleep(sf::milliseconds(msDelay));
    }

    // Set the source and destination from the top left to bottom right
    // This is complicated due to random selection as I must prevent the source and dest from being placed on a wall
    int evenRandX = (randX % 2 == 0) ? 1 : 0;
    int evenRandY = (randY % 2 == 0) ? 1 : 0;

    grid.setSource(1 - evenRandX, 1 - evenRandY); // index 0 if even, index 1 if odd

    int destX = width - 1;
    int destY = height - 1;
    if (width % 2 == 0) destX -= evenRandX;
    if (height % 2 == 0) destY -= evenRandY;
    grid.setDest(destX, destY);

    // free
    for (int y = 0; y < height; ++y) {
        delete[] visited[y];
    }
    delete visited;
}

// Generate a maze using a randomized prim's algorithm, no animation
void MazeGenerator::generate(Grid& grid) {
    generateAnimated((sf::RenderWindow*)nullptr, grid, 0, 0, 0, 0);
}