/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: LED Flasher and Graphic Demo
 * Note(s): 
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2008-2011 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/
                  
#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"
#include <time.h>
extern void photo_viewer(void);
extern void music_player(void);
extern void game(void);
int main (void) 
{  	/* Main Program                       */
	int cursor = 1; //index to keep track of which icon the user is hovering over
										//'1' for photo viewer, '2' for audio file, '3' for game
	int joystick_val = 0;   //track the current joystick value
	int joystick_prev = 0;  //track the previous value for the joystick
	
	KBD_Init();

  LED_Init ();
  GLCD_Init();

  GLCD_Clear  (White);
  SysTick_Config(SystemCoreClock/100); 
	GLCD_SetBackColor(White);
  GLCD_SetTextColor(Black);
	GLCD_DisplayString (0, 0, 1, "COE 718 Project Demo");
	GLCD_DisplayString (1, 6, 1, "MAIN MENU");

  for (;;)		//loop forever
	{
			joystick_val = get_button();	//read the joystick
			
			if (joystick_val != joystick_prev)	//new input
			  {
					if (joystick_val == KBD_DOWN)
						{
							cursor +=1;	//joystick down means change the cursor pointer
							cursor = cursor %4;		//pressing down brings you back to the top
						}
					else if (joystick_val == KBD_UP)
						{
							cursor -=1;
							if (cursor < 1)
							{
									cursor = 1;
							}
						}
					else if(joystick_val == KBD_SELECT)
							{
								if (cursor == 1)
								{
									photo_viewer();
									GLCD_Clear(White);
									GLCD_SetBackColor(White);
									GLCD_SetTextColor(Black);
									GLCD_DisplayString (0, 0, 1, "COE 718 - Media Center");
									GLCD_DisplayString (1, 6, 1, "MAIN MENU");									
									//cursor =1;
								}
								else if (cursor == 2)
								{
									//music player function call
									music_player();
									//delay(10);
									GLCD_Clear(White);
									GLCD_SetBackColor(White);
									GLCD_SetTextColor(Black);
									GLCD_DisplayString (0, 0, 1, "COE 718 - Media Center");
									GLCD_DisplayString (1, 6, 1, "MAIN MENU");									
									//cursor =2;
								}
								else if (cursor == 3)
								{
									GLCD_Clear(White);
									game();
									GLCD_Clear(White);
									GLCD_SetBackColor(White);
									GLCD_SetTextColor(Black);
									GLCD_DisplayString (0, 0, 1, "COE 718 - Media Center");
									GLCD_DisplayString (1, 6, 1, "MAIN MENU");
									//cursor = 1;
								}
								
							}
					joystick_prev = joystick_val;	
			}
			
			/*this is to update the LCD each time the user interfaces with the joystick*/
			if (cursor == 1)	//for displaying now
				{
						GLCD_SetBackColor(Green);
						GLCD_SetTextColor(White);
						GLCD_DisplayString(4,0,1, "Photo Gallery");
						GLCD_SetBackColor(White);
						GLCD_SetTextColor(Black);
						GLCD_DisplayString(5,0,1, "MP3 Player");
						GLCD_DisplayString(6,0,1, "Game");
						
				}
			else if(cursor == 2)
				{
						GLCD_SetBackColor(White);
						GLCD_SetTextColor(Black);
						GLCD_DisplayString(4,0,1, "Photo Gallery");
						GLCD_SetBackColor(Green);
						GLCD_SetTextColor(White);
						GLCD_DisplayString(5,0,1, "MP3 Player");
						GLCD_SetBackColor(White);
						GLCD_SetTextColor(Black);
						GLCD_DisplayString(6,0,1, "Game");
				}
			else if(cursor == 3)
				{
						GLCD_SetBackColor(White);
						GLCD_SetTextColor(Black);
						GLCD_DisplayString(4,0,1, "Photo Gallery");
						GLCD_DisplayString(5,0,1, "MP3 Player");
						GLCD_SetBackColor(Green);
						GLCD_SetTextColor(White);
						GLCD_DisplayString(6,0,1, "Game");
				}
	}
}