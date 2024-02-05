/* Programmer: Genevieve Kochel 
Class: CptS 121
Date: 11/08/23
Program Description: This program will simulate a game of 5-card draw poker; The user will be able to 
play against the computer (aka the dealer) 
File purpose: This file will contain all #includes and #defines for the program, any struct declarations, and 
all function prototypes */

// source code taken from Deitel & Deitel - C How to Program

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

typedef struct card {

	int suit; // represents row number in deck array
	int face; // represents column number in deck array

} Card;

typedef struct hand {

	Card cards[6]; // array of cards, each card has a suit (int) and a face (int)
	// size 6 so can use index number as input for replacing/discarding cards

} Hand;

void shuffle(int wDeck[][13]);
int deal_and_drawp1(int wDeck[][13], Hand* player1_hand_ptr, int cards_to_deal_or_draw, int starting_card);
int dealer_evaluate_and_redraw(Hand* dealer_hand_ptr, int dealer_points, int starting_card, int wDeck[][13]);
int display_rules(void);
void print_cards(Hand* player_hand, const char* wFace[], const char* wSuit[], int player_num);
int display_menu_get_input(void);
int is_pair(int face_freq_table[13]);
int is_two_pair(int face_freq_table[13]);
int is_three_of_kind(int face_freq_table[13]);
int is_four_kind(int face_freq_table[13]);
int is_full_house(int face_freq_table[13]);
int is_flush(int suit_freq_table[4]);
int is_straight(int face_freq_table[13]);
int evaluate_hand(int face_freq_table[13], int suit_freq_table[4]);
int break_tie(Hand player1_hand, Hand dealer_hand);
void update_frequency_table(Hand player_hand, int frequency_table[], int size);
void reset_frequency_table(int frequency_table[], int size);
void update_frequency_table(Hand player_hand, int frequency_table[], int size);
int another_round(void);