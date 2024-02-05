#include "header.h"

/* Programmer: Genevieve Kochel
Class: CptS 121
Date: 11/08/23
Program Description: This program will simulate a game of 5-card draw poker; The user will be able to
play against the computer (aka the dealer)
File purpose: This file will contain all cunction declarations for the program */

/* Function: void update_frequency_table(Hand player_hand, int frequency_table[13], int size)
Date created: November 16th
Date last modified: November 16th
Description: Function updates face frequency table that holds a number corresponding to how many times a face appears in a hand.
Accepts: The hand of the player who's hand needs to be evaluated, a frequency table array of size 13 (indexes 0-12) and the size of the frequency table.
Returns: None.
Preconditions: Frequency table must initially hold all 0 values to indicate that the player does not have a certain face. Frequency table must be
filled with 0's at end of each new hand evaluation for each player.
Postconditions: The frequency array must be modified to reflect the number of a certain face a player's hand has. This table will then be used to 
identify if the player has 1 pair, 2 pair etc.
*/
void update_frequency_table(Hand player_hand, int frequency_table[], int size)
{
	int j = 1;

	if (size == 13) // if dealing with face frequency array
	{

		for (j = 1; j < 6; ++j) // controls index of cards (cards is size 6, 0 index not used)
		{
			frequency_table[player_hand.cards[j].face]++; // goes to face value of hand at current index (j) and increments that face number index of freq table by 1
		}

	}

	if (size == 4) // if dealing with suit frequency array
	{

		for (j = 1; j < 6; ++j) // controls index of cards (cards is size 6, 0 index not used)
		{
			frequency_table[player_hand.cards[j].suit]++; // goes to suit value of hand at current index (j) and increments that suit number index of freq table by 1
		}
	}
}

/* Function: void reset_frequency_table(int frequency_table[], int size)
Date created: November 8th
Date last modified: November 19thth
Description: Function resets a frequency table of any size to all 0's after use. 
Accepts: A 1D frequency table array and the size of the frequency table.
Returns: None.
Preconditions: Frequency table must have been initialized in main and previously filled with values to represent the frequency of certain faces/suits.
Postconditions: The integer array must be overwritten with all 0's in every index of the arrayy.
Source: Deitel & Deitel - C How to Program
*/
void reset_frequency_table(int frequency_table[], int size) // resets frequency table back to all 0's after each player hand evaluation
{
	int i = 0;

	for (; i < size; ++i)
	{
		frequency_table[i] = 0;
	}
}

/* Function: void shuffle(int wDeck[][13])
Date created: November 8th
Date last modified: November 8th
Description: Function simulates a shuffle of a deck of 52 cards by randomly placing numbers 1-52 into 
corresponding rows and columns in the deck array. Each row and column corresponds to a suit and face.
Accepts: A 2D integer array that represents the deck of cards for the game of poker.
Returns: None.
Preconditions: Deck array must be initalized in main.
Postconditions: The integer array must be modified to have random placements of numbers 1-52 throughout the array.
Source: Deitel & Deitel - C How to Program
*/
void shuffle(int wDeck[][13])
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */

	/* for each of the 52 cards, choose slot of deck randomly */
	for (card = 1; card <= 52; card++)
	{
		/* choose new random location until unoccupied slot found */
		do
		{
			row = rand() % 4;
			column = rand() % 13;
		} while (wDeck[row][column] != 0);

		/* place card number in chosen slot of deck */
		wDeck[row][column] = card;
	}


}

/* Function: int deal_and_draw(int wDeck[][13], Hand* player_hand_ptr, int cards_to_deal_or_draw, int starting_card)
Date created: November 8th
Date last modified: November 19th
Description: This function deals both player's initial hands and goes through re-drawing for player 1 (the user). 
Accepts: A 2d deck array, a pointer to player1's hand, the number of cards to deal or draw for that function call and the starting card that 
the function will begin dealing/drawing at.
Returns: An integer representing the new starting card for following calls of this function or the dealer version of this function.
Preconditions: The deck array must be defined and already shuffled before function call. Only a 5 or numbers 1-3 may be passed into the cards_to_deal_or_draw
parameter and the starting card must be returned after each function call.
Postconditions: The player's hand struct must be updated with either a full hand of cards (deal) or replaced the cards specified in thier hand. The 
player may only select to replace up to 3 cards per round.
Source: Deitel & Deitel - C How to Program
*/
int deal_and_drawp1(int wDeck[][13], Hand* player1_hand_ptr, int cards_to_deal_or_draw, int starting_card)
{

	int row = 0;    /* row number, corresponds to suit */ 
	int column = 0; /*column number, corresponds to face */
	int card = starting_card;   /* card counter, how many cards dealt */ /*************SET EQUAL TO STARTING CARD< OG 1******************/
	int index = 1; // start placing cards at index 1 "card 1" of hand array
	


		/* initially deal cards */
	if (cards_to_deal_or_draw == 5)
	{
		for (card = starting_card; card < starting_card + cards_to_deal_or_draw; card++) // could be <=, check this?
		{
			/* loop through rows of wDeck */
			for (row = 0; row <= 3; row++)
			{
				/* loop through columns of wDeck for current row */
				for (column = 0; column <= 12; column++)
				{
					/* if slot contains current card, deal that card */
					if (wDeck[row][column] == card)
					{

						player1_hand_ptr->cards[index].suit = row;// put that card in index 1 of player hand (card #1 in hand)
						player1_hand_ptr->cards[index].face = column;
						++index;

					}
				}
			}

		}
	}

	else if (cards_to_deal_or_draw != 5) // indicates it is a re-draw for player 1
	{
		
			int cards_drawn = 0;
			int card_num = 0;
			int invalid_card = 0;
			int track_already_replaced[3] = { 0, 0, 0 }; // initialize array to track which cards already drawn (ensures can't draw same card number more than once)

			// prompt for which cards to keep/re-draw...first loop validates whether card has already been re-drawn, or if not between 1-5

			do  // stops prompting and drawing when user has no more cards left to draw
			{
				/*card = starting_card + cards_drawn;*/

				do // prompt which card to re-draw
				{
					invalid_card = 0; // set invalid card back to 0 every loop of searching for invalid card

					printf("\nPlease enter card #%d (1-5) that you would like to re-draw: ", cards_drawn + 1);
					scanf("%d", &card_num);

					// search card tracker array for card number entered

					for (int i = 0; i < 3 && invalid_card != 1; ++i) // only searches for invalid card as long as one hasn't been found
					{
						
						if (track_already_replaced[i] == card_num)
						{
							invalid_card = 1; // player tried to replace card already replaced
						}
						
					}

					if (card_num < 1 || card_num > 5 || invalid_card == 1)
					{
						system("cls");
						printf("Invalid input. Please try again. Note that you cannot re-draw the same card twice.\n");
					}

				} while (card_num < 1 || card_num > 5 || invalid_card == 1); // input validation to check if not 1-5, or already re-drawn

				// redraw that card and update cards drawn tracker (drawing loop) *************************************************************************
					// go to index in hand array of card player wants to re-draw and re-draw there (generate a new row/suit and col/face)


			
				/*for (; card < starting_card + cards_to_deal_or_draw; ++card)*/ 
				//{
					/* loop through rows of wDeck */
					for (row = 0; row <= 3; row++)
					{
						/* loop through columns of wDeck for current row */
						for (column = 0; column <= 12; column++)
						{
							/* if slot contains current card, deal that card */
							if (wDeck[row][column] == card)
							{

								player1_hand_ptr->cards[card_num].suit = row;
								player1_hand_ptr->cards[card_num].face = column;
			

							}
						}
					}



				track_already_replaced[cards_drawn] = card_num; // updates the card that has been drawn in tracking array

				++cards_drawn; // increment number of cards drawn so far
				++card;

			} while (cards_drawn != cards_to_deal_or_draw); // keeps drawing as long as there are more cards left to draw


	}

		card = starting_card + cards_to_deal_or_draw; // update new current card in deck to return from entire function

		return card; // new starting card for next call of this function

}

//Function: int is_pair(int face_freq_table[13])
//Date created : November 8th
//Date last modified : November 19th
//Description : Determines if a player has a pair depending on the frequency table.
//Accepts : The face frequency table.
//Returns : An integer (0 or 1) that represents whether the player has a pair.
//Preconditions : The face frequency table must have been updated with the frequency of the face values of a player's hand.
//Postconditions : The function must return 1 if the player has a pair, 0 if the player does not.

int is_pair(int face_freq_table[13]) // returns 1 if SINGLULAR pair has been found
{
	int index = 0;

	for (; index < 13; ++index)
	{
		if (face_freq_table[index] == 2) // indicates two of same face has been found
		{
			return 1;
		}
	}

	return 0;
}

//Function: int is_two_pair(int face_freq_table[13])
//Date created : November 8th
//Date last modified : November 19th
//Description : Determines if a player has two pair depending on the frequency table.
//Accepts : The face frequency table.
//Returns : An integer (0 or 1) that represents whether the player has two pair.
//Preconditions : The face frequency table must have been updated with the frequency of the face values of a player's hand.
//Postconditions : The function must return 1 if the player has two pair, 0 if the player does not.

int is_two_pair(int face_freq_table[13])
{
	int index = 0, pair_count = 0;

	for (; index < 13; ++index)
	{
		if (face_freq_table[index] == 2)
		{
			++pair_count; // keeps track of amount of distinct pairs found
		}
		if (pair_count == 2) // 2 distinct pairs have been found
		{

			return 1; // returns 1 as two distinct pairs have been found

		}
	}

	return 0; // if pair count never reaches 2, there isn't two pairs
}

//Function: int is_three_of_kind(int face_freq_table[13])
//Date created : November 8th
//Date last modified : November 19th
//Description : Determines if a player has three of a kind depending on the frequency table.
//Accepts : The face frequency table.
//Returns : An integer (0 or 1) that represents whether the player has three of a kind.
//Preconditions : The face frequency table must have been updated with the frequency of the face values of a player's hand.
//Postconditions : The function must return 1 if the player has three of a kind, 0 if the player does not.


int is_three_of_kind(int face_freq_table[13])
{

	int index = 0;

	for (; index < 13; ++index)
	{
		if (face_freq_table[index] == 3) 
		{
			return 1; // found three of a kind
		}
	}

	return 0; // three of a kind has not been found
}

//Function: int is_four_kind(int face_freq_table[13])
//Date created : November 8th
//Date last modified : November 19th
//Description : Determines if a player has four of a kind depending on the frequency table.
//Accepts : The face frequency table.
//Returns : An integer (0 or 1) that represents whether the player has four of a kind.
//Preconditions : The face frequency table must have been updated with the frequency of the face values of a player's hand.
//Postconditions : The function must return 1 if the player has four of a kind, 0 if the player does not.

int is_four_kind(int face_freq_table[13])
{
	int index = 0;

	for (; index < 13; ++index)
	{
		if (face_freq_table[index] == 4)
		{
			return 1; // found four of a kind
		}
	}

	return 0; // four of a kind was not found in freq table 
}

//Function: int is_full_house(int face_freq_table[13])
//Date created : November 8th
//Date last modified : November 19th
//Description : Determines if a player has a full house depending on the frequency table.
//Accepts : The face frequency table.
//Returns : An integer (0 or 1) that represents whether the player has a full house.
//Preconditions : The face frequency table must have been updated with the frequency of the face values of a player's hand.
//Postconditions : The function must return 1 if the player has a full house, 0 if the player does not.

int is_full_house(int face_freq_table[13])
{
	int index = 0, two_pair_found_at = 0, three_pair_found = 0;

	for (; index < 13; ++index) // search for at least a pair
	{

		if (face_freq_table[index] == 2) // if a pair is found, guarenteed if will find full house eventually because 5 cards
		{

			for (index = 0; index < 13; ++index) // search frequency table again for three of a kind
			{
				if (face_freq_table[index] == 3)
				{
					return 1; // a pair and three of a kind found 
				}
			}
			
		}

	}

	return 0; // full-house not found


}

//Function: int is_flush(int suit_freq_table[4])
//Date created : November 8th
//Date last modified : November 19th
//Description : Determines if a player has a flush depending on the frequency table.
//Accepts : The suit frequency table.
//Returns : An integer (0 or 1) that represents whether the player has a flush.
//Preconditions : The face frequency table must have been updated with the frequency of the suit values of a player's hand.
//Postconditions : The function must return 1 if the player has a flush, 0 if the player does not.

int is_flush(int suit_freq_table[4])
{

	int index = 0;

	for (; index < 4; ++index)
	{
		if (suit_freq_table[index] == 5)
		{
			return 1; // found a flush (5 of same suit)
		}
	}

	return 0; // did not find a flush/ 5 of same suit


}

//Function: int is_flush(int suit_freq_table[4])
//Date created : November 8th
//Date last modified : November 19th
//Description : Determines if a player has a straight depending on the frequency table.
//Accepts : The face frequency table.
//Returns : An integer (0 or 1) that represents whether the player has a straight.
//Preconditions : The face frequency table must have been updated with the frequency of the face values of a player's hand.
//Postconditions : The function must return 1 if the player has a straight, 0 if the player does not.

int is_straight(int face_freq_table[13])
{
	int index = 0, straight_count = 0;

	for (; index < 13; ++index)
	{
		if (face_freq_table[index] == 1)
		{
			++straight_count; // keeps counting up if finds a single 1 in 5 consecutive cells  (2, 3, 4, 5, 6)
		}
		if (straight_count == 5)
		{
			return 1; // found 5 consecutive face values in frequency array
		}
		else if (face_freq_table[index] != 1)
		{
			straight_count = 0; // found break in consecutive line of 1's in freq table, 
		}
	}

		return 0; // did not find a straight
	
	
}

//Function: int evaluate_hand(Hand player_hand, int face_freq_table[13], int suit_freq_table[4])
//Date created : November 8th
//Date last modified : November 19th
//Description : Function evaluates the player's hand and ranks the quality of the hand depending on the precedence
// of the hand type, a pair being the lowest and four of a kind being the highest.
//Accepts : The face and suit freqency tables corresponding to the player's hand that is being evaluated.
//Returns : An integer representing the number of points earned for that hand. 0 will be returned if there are no combos found.
//Preconditions : The face and suit frequency tables of the player must have been filled with the correspoinding values to thier hand prior to function call.
//Postconditions : The frequency arrays must be reset and reevaluated before a second call to this function.

int evaluate_hand(int face_freq_table[13], int suit_freq_table[4])
{
	int points_earned = 0; // returns 0 if hand did not have any of the combos, if both players get 0 points,
	//evaluate highest card via tiebreaker function

	if (is_pair(face_freq_table) == 1) // one pair
	{

		points_earned = 1;

	}

	if (is_two_pair(face_freq_table) == 1) // two pair
	{

		points_earned = 2;

	}

	if (is_three_of_kind(face_freq_table) == 1) // three of a kind
	{

		points_earned = 3;

	}

	if (is_four_kind(face_freq_table) == 1) // four of a kind found
	{

		points_earned = 7;

	}

	if (is_full_house(face_freq_table) == 1) // full house
	{

		points_earned = 6;

	}

	if (is_flush(suit_freq_table) == 1) // flush
	{

		points_earned = 5;

	}


	if (is_straight(face_freq_table) == 1) // straight
	{

		points_earned = 4;

	}

	return points_earned;


}


//Function: int break_tie(Hand player1_hand, Hand dealer_hand)
//Date created : November 8th
//Date last modified : November 20th
//Description : Function finds the high card in each player's hand in the event that both players do not have any of the hand combinations. 
// If both of the player's high cards are the same, the function continues to evaluate until a distinct high card is found and compares those. 
// In the event that the faces of all of the cards in each hand are the same, the function returns -1. 
//Accepts : A hand struct representing player 1's hand and a hand struct representing player 2's hand.
//Returns : -1 if no distinct high cards could be found and compared, 0 if the dealer had the high card and 1 if player 1 had the high card and won.
//Preconditions : Function is only called if the hand must have been evaluated so that neither player earned any points 
// for thier hand (no combos were found). Player 1 points and dealer points both == 0 in main.
//Postconditions : The function must return -1, 0 or 1 depending on the outcome.

int break_tie(Hand player1_hand, Hand dealer_hand) // finds the highest cards in each hand and compares (ace = 1 in this case)
{
	int player1_max = 0, dealer_max = 0, index = 1;
	int temp = 0;


	// sort player 1 hand from lowest to highest values in the array

	for (index = 1; index < 6; ++index) 
	{
		for (int j = 1; j < 5 - index + 1; ++j) {
			if (player1_hand.cards[j].face > player1_hand.cards[j + 1].face) {
				
				temp = player1_hand.cards[j].face;
				player1_hand.cards[j].face = player1_hand.cards[j + 1].face;
				player1_hand.cards[j + 1].face = temp;
			}
		}
	}

	for (index = 1; index < 6; ++index) 
	{
		for (int j = 1; j < 5 - index + 1; ++j) {
			if (dealer_hand.cards[j].face > dealer_hand.cards[j + 1].face) {

				temp = dealer_hand.cards[j].face;
				dealer_hand.cards[j].face = dealer_hand.cards[j + 1].face;
				dealer_hand.cards[j + 1].face = temp;
			}
		}
	}

	for (index = 5; index >= 1; --index) // checks from index 6 (card 5 -- highest ranking face in hand) down to index 1 (lowest ranking card in hand)
	{

		if (player1_hand.cards[index].face > dealer_hand.cards[index].face)
		{
			return 1; // player 1 had the higher card

		}
		if (player1_hand.cards[index].face < dealer_hand.cards[index].face)
		{
			return 0; // dealer had the higher card

		}
		

	} // check each index down to 1 until one value in a hand is bigger than the other


	return -1; // all the high cards in each hand were equivalent, no clear winner


}


///* Function: int dealer_evaluate_and_redraw(Hand* dealer_hand_ptr, int dealer_points, int starting_card, int wDeck [][13])
//Date created: November 10th
//Date last modified: November 19th
//Description: This function automatically evaluates the quality of the dealer's hand and selects to replace cards in it's hand accordingly.
//Accepts: A pointer to the dealer's hand struct, the number of points the dealer earned from it's original hand (decided by the evaluate_hand() function)
//, the card to start dealing in the deck from, and the shuffled deck array.
//Returns: An integer representing the new starting card for following calls of this function or the player 1 version of this function.
//Preconditions: Function must only be called if the dealer earned 3 points or below for that hand.
//The deck array must be defined and already shuffled before function call. The quality of the dealer's hand must have been evaluated by the
//evaluate hand function and passed in as the dealer points parameter and the starting card must be returned after each function call.
//Postconditions: The dealer's hand must be updated with the appropriate number of re-drawn cards (between 1-3). 
//*/

int dealer_evaluate_and_redraw(Hand* dealer_hand_ptr, int dealer_points, int starting_card, int wDeck [][13])
{
	int cards_to_draw = 0, card_num = 0, card = starting_card;
	int row = 0, column = 0;
	int cards_drawn = 0; // keeps track of how many cards drawn so far
	int invalid_card = 0; // set to 1 if card generated has already been re-drawn

	int track_already_replaced[3] = { 0 }; // initialize tracking array

	// determine number of cards to re-draw

	// if (dealer_points >= 4) // don't re-draw any cards if hand is already high enough
	if (dealer_points == 3)
	{
		cards_to_draw = 2; // draw two cards
	}
	else if (dealer_points == 2)
	{
		cards_to_draw = 1; // draw one card
	}
	else if (dealer_points == 1 || dealer_points == 0)
	{
		cards_to_draw = 3; // draw 3 cards
	}


	do  // stops prompting and drawing when dealer has no more cards left to draw
	{

		do 
		{
			invalid_card = 0; // reset invalid card flag

			card_num = rand() % 5 + 1; // generate random card index to replace 1-5

			// search card tracker array for card number entered

			for (int i = 0; i < 3 && invalid_card != 1; ++i)
			{
				if (track_already_replaced[i] == card_num)
				{
					invalid_card = 1; // player tried to replace card already replaced
				}
			}

		} while (invalid_card == 1); // input validation to check if not 1-5, or already re-drawn

		/* redraw that card and update cards drawn tracker go to index in hand array of valid card
		 generated and get a new row/suit and col/face */

			/* loop through rows of wDeck */
			for (row = 0; row <= 3; row++)
			{
				/* loop through columns of wDeck for current row */
				for (column = 0; column <= 12; column++)
				{
					/* if slot contains current card, deal that card */
					if (wDeck[row][column] == card)
					{

						dealer_hand_ptr->cards[card_num].suit = row;
						dealer_hand_ptr->cards[card_num].face = column;
						

					}
				}
			}

		

		track_already_replaced[cards_drawn] = card_num; // updates the card that has been drawn in tracking array

		++cards_drawn; // increment number of cards drawn so far
		++card;

	} while (cards_drawn != cards_to_draw); // keeps drawing as long as there are more cards left to draw

	card = starting_card + cards_to_draw; // update new current card in deck to return from entire function

	return card;

}


//Function: void print_cards(Hand* player_hand, const char* wFace[], const char* wSuit[])
//Date created : November 8th
//Date last modified : November 19th
//Description : Function prints the cards in a player's hand (1-5) with the face and suit of each card.
//Accepts : A pointer to the player's hand struct, the string array holding the face names, and the string array holding the suit names.
//Returns : None.
//Preconditions : The face and suit arrays must be defined in main and the hand struct must have been filled with face and suit values prior to 
// function call.
//Postconditions : The cards of a player's hand (1-5) will be printed to the screen.

void print_cards(Hand* player_hand, const char* wFace[], const char* wSuit[], int player_num)
{
	int index = 1; // set index = 1 because hand array is size 6...don't want to print 0 index

	if (player_num == 1) {

		printf("*** Your hand ***\n");

	}
	else {

		printf("\n*** Dealer's hand ***\n");
	}

	for (; index < 6; ++index)
	{
		
		printf("Card [%d]: %5s of %-8s%c", index, wFace[player_hand->cards[index].face], wSuit[player_hand->cards[index].suit], '\n');

	}// use this function to print out cards to player 1

}


//Function: int display_menu_get_input(void)
//Date created : November 8th
//Date last modified : November 19th
//Description : Function displays the initial poker menu and validates input from the user.
//Accepts : None.
//Returns : The user input (1-3).
//Preconditions : None.
//Postconditions : The input returned must be used in a switch statement controlling the gameplay, rule display or exit.

int display_menu_get_input(void)
{

	int input = 0;

	do {
		
		
		printf("Welcome to Poker!!\n"
			"Please select from the following menu:\n"
			"1) Display game rules\n"
			"2) Play game\n"
			"3) Exit game\n"
			"Please enter your input here: "
		);

		scanf("%d", &input); // get input

		if (input < 1 || input > 3)
		{
			system("cls");
			printf("Sorry, that input is invalid. Please try again.\n\n");
		}

	} while (input < 1 || input > 3); // while input not 1-3

	return input;
	
}

//Function: int display_rules(void)
//Date created : November 8th
//Date last modified : November 19th
//Description : Function displays the poker rules and prompts for/validates input for exiting the game or going back to the main menu.
//Accepts : None.
//Returns : The user input 1 or 0.
//Preconditions : None.
//Postconditions : The input returned must be used to determine if the game is exited or not.
int display_rules(void)
{
	int input = 0;


	printf("Welcome to 5-card-draw Poker!! Each player gets 5 cards. You may choose\n"
		"to re - draw up to 3 cards after the initial deal, or you can play your hand.\n"
		"The winner is determined based on the quality of your hand versus your opponent's\n"
		"hand. The types of hands include: one pair, two pair, three of a kind, four of a kind,\n"
		"full-house, flush, or straight. If the value of your hand is greater than that of your opponent's, you win!\n");

	do {
		
		printf("\nWould you like to go back to the main menu? Enter 1 for yes, 0 for no: ");
		scanf("%d", &input);

		if (input != 1 && input != 0)
		{
			system("cls");
			printf("Invalid input. Please try again.\n");
		}

	} while (input != 1 && input != 0);

	return input;

}

//Function: int another_round(void)
//Date created : November 8th
//Date last modified : November 20th
//Description : Function gets input after each round of poker is done to determine if player wants to keep playing additional rounds.
//Accepts : None.
//Returns : The user input 1 or 0.
//Preconditions : None.
//Postconditions : The input returned must be used to determine if the round play is exited or not.
int another_round(void)
{
	int input = 0;

	do {

		printf("Do you want to play another round?\n"
			"Please enter 1 for yes, 0 for no: "
		);
		scanf("%d", &input);

		if (input != 1 && input != 0)
		{
			system("cls");
			printf("\nInvalid input. Please try again.\n");

		}

	} while (input != 1 && input != 0); // if 0, will exit entire program

	return input;
}

