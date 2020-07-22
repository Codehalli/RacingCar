/*
 * initialize.h
 *
 *  Created on: November 10, 2019
 *      Author: Pranav Rao
 */

#ifndef INITIALIZE_H_
#define INITIALIZE_H_


void init_ADC(void);
void init_Joystick(void);
void start_ADC(void);

void initialize();
void init_GPIO();


char Get_Status_Joystick_Sel();

void TurnOn_Launch_LED1();
void TurnOff_Launch_LED1();

char switch_stat_BPT();
char switch_stat_BPB();


char Boosterpack_PButtonT();
char Boosterpack_PButtonB();

void TurnOn_BoosterRed();
void TurnOff_BoosterRed();


void getSampleJoystick(unsigned *X, unsigned *Y);

#endif /* INITIALIZE_H_ */


