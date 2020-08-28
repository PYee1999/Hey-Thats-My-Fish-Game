/*
Preston Yee
CS 250 Project 01 - Hey, that's my Fish!
01/25/2020
*/

#include <stdlib.h>
#include <stdio.h>

// NEED TO CUMULATE AS AN ARRAY OF 36 (SET ALL VALUES TO -1).
int playerPoints[50];                    // Total points for Player
int playerPointCount = 0;                // Index pointer for Player's score array
int aiPoints[50];                        // Total points for AI
int aiPointCount = 0;                    // Index pointer for AI's score array

int playerCoordinates[2] = { 0, 0 };     // Player's current coordinates
int aiCoordinates[2] = { 0, 0 };         // AI's current coordinates

char board[6][6] = {                     // Game Board comprising of the points
          { '1', '1', '1', '1', '1', '1' },
          { '1', '2', '2', '2', '2', '1' },
          { '1', '2', '3', '3', '2', '1' },
          { '1', '2', '3', '3', '2', '1' },
          { '1', '2', '2', '2', '2', '1' },
          { '1', '1', '1', '1', '1', '1' }
      };

void finalResults(int player[], int ai[])
{
    int playerSum = 0;
    int aiSum = 0;
    
    printf("Player's Score: "); // Print out Player's Cumulated Score
    for (int i = 0; i < 50; i++)
    {
        if (player[i] == -1 || player[i] == 32)  // If there is a -1 found or random number, skip
        {
            continue;
        }
        if (i == playerPointCount - 1)   // At the last number, print "="
        {
            printf("%i = ", player[i]);
        }
        else    // Otherwise, print "+"
        {
            printf("%i + ", player[i]);
        }
        playerSum += playerPoints[i];
    }
    printf("%i\n", playerSum); // Print Player's results
    
    printf("AI's Score:     "); // Print out AI's Cumulated Score
    for (int i = 0; i < 50; i++)
    {
        if (ai[i] == -1)  // If there is a -1 found; break loop
        {
            continue;
        }
        if (i == aiPointCount - 1)   // At the last number, print "="
        {
            printf("%i = ", ai[i]);
        }
        else    // Otherwise, print "+"
        {
            printf("%i + ", ai[i]);
        }
        aiSum += aiPoints[i];
    }
    printf("%i\n", aiSum); // Print AI's results
    
    // Determine the winner
    if (playerSum == aiSum)       // If equal, it is a tie
    {
        printf("IT'S A TIE!\n");
    }
    else if (playerSum > aiSum)   // If Player has more points than AI, Player wins
    {
        printf("YOU WIN!\n");
    }
    else                          // Otherwise, AI wins
    {
        printf("YOU LOSE!\n");
    }
}

// Helper method that checks whether the given coordinate is out of bounds
int outOfBounds(int x, int y)
{
    if (x > 5 || x < 0 || y > 5 || y < 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Helper method to return largest number of out three numbers
int largestNumOfThree(int a, int b, int c)
{
    if (a >= b && a >= c)
    {
        return a;
    }
    else if (b >= a && b >= c)
    {
        return b;
    }
    else
    {
        return c;
    }
}

// Helper method to return largest number of out two numbers
int largestNumOfTwo(int a, int b)
{
    if (a >= b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

// Update board with character given the coordinates (character can be either "P", "A" or ".")
void updateBoard(int x, int y, char object)
{
    board[x][y] = object; // Set the character on the given coordinates of the board
    if (object == 'P') // If the char is the Player ('P'), also update the Player's saved coordinates
    {
        playerCoordinates[0] = x;
        playerCoordinates[1] = y;
    }

    if (object == 'A')  // If the char is the AI ('A'), also update the AI's saved coordinates
    {
        aiCoordinates[0] = x;
        aiCoordinates[1] = y;
    }
}

// Print current layout of the game board
int printBoard()
{
    printf("  X 1 2 3 4 5 6\n");
    printf("Y -------------\n");
    for (int i = 0; i < 6; i++)
    {
        printf("%i | ", i+1);
        for (int j = 0; j < 6; j++)
        {
            printf("%c ", board[j][i]);
        }
        printf("\n");
    }
    return 0;
}

// Helper method to cumulate array of scores for AI, given coordinates of score
void addToAIScore(int x, int y)
{
    char value = board[x][y];
    aiPoints[aiPointCount] = (value - '0');         // Add points to AI's array score
    aiPointCount++;
}

// Helper method to cumulate array of scores for Player, given coordinates of score
void addToPlayerScore(int x, int y)
{
    char value = board[x][y];
    playerPoints[playerPointCount] = (value - '0');     // Add points to Player's array score
    playerPointCount++;
}

// Boolean to check whether there are any moves available for Player to go, given Player's current coordinate
int anyPlayerMovesAvailable()
{
    int xPlayerCoord = playerCoordinates[0];
    int yPlayerCoord = playerCoordinates[1];

    if (xPlayerCoord > 0 && (board[xPlayerCoord-1][yPlayerCoord] != '.' && board[xPlayerCoord-1][yPlayerCoord] != 'A')) // Check if Player's left position is valid
    {
        return 1;
    }
    if (xPlayerCoord < 5 && (board[xPlayerCoord+1][yPlayerCoord] != '.' && board[xPlayerCoord+1][yPlayerCoord] != 'A')) // Check if Player's right position is valid
    {
        return 1;
    }
    if (yPlayerCoord > 0 && (board[xPlayerCoord][yPlayerCoord-1] != '.' && board[xPlayerCoord][yPlayerCoord-1] != 'A')) // Check if Player's up position is valid
    {
        return 1;
    }
    if (yPlayerCoord < 5 && (board[xPlayerCoord][yPlayerCoord+1] != '.' && board[xPlayerCoord][yPlayerCoord+1] != 'A')) // Check if Player's down position is valid
    {
        return 1;
    }
    if (xPlayerCoord > 0 && yPlayerCoord > 0 &&
        (board[xPlayerCoord-1][yPlayerCoord-1] != '.' && board[xPlayerCoord-1][yPlayerCoord-1] != 'A')) // Check if Player's upper-left position is valid
    {
        return 1;
    }
    if (xPlayerCoord > 0 && yPlayerCoord < 5 &&
        (board[xPlayerCoord-1][yPlayerCoord+1] != '.' && board[xPlayerCoord-1][yPlayerCoord+1] != 'A')) // Check if Player's lower-left position is valid
    {
        return 1;
    }
    if (xPlayerCoord < 5 && yPlayerCoord > 0 &&
        (board[xPlayerCoord+1][yPlayerCoord-1] != '.' && board[xPlayerCoord+1][yPlayerCoord-1] != 'A')) // Check if Player's upper-right position is valid
    {
        return 1;
    }
    if (xPlayerCoord < 5 && yPlayerCoord < 5 &&
        (board[xPlayerCoord+1][yPlayerCoord+1] != '.' && board[xPlayerCoord+1][yPlayerCoord+1] != 'A')) // Check if Player's lower-right position is valid
    {
        return 1;
    }

    return 0; // Otherwise, there are no possible ways for player to move; Player is stuck for the rest of the game.
}

// Boolean to check whether there are any moves available for AI to go, given AI's current coordinate
int anyAIMovesAvailable()
{
    int xAICoord = aiCoordinates[0];
    int yAICoord = aiCoordinates[1];

    if (xAICoord > 0 && (board[xAICoord-1][yAICoord] != '.' && board[xAICoord-1][yAICoord] != 'P')) // Check if AI's left position is valid
    {
        return 1;
    }
    if (xAICoord < 5 && (board[xAICoord+1][yAICoord] != '.' && board[xAICoord+1][yAICoord] != 'P')) // Check if AI's right position is valid
    {
        return 1;
    }
    if (yAICoord > 0 && (board[xAICoord][yAICoord-1] != '.' && board[xAICoord][yAICoord-1] != 'P')) // Check if AI's up position is valid
    {
        return 1;
    }
    if (yAICoord < 5 && (board[xAICoord][yAICoord+1] != '.' && board[xAICoord][yAICoord+1] != 'P')) // Check if AI's down position is valid
    {
        return 1;
    }
    if (xAICoord > 0 && yAICoord > 0 &&
        (board[xAICoord-1][yAICoord-1] != '.' && board[xAICoord-1][yAICoord-1] != 'P')) // Check if AI's upper-left position is valid
    {
        return 1;
    }
    if (xAICoord > 0 && yAICoord < 5 &&
        (board[xAICoord-1][yAICoord+1] != '.' && board[xAICoord-1][yAICoord+1] != 'P')) // Check if AI's lower-left position is valid
    {
        return 1;
    }
    if (xAICoord < 5 && yAICoord > 0 &&
        (board[xAICoord+1][yAICoord-1] != '.' && board[xAICoord+1][yAICoord-1] != 'P')) // Check if AI's upper-right position is valid
    {
        return 1;
    }
    if (xAICoord < 5 && yAICoord < 5 &&
        (board[xAICoord+1][yAICoord+1] != '.' && board[xAICoord+1][yAICoord+1] != 'P')) // Check if AI's lower-right position is valid
    {
        return 1;
    }

    return 0; // Otherwise, there are no possible ways for AI to move; AI is stuck for the rest of the game.
}

// Boolean to check whether the xy-coordinate is valid (Does NOT have AI or '.')
int isCoordinateAvailable(int x, int y)
{
    if (board[x][y] == 'A' || board[x][y] == '.')
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/*
    Initialize game by:
    - Setting board to default layout
    - Setting Player and AI's points to 0
    - Setting Player's coordinates by asking player for input
    - Setting AI's coordinates by random
*/
void initBoard()
{
    // Set up Player and AI point list
    for (int i = 0; i < 50; i++)
    {
        playerPoints[i] = -1;
        aiPoints[i] = -1;
    }
    
    playerPointCount = 0;     // Set Player's Points Index Pointer (Counter) to 0
    aiPointCount = 0;         // Set AI's Points Index Pointer (Counter) to 0
    
    printBoard(); // Show Player the board.

    // Set Player's Coordinates by asking Player to input xy-coordinates (Must be in a spot that has 1 point)
    int playerInitX;
    int playerInitY;
    int isPlayerCoordinateValid = 0;
    while (isPlayerCoordinateValid == 0)     // Ask user to input their starting coordinates, and check if they is valid
    {
        printf("Input X-Value and Y-Value for beginning coordinate in Game Board \n(coordinate must have only 1 point): ");
        scanf("%i %i", &playerInitX, &playerInitY);
        
        playerInitX--;
        playerInitY--;
        
        if (outOfBounds(playerInitX, playerInitY) == 1)     // If coordinate is out of bounds, make Player input again
        {
            printf("Not a valid coordinate: Out of bounds\n");
            continue;
        }

        if (board[playerInitX][playerInitY] == '1')         // If coordinate inputted is valid,
        {
            updateBoard(playerInitX, playerInitY, 'P');     // Set player's coordinates in board and break out of loop
            break;
        }
        else                                                // Otherwise, make Player input again
        {
            printf("Not a valid coordinate: Needs to be a coordinate with 1 point (anywhere along the border)\n");
        }
    }

    if (board[5][5] == 'P')     // If bottom right corner is occupied by Player,
    {
        updateBoard(0, 0, 'A'); // Set AI's coordinates to top left
    }
    else
    {
        updateBoard(5, 5, 'A'); // Otherwise, set AI's coordinates to bottom right by default
    }
    
    playerPoints[0] = 1; // Add 1 point to Player's score
    aiPoints[0] = 1;     // Add 1 point to AI's score
    playerPointCount++;  // Increment Player's score index
    aiPointCount++;      // Increment AI's score index
    
    system("clear"); // Clear Console
}

// Player moves - checks to see if the xy-coordinate inputted is valid
int playerMove(int x, int y)
{
    if (outOfBounds(x, y) == 1) // Check whether the coordinate is within the game board (NOT out of bounds)
    {
        printf("Invalid Move: Coordinate is out of bounds of Game Board\n");
        return 0;
    }
    
    if (isCoordinateAvailable(x, y) == 0) // Check whether the coordinate is available (Not occupied with 'A' or '.')
    {
        printf("Invalid Move: Coordinate is not available\n");
        return 0;
    }

    int xCoordDiff = x - playerCoordinates[0];  // Get difference between x-coordinates of current and new locations
    int yCoordDiff = y - playerCoordinates[1];  // Get difference between y-coordinates of current and new locations

    if (xCoordDiff == 0 && yCoordDiff == 0)     // If the differences are both zero, the move is invalid because it is the same position
    {
        printf("Invalid Move: Same Coordinates as current position\n");
        return 0;
    }
    
    int xPointer = playerCoordinates[0];    // Keep track of Player's current x-position
    int yPointer = playerCoordinates[1];    // Keep track of Player's current y-position
    
    int tempXPointer = xPointer; // Create temporary x and y pointers for traversing path to check whether the path is clear/valid
    int tempYPointer = yPointer;
    
    if (abs(xCoordDiff) == abs(yCoordDiff))     // Check whether the coordinate makes a diagonal line
    {
        int delta = abs(xCoordDiff);            // Get absolute value of x (and y) difference (Change in coordinates, since x and y are the same value)
        
        for (int i = 0; i <= delta; i++)        // First check that the path is clear (AI or '.' is not in the line of the diagonal path)
        {
            if (isCoordinateAvailable(tempXPointer, tempYPointer) == 0)     // If path is not clear, move is invalid
            {
                printf("Invalid Move: Not a clear path (Obstracles are in the way)\n");
                return 0;
            }
            
            if (xCoordDiff > 0 && yCoordDiff > 0)        // Diagonal move is right-down
            {
                tempXPointer++;
                tempYPointer++;
            }
            else if (xCoordDiff > 0 && yCoordDiff < 0)   // Diagonal move is right-up
            {
                tempXPointer++;
                tempYPointer--;
            }
            else if (xCoordDiff < 0 && yCoordDiff > 0)   // Diagonal move is left-down
            {
                tempXPointer--;
                tempYPointer++;
            }
            else                                         // Diagonal move is left-up
            {
                tempXPointer--;
                tempYPointer--;
            }
        }
    }
    else if (xCoordDiff == 0 && yCoordDiff != 0) // Check whether the coordinate makes a horizontal line
    {
        int delta = abs(yCoordDiff); // Get absolute value of x (and y) difference (Change in coordinates, since x and y are the same value)
        
        for (int i = 0; i <= delta; i++) // First check that the path is clear (AI or '.' is not in the line of the diagonal path)
        {
            if (isCoordinateAvailable(tempXPointer, tempYPointer) == 0)     // If path is not clear, move is invalid
            {
                printf("Invalid Move: Not a clear path (Obstracles are in the way)\n");
                return 0;
            }
            
            if (yCoordDiff > 0)
            {
                tempYPointer++;
            }
            else
            {
                tempYPointer--;
            }
        }
    }
    else if (xCoordDiff != 0 && yCoordDiff == 0) // Check whether the coordinate makes a vertical line
    {
        int delta = abs(xCoordDiff); // Get absolute value of x (and y) difference (Change in coordinates, since x and y are the same value)
        
        for (int i = 0; i <= delta; i++) // First check that the path is clear (AI or '.' is not in the line of the diagonal path)
        {
            if (isCoordinateAvailable(tempXPointer, tempYPointer) == 0)     // If path is not clear, move is invalid
            {
                printf("Invalid Move: Not a clear path (Obstracles are in the way)\n");
                return 0;
            }
            
            if (xCoordDiff > 0)
            {
                tempXPointer++;
            }
            else
            {
                tempXPointer--;
            }
        }
    }
    else // Otherwise, the move is invalid because it doesn't make a straight line
    {
        printf("Invalid Move: Coordinate doesn't create a straight line - Must be vertical, horizontal or diagonal\n");
        return 0;
    }
    
    updateBoard(playerCoordinates[0], playerCoordinates[1], '.'); // Replace Player's original spot with '.'
    addToPlayerScore(x, y); // Add point to player's score
    updateBoard(x, y, 'P'); // If all of the three checks pass and points have been cumulated, move player to the coordinate
    
    return 1;
}

// Helper method that returns the largest point possible for given movement for AI
int aiLargestPoint(int horizontalIncrement, int verticalIncrement, int xAIPointer, int yAIPointer)
{
    int largestPoint = 0;
    int validMove = 1;
    while (validMove == 1)
    {
        // Move 1 unit (up, down, left, right, upleft, upright, downleft, downright)
        xAIPointer = xAIPointer + horizontalIncrement;
        yAIPointer = yAIPointer + verticalIncrement;

        // If new location is valid and available,
        if (outOfBounds(xAIPointer, yAIPointer) == 0 && (board[xAIPointer][yAIPointer] != '.' && board[xAIPointer][yAIPointer] != 'P'))
        {
            
            char value = board[xAIPointer][yAIPointer];
            int valueInt = (value - '0');
            if (valueInt > largestPoint)
            {
                largestPoint = valueInt;   // If value is larger than saved value, update
            }
        }
        else // Otherwise, get out of the loop
        {
            validMove = 0;
        }
    }

    return largestPoint;
}

// Helper method that moves AI's position, given direction, current position and largest point
int moveAIOnBoard(int horizontalIncrement, int verticalIncrement, int xAIPointer, int yAIPointer, int largestPoint)
{
    updateBoard(xAIPointer, yAIPointer, '.'); // Replace AI's current position with '.'

    int validMove = 1;
    while (validMove == 1)
    {
        // Move 1 unit (up, down, left, right, upleft, upright, downleft, downright)
        xAIPointer = xAIPointer + horizontalIncrement;
        yAIPointer = yAIPointer + verticalIncrement;

        // Get value of the pointed coordinate
        char value = board[xAIPointer][yAIPointer];
        int valueInt = (value - '0');
        
        // If traversed coordinate is valid and available and contains the largest point,
        if (outOfBounds(xAIPointer, yAIPointer) == 0 && (board[xAIPointer][yAIPointer] != '.' || board[xAIPointer][yAIPointer] != 'P') && (valueInt == largestPoint))
        {
            addToAIScore(xAIPointer, yAIPointer);      // Add points to Player's array score
            updateBoard(xAIPointer, yAIPointer, 'A'); // Update AI's new position on board
            validMove = 0; // Get out of loop
        }
    }
    return 0;
}

// AI Moves; AI chooses move that gives it the largest point
int aiMove()
{
    // Check every direction and see which direction gives the most points
    int xAIPointer = aiCoordinates[0];
    int yAIPointer = aiCoordinates[1];

    int upPoints = aiLargestPoint(0, -1, aiCoordinates[0], aiCoordinates[1]);       // Calculate largest point for going up
    int downPoints = aiLargestPoint(0, 1, aiCoordinates[0], aiCoordinates[1]);      // Calculate largest point for going down
    int leftPoints = aiLargestPoint(-1, 0, aiCoordinates[0], aiCoordinates[1]);     // Calculate largest point for going left
    int rightPoints = aiLargestPoint(1, 0, aiCoordinates[0], aiCoordinates[1]);     // Calculate largest point for going right
    int upLeftPoints = aiLargestPoint(-1, -1, aiCoordinates[0], aiCoordinates[1]);  // Calculate largest point for going up-left
    int upRightPoints = aiLargestPoint(1, -1, aiCoordinates[0], aiCoordinates[1]);  // Calculate largest point for going up-right
    int downLeftPoints = aiLargestPoint(-1, 1, aiCoordinates[0], aiCoordinates[1]); // Calculate largest point for going down-left
    int downRightPoints = aiLargestPoint(1, 1, aiCoordinates[0], aiCoordinates[1]); // Calculate largest point for going down-right

    // Identify which of the 8 possible directions yield the largest point
    int firstGroup = largestNumOfThree(upPoints, downPoints, leftPoints);
    int secondGroup = largestNumOfThree(rightPoints, upLeftPoints, upRightPoints);
    int thirdGroup = largestNumOfTwo(downLeftPoints, downRightPoints);
    int largestPoints = largestNumOfThree(firstGroup, secondGroup, thirdGroup);
    
    if (largestPoints == upPoints) // If the largest amount of points is up, then move AI up
    {
        moveAIOnBoard(0, -1, aiCoordinates[0], aiCoordinates[1], largestPoints);
    }
    else if (largestPoints == downPoints) // If the largest amount of points is down, then move AI down
    {
        moveAIOnBoard(0, 1, aiCoordinates[0], aiCoordinates[1], largestPoints);
    }
    else if (largestPoints == leftPoints) // If the largest amount of points is left, then move AI left
    {
        moveAIOnBoard(-1, 0, aiCoordinates[0], aiCoordinates[1], largestPoints);
    }
    else if (largestPoints == rightPoints) // If the largest amount of points is right, then move AI right
    {
        moveAIOnBoard(1, 0, aiCoordinates[0], aiCoordinates[1], largestPoints);
    }
    else if (largestPoints == upLeftPoints) // If the largest amount of points is up-left, then move AI up-left
    {
        moveAIOnBoard(-1, -1, aiCoordinates[0], aiCoordinates[1], largestPoints);
    }
    else if (largestPoints == upRightPoints) // If the largest amount of points is up-right, then move AI up-right
    {
        moveAIOnBoard(1, -1, aiCoordinates[0], aiCoordinates[1], largestPoints);
    }
    else if (largestPoints == downLeftPoints) // If the largest amount of points is down-left, then move AI down-left
    {
        moveAIOnBoard(-1, 1, aiCoordinates[0], aiCoordinates[1], largestPoints);
    }
    else // If the largest amount of points is down-right, then move AI down-right
    {
        moveAIOnBoard(1, 1, aiCoordinates[0], aiCoordinates[1], largestPoints);
    }

    return 0;
}

// main function to run game
int main()
{
    initBoard(); // Initialize the board first
    printBoard(); // Print Board

    // Loop through and check if the Player and AI has any moves to make until both are out of moves
    while (anyPlayerMovesAvailable() != 0 || anyAIMovesAvailable() != 0)
    {
        int currentPlayerX = playerCoordinates[0];
        int currentPlayerY = playerCoordinates[1];
        int currentAIX = aiCoordinates[0];
        int currentAIY = aiCoordinates[1];
        printf("You are located at: (%i, %i)\n", currentPlayerX+1, currentPlayerY+1); // Show Player's current coordinates.
        printf("AI is located at:   (%i, %i)\n", currentAIX+1, currentAIY+1); // Show AI's current coordinates.
        
        if (anyPlayerMovesAvailable() != 0) // If player has moves to make, ask user to input x and y coordinates; otherwise, skip
        {
            int playerMoveValid = 0; // Value to check whether the user's input is valid
            while (playerMoveValid == 0)
            {
                int xInput;
                int yInput;

                // Ask Player to input coordinate
                printf("Input X-Value and Y-Value for coordinate: ");
                scanf("%i %i", &xInput, &yInput);
                
                // Decrement x and y input to convert coordinate range from (1-6) to (0-5)
                xInput--;
                yInput--;

                // Player makes move.
                playerMoveValid = playerMove(xInput, yInput); // If the move is valid, get out of loop; otherwise, input try again and input new coordinates
            }
        }

        if (anyAIMovesAvailable() != 0) // If AI has moves to make, AI makes move (based on algorithm implemented); otherwise, skip
        {
            aiMove();
        }

        printf("\n");
        printBoard(); // Display updated board
    }
    finalResults(playerPoints, aiPoints); // When game ends, reveal scores and winner
}
