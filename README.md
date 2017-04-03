# Pathfinder
Use different algorithms to find the shortest path in a 2D grid.  
First time writing search algorithms and using SFML.  
**Now featuring maze generation algorithms**

## Progress
### 4/02/2017
![4-02-2017](http://i.imgur.com/ej4gLVQ.gif)

*Modularized maze generation, pathfinding, tile holding.  
Displays frontier tiles during maze generation steps.  
Displays Dijkstra's search steps*

### 4/01-2017 Midnight
![4-01-2017](http://i.imgur.com/mYr6yua.gif)

*Fixed maze generation algorithm.  
Integrated drawing the maze as it is being created (doing so also created much needed refactoring)  
How do I implement drawing DURING a search while maintaining separation of concerns?*  

### 4/01/2017
![4-01-2017](http://i.imgur.com/56KYgeM.gif)

*Clicking on the tiles will toggle their wall status.*

### 3/31/2017
![3-31-2017](https://i.imgur.com/LdGksmq.png)

*Given a tile map, Pathfinder finds the shortest path using Dijkstra's algorithm.  
Features the ability to generate a random maze using Prim's algorithm.  
Edit: Maze generation was broken in this (now fixed)
*

### 3/30/2017
![3-30-2017](https://i.imgur.com/52r6UpR.png)

*SFML works!  
Can generate a random tile map (completely random, no path, no source/destination, etc.).  
Creates a tile map given an input string.*
