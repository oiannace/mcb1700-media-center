
#include "string.h"

#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
extern unsigned char ACE_pixel_data[43 * 70 * 2 + 1];
extern unsigned char TWO_pixel_data[46 * 70 * 2 + 1];
extern unsigned char THREE_pixel_data[44 * 70 * 2 + 1];
extern unsigned char FOUR_pixel_data[43 * 70 * 2 + 1];
extern unsigned char FIVE_pixel_data[44 * 70 * 2 + 1];
extern unsigned char SIX_pixel_data[44 * 70 * 2 + 1];
extern unsigned char SEVEN_pixel_data[44 * 70 * 2 + 1];
extern unsigned char EIGHT_pixel_data[44 * 70 * 2 + 1];
extern unsigned char NINE_pixel_data[44 * 70 * 2 + 1];
extern unsigned char TEN_pixel_data[44 * 70 * 2 + 1];
extern unsigned char JACK_pixel_data[44 * 70 * 2 + 1];
extern unsigned char QUEEN_pixel_data[43 * 70 * 2 + 1];
extern unsigned char KING_pixel_data[44 * 70 * 2 + 1];
int card_position = 15;
int card_count = 0;
int card_position_y = 150;
time_t t;
char dealer_amt_display[4];
char player_amt_display[4];

int seed = 65;
int r;
int player_card_amount = 0;
int dealer_card_amount = 0;
int dealer_bust = 0;

int main_menu = 0;
int new_game = 0;


void reset() {
	card_position = 15;
	card_count = 0;
	card_position_y = 150;

	seed = player_card_amount  * 17 + 31;
	
	player_card_amount = 0;
	dealer_card_amount = 0;
	dealer_bust = 0;
	main_menu = 0;
	new_game = 0;
}

void new_game_or_exit() {
	int joystick_val = 0;
	int joystick_prev = 0;
	while(1)		//loop forever
	{
			joystick_val = get_button();	//read the joystick
			
			if (joystick_val != joystick_prev)	//new input
			  {
					if(joystick_val == KBD_RIGHT) {
						main_menu = 1;
						break;
					}
					else if(joystick_val == KBD_LEFT) {
						new_game = 1;
						break;
					}
				}
	}
}

void lose_game() {
	
	sprintf(dealer_amt_display, "%d", dealer_card_amount);
	sprintf(player_amt_display, "%d", player_card_amount);
	
	GLCD_Clear(DarkGreen);
  GLCD_SetTextColor(Black);
	GLCD_DisplayString (0, 5, 1, "YOU LOSE!");
	GLCD_DisplayString (3, 0, 1, "You: ");
	GLCD_DisplayString (3, 5, 1, player_amt_display);
	GLCD_DisplayString (3, 9, 1, "Dealer: ");
	GLCD_DisplayString (3, 17, 1, dealer_amt_display);
	GLCD_DisplayString (7, 1, 1, "Right for new game, left to exit.");
	new_game_or_exit();
}


void display_card(int card_num) {
	card_count++;
		if(card_count > 5) {
			card_position = 15;
			card_position_y = 70;
			card_count = 0;
		}
		
	switch(card_num){
		case 0:
			GLCD_Bitmap(card_position, card_position_y, 43, 70, ACE_pixel_data);
			break;
		case 1:
			GLCD_Bitmap(card_position, card_position_y, 46, 70, TWO_pixel_data);
			break;
		case 2:
			GLCD_Bitmap(card_position, card_position_y, 44, 70, THREE_pixel_data);
			break;
		case 3:
			GLCD_Bitmap(card_position, card_position_y, 43, 70, FOUR_pixel_data);
			break;
		case 4:
			GLCD_Bitmap(card_position, card_position_y, 44, 70, FIVE_pixel_data);
			break;
		case 5:
			GLCD_Bitmap(card_position, card_position_y, 44, 70, SIX_pixel_data);
			break;
		case 6:
			GLCD_Bitmap(card_position, card_position_y, 44, 70, SEVEN_pixel_data);
			break;
		case 7:
			GLCD_Bitmap(card_position, card_position_y, 44, 70, EIGHT_pixel_data);
			break;
		case 8:
			GLCD_Bitmap(card_position, card_position_y, 44, 70, NINE_pixel_data);
			break;
		case 9:
			GLCD_Bitmap(card_position, card_position_y, 44, 70, TEN_pixel_data);
			break;
		case 10:
			GLCD_Bitmap(card_position, card_position_y, 44, 70, JACK_pixel_data);
			break;
		case 11:
			GLCD_Bitmap(card_position, card_position_y, 43, 70, QUEEN_pixel_data);
			break;
		case 12:
			GLCD_Bitmap(card_position, card_position_y, 44, 70, KING_pixel_data);
			break;
		default:
			GLCD_DisplayString(15,15,0,"no match");
	}
	
	card_position+=60;
}

void deal_card(int dealer) {
	
	r = rand() % 13;
	switch(dealer){
		case 0:
			display_card(r);
			if(r >= 10) {
				r = 10;
			}
			else {
				r +=1;
			}
			if(r == 1) {
				if((player_card_amount + 11) <= 21){
					r = 11;
				}
			}
			player_card_amount += r;
			if(player_card_amount > 21) {
				lose_game();
			}
			break;
		case 1:
			if(r >= 10) {
				r = 10;
			}
			else {
				r +=1;
			}
			dealer_card_amount += r;
			break;
	}
}

void dealer_finish() {
	while(dealer_card_amount < 17) {
		deal_card(1);
	}
}

void player_stays() {
	dealer_finish();
	if((player_card_amount > dealer_card_amount) || (dealer_card_amount > 21)) {
		sprintf(dealer_amt_display, "%d", dealer_card_amount);
		sprintf(player_amt_display, "%d", player_card_amount);
		
		GLCD_Clear(DarkGreen);
		GLCD_SetTextColor(Black);
		GLCD_DisplayString (0, 5, 1, "YOU WIN!");
		GLCD_DisplayString (3, 0, 1, "You: ");
		GLCD_DisplayString (3, 5, 1, player_amt_display);
		GLCD_DisplayString (3, 9, 1, "Dealer: ");
		GLCD_DisplayString (3, 17, 1, dealer_amt_display);
		GLCD_DisplayString (7, 1, 1, "Right for new game, left to exit.");
		new_game_or_exit();
	}
	else {
		lose_game();
	}
}

void game_start() {
	srand(seed);
	GLCD_Clear(DarkGreen);
  GLCD_SetTextColor(Black);
	GLCD_DisplayString (0, 0, 1, "Right to hit ");
	GLCD_DisplayString (1, 0, 1, "Left to stay");
	GLCD_DisplayString (2, 0, 1, "Return to Main Menu");
	deal_card(0);
	deal_card(0);
	deal_card(1);
	deal_card(1);
}

/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
void game (void) {                       /* Main Program                       */
	 //index to keep track of which icon the user is hovering over
										//'1' for photo viewer, '2' for audio file, '3' for game
	int joystick_val = 0;   //track the current joystick value
	int joystick_prev = 0;  //track the previous value for the joystick

	game_start();
	
  while(1)		//loop forever
	{
			joystick_val = get_button();	//read the joystick
			
			if (joystick_val != joystick_prev)	//new input
			  {
					if (joystick_val == KBD_RIGHT)
						{
							deal_card(0);
						}
					else if (joystick_val == KBD_LEFT)
						{
							player_stays();
						}
					else if(joystick_val == KBD_DOWN){
						main_menu = 1;
						GLCD_SetBackColor(Black);
						GLCD_SetTextColor(White);
						GLCD_DisplayString (0, 9, 1, "Return to Main Menu");
					}
					else if(joystick_val == KBD_UP) {
						main_menu = 0;
						GLCD_SetBackColor(Green);
						GLCD_SetTextColor(White);
						GLCD_DisplayString (0, 9, 1, "Return to Main Menu");
					}
					else if(joystick_val == KBD_SELECT && main_menu == 1){
						break;
					}
					
					if(main_menu == 1) {
						reset();
						break;
					}
					if(new_game == 1) {
						joystick_val = 0;   //track the current joystick value
						joystick_prev = 0;  
						reset();
						game_start();
					}
					
					
					joystick_prev = joystick_val;	
			}
		}
}