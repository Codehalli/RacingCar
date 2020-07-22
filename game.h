/*
 *  game.h
 *
 *  Created on: November 10, 2019
 *      Author: Pranav Rao
 */

#ifndef GAME_H_
#define GAME_H_
#include <ti/grlib/grlib.h>
#include <stdbool.h>


typedef enum{Main, Playing, HighScore, Explanation, Splash, Over, Pause} state;
typedef enum{Play, High, How, Continue, Exit} select;
typedef enum {Up, Down} button_state;
typedef enum {s1,s2,s3,s4,s5} objSize;
#define HIGHER_THRESHOLD_Y 10000
#define LOWER_THRESHOLD_Y 6000

typedef struct
{
    int x_Min;
    int y_Min;

    int x_Max;
    int y_Max;

    int steps;

    int position;

} ast_t;

typedef struct
{
    Graphics_Context g_sContext;
    state curr_Mode; //mode the game is currently on
    select curr_Selec; // indicate the cursor
    unsigned int vx; //input for X
    unsigned int vy; //input for Y
    bool gameplay;
    int8_t stock[1];
    int currentStock;


    int leftB;
    int leftObs;
    int yleftObs;

    int x_Min;
    int ydown;
    int mid;
    int top;

    int8_t score[3]; //Best score 1st
    int currentScore; //Best score 2nd
    int BestScore[3]; //Best score 3rd

    ast_t object[100];
    int increment;

}race_t;

//sets the values for the initial state of the game
void Init_race(race_t *race);
//JS movement
void menu_selection(race_t *race);
//JS clicking
void menu_clicking(race_t *race);
//car movement
void moveStar(race_t *race);
//moving the object while it grows
void moveObject(race_t *race);
//moving the collide object
void collide(race_t *race);


#endif

