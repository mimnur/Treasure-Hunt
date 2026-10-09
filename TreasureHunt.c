#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define GRID_SIZE 5
#define MAX_MOVES 20
#define TREASURES 5
#define TRAPS 5
#define POWERUPS 2
#define MAX_LEADERBOARD_ENTRIES 10
#define NAME_LENGTH 50
#define GAME_TIME 60  // 60 seconds timer

#define PLAYER 'P'
#define UNEXPLORED '?'
#define TREASURE 'T'
#define TRAP 'X'
#define POWERUP '+'
#define EMPTY ' '

typedef struct {
    char name[NAME_LENGTH];
    int score;
} LeaderboardEntry;

void initializeGrid(char grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = EMPTY;
        }
    }
}

void initializeVisibleGrid(char visibleGrid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            visibleGrid[i][j] = UNEXPLORED;
        }
    }
}

void placeItems(char grid[GRID_SIZE][GRID_SIZE], char item, int count) {
    for (int i = 0; i < count; i++) {
        int x, y;
        do {
            x = rand() % GRID_SIZE;
            y = rand() % GRID_SIZE;
        } while (grid[x][y] != EMPTY);
        grid[x][y] = item;
    }
}

void displayGrid(char visibleGrid[GRID_SIZE][GRID_SIZE], int playerX, int playerY) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (i == playerX && j == playerY) {
                printf(" %c ", PLAYER);
            } else {
                printf(" %c ", visibleGrid[i][j]);
            }
        }
        printf("\n");
    }
}

int movePlayer(char hiddenGrid[GRID_SIZE][GRID_SIZE], char visibleGrid[GRID_SIZE][GRID_SIZE], int *playerX, int *playerY, char direction, int *score, int *health, int *movesLeft, int *treasuresCollected) {
    int newX = *playerX, newY = *playerY;
    switch (direction) {
        case 'W': case 'w': newX--; break;
        case 'A': case 'a': newY--; break;
        case 'S': case 's': newX++; break;
        case 'D': case 'd': newY++; break;
        default: return 0;
    }

    if (newX < 0 || newX >= GRID_SIZE || newY < 0 || newY >= GRID_SIZE) {
        return 0;
    }

    *playerX = newX;
    *playerY = newY;
    (*movesLeft)--;

    char cell = hiddenGrid[newX][newY];
    visibleGrid[newX][newY] = cell;

    if (cell == TREASURE) {
        (*score) += 10;
        (*treasuresCollected)++;
        printf("You found a treasure! +10 points!\n");
    } else if (cell == TRAP) {
        (*health)--;
        printf("You stepped on a trap! -1 health!\n");
    } else if (cell == POWERUP) {
        (*movesLeft) += 3;
        printf("You got a power-up! +3 moves!\n");
    }
    hiddenGrid[newX][newY] = EMPTY;
    return 1;
}

void moveDynamicTraps(char hiddenGrid[GRID_SIZE][GRID_SIZE]) {
    char tempGrid[GRID_SIZE][GRID_SIZE];
    initializeGrid(tempGrid);

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (hiddenGrid[i][j] == TRAP) {
                int newX, newY;
                do {
                    newX = rand() % GRID_SIZE;
                    newY = rand() % GRID_SIZE;
                } while (tempGrid[newX][newY] != EMPTY || hiddenGrid[newX][newY] != EMPTY);
                tempGrid[newX][newY] = TRAP;
            }
        }
    }

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (tempGrid[i][j] == TRAP) {
                hiddenGrid[i][j] = TRAP;
            } else if (hiddenGrid[i][j] == TRAP) {
                hiddenGrid[i][j] = EMPTY;
            }
        }
    }
}

void updateLeaderboard(LeaderboardEntry leaderboard[], int *leaderboardSize, char *name, int score) {
    if (*leaderboardSize < MAX_LEADERBOARD_ENTRIES) {
        strcpy(leaderboard[*leaderboardSize].name, name);
        leaderboard[*leaderboardSize].score = score;
        (*leaderboardSize)++;
    }
}

void displayLeaderboard(LeaderboardEntry leaderboard[], int leaderboardSize) {
    printf("\n--- Leaderboard ---\n");
    for (int i = 0; i < leaderboardSize; i++) {
        printf("%d. %s - %d points\n", i + 1, leaderboard[i].name, leaderboard[i].score);
    }
    printf("-------------------\n");
}

int main() {
    srand(time(NULL));

    char hiddenGrid[GRID_SIZE][GRID_SIZE];
    char visibleGrid[GRID_SIZE][GRID_SIZE];
    int playerX = 0, playerY = 0;
    int score = 0, health = 3, movesLeft = MAX_MOVES;
    int treasuresCollected = 0;

    LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES];
    int leaderboardSize = 0;

    initializeGrid(hiddenGrid);
    initializeVisibleGrid(visibleGrid);
    placeItems(hiddenGrid, TREASURE, TREASURES);
    placeItems(hiddenGrid, TRAP, TRAPS);
    placeItems(hiddenGrid, POWERUP, POWERUPS);

    // Introduction
    printf("========================================================\n");
    printf("            Welcome to The Treasure Hunt!          \n");
    printf("========================================================\n");
    printf("The team: <|  Syntax Error |> \n");
    printf("Creators: Mim Nur, Nafisa Tasfia, Oishee Chowdhury, Richi Hasnin, Anindya Prashed Barua!\n \n");
    printf("Game Rules:\n");
    printf("1. Collect all treasures to win the game.\n");
    printf("2. Avoid traps as they will reduce your health.\n");
    printf("3. Use power-ups to gain extra moves.\n");
    printf("4. Time: 60 seconds\n");
    printf("Good Luck!\n");
    printf("========================================================\n\n");

    // Username Input
    char username[NAME_LENGTH];
    printf("Enter your username: ");
    fgets(username, NAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0;

    // Start Game
    char playCommand[10];
    printf("\nEnter 'go' to take the challenge!: ");
    fgets(playCommand, sizeof(playCommand), stdin);
    playCommand[strcspn(playCommand, "\n")] = 0;

    if (strcmp(playCommand, "go") != 0) {
        printf("\nInvalid command. Please restart the game and type 'play' to begin.\n");
        return 0;
    }

    printf("\nWelcome, %s! Challenge started now!\n", username);
    time_t start_time = time(NULL);  // Start timer
    time_t current_time;
    int elapsed_time = 0;

    // Game loop with time limit
    while (movesLeft > 0 && health > 0) {
        current_time = time(NULL);
        elapsed_time = difftime(current_time, start_time);
        if (elapsed_time >= GAME_TIME) {
            printf("\nTime's up! Game Over, %s!\n", username);
            printf("Final Score: %d\n", score);
            break;
        }

        printf("\nTime remaining: %d seconds\n", GAME_TIME - elapsed_time);

        if (treasuresCollected == TREASURES) {
            printf("\nCongratulations, %s! You found all the treasures! Final Score: %d\n", username, score);
            printf("Game Over! You Win!\n");
            updateLeaderboard(leaderboard, &leaderboardSize, username, score);
            displayLeaderboard(leaderboard, leaderboardSize);
            return 0;
        }

        printf("\nYour Status: Score = %d, Health = %d, Moves Left = %d, Treasures Collected = %d/%d\n", score, health, movesLeft, treasuresCollected, TREASURES);
        displayGrid(visibleGrid, playerX, playerY);

        printf("Enter your move W(up) | A(left) | S(down) | D(right): ");
        char move;
        scanf(" %c", &move);

        if (movePlayer(hiddenGrid, visibleGrid, &playerX, &playerY, move, &score, &health, &movesLeft, &treasuresCollected)) {
            printf("\nMove successful!\n");
            moveDynamicTraps(hiddenGrid);
        } else {
            printf("\nInvalid move! Try again.\n");
        }
    }

    if (health <= 0) {
        printf("\nGame Over, %s! You lost all your health.\n", username);
        printf("Final Score: %d\n", score);
    } else if (movesLeft <= 0) {
        printf("\nGame Over, %s! You ran out of moves.\n", username);
        printf("Final Score: %d\n", score);
    }

    updateLeaderboard(leaderboard, &leaderboardSize, username, score);
    displayLeaderboard(leaderboard, leaderboardSize);
    return 0;
}
