#ifndef __BLACKJACK_H__
#define __BLACKJACK_H__

#include<string>
using std::string;

class BlackJack
{
private:
	unsigned sumPlayer, sumComputer, playerCash;

public:
	//Constructor
	BlackJack();
	//Generate a random card
	char generateCard(unsigned& sumCards);
	//Start game
	void play(void);
	//Display card type
	void displayCard(char cardNumber);
	//The laptop's turn to extract cards
	void computerTurns(int bet);
	//Restart game
	void rematch(void);
	//Create game
	void menu(void);
	//Cash handler for players money
	void cashHandler(int bet);

};

#endif
