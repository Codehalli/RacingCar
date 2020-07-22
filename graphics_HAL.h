/*
 *  graphics_HAL.h
 *
 *  Created on: November 10, 2019
 *      Author: Pranav Rao
 */

#ifndef GRAPHICS_HAL_H_
#define GRAPHICS_HAL_H_

#include "game.h"
#include "initialize.h"
//The very first splash screen when you turn on the device
void drawSplash(race_t *race);
//for the fonts for the text on the screen
void init_Font();
//creates the graphics
void init_Graphics(race_t *race);
//This is main screen
void Disp_Menu(race_t *race);
//cursor image
void draw_Select(race_t *race);
//creates the play screen
void Disp_Play(race_t *race);
//create the explanation screen
void Disp_How(race_t *race);
//creates the top score
void Disp_Top(race_t *race);
//images ??
//created the roads
void draw_Lane(race_t *race);
//this is the vehicle
void deathStar(race_t* race);
//this helps to create the road and change the road color speed
void draw_relane(race_t* race);
//this is the obstacle(asteroids)
void draw_obstacle(race_t *race);



extern const Graphics_Image CarSplash4BPP_UNCOMP;

#endif
