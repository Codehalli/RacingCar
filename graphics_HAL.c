/*
 *  grpahics_HAL.c
 *
 *  Created on: November 10, 2019
 *      Author: Pranav Rao
 */

#include "graphics_HAL.h"
#include "Timer_HAL.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include <stdio.h>
#include <game.h>

//Draw Splash
void drawSplash(race_t *race) //game starts here, called in main.
{
    Graphics_Context *g_sContext_p = &race->g_sContext;
    if(race->curr_Mode == Splash)
    {
        Graphics_setForegroundColor(g_sContext_p,GRAPHICS_COLOR_LIGHT_GREEN);
        Graphics_drawString(g_sContext_p, (int8_t*) "Car Racing Game", AUTO_STRING_LENGTH, 0, 20, true);
        Graphics_drawString(g_sContext_p, (int8_t*) "Programmed By", AUTO_STRING_LENGTH, 0, 40, true);
        Graphics_drawString(g_sContext_p, (int8_t*) "Pranav Rao", AUTO_STRING_LENGTH, 0, 60, true);
    }
}

//Display Menu
void Disp_Menu(race_t *race)
{
    Graphics_Context *g_sContext_p = &race->g_sContext;
    Graphics_setFont(g_sContext_p, &g_sFontCmtt12);
    Graphics_setForegroundColor(g_sContext_p,GRAPHICS_COLOR_RED);
    Graphics_drawString(g_sContext_p, (int8_t*)"GAME MENU", AUTO_STRING_LENGTH, 0, 5 , true);
    Graphics_drawString(g_sContext_p, (int8_t*)"--------------------", AUTO_STRING_LENGTH, 0, 20, true);

    Graphics_setForegroundColor(g_sContext_p,GRAPHICS_COLOR_CYAN);
    Graphics_drawString(g_sContext_p, (int8_t*)"PLAY GAME", AUTO_STRING_LENGTH, 20, 40,true);
    Graphics_drawString(g_sContext_p, (int8_t*)"HIGH SCORES", AUTO_STRING_LENGTH, 20, 60, true);
    Graphics_drawString(g_sContext_p, (int8_t*)"HOW TO PLAY", AUTO_STRING_LENGTH, 20, 80, true);
}
void Disp_Play(race_t* race)
{
    if(race->gameplay == false)
    {

    Graphics_Context *g_sContext_p = &race->g_sContext;

    Graphics_Rectangle road = {0, 55, 127, 127};
    Graphics_Rectangle sky = {0,0,127,55};
    Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLACK);
    Graphics_drawRectangle(g_sContext_p, &sky);
    Graphics_fillRectangle(g_sContext_p, &sky);

    Graphics_setForegroundColor(g_sContext_p,GRAPHICS_COLOR_ROYAL_BLUE);
    Graphics_drawRectangle(g_sContext_p, &road);
    Graphics_fillRectangle(g_sContext_p, &road);

    Graphics_setForegroundColor(g_sContext_p,GRAPHICS_COLOR_ORANGE_RED);
    Graphics_fillCircle(g_sContext_p, 127, 0 , 20);


    Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_RED);
    //Graphics_setBackgroundColor(g_sContext_p, GRAPHICS_COLOR_BLACK);
    Graphics_setFont(g_sContext_p, &g_sFontCmtt12);
    Graphics_drawString(g_sContext_p,(int8_t*)"Score:", AUTO_STRING_LENGTH, 0, 2, true);
    Graphics_drawString(g_sContext_p,(int8_t*)race->currentScore, AUTO_STRING_LENGTH, 18, 2, true);
    Graphics_drawString(g_sContext_p,(int8_t*)"High Score:", AUTO_STRING_LENGTH, 0, 12, true);

    if(race->currentStock==3)
    {
        Graphics_drawString(g_sContext_p, (int8_t*)"Lives: 3", AUTO_STRING_LENGTH,0, 22, true);
    }
    if(race->currentStock==2)
    {
        Graphics_drawString(g_sContext_p, (int8_t*)"Lives: 2", AUTO_STRING_LENGTH,0, 22, true);
    }

    if(race->currentStock==1)
    {
        Graphics_drawString(g_sContext_p, (int8_t*)"Lives: 1", AUTO_STRING_LENGTH,0, 22, true);
    }

    draw_Lane(race);
    deathStar(race);

    race->gameplay = true;
    }
}

void Disp_Top(race_t* race)
{
    Graphics_Context *g_sContext_p = &race->g_sContext;
    Graphics_setForegroundColor(g_sContext_p,GRAPHICS_COLOR_RED);
    Graphics_drawString(g_sContext_p,(int8_t*)"TOP SCORES:", AUTO_STRING_LENGTH, 0, 5, true);
    Graphics_drawString(g_sContext_p, (int8_t*)"--------------------", AUTO_STRING_LENGTH, 0, 20, true);
    Graphics_setForegroundColor(g_sContext_p,GRAPHICS_COLOR_VIOLET);
    Graphics_drawString(g_sContext_p,(int8_t*)"1st:", AUTO_STRING_LENGTH, 10, 40, true);
    Graphics_drawString(g_sContext_p,(int8_t*)"2nd:", AUTO_STRING_LENGTH, 10, 60, true);
    Graphics_drawString(g_sContext_p,(int8_t*)"3rd:", AUTO_STRING_LENGTH, 10, 80, true);

}

void draw_Lane(race_t* race)
{
    Graphics_Context *g_sContext_p = &race->g_sContext;
    Graphics_drawLine(g_sContext_p, 43,127,53,55);
    Graphics_drawLine(g_sContext_p, 83,127,73,55);
    Graphics_drawLine(g_sContext_p, 3,127,33,55);
    Graphics_drawLine(g_sContext_p, 127,127,93,55);
}

void deathStar(race_t* race)
{
    Graphics_Context *g_sContext_p = &race->g_sContext;
    Graphics_setForegroundColor(g_sContext_p,GRAPHICS_COLOR_DIM_GRAY);
    Graphics_fillCircle(g_sContext_p, race->leftB+22, 112, 12);
    Graphics_setForegroundColor(g_sContext_p,GRAPHICS_COLOR_GRAY);
    Graphics_fillCircle(g_sContext_p,race->leftB+27, 112, 4);
    Graphics_setForegroundColor(g_sContext_p,GRAPHICS_COLOR_LIME_GREEN);
    Graphics_fillCircle(g_sContext_p, race->leftB+27, 112, 2);
}

void draw_relane(race_t* race)
{
       Graphics_Context *g_sContext_p= &((race_t*)race)->g_sContext;

       Graphics_Rectangle sky = {0,35,127,55};
       Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLACK);
       Graphics_drawRectangle(g_sContext_p, &sky);
       Graphics_fillRectangle(g_sContext_p, &sky);

       Graphics_Rectangle road = {0, 55, 127, 127};
       Graphics_setForegroundColor(g_sContext_p,GRAPHICS_COLOR_VIOLET);
       Graphics_drawRectangle(g_sContext_p, &road);
       Graphics_fillRectangle(g_sContext_p, &road);


       Graphics_setForegroundColor(g_sContext_p,GRAPHICS_COLOR_CYAN);
       draw_Lane(race);

       Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
       deathStar(race);
}

void draw_obstacle(race_t *race)
{
    Graphics_Context *g_sContext_p = &race->g_sContext;
    //draw_relane(race);

    ast_t obs = race->object[race->increment];

    int bot_X = obs.x_Min;
    int bot_Y = obs.y_Min;
    int top_X = obs.x_Max;
    int top_Y = obs.y_Max;



    Graphics_Rectangle box = {bot_X, bot_Y, top_X, top_Y};

    Graphics_drawRectangle(g_sContext_p, &box);
    Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BROWN);
    Graphics_fillRectangle(g_sContext_p, &box);
}
void disp_Pause(race_t *race)
{
    Graphics_Context *g_sContext_p = &race->g_sContext;

    Graphics_setForegroundColor(g_sContext_p,GRAPHICS_COLOR_RED);
    Graphics_setFont(g_sContext_p, &g_sFontCmtt12);
    Graphics_drawString(g_sContext_p,(int8_t*)"GAME PAUSED:", AUTO_STRING_LENGTH, 5, 5, true);

    Graphics_setFont(g_sContext_p, &g_sFontCmtt12);
    Graphics_drawString(g_sContext_p,(int8_t*)"Play", AUTO_STRING_LENGTH, 16, 40, true);
    Graphics_drawString(g_sContext_p,(int8_t*)"Quit", AUTO_STRING_LENGTH, 16, 80, true);
}

void Disp_How(race_t* race)
{
    Graphics_Context *g_sContext_p = &race->g_sContext;
    Graphics_setFont(g_sContext_p, &g_sFontCmss12);
    Graphics_setForegroundColor(g_sContext_p,GRAPHICS_COLOR_RED);
    Graphics_drawString(g_sContext_p,(int8_t*)"EXPLANATION", AUTO_STRING_LENGTH, 0, 5, GRAPHICS_COLOR_RED);
    Graphics_drawString(g_sContext_p, (int8_t*)"--------------------", AUTO_STRING_LENGTH, 0, 20, true);
    Graphics_setForegroundColor(g_sContext_p,GRAPHICS_COLOR_YELLOW);
    Graphics_drawString(g_sContext_p, (int8_t*)"One must move the joy", AUTO_STRING_LENGTH, 0, 32, true);
    Graphics_drawString(g_sContext_p, (int8_t*)"stick to dodge the   ", AUTO_STRING_LENGTH, 0, 44, true);
    Graphics_drawString(g_sContext_p, (int8_t*)"obstacles. After the ", AUTO_STRING_LENGTH, 0, 56, true);
    Graphics_drawString(g_sContext_p, (int8_t*)"ship hits 3 obstacles ", AUTO_STRING_LENGTH, 0, 68, true);
    Graphics_drawString(g_sContext_p, (int8_t*)"the game is over.    ", AUTO_STRING_LENGTH, 0, 80, true);
    Graphics_drawString(g_sContext_p, (int8_t*)"To go back to the    ", AUTO_STRING_LENGTH, 0, 92, true);
    Graphics_drawString(g_sContext_p, (int8_t*)"main menu press the  ", AUTO_STRING_LENGTH, 0, 104, true);
    Graphics_drawString(g_sContext_p, (int8_t*)"S1 button. Good Luck!", AUTO_STRING_LENGTH, 0, 116, true);

}

//creating the menu cursor
void draw_Select(race_t* race)
{
    Graphics_Context *g_sContext_p = &race->g_sContext;
    if(race->curr_Selec == Play)
    {
        Graphics_drawString(g_sContext_p, (int8_t*)">", AUTO_STRING_LENGTH, 5,40, GRAPHICS_COLOR_WHITE); //blank by high scores
        Graphics_drawString(g_sContext_p, (int8_t*)" ", AUTO_STRING_LENGTH, 5,60, GRAPHICS_COLOR_WHITE); //blank by htp
        Graphics_drawString(g_sContext_p, (int8_t*)" ", AUTO_STRING_LENGTH, 5,80, GRAPHICS_COLOR_WHITE); //highlight play
    }
    else if(race->curr_Selec == High)
    {
        Graphics_drawString(g_sContext_p, (int8_t*)" ", AUTO_STRING_LENGTH, 5,40, GRAPHICS_COLOR_WHITE); //blank by play
        Graphics_drawString(g_sContext_p, (int8_t*)">", AUTO_STRING_LENGTH, 5,60, GRAPHICS_COLOR_WHITE);//blank by htp
        Graphics_drawString(g_sContext_p, (int8_t*)" ", AUTO_STRING_LENGTH, 5,80, GRAPHICS_COLOR_WHITE);//highlight hscores
    }
    else if(race->curr_Selec == How)
    {
        Graphics_drawString(g_sContext_p, (int8_t*)" ", AUTO_STRING_LENGTH, 5,40, GRAPHICS_COLOR_WHITE);//blank by play
        Graphics_drawString(g_sContext_p, (int8_t*)" ", AUTO_STRING_LENGTH, 5,60, GRAPHICS_COLOR_WHITE); //blank by hscores
        Graphics_drawString(g_sContext_p, (int8_t*)">", AUTO_STRING_LENGTH, 5,80, GRAPHICS_COLOR_WHITE);//highlight htp
    }
}

//Fonts
void init_Font()
{
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
}
//Graphics background
void init_Graphics(race_t *race) //initial frame graphics 10 white boxes & background)
{
    Graphics_Context *g_sContext_p=&((race_t*)race)->g_sContext;
    Graphics_initContext(g_sContext_p, &g_sCrystalfontz128x128, &g_sCrystalfontz128x128_funcs);

    Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);//white boxes
    Graphics_setBackgroundColor(g_sContext_p, GRAPHICS_COLOR_BLACK); //black background
    Graphics_setFont(g_sContext_p, &g_sFontCmtt12);

    init_Font(); //the fonts function declared above

    Graphics_clearDisplay(g_sContext_p); //all empty @ start
}
