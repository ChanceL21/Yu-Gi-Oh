#ifndef PA5_H
#define PA5_H

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

// card object that has a name, attack, defense, and type
struct Card
{
	char name[50];
	int atk;
	int def;
	char type[50];
};

// node for both stack and queue. holds a card and a pointer to the next node
struct Node
{
	Card monster;
	Node* next;
};

// used for the card deck
class Stack
{
private:
	Node* top;
	int deck_size;
public:
	Stack(); // constructor, adds 30 cards to deck.
	Card pop(); // grab card from top and decrease deck size if not empty
	void push(Card monster); // put a card into the deck and increase deck size
	void locate_card(char name[], int& position, Card& monster); // finds position of card and card itself. returns through pass by reference parameters
	void replace_card(int position, Card monster); // replaces a card at a given position which parameter card
	void clear(); // deallocates entire deck, sets deck size to 0
	int get_size(); // retrieves the number of cards currently in the deck
	Card draw(); // draws a random card from the deck by swapping the card at a random position with the card at the front and then using pop
};

//used for cards on the field. one queue is for monsters played in attack mode, another for those played in defense mode
class Queue
{
private:
	Node* front;
	Node* rear;
public:
	Queue(); // constructor, starts as empty
	void enqueue(Card monster); // add card to rear
	Card dequeue(); //take out card from front
	void clear(); // deallocate queue
	Card peek(); // retrieve card at front (about to be dequeued, but not dequeued)
};

//player 1 and player 2 objects.
struct Player
{
	int player_num; // 1 or 2 for player 1 or player 2. Used for simple print statements and function applicability
	int life_points; // starts at 8000
	Card hand[5]; // array of up to 5 cards
	int hand_size; // number of cards in hand, up to 5
	Stack deck; // each player has a deck
	Queue attack_mode; // each player has an attack queue
	Queue defense_mode; // each player has a defense queue
};

// prints main menu to user
void display_menu(void);

// checks if option is between 1 and max, inclusively. Returns 1 if so, 0 otherwise (along with print statement)
int check_option(int option, int max);

// prints rules to user
void display_rules(void);

// populates player 1's deck with 30 cards (Joey's deck) and player 2's deck with 30 cards (Yugi's deck). Both stacks are fully cleared beforehand.
void create_players(Player &player1, Player &player2);

//allows user to choose a player's deck to add a card to. User can input name, ATK, DEF, and type. Card is pushed into the deck. Players must be created first.
void add_cards(Player& player1, Player& player2);

// returns 1 if num is positive, 0 if not
int check_positive(int num);

// returns 1 if string has at least 1 character, 0 if only null character
int check_zero(char str[]);

// allows user to select a card by name from each deck and swap them. Players must be created first.
void trade_cards(Player& player1, Player& player2);

// allows player 1 and player 2 to duel with their current decks.
void battle(Player player1, Player player2);

// print a player's hand, up to 5 cards
void display_hand(Player& player);

// Allows a player to queue up 1 card in attack mode and 1 card in defense mode from their hand. Displays hand as well.
void set_up_turn(int round, Player& player, Player& player1, Player& player2);

// Shifts cards over once a card is selected. So if a hand has 5 cards, and the 3rd card is selected, the 4th card shifts to the 3rd, 5th to 4th, and the hand size is decreased by 1.
void adjust_hand(Player& player, int option);

// prompts a player to either attack or defend this turn
int finish_turn(int round, Player& player, Player& player1, Player& player2);

// shows the round number, and life points / number of cards in deck for each player
void display_stats(int round, Player& player1, Player& player2);

// return number of digits in a number. used to print extra spaces as number gets smaller for visual convenience
int num_length(int num);

#endif