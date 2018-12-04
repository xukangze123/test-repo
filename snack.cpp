#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define WALL_CELL '*'
#define food $

void snake_move();
void output();
int gameover();
void creat_food();

char map[12][12] = {
    "***********",
    "*XXXXH    *",
    "*         *",
    "*         *",
    "*         *",
    "*         *",
    "*         *",
    "*         *",
    "*         *",
    "*         *",
    "***********",
};

int snake_length = 5;
int snake_location_x[10] = {5, 4, 3, 2, 1};
int snake_location_y[10] = {1, 1, 1, 1, 1};
int food_x;
int food_y;


int main() {
    creat_food();
    char choice;
    output();
    while (1) {
        scanf(" %c", &choice);
        snake_move();
        if (choice == 'w') {
            snake_location_y[0] -= 1;
            map[snake_location_y[0]][snake_location_x[0]] = 'H';
        }
        if (choice == 's') {
            snake_location_y[0] += 1;
            map[snake_location_y[0]][snake_location_x[0]] = 'H';
        }
        if (choice == 'a') {
            snake_location_x[0] -= 1;
            map[snake_location_y[0]][snake_location_x[0]] = 'H';
        }
        if (choice == 'd') {
            snake_location_x[0] += 1;
            map[snake_location_y[0]][snake_location_x[0]] = 'H';
        }
        if (snake_location_x[0] == food_x && snake_location_y[0] == food_y) {
            creat_food();
            snake_length++;
            snake_location_x[snake_length - 1] = snake_location_x[snake_length - 2];
            snake_location_y[snake_length - 1] = snake_location_y[snake_length - 2];
            map[snake_location_y[snake_length - 1]][snake_location_x[snake_length - 1]] = 'X';
        }
        if (!gameover()) {
            printf("GAMEOVER!\n");
            return 0;
        } else {
            output();
        }
    }
    return 0;
}

void snake_move() {
    int i;
    map[snake_location_y[snake_length - 1]][snake_location_x[snake_length - 1]] = ' ';
    for (i = snake_length - 1; i > 0; i--) {
        snake_location_x[i] = snake_location_x[i - 1];
        snake_location_y[i] = snake_location_y[i - 1];
        map[snake_location_y[i]][snake_location_x[i]] = 'X';
    }
}

int gameover() {
    if (snake_location_x[0] == 10 || snake_location_x[0] == 0) {
        return 0;
    }
    if (snake_location_y[0] == 10 || snake_location_y[0] == 0) {
        return 0;
    }
    for (int i = 1; i < snake_length; i++) {
        if (snake_location_x[0] == snake_location_x[i] && snake_location_y[0] == snake_location_y[i]) {
            return 0;
        }
    }
    return 1;
}
void output() {
    for (int i = 0; i <= 11; i++) {
        for (int j = 0; j <= 11; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}
void creat_food() {
    srand((unsigned)(time(NULL)));
    food_x = rand() % 9 + 1;
    food_y = rand() % 9 + 1;
    while (map[food_y][food_x] != ' ') {
        food_x = rand() % 9 + 1;
        food_y = rand() % 9 + 1;
    }
    map[food_y][food_x] = '$';
}
