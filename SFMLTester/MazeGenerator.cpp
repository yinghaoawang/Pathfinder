#include "MazeGenerator.h"
#include "Utility.h"

// Constructor
MazeGenerator::MazeGenerator(Grid *g) {
    grid = g;
    generationFinished = false;

    visited = new bool*[g->getHeight()];
    // fill the grid up with walls
    
    for (int y = 0; y < g->getHeight(); ++y) {
        visited[y] = new bool[g->getWidth()];
        for (int x = 0; x < g->getWidth(); ++x) {
            g->getTileAt(x, y).setWall(true);
            visited[y][x] = false;
        }
    }
    
}

// Destructor
MazeGenerator::~MazeGenerator() {
    for (int y = 0; y < grid->getHeight(); ++y) {
        delete[] visited[y];
    }
    delete visited;
}

bool MazeGenerator::isGenerationFinished() {
    return generationFinished;
}

// Get adjacent tiles that are 2 tiles away, does not matter if they're walls
// 2 Tiles away because 1 tile away represents the walls of the maze
std::vector<std::pair<int, int>> MazeGenerator::getMazeNeighbors(int xPos, int yPos) {
    std::vector<std::pair<int, int>> result;
    for (int x = -2; x <= 2; x += 2) {
        for (int y = -2; y <= 2; y += 2) {
            if (std::abs(x) == std::abs(y)) continue;
            if (x + xPos < 0 || y + yPos < 0 || x + xPos >= grid->getWidth() || y + yPos >= grid->getHeight()) continue;
            //if (visited[y + yPos][x + xPos] == true) continue;
            result.push_back(std::make_pair(x + xPos, y + yPos));
        }
    }
    return result;
}
std::vector<std::pair<int, int>> MazeGenerator::getMazeNeighbors(std::pair<int, int> vertex) {
    return getMazeNeighbors(vertex.first, vertex.second);
}


void MazeGenerator::generateAnimatedStep(sf::RenderWindow *window, int size, int xOffset, int yOffset) {
    std::pair<int, int> cell;
    static int randX = -1;
    static int randY = -1;

    // if the frontier is empty then it must be starting or ending
    if (frontier.empty()) {
        // if the random has not been set then it just starting
        if (randX == -1 || randY == -1) {
            randX = rand() % grid->getWidth();
            randY = rand() % grid->getHeight();
            frontier.push_back(std::make_pair(randX, randY));
        } else if (!generationFinished) { // otherwise it is ending
            int evenRandX = (randX % 2 == 0) ? 1 : 0;
            int evenRandY = (randY % 2 == 0) ? 1 : 0;

            grid->setSource(1 - evenRandX, 1 - evenRandY); // index 0 if even, index 1 if odd

            int destX = grid->getWidth() - 1;
            int destY = grid->getHeight() - 1;
            if (grid->getWidth() % 2 == 0) destX -= evenRandX;
            if (grid->getHeight() % 2 == 0) destY -= evenRandY;
            grid->setDest(destX, destY);
            generationFinished = true;
        }
    }

    if (!frontier.empty()) {
        // pick a cell off the vector (a random cell)
        std::random_shuffle(frontier.begin(), frontier.end());
        cell = frontier.back();
        frontier.pop_back();
        int x = cell.first;
        int y = cell.second;
        if (!visited[y][x]) {
            grid->getTileAt(x, y).setWall(false); // hard to explain, but necessary

            // add its neighbors to the vector
            bool wallDowned = false; // keeps track of whether a wall has been knocked down
            std::vector<std::pair<int, int>> neighbors = getMazeNeighbors(cell);
            std::random_shuffle(neighbors.begin(), neighbors.end()); // I want a random neighbor
            for (auto it = neighbors.begin(), end = neighbors.end(); it != end; ++it) {
                int neighX = it->first;
                int neighY = it->second;

                if (visited[neighY][neighX]) { // only knocks down a wall if it's connected to a visited cell (makes the maze have a sol.)
                    if (!wallDowned) { // only want to knock down 1 wall
                        Tile &tileInBetween = grid->getTileAt(((x + neighX) / 2), ((y + neighY) / 2));
                        // knock down a wall between it and a neighbor
                        tileInBetween.setWall(false);
                        wallDowned = true;
                    }
                } else frontier.push_back(*it); // add its unvisited neighbors to the frontier
            }
            std::unique(frontier.begin(), frontier.end()); // removes duplicates

            // mark that cell visited
            visited[y][x] = true;
        }
    }

    // to draw the maze
    std::vector<sf::RectangleShape> tiles = gridToRects(grid, size, xOffset, yOffset);
    drawRects(*window, tiles);

    std::vector<sf::RectangleShape> frontierTiles = pairsToRects(frontier, size, xOffset, yOffset, sf::Color(100, 20, 20));
    drawRects(*window, frontierTiles);
}

// Generate a maze using a randomized prim's algorithm, no animation
void MazeGenerator::generate() {
    //generateAnimated((sf::RenderWindow*)nullptr, 0, 0, 0, 0);
}