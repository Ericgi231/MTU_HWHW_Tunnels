//Eric Grant
//ewgrant
//generate 2d array of dig spots from data in a text file
//discover dig paths from left to right of array
//outputs data regarding array and path taken
//it aint pretty, but it does the job. Would like to expand and clean code in future.

#include <stdio.h>
#include <stdlib.h>

//print tunnel
void printGrid(int rows, int cols, int digSpots[rows][cols]){
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (digSpots[r][c] != -1)
            {
                printf("%d", digSpots[r][c]);
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    //exit if no argument
    if (argc < 2){
        printf("Usage: Tunnel <Start row> [verbose]\n");
        return 0;
    }

    //set starting row
    int start = atoi(argv[1]);

    //set verbose flag
    int verbose = 0;
    if (argc > 2 && atoi(argv[2]) != 0){
        verbose = 1;
    }

    //vars, this is a bit sloppy but my ide was refusing to do debugging unless my vars were declared before the first scanf
    int temp1, temp2;
    int min = 10;
    int max = 0;
    int totalSum = 0;
    int canMove = 1;
    int dir[4]; // east south noth west
    int choice = 0;
    int xCord = 0;
    int yCord = start;
    int val;
    int cost = 0;
    int len = 0;

    //scan in row and col count
    if (!scanf("%d %d", &temp1, &temp2)){
        printf("ERROR: Data invalid.");
    }
    int rows = temp1;
    int cols = temp2;
    int digSpotCount = rows * cols;

    //exit if start is greater than row count
    if (start >= rows){
        printf("ERROR: Invalid starting row!\n");
        return 0;
    }

    //create 2d array to store dig spots
    int digSpots[rows][cols];

    //populate 2d array with dig difficulty
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            //read dig spot
            if (!scanf("%d", &val)){
                printf("ERROR: Data invalid.");
            }
            digSpots[r][c] = val;

            //add num to sum
            totalSum += val;

            //check if new max
            if (val > max){
                max = val;
            }

            //check if new min
            if (val < min){
                min = val;
            }
        }
    }
    
    //print stats
    printf("Data points: %d\n", digSpotCount);
    printf("Avg difficulty: %.3f\n", (double)totalSum/digSpotCount);
    printf("Min difficulty: %d\n", min);
    printf("Max difficulty: %d\n\n", max);

    //dig tunnel
    cost += digSpots[yCord][xCord];
    digSpots[yCord][xCord] = -1;
    len++;
    if(verbose){
        printGrid(rows, cols, digSpots);
    }
    while (canMove)
    {
        //find value of each move, set to 10 if invalid
        dir[0] = (xCord+1 < cols) ? digSpots[yCord][xCord+1] : -1; //east
        dir[1] = (yCord+1 < rows) ? digSpots[yCord+1][xCord] : -1; //south
        dir[2] = (yCord-1 > -1) ? digSpots[yCord-1][xCord] : -1; //north
        dir[3] = (xCord-1 > -1) ? digSpots[yCord][xCord-1] : -1; //west

        //find direction to dig
        choice = -1;
        for (int i = 0; i < 4; i++){
            //if no direction picked and valid direction found, set
            if (choice == -1 && dir[i] != -1) {
                choice = i;
            }

            //if direction picked and new direction is less than, set
            if (choice != -1 && dir[i] != -1 && dir[i] < dir[choice]){
                choice = i;
            }
        }

        //dig out spot
        switch (choice)
        {
        case 0:
            cost += digSpots[yCord][xCord+1];
            digSpots[yCord][xCord+1] = -1;
            xCord++;
            len++;
            break;
        case 1:
            cost += digSpots[yCord+1][xCord];
            digSpots[yCord+1][xCord] = -1;
            yCord++;
            len++;
            break;
        case 2:
            cost += digSpots[yCord-1][xCord];
            digSpots[yCord-1][xCord] = -1;
            yCord--;
            len++;
            break;
        case 3:
            cost += digSpots[yCord][xCord-1];
            digSpots[yCord][xCord-1] = -1;
            xCord--;
            len++;
            break;
        default:
            canMove = 0;
            break;
        }

        //check if done digging
        if(xCord == cols-1){
            canMove = 0;
        }

        //check if dead end to avoid extra loop
        dir[0] = (xCord+1 < cols) ? digSpots[yCord][xCord+1] : -1; //east
        dir[1] = (yCord+1 < rows) ? digSpots[yCord+1][xCord] : -1; //south
        dir[2] = (yCord-1 > -1) ? digSpots[yCord-1][xCord] : -1; //north
        dir[3] = (xCord-1 > -1) ? digSpots[yCord][xCord-1] : -1; //west
        if(dir[0] == -1 && dir[1] == -1 && dir[2] == -1 && dir[3] == -1){
            canMove = 0;
        }

        //print grid each step if verbose
        if(verbose){
            printGrid(rows, cols, digSpots);
        }
    }


    //print grid if not done in digging steps
    if (verbose == 0)
    {
        printGrid(rows, cols, digSpots);
    }
    
    //print more stats
    printf("Length = %d\n", len);
    printf("Cost = %d\n\n", cost);
    
    return 0;
}
