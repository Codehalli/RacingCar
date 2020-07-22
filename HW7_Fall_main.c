// This application uses button 1 and LED 1
// The operation is such that if you press the left button, as long as you keep the button pressed,
// the LED is on. As soon as you release the button, LED is off and stays off until the button is pressed again.
// This program uses Hardware Abstraction Level (HAL) functions that hide away device-specific details.
/*
 *  HW7_Fall_main.h
 *
 *  Created on: November 10, 2019
 *      Author: Pranav Rao
 */


#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "game.h"
#include "initialize.h"
#include "graphics_HAL.h"
#include "stdio.h"
#include "Timer_HAL.h"

// According to the schematics on page 37 of the Launchpad user guide,
// When a button is pressed, it is grounded (logic 0)

#define PRESSED 0

//main function
int main(void)
    {

    race_t race;//setting up racing game
    Init_race(&race); //setting up front initial screen
    init_Graphics(&race); //setting the graphics
    initialize(); //initializing the timers

    while (1)
        {
            if(Boosterpack_PButtonB())
            {
                TurnOn_Launch_LED1(); //turns on after pressing S2
            }
            else
            {
                TurnOff_Launch_LED1(); //turns off after pressing S3
            }

            getSampleJoystick(&race.vx, &race.vy); // x and y joystick

            if(race.curr_Mode == Splash)
            {
                drawSplash(&race); //display the splash screen
                splashClock(6000000); //show it for just over 3 seconds
                Graphics_Context *g_sContext_p = &race.g_sContext;
                Graphics_clearDisplay(g_sContext_p);//clear the screen
                race.curr_Mode = Main; //change to main menu
            }
            if(race.curr_Mode == Main)
            {
                Disp_Menu(&race); //display the main menu
                draw_Select(&race); //show the cursor on the menu
                menu_selection(&race); //decide where the cursor is on the menu
                menu_clicking(&race); //decide what the user is selecting on the menu
            }
            if(race.curr_Mode == Playing) //if the user selected to play the game
            {
                Disp_Play(&race);
                deathStar(&race);
                moveStar(&race);
                collide(&race);
                draw_obstacle(&race);
                moveObject(&race);



                if(Boosterpack_PButtonT())
                {
                   race.curr_Mode = Main;
                   Graphics_clearDisplay(&race.g_sContext);
                   race.gameplay = false;
                }
            }


            if(race.curr_Mode == HighScore) // view the highscores
            {
                Disp_Top(&race);
                if(Boosterpack_PButtonT())
                {
                   race.curr_Mode = Main;
                   Graphics_clearDisplay(&race.g_sContext);
                }
            }
            if(race.curr_Mode == Explanation) // view how-to-play menu
            {
                Disp_How(&race);
                if(Boosterpack_PButtonT())
                 {
                    race.curr_Mode = Main;
                    Graphics_clearDisplay(&race.g_sContext);
                 }
            }
        }
}



