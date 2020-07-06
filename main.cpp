#include "PA5.h"

int main(void)
{
	srand(time(0)); // establish randomness seed for who goes first
	int program_running = 1, option = 0, players_created = 0;
	cout << "Welcome to Yu-Gi-Oh!\n\n";

	Player player1, player2; // initialize players: given starting life points, hand size, and player number that won't change as more games are played.
	player1.life_points = 8000;
	player1.player_num = 1;
	player2.life_points = 8000;
	player2.player_num = 2;

	player1.hand_size = 5;
	player2.hand_size = 5;

	while (program_running)
	{
		do { // continuously display main menu until satisfactory input
			display_menu();
			cin >> option;
			system("cls");
		} while (!check_option(option, 6));

		switch (option)
		{
		case 1: display_rules();
			break;
		case 2: create_players(player1, player2);
			players_created = 1;
			break;
		case 3: if (players_created) // make sure option 2 already selected
					add_cards(player1, player2);
				else
					cout << "You must create players first!\n";
			break;
		case 4: if (players_created) // make sure option 2 already selected
					trade_cards(player1, player2);
				else
					cout << "You must create players first!\n";
			break;
		case 5: if (players_created) // make sure option 2 already selected
					battle(player1, player2);
				else
					cout << "You must create players first!\n";
			break;
		case 6: cout << "Thanks for playing!\n";
			program_running = 0; // end program
			break;
		}

	}


	return 0;
}