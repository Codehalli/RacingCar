/*
 *  game.c
 *
 *  Created on: November 10, 2019
 *      Author: Pranav Rao
 */
#include "game.h"
#include "graphics_HAL.h"
#include "Timer_HAL.h"
#include "initialize.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//sets the values for the initial state of the game
void Init_race(race_t *race)
{
    race-> curr_Mode = Splash;
    race-> curr_Selec = Play;


    race-> gameplay = false;
    race-> leftB = 43;
    //race-> rightB = 127;
    race -> currentStock = 3;
    race -> currentScore = 0;

    ast_t leftR;
    ast_t midR;
    ast_t rightR;

    midR.x_Min = 55;
    midR.y_Min = 37;
    midR.x_Max = midR.x_Min + 17;
    midR.y_Max = midR.y_Min + 18;
    midR.position = 2;

    rightR.x_Min = 75;
    rightR.y_Min = 37;
    rightR.x_Max = rightR.x_Min + 17;
    rightR.y_Max = rightR.y_Min + 18;
    rightR.position=3;


    leftR.x_Min = 35;
    leftR.y_Min = 37;
    leftR.x_Max = leftR.x_Min + 17;
    leftR.y_Max = leftR.y_Min + 18;
    leftR.position= 1;

    int j;
    int count;
    //int random[9];
    //int a;
    int i[100];

    time_t t;

    count = 100;

    srand((unsigned) time(&t));



    for( j = 0 ; j < count ; j++ )
    {

          i[j] = rand() % 3;

         if( i[j] == 0)
          {
            race->object[j]=leftR; //leftR;
          }

         if( i[j] == 1)
          {
            race->object[j]= midR;
          }

          if(i[j] == 2)
          {
           race->object[j]=rightR;
          }
     }

        race->increment = 0;

}

void moveStar(race_t *race)
{
      if(race->vx < LOWER_THRESHOLD_Y)
        {
          if(race -> leftB >= 0)
            race ->  leftB = race ->leftB -4;

          draw_relane(race);
        }

       if(race->vx > HIGHER_THRESHOLD_Y)
        {
           if(race ->leftB <= 85)
             race -> leftB = race ->leftB +4;

           draw_relane(race);
        }
}


void moveObject(race_t *race)
{
    splashClock(50000);
    race->gameplay= true;
    ast_t obs = race->object[race->increment];
    if (obs.position == 2)
    {
        race->object[race->increment].y_Min += 2;
        race->object[race->increment].steps ++;

        if(race->object[race->increment].steps >= 8)
          {
            race->object[race->increment].x_Min -= .4 ;
            race->object[race->increment].y_Max += 4;
            race->object[race->increment].x_Max += 1;
            race->object[race->increment].steps = 0;
          }
            deathStar(race);
            draw_relane(race);
            draw_obstacle(race);
     }
     else if (obs.position == 3)
     {
         race->object[race->increment].y_Min += 2;
         race->object[race->increment].steps ++;

         if(race->object[race->increment].steps >= 8)
         {
           race->object[race->increment].x_Min += 1.35 ;
           //race->object[race->increment].y_Min +=  4;
           race->object[race->increment].y_Max +=  5;
           race->object[race->increment].x_Max +=  4.6;
           race->object[race->increment].steps =  0;
         }

         deathStar(race);
         draw_relane(race);
         draw_obstacle(race);

     }
     else if (obs.position == 1)
     {

      race->object[race->increment].y_Min +=2;
      race->object[race->increment].steps ++;
      if(race->object[race->increment].steps >= 8)
       {
          race->object[race->increment].x_Min -= 4.5 ;
          race->object[race->increment].y_Max += 4;
          race->object[race->increment].x_Max -= 1;
          race->object[race->increment].steps = 0;
       }

      deathStar(race);
      draw_relane(race);
      draw_obstacle(race);
      }
}

void collide(race_t *race)
{
    static bool thing = true;
    static bool col = false;

    if( race->object[race->increment].y_Max >= 80 && race->object[race->increment].y_Max < 85)
    {
        if(race->leftB > race->object[race->increment].x_Min-30 && race-> leftB < race -> object[race->increment].x_Max-5)
        {
            race->currentStock --;
            TurnOn_BoosterRed();
            col= true;

        }
    }

    if( race->object[race->increment].y_Max >= 130 && thing && !col)
    {
        race -> currentScore ++;
        race -> increment ++;
        race -> gameplay = true;
    }

    if( race->object[race->increment].y_Max >= 130 && thing && col)
    {
       TurnOff_BoosterRed();
       race -> increment ++;
       race -> gameplay = true;
     }
}


void menu_selection(race_t *race) //switching the cursor between the 3 opitions
{
    switch (race->curr_Selec)
    {
        case Play: //if indicating the play option
        {
            if(race -> vy < LOWER_THRESHOLD_Y) //Down
            {
                race->curr_Selec = High; //indicates how to play
            }
            else if(race->vy > HIGHER_THRESHOLD_Y)
            {
                race->curr_Selec= How; //lists the highest scores
            }
        }
        break;
        case Continue: //if indicating the play option
        {
             if(race -> vy < LOWER_THRESHOLD_Y) //Down
             {
                  race->curr_Selec = Exit; //indicates how to play
             }

        }
        break;
        case High: //if indicating the the high score option
        {
            if(race->vy < LOWER_THRESHOLD_Y) //and you move the js down
            {
                race->curr_Selec = How; //cursor is now on htp option
            }
            else if(race->vy > HIGHER_THRESHOLD_Y) //or if you move the js up
            {
                race->curr_Selec = Play; //cursor is on htp option
            }
        }
        break;
        case How:
        {
            if(race->vy < LOWER_THRESHOLD_Y) //if the cursor is on the htp option & you move the cursor up
            {
                race->curr_Selec = Play; //the cursor will be on HS option
            }
            else if(race->vy > HIGHER_THRESHOLD_Y) //if stick is moved up
            {
                 race->curr_Selec = High; //select goes back to play
            }
        }
        break;
        case Exit: //if indicating the play option
        {
            if(race -> vy > HIGHER_THRESHOLD_Y) //Down
            {
              race->curr_Selec = Continue; //indicates how to play
            }

        }
        break;
        default:
        {
            race->curr_Selec = Play;
        }
        break;
    }
    Debounce_Button(2500000);
}

void menu_clicking(race_t *race) //clicking for the selections function
{

    if(!(Get_Status_Joystick_Sel())) //joy stick clicking .
    {
        if(race->curr_Selec == Play)
        {
            race->curr_Mode = Playing;
            race-> leftB = 43;
            //race-> rightB = 127;
        }

        if(race->curr_Selec == High)
        {
           if ( race->curr_Mode == HighScore)
           {
               race->curr_Mode = Main;
           }
           else
           {
               race->curr_Mode = HighScore;
           }
        }

        if(race->curr_Selec == How)
        {
            if ( race->curr_Mode ==Explanation)
            {
                race->curr_Mode = Main;
            }
            else
            {
                race->curr_Mode = Explanation;
            }
        }
        if(race->curr_Selec == Continue)
            {
            if (race->curr_Mode ==Pause)
               {
               race->curr_Mode = Playing;
               }
             else
               {
                 race->curr_Mode = Pause;
               }
            }
        if(race->curr_Selec == Exit)
             {
            if (race->curr_Mode ==Pause)
              {
                race->curr_Mode = Main;
               }
                 else
                  {
                     race->curr_Mode = Pause;
                   }
                }

        init_Graphics(race);
        Debounce_Button(10000);
    }
}




