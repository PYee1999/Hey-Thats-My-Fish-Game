# Hey-Thats-My-Fish-Game
CS 250 Project #1
Preston Yee

The Game begins by letting the Player choose a spot, as long as that spot contains only 1 point. The AI is given only two possible, fixed positions on the game to begin, depending on where the Player is located.

Player Moves are checked to make sure that they are valid (Straight line, no interference of '.' or 'A'). If that is the case, then the Player makes that move, occupying the coordinate and leaving its original coordinate with a '.'. Points will be accumulated into a global array. Otherwise, the player will be notified to input another coordinate.  The Player's current (x, y) coordinates and points allocation are in global arrays.

AI is designed so that it will identify all of the possible moves it can make, and how many points it can possible earn for every move available. The AI's algorithm will then determine which direction will yield the largest point possible, make that move,  occupy the new coordinate and leave its original coordinate with a '.'. The AI's points will also be cumulated in an array. The AI's current (x, y) coordinates and points allocation are also stored in global arrays.

At the end of the game, points are totaled up and compared to see who wins.

Video Link: https://www.youtube.com/watch?v=3TPhla6TlXY
