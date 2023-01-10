#include"BlackJack.h"
#include<iostream>
#include <stdlib.h>
#include <time.h> 
#include<windows.h>


BlackJack::BlackJack()
{
	//Initialize sum of both player with 0
	sumPlayer = playerCash = sumComputer = 0;
}

char BlackJack::generateCard(unsigned& sumCards)
{
	int number;
	char card;
	string cardTenType = { "JQK" };
	srand(time(NULL));

	//Choose a random card between 1 and 10
	number = rand() % 10 + 1;

	//If the number will be 1 and sum of the card is less or equal we will use it as A 
	if (sumCards <= 10 && number == 1)
	{
		sumCards += 11;
		card = 'A';
	}
	else if (number == 10)
	{
		//If number is 10 we will use J Q or K  
		sumCards += 10;
		number = rand() % 3;
		card = cardTenType[number];
	}
	else
	{
		sumCards += number;
		card = (char)number + 48;
	}

	return card;
}

void BlackJack::play(void)
{
	char answear;
	char card;
	int bet;

	system("CLS");

	std::cout << "Your balance: " << playerCash << "$\n";
	std::cout << "Choose bet: ";
	std::cin >> bet;
	while (bet > playerCash)
	{
		std::cout << "You don't have enough money! Insert another bet\n";
		std::cin >> bet;
	}

	//Choose a random card and display on the screen
	std::cout << "First card:\n";
	card = generateCard(sumPlayer);
	displayCard(card);

	//Pause the game a little bit so he can choose a new random card 
	Sleep(1000);

	//Choose another random card and display on the screen and the sum of the cards
	std::cout << "Second card:\n";
	card = generateCard(sumPlayer);
	displayCard(card);

	std::cout << "Cards sum:  " << sumPlayer << "\n";
	if (sumPlayer == 21)
	{
		std::cout << "Congrats! You won!\n";
		cashHandler(bet);
		std::cout << "Current balance: " << playerCash << "$\n";
		rematch();
	}
	else
	{

		std::cout << "Do you want to pull another card? (y/n)\n";
		std::cin >> answear;
		while (answear == 'y' && sumPlayer < 21)
		{
			card = generateCard(sumPlayer);
			displayCard(card);
			std::cout << "Cards sum:  " << sumPlayer << "\n";
			if (sumPlayer < 21)
			{
				std::cout << "Do you want to pull another card? (y/n)\n";
				std::cin >> answear;
			}

		}

		if (sumPlayer == 21)
		{
			std::cout << "You won!\n";
			cashHandler(bet);
			std::cout << "Current balance: " << playerCash << "$\n";
			rematch();
		}
		else if (sumPlayer > 21)
		{
			std::cout << "You lost! Good luck next time!\n";
			bet *= -1;
			cashHandler(bet);
			std::cout << "Current balance: " << playerCash << "$\n";
			rematch();
		}
		else
		{
			computerTurns(bet);
			rematch();
		}
	}

}


//symbole ascii code : heart = 3, diamond = 4, clover = 5, leaf = 6
void BlackJack::displayCard(char cardNumber)
{
	srand(time(NULL));
	int cardType = (rand() % 4);
	cardType += 3;
	std::cout << " _______________\n| " << cardNumber << "             |\n|               |\n|               |\n|               |\n|       " << (char)cardType << "       | \n|               |\n|               |\n|               |\n|             " << cardNumber << " | \n|_______________| \n";
}

//Time to extract some cards for computer
void BlackJack::computerTurns(int bet)
{
	srand(time(NULL));
	std::cout << "Computer turns :D\n";
	//number of card that computer will extract after the first 2 cards if his sum is lower than yours
	int numbersOfCard = rand() % 3 + 1;
	char card;

	std::cout << "Computer first card:\n";
	card = generateCard(sumComputer);
	displayCard(card);

	Sleep(1000);

	std::cout << "Computer second card:\n";
	card = generateCard(sumComputer);
	displayCard(card);
	std::cout << "Computer cards sum:  " << sumComputer << "\n";

	if (sumComputer <= 21 && sumComputer > sumPlayer)
	{
		std::cout << "Computer won! Good luck next time!\n";
		bet *= -1;
		cashHandler(bet);
		std::cout << "Current balance: " << playerCash << "$\n";
	}
	else {

		Sleep(1000);

		while (numbersOfCard != 0 && sumComputer < 21 && sumComputer < sumPlayer)
		{
			std::cout << "Computer next card:\n";
			card = generateCard(sumComputer);
			displayCard(card);
			std::cout << "Computer cards sum:  " << sumComputer << "\n";
			numbersOfCard--;
			Sleep(1000);
		}
		if (sumComputer > 21 || sumComputer < sumPlayer)
		{
			std::cout << "Computer lose! You won!\n";
			cashHandler(bet);
			std::cout << "Current balance: " << playerCash << "$\n";
		}
		else if (sumComputer == sumPlayer)
		{
			std::cout << "It's tie!\n";
			std::cout << "Current balance: " << playerCash << "$\n";
		}
		else if (sumComputer > sumPlayer && sumComputer <= 21)
		{
			std::cout << "Computer won! You lose!\n";
			bet *= -1;
			cashHandler(bet);
			std::cout << "Current balance: " << playerCash << "$\n";
		}
	}
}

void BlackJack::rematch(void)
{
	char answear;
	std::cout << "Wolud you like to rematch? (y/n)\n";
	std::cin >> answear;
	if (answear == 'y')
	{
		sumComputer = sumPlayer = 0;
		Sleep(750);
		system("Cls");
		play();
	}
}

void BlackJack::menu(void)
{
	char answear;
	std::cout << "Hi! Wanna play a game of BlackJack? (y/n)\n";

	std::cin >> answear;

	if (answear == 'y')
	{
		int money;
		std::cout << "Insert your balance: ";
		std::cin >> money;
		cashHandler(money);
		play();
	}

	std::cout << "See ya next time!\n";

}

void BlackJack::cashHandler(int bet)
{
	playerCash += bet;
}