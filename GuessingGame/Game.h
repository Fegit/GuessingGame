#pragma once
#include <iostream>
#include <string>
#include <random>
#include <vector>


#define OUT(x); std::cout << x;
#define OUTEND(x); std::cout << x << std::endl;
#define IN(x); std::cin >> x;

#define DEBUG(x, y); std::cout << x << ": " << y << std::endl;

class Game {
private:

	unsigned int topGuess{ 100 };
	unsigned int bottomGuess{ 1 };
	unsigned int randomInt{ 0 };
	unsigned int userGuess{ 0 };
	int tries{ 0 };
	std::string menuChoice;

	bool wincheck{ false };
	bool inStartMenu{ true };
	bool endGame{ false };
	

	char input();

	void hotOrCold();
	void generateRandomInt();
	void getInput();
	void countTries();
	void resetTries();
	void gameloop();
	void won();
	void startGame();
	void createMenu(std::vector <std::string> menuEntries);


	void menu();
	void printMenu();
	void handleInput();

	void generateBanners();
	void generateGuessBanner(std::string text);
	std::string menuBanner{ "" };
	std::string exitBanner{ "" };
	std::string guessBanner{ "" };

public:

	void start();

	void debug();
};