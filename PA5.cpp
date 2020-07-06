#include "PA5.h"

//deck

Stack::Stack() // constructor
{
	top = nullptr;
	deck_size = 30;
}

Card Stack::pop() // draw card from deck
{
	Card monster = { "", -1, -1, "" }; // make a dummy card
	if (top != nullptr) // if not empty
	{
		monster = top->monster; // collect card
		top = top->next; // set next card as new top
	}

	if (monster.atk != -1) // dummy card doesn't remain, meaning a card was actually popped out
		deck_size--; // decrement deck size

	return monster;
}

void Stack::push(Card monster) // add card to deck
{
	Node* new_node = new Node; // make new node
	new_node->monster = monster; // put card in it
	new_node->next = nullptr;

	if (top == nullptr) // if empty deck
	{
		top = new_node; // new node is new top
	}
	else // deck not empty
	{
		new_node->next = top; // link to old top
		top = new_node;// still make top
	}

	deck_size++; // incrememnt deck size
}
void Stack::locate_card(char name[], int& position, Card& monster) // determine card position and retrieve the card
{
	int i = 1; // start at index 1
	Node* temp = top; // navigate with a temp node
	while (temp != nullptr)
	{
		if (strcmp(temp->monster.name, name) == 0) // if name matches
		{
			strcpy(monster.name, temp->monster.name); // copy name
			monster.atk = temp->monster.atk; // copy atk
			monster.def = temp->monster.def; // copy def
			strcpy(monster.type, temp->monster.type); // copy type
			position = i; // record position
			return; // exit function
		}
		// if name doesnt match
		i++; // update index
		temp = temp->next; // move to next node
	}
	// if traversed through deck without finding card
	cout << "That card is not in that deck!\n";
}
void Stack::replace_card(int position, Card monster) // replace card in deck at a current position
{
	int i = 1;
	Node* temp = top;
	while (i < position)
	{
		i++; // update index
		temp = temp->next; // move to next node
	}
	// at this point, the index will always be found (node will never be null either)
	strcpy(temp->monster.name, monster.name); // copy card attributes from parmeter into deck at current position
	temp->monster.atk = monster.atk;
	temp->monster.def = monster.def;
	strcpy(temp->monster.type, monster.type);
}

void Stack::clear() // deallocate all nodes in stack (deck)
{
	Node* temp = nullptr;
	while (top != nullptr) // while not empty
	{
		temp = top;
		top = top->next;
		delete temp; 
	}
	deck_size = 0; // reset deck size to 0
}

int Stack::get_size() // fetch current size of deck
{
	return deck_size;
}

Card Stack::draw() // draws a random card from the deck by swapping the card at a random position with the card at the front and then using pop
{
	if (top != nullptr)
	{
		Card monster1;
		int position = rand() % deck_size + 1; // pick a position in the deck
		int i = 1;
		Node* temp = top;

		while (i != position) // navigate to that position's node and card
		{
			temp = temp->next;
			i++;
		}
		strcpy(monster1.name, temp->monster.name); // copy card attributes from parmeter into deck at current position
		monster1.atk = temp->monster.atk;
		monster1.def = temp->monster.def;
		strcpy(monster1.type, temp->monster.type);

		Card monster2; // retrieve the card at the top of the deck

		strcpy(monster2.name, top->monster.name); // copy card attributes from parmeter into deck at top position
		monster2.atk = top->monster.atk;
		monster2.def = top->monster.def;
		strcpy(monster2.type, top->monster.type);

		// swap the positions of the cards
		replace_card(1, monster1); 
		replace_card(position, monster2);
	}
	return pop(); // pop out the card on the front
}

//field

Queue::Queue() // constructor, starts out empty
{
	front = nullptr;
	rear = nullptr;
}

void Queue::enqueue(Card monster) // add card to rear
{
	Node *new_node = new Node; // allocate memory

	new_node->monster = monster; // add card to node
	new_node->next = nullptr;

	if (front == nullptr) // if empty
	{
		front = new_node; // make node both rear and front
		rear = new_node;
	}
	else // not empty
	{
		rear->next = new_node; // add to rear
		rear = new_node; // make new rear
	}
}

Card Queue::dequeue()
{
	Card monster = { "", -1, -1, "" }; // make dummy card

	if (front != nullptr)
	{
		monster = front->monster; // 
		front = front->next; // make next node new front
	}

	return monster; // return card
}

void Queue::clear()
{
	Node* temp = nullptr;
	while (front != nullptr) // while not empty
	{
		temp = front; 
		front = front->next;
		delete temp; // deallocate node
	}
}

Card Queue::peek()
{
	Card monster = { "", -1, -1, "" }; // make dummy card

	if (front != nullptr)
	{
		monster = front->monster; // get card (but don't dequeue)
	}

	return monster; // return card
}


//general


void display_menu(void) // dislay main menu
{
	cout << "Please enter the number corresponding to the desired action:\n"
		"1. Display Rules\n"
		"2. Create Players\n"
		"3. Add Cards to Specific Players\n"
		"4. Trade Cards with Other players\n"
		"5. Battle Other Player\n"
		"6. Exit\n";
}

int check_option(int option, int max) // determine if option is between 1 and max
{
	if (option < 1 || option > max)
	{
		cout << "That is not a valid input!\n";
		return 0; // not between
	}

	return 1; // between
}

void display_rules(void) // print rules
{
	cout << "Yu-Gi-Oh is a card game between 2 players. Each player starts with a deck of 30+ cards, 8000 life points\n"
		"and draws 5 cards at the start of the game. Each player then selects 1 card to queue up into\n"
		"attack mode and 1 in defense mode. Each player then decides if they would like to attack or\n"
		"defend. If both players defend, the cards are discarded. If one player chooses atttack and the\n"
		"other chooses defense, the defenders life points are reduced by the difference between the ATK\n"
		"and DEF (life points cannot increase from extra defense). If both players choose attack mode, then\n"
		"the player with a lower ATK has their life points reduced by the difference in ATK. The game continues\n"
		"until a player wins be reducing the other player's life points to zero, or a draw when either player does\n"
		"not have enough cards to continue the game\n\n";

}

void create_players(Player& player1, Player& player2)
{
	//deallocate decks for consecutive calls
	player1.deck.clear();
	player2.deck.clear();

	char line[100];
	 
	// open file that contains deck information
	FILE* decks;
	decks = fopen("decks.txt", "r");
	fgets(line, 100, decks); // toss header line

	Card monster; 

	for (int i = 0; i < 30; i++)
	{
		//read line contents into monster attributes with correct typing
		fgets(line, 100, decks);
		strcpy(monster.name, strtok(line, ","));
		monster.atk = atoi(strtok(NULL, ","));
		monster.def = atoi(strtok(NULL, ","));
		strcpy(monster.type, strtok(NULL, ","));
		player1.deck.push(monster); // put first 30 cards into player 1's deck
	}

	for (int i = 0; i < 30; i++)
	{
		fgets(line, 100, decks);
		strcpy(monster.name, strtok(line, ","));
		monster.atk = atoi(strtok(NULL, ","));
		monster.def = atoi(strtok(NULL, ","));
		strcpy(monster.type, strtok(NULL, ","));
		player2.deck.push(monster); // put last 30 cards into player 2's deck
	}

	fclose(decks);

	cout << "Players now have default 30 card decks.\n";
}

void add_cards(Player& player1, Player& player2) // let user add a card to a player's deck
{
	int option = 0;
	do { // continuously display sub menu until input satisfied
		cout << "Please enter the integer corresponding to the desired action:\n"
			"1. Add cards to Player 1\n"
			"2. Add cards to Player 2\n"
			"3. Return to main menu\n";

		cin >> option;
		system("cls");
	} while (!check_option(option, 3));

	if (option == 3)
	{
		return; // go to main menu
	}

	Card monster;
	char scanned;
	scanf("%c", &scanned); // scan enter key

	do { // get monster name
		cout << "Please enter the name of the card you would like to add: ";
		cin.getline(monster.name, 50);
		system("cls");
	} while (!check_zero(monster.name));

	do { // get atk
		cout << "Please enter the attack points of the card you would like to add: ";
		cin >> monster.atk;
		system("cls");
	} while (!check_positive(monster.atk));

	do { // get def
		cout << "Please enter the defense points of the card you would like to add: ";
		cin >> monster.def;
		system("cls");
	} while (!check_positive(monster.def));

	scanf("%c", &scanned);

	do { // get type
		cout << "Please enter the type of the card you would like to add: ";
		cin.getline(monster.type, 50);
		system("cls");
	} while (!check_zero(monster.type));

	if (option == 1) // add to player 1 deck
		player1.deck.push(monster);

	if (option == 2) // add to player 2 deck
		player2.deck.push(monster);

	cout << monster.name << " was successfully added to Player " << option << "'s deck.\n";
}

int check_positive(int num) // check if num is positive
{
	if (num < 0)
	{
		cout << "Can't be a negative number!\n";
		return 0;
	}
	return 1;
}

int check_zero(char str[]) // check if string has length 0
{
	if (strlen(str) == 0)
	{
		cout << "A name must have at least one character!\n";
		return 0;
	}
	return 1;
}


void trade_cards(Player& player1, Player& player2)
{
	char scanned;
	scanf("%c", &scanned); // scan enter key
	char name1[50], name2[50];
	int position1 = -1, position2 = -1; // initialize position has impossible index
	Card monster1, monster2;
	do {
		cout << "Player 1, enter the card in your deck that you would like to trade: ";
		cin.getline(name1, 50);
		player1.deck.locate_card(name1, position1, monster1); // position1 holds card index, monster1 holds card
	} while (position1 == -1 || strlen(name1) == 0); // while position not found and string length of 0 

	do {
		cout << "Player 2, enter the card in your deck that you would like to trade: ";
		cin.getline(name2, 50);
		player2.deck.locate_card(name2, position2, monster2);
	} while (position2 == -1 || strlen(name2) == 0);

	player1.deck.replace_card(position1, monster2); // put player 2 monster in player 1 deck
	player2.deck.replace_card(position2, monster1); // put player 1 monster in player 2 deck

	cout << "Cards traded successfully.\n";
}



void battle(Player player1, Player player2) // main battle function. Players are passed by value, not reference,
{											// so that life points, hand_size, and deck top are not altered for consecutive games
	
	for (int i = 0; i < 5; i++) // add 5 cards to each player's hand from respective decks
	{
		player1.hand[i] = player1.deck.draw();
		player2.hand[i] = player2.deck.draw();
	}

	int go_first = rand() % 2 + 1; // randomly decide who goes first during the game
	int playing = 1;
	int round = 1;

	while (playing)
	{

		if (go_first == 1) // player 1 goes first
		{
			set_up_turn(round, player1, player1, player2);
			set_up_turn(round, player2, player1, player2);
		}
		else // player 2 goes first
		{
			set_up_turn(round, player2, player1, player2);
			set_up_turn(round, player1, player1, player2);
		}

		int atk_def1 = 0; // 1 means atk, 2 means defense. Initialize as 0.
		int atk_def2 = 0;

		if (go_first == 1)
		{
			atk_def1 = finish_turn(round, player1, player1, player2);
			atk_def2 = finish_turn(round, player2, player1, player2);
		}
		else
		{
			atk_def2 = finish_turn(round, player2, player1, player2);
			atk_def1 = finish_turn(round, player1, player1, player2);
		}

		Card monster1, monster2; //make monster cards for player 1 and player 2

		if (atk_def1 == 1) // player 1 chose attack
		{
			monster1 = player1.attack_mode.dequeue(); //put card in monster from queue
			cout << "Player 1 chooses " << monster1.name << " (ATK/" << monster1.atk << " DEF/" << monster1.def << ") in ATK mode.\n";
		}
		else // player 1 chose defense
		{
			monster1 = player1.defense_mode.dequeue();
			cout << "Player 1 chooses " << monster1.name << " (ATK/" << monster1.atk << " DEF/" << monster1.def << ") in DEF mode.\n";
		}

		if (atk_def2 == 1) // player 2 chose attack
		{
			monster2 = player2.attack_mode.dequeue();
			cout << "Player 2 chooses " << monster2.name << " (ATK/" << monster2.atk << " DEF/" << monster2.def << ") in ATK mode.\n";
		}
		else // player 2 chose defense
		{
			monster2 = player2.defense_mode.dequeue();
			cout << "Player 2 chooses " << monster2.name << " (ATL/" << monster2.atk << " DEF/" << monster2.def << ") in DEF mode.\n";
		}

		if (atk_def1 == atk_def2) // both players chose same atk/def
		{
			if (atk_def1 == 1) // both players choose attack
			{
				if (monster1.atk > monster2.atk) // adjust life points
				{
					player2.life_points -= monster1.atk - monster2.atk;
					cout << "Player 2 loses " << monster1.atk - monster2.atk << " life points.\n";
				}
				else if (monster1.atk < monster2.atk)
				{
					player1.life_points -= monster2.atk - monster1.atk;
					cout << "Player 1 loses " << monster2.atk - monster1.atk << " life points.\n";
				}
				else
				{
					cout << "The monsters have equal ATK so life points are unaffected.\n";
				}

			}
			else // both players choose defense
			{
				cout << "Both players chose defense so the cards are discarded. Life points are not affected.\n";
			}
		}
		else // players chose differently
		{
			if (atk_def1 == 1) // player 1 chooses attack. player 2 chooses defense
			{
				if (monster1.atk > monster2.def)
				{
					player2.life_points -= monster1.atk - monster2.def;
					cout << "Player 2 loses " << monster1.atk - monster2.def << " life points.\n";
				}
				else
				{
					cout << "Player 2 defended Player 1's attack fully and lost no life points.\n";
				}
			}
			else // player 1 chooses defense. player 2 chooses defense
			{
				if (monster2.atk > monster1.def)
				{
					player1.life_points -= monster2.atk - monster1.def;
					cout << "Player 1 loses " << monster2.atk - monster1.def << " life points.\n";
				}
				else
				{
					cout << "Player 1 defended Player 2's attack fully and lost no life points.\n";
				}
			}
		}



		if (player1.life_points <= 0) // player 1 lost
		{
			playing = 0;
			cout << "Player 1 has no life points. Player 2 wins!\n";
		}
		else if (player2.life_points <= 0) // player 2 lost
		{
			playing = 0;
			cout << "Player 2 has no life points. Player 1 wins!\n";
		}
		else if (player1.hand_size < 2 || player2.hand_size < 2) // either player doesn't have 2 or no more cards in hand
		{
			playing = 0; // game can't continue because each user can't queue up 2 cards
			cout << "There are not enough cards to continue the game. It's a draw!\n";
		}
		round++; // update round
		
		system("pause");
		system("cls");
	}

	// deallocate the queues at the end of the battle so that consecutive battles don't cause issues
	player1.attack_mode.clear();
	player1.defense_mode.clear();
	player2.attack_mode.clear();
	player2.defense_mode.clear();
}

void display_hand(Player& player) // show hand of a player
{
	for (int i = 0; i < player.hand_size; i++) // for every card in hand
	{
		cout << i + 1 << ". " << player.hand[i].name << ": ATK/" << player.hand[i].atk << " DEF/" << player.hand[i].def << " Type: " << player.hand[i].type << endl; // show card number, name, atk, def, type
	}
}

void set_up_turn(int round, Player& player, Player& player1, Player& player2) // player chooses 2 cards from hand to queue up in atk and def
{
	int option = 0;
	do { // continuously prompt which card to queue for attack until satisfactory
		cout << "Turn: Player " << player.player_num << endl;
		display_stats(round, player1, player2); // display round, life points, and number of cards in decks
		cout << "Enter the integer corresponding with the card in your hand that you wish to put on the field in attack mode:\n";
		display_hand(player); // show hand
		cin >> option;
		system("cls");
	} while (!check_option(option, player.hand_size));

	player.attack_mode.enqueue(player.hand[option - 1]); // enqueue chosen card
	adjust_hand(player, option); // shift hand so that there are no gaps

	do { // same but for defense instead of attack
		cout << "Turn: Player " << player.player_num << endl;
		display_stats(round, player1, player2);
		cout << "Enter the integer corresponding with the card in your hand that you wish to put on the field in defense mode:\n";
		display_hand(player);
		cin >> option;
		system("cls");
	} while (!check_option(option, player.hand_size));

	player.defense_mode.enqueue(player.hand[option - 1]);
	adjust_hand(player, option);

	player.hand[3] = player.deck.draw(); // draw new card
	if (player.hand[3].atk != -1) // if not a dummy card (therefore, deck wasn't empty)
		player.hand_size++; // increase hand size
	player.hand[4] = player.deck.draw(); // repeat since 2 cards need to be drawn (if available)
	if (player.hand[4].atk != -1)
		player.hand_size++;
}

void adjust_hand(Player& player, int option) // shift cards to remove gaps
{
	for (int i = option; i < player.hand_size; i++) // loop from removed card to final card
	{
		player.hand[i - 1] = player.hand[i]; // shift left by 1
	}
	player.hand_size--; // reduce hand size
}

int finish_turn(int round, Player& player, Player& player1, Player& player2) // let a player either attack or defend this turn. return their choice as an integer
{
	Card attack_front = player.attack_mode.peek(); // fetch the card primed for attack dequeue
	Card defense_front = player.defense_mode.peek(); // fetch the card primed for defense dequeue

	int option = 0;
	do { // continuously prompt player until the enter either 1 (attack) or 2 (defend), showing them relevant monster cards
		cout << "Turn: Player " << player.player_num << endl;
		display_stats(round, player1, player2);
		cout << "Enter 1 to attack with " << attack_front.name << " (ATK/" << attack_front.atk << " DEF/" << attack_front.def << 
			") or 2 to defend with " << defense_front.name << " (ATK/" << defense_front.atk << " DEF/" << defense_front.def << "): ";
		cin >> option;
		system("cls");
	} while (!check_option(option, 2));
	
	return option; // return choice
}

void display_stats(int round, Player& player1, Player& player2) // show main scoreboard
{
	cout << "Round: " << round << endl;
	cout << "               Player 1   Player2\n";
	cout << "Life Points:   " << player1.life_points << "       ";
	
	for (int i = 0; i < 4 - num_length(player1.life_points); i++)
	{
		cout << " "; // adjust printing so that there are more spaces if the life points decrease digits throughout game
	}

	cout << player2.life_points << endl;
	cout << "Cards in Deck: " << player1.deck.get_size() << "        ";

	for (int i = 0; i < 3 - num_length(player1.deck.get_size()); i++)
	{
		cout << " "; // adjust as above for card number digit changes
	}

	cout << player2.deck.get_size() << endl << endl;
}

int num_length(int num) // return number of digits of integer
{
	stringstream ss;
	ss << num;
	string s;
	ss >> s; // convert integer to string
	return s.length(); // return the string length
}