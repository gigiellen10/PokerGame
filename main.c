#include "header.h"

/* Programmer: Genevieve Kochel
Class: CptS 121
Date: 11/08/23
Program Description: This program will simulate a game of 5-card draw poker; The user will be able to
play against the computer (aka the dealer)
File purpose: This file contains the main function */


int main(void)
{
	
	/* initialize suit array */
	const char* suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	/* initialize face array */
	const char* face[13] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
		"Nine", "Ten", "Jack", "Queen", "King" };

	/* initalize deck array and frequency table */
	
	int deck[4][13] = { 0 };
	
	int face_freq_table[13] = { 0 }; // pass into pair, two pair, three of a kind, full house functions
	int suit_freq_table[4] = { 0 }; // pass into flush function

	srand((unsigned)time(NULL)); /* seed random-number generator */

	/* initalize player 1 hand and dealer hand */

	Hand player1_hand = { {0} };
	Hand dealer_hand = { {0} };
	
	int input = 0, display_menu = 0, play_game = 0, start_card = 1, dealer_points = 0, player1_points = 0,
		winner = 0, replace_cards = 0, cards_to_draw = 0, play = 0, play_flag = 0; // start dealing at card number 1


	do { // reset all variables while playing

		
		/* Menu portion */

		do {
			
			system("cls");
			input = display_menu_get_input();

			switch (input)
			{
			case 1:

				system("cls");
				display_menu = display_rules(); // display_menu = display_rules(); ...display rules function, also takes player back to main menu


				break;

			case 2:

				play_game = 1; // enter game play
				display_menu = 0; // break out of menu loop
				

				break;

			case 3:

				system("cls");
				printf("Thanks for playing Poker! 'Till next time...\n");
				// exit entire program
				return;

				break;
			}

		} while (display_menu == 1);

		if (display_menu == 0 && play_game != 1)
		{
			system("cls");
			printf("Thanks for playing Poker! 'Till next time...\n");
			return; // user wanted to exit entire gameplay
		}

		/* Game play portion */
		do
		{

			int deck[4][13] = { 0 };

			int face_freq_table[13] = { 0 }; // pass into pair, two pair, three of a kind, full house functions
			int suit_freq_table[4] = { 0 };

			Hand player1_hand = { {0} };
			Hand dealer_hand = { {0} };

			int input = 0, display_menu = 0, start_card = 1, dealer_points = 0, player1_points = 0,
				winner = 0, replace_cards = 0, cards_to_draw = 0, play = 0; // start dealing at card number 1

			
			system("cls");
			printf("Let's play 5-card-draw!!\n");
			printf("\n*** Dealer status: Dealing cards ***\n");
			putchar('\n');
			system("pause");

			// clear screen
			system("cls");

			// shuffle deck
			shuffle(deck);

			// deal cards to player 1
			start_card = deal_and_drawp1(deck, &player1_hand, 5, start_card);

			// print player 1 cards
			print_cards(&player1_hand, face, suit, 1);

			// deal cards to dealer
			start_card = deal_and_drawp1(deck, &dealer_hand, 5, start_card);
			printf("\nThe dealer's hand has been dealt face-down.\n");
			putchar('\n');
			system("pause");

			// prompt if player 1 wants to replace cards

			system("cls");
			print_cards(&player1_hand, face, suit, 1);

			do {

				printf("\nWould you like to re-draw cards for this hand? Please enter 1 for yes, 0 for no: ");
				scanf("%d", &replace_cards);

				if (replace_cards != 1 && replace_cards != 0)
				{
					system("cls");
					printf("\nInvalid input. Please try again.\n");
				}


			} while (replace_cards != 1 && replace_cards != 0); // input validation

			// if yes, get number to redraw and allow redraw
			if (replace_cards == 1)
			{
				system("cls");

				do {

					print_cards(&player1_hand, face, suit, 1);
					printf("\nHow many cards would you like to re-draw? (You may only re-draw up to 3 cards): ");
					scanf("%d", &cards_to_draw);

					if (cards_to_draw > 3 || cards_to_draw < 1)
					{
						system("cls");
						printf("\nInvalid input. Please enter a number 1-3.\n");
						putchar('\n');
					}

				} while (cards_to_draw > 3 || cards_to_draw < 1);

				start_card = deal_and_drawp1(deck, &player1_hand, cards_to_draw, start_card);
				putchar('\n');
				system("cls");
				print_cards(&player1_hand, face, suit, 1);

			}

			// evaluate player 1 hand and determine points earned

			update_frequency_table(player1_hand, face_freq_table, 13); // fill frequency table with hand
			update_frequency_table(player1_hand, suit_freq_table, 4);
			player1_points = evaluate_hand(face_freq_table, suit_freq_table); // evaluate dealer points for that hand

			reset_frequency_table(face_freq_table, 13); // reset each freq table after use
			reset_frequency_table(suit_freq_table, 4);


			// evaluate dealer hand (1st time) -- if dealer earned above three points, don't call re-draw

			printf("\n*** Dealer status: Evaluating hand ***\n");
			putchar('\n');
			system("pause");
			system("cls");

			update_frequency_table(dealer_hand, face_freq_table, 13); // fill frequency table with hand
			update_frequency_table(dealer_hand, suit_freq_table, 4);
			dealer_points = evaluate_hand(face_freq_table, suit_freq_table); // evaluate dealer points for that hand

			reset_frequency_table(face_freq_table, 13); // reset each freq table after use
			reset_frequency_table(suit_freq_table, 4);

			// call dealer re-draw function if earned 3 points or below

			if (dealer_points <= 3)
			{
				int previous_start_card = 0;

				previous_start_card = start_card; // store value of start card before update to determine how many cards were re-drawn

				printf("*** Dealer status: Re-drawing cards ***\n");
				putchar('\n');
				system("pause");
				system("cls");

				start_card = dealer_evaluate_and_redraw(&dealer_hand, dealer_points, start_card, deck);

				// re-evaluate dealer hand for a second time, update points with new points earned for new hand

				update_frequency_table(dealer_hand, face_freq_table, 13); // fill frequency table with hand
				update_frequency_table(dealer_hand, suit_freq_table, 4);
				dealer_points = evaluate_hand(face_freq_table, suit_freq_table); // evaluate dealer points for that hand

				reset_frequency_table(face_freq_table, 13); // reset each freq table after use
				reset_frequency_table(suit_freq_table, 4);

				printf("The dealer re-drew %d cards!\n", start_card - previous_start_card);
			}

			printf("Continue the game to determine the winner!!\n");
			putchar('\n');
			system("pause");
			system("cls");


			// if both player 1 and dealer has same number of points, call break tie function

			if (player1_points == dealer_points)
			{
				printf("Oh no, looks like there's a tie! Continue to determine the high cards and resolve the tie.\n"); // oh no theres a tie!
				putchar('\n');
				system("pause");
				system("cls");

				winner = break_tie(player1_hand, dealer_hand);
				if (winner == 1) // if player 1 has more points, print player 1 winner
				{
					printf("Congratulations, you beat the dealer!!\n\n");
					print_cards(&player1_hand, face, suit, 1);
					print_cards(&dealer_hand, face, suit, 0);
				}
				else if (winner == 0) // if dealer has more points, print dealer winner
				{
					printf("Uh oh, the house won this round!! Read 'em and weep!\n");
					print_cards(&dealer_hand, face, suit, 0);
				}
				else
				{
					printf("The high cards in each hand were the same and no winner was determined...\n"
						"Looks like this round was draw!!\n");
					print_cards(&player1_hand, face, suit, 1);
					print_cards(&dealer_hand, face, suit, 0);
				}



			}
			else
			{

				if (player1_points > dealer_points) // if player 1 has more points, print player 1 winner
				{
					printf("Congratulations, you beat the dealer!!\n");
				}
				else if (player1_points < dealer_points) // if dealer has more points, print dealer winner
				{
					printf("Uh oh, the house won this round!! Read 'em and weep!\n");
					print_cards(&dealer_hand, face, suit, 0);
				}

			}

			putchar('\n');
			system("pause");
			system("cls");

			play_flag = another_round();
			

		} while (play_flag == 1);
		
		// if user wants to stop playing game at end (ask them), set play_game = 0
		do {

			printf("\nDo you want to go back to the main menu?\n"
				"Please enter 1 for yes, 0 for no: "
			);
			scanf("%d", &play_game);

			if (play_game != 1 && play_game != 0)
			{
				system("cls");
				printf("\nInvalid input. Please try again.\n");

			}

		} while (play_game != 1 && play_game != 0); // if 0, will exit entire program
		
		system("cls");

	} while (play_game == 1); // set = 0 to break out of entire program

	printf("Thanks for playing 5-card-draw! 'Till next time!!\n");
	return 0;
}