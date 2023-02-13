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
extern unsigned char WAVE_ART[250 * 160 * 2 + 1];
extern unsigned char TORONTO_RAPTORS[170 * 170 * 2 + 1];
extern unsigned char LUNENBURG[250 * 167 * 2 + 1];



/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
void photo_viewer (void) {                       /* Main Program                       */
	int pic_num = 0; //index to keep track of which icon the user is hovering over
										//'1' for photo viewer, '2' for audio file, '3' for game
	int joystick_val = 0;   //track the current joystick value
	int joystick_prev = 0;  //track the previous value for the joystick
	int back_flag = 0;
	
	GLCD_Clear(White);
	GLCD_Bitmap (  0,   0, 250,  160, WAVE_ART);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString (8, 0, 1, "Back to Main Menu");
	
  while(1)		//loop forever
	{
			joystick_val = get_button();	//read the joystick
			
			if (joystick_val != joystick_prev)	//new input
			  {
					
					if (joystick_val == KBD_RIGHT)
						{
							pic_num +=1;	//joystick down means change the cursor pointer
							pic_num = pic_num %3;		//pressing down brings you back to the top
						}
					else if (joystick_val == KBD_LEFT)
						{
							pic_num -=1;
							if (pic_num < 0)
							{
									pic_num = 2;
							}
						}
					else if(joystick_val == KBD_DOWN)
						{
							GLCD_SetTextColor(White);
							GLCD_SetBackColor(Black);
							GLCD_DisplayString (8, 0, 1, "Back to Main Menu");
							back_flag = 1;
						}
					else if(joystick_val == KBD_UP)
					{
						  GLCD_SetTextColor(Black);
							GLCD_SetBackColor(White);
							GLCD_DisplayString (8, 0, 1, "Back to Main Menu");
							back_flag = 0;
					}
					else if(joystick_val == KBD_SELECT && back_flag == 1)
					{
						break;
					}
					
					if (pic_num == 0)
						{
							//GLCD_Clear();
							GLCD_Bitmap (  0,   0, 250,  160, WAVE_ART);
						}
					else if (pic_num == 1)
						{
							//GLCD_Clear(White);
							GLCD_Bitmap (  0,   0, 170,  170, TORONTO_RAPTORS);
						}
					else if (pic_num == 2)
						{
							//GLCD_Clear(White);
							GLCD_Bitmap (  0,   0, 250,  167, LUNENBURG);
						}
					joystick_prev = joystick_val;	
			}
		}
}
