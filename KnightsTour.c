#include <stdio.h> 
#include <stdbool.h>

bool isVisited(int x, int y, int visited[5][5]){ // checks if the knight has already been at a position x, y
    if(visited[y][x] == 1){
        return true;
    }
    return false;
}

bool isLegal(int x, int y, int move[2]){ // checks if the next move is within the bounds of the board

    if(4 >= (x + move[0]) && (x + move[0]) >= 0){
        if(4 >= (y + move[1]) && (y + move[1]) >= 0){
            return true;
        }
    }
    return false;
}

int move(int x, int y, int steps, int board[5][5], int visited[5][5],  int linVisited[25], int moves[8][2]){

    if(linVisited[24] != -1){ // prints a completed tour of the knight if linVisited is full
        for (int f = 0; f < 25; f++){
            printf("%d ", linVisited[f]);
        }
        printf("\n");
        return 0;
    }

    for(int i = 0; i < 8; i++){ // looks through all the moves the knight can make
        if(isLegal(x, y, moves[i]) && !isVisited(x + moves[i][0], y + moves[i][1], visited)){ // checks if the move can be done
            visited[y + moves[i][1]][x + moves[i][0]] = 1; // updates the visited 2d array
            linVisited[steps] = board[y + moves[i][1]][x + moves[i][0]]; // updates the list of moves the knight has made
            steps++;
            
            move(x + moves[i][0], y + moves[i][1], steps,  board, visited, linVisited, moves);

            visited[y + moves[i][1]][x + moves[i][0]] = 0; // removes the last move if it is a dead end or it is done
            steps--;
            linVisited[steps] = -1;
        }
    }
    return 0;
}

int main() { 

    int board[5][5]; // board with the numbered spots from 1 to 25
    int visited[5][5]; // board of visited spots where 0 means not visited and 1 means it is visited
    int linVisited[25]; // list of positions the knight has been. -1 by default
    int moves[8][2] = {{-1, -2}, {1, -2}, {-2, -1}, {2, -1}, {-2, 1}, {2, 1}, {-1, 2}, {1, 2}};
    
    for (int y = 0; y < 5; y++){
        for (int x = 0; x < 5; x++){
            for (int i = 0; i < 5; i++) { // resets the board to start at another position
                for (int j = 0; j < 5; j++) {
                    visited[i][j] = 0; // makes all position unvisited
                    board[i][j] = 5*i + j + 1; // fills the board form 1 to 25
                    linVisited[i*5 + j] = -1;  // sets all elements to be unexplored(-1);
                }  
            }
            visited[y][x] = 1;
            linVisited[0] = board[y][x];
            move(x, y, 1, board, visited, linVisited, moves);
        }   
    }
    return 0; 
} 