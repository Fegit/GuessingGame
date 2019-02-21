#include "Game.h"
#include "BannerCreator/Banner.cpp" class Banner;

// Generate random number
void Game::generateRandomInt() {
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> randInt(bottomGuess, topGuess); // distribution in range bottomGuess - topGuess
	randomInt = randInt(rng);
	//DEBUG("randomInt", randomInt)
}

// get userinput (guess)
void Game::getInput() {
	OUT(">>> ")
	IN(userGuess)
		// check if the input went correctly, if not -> clear and get new input
		if (!std::cin) {
			std::cout << "That is not a valid number!\nPossible numbers are in range from " << bottomGuess << " - " << topGuess << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			system("pause");
			system("CLS");
			generateGuessBanner("Take your choice");
			getInput();
		}
		// check if input is in possible range of numbers
		else if(userGuess > topGuess || userGuess < bottomGuess){
			std::cout << "That is not a valid number!\nPossible numbers are in range from " << bottomGuess << " - " << topGuess << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			system("pause");
			system("CLS");
			generateGuessBanner("Take your choice");
			getInput();
		}
		else {
			countTries();
		}
	system("CLS");
	
}

// higher or lower check
void Game::hotOrCold() {
	generateGuessBanner("Take your choice");
	if (userGuess > randomInt) {
		std::cout << "Your guess " << userGuess << " is greater than the number we're looking for" << std::endl;
	}
	else if (userGuess < randomInt) {
		std::cout << "Your guess " << userGuess << " is smaller than the number we're looking for" << std::endl;
	}
	else if(userGuess == randomInt){
		wincheck = true;
	}
}

// counts the tries it took the user to guess the number
void Game::countTries(){
	tries++;
}

// reset tries
void Game::resetTries() {
	tries = 0;
}

// gets called when user guesses the right number
void Game::won() {
	system("cls");
	generateGuessBanner("Congratulations!");
	OUT("You've correctly guessed the number in ")
	OUT(tries)
	OUTEND(" tries.\n---------------------------------------------------\n")
	resetTries();
}

// gameloop
void Game::gameloop() {
	wincheck = false;
	generateGuessBanner("Take your choice");
	while (!wincheck) {
		getInput();
		hotOrCold();
	}
}

// starts the actual game
void Game::startGame() {
	generateRandomInt();
	gameloop();
	won();
	system("pause");
}

// create Menu out of a vector of possibilities 
void Game::createMenu(std::vector <std::string> menuEntries) {
	int countEntries = size(menuEntries);

	for (int entry = 0; entry < countEntries; entry++) {
		if (entry + 1 < countEntries) {
			std::cout << menuEntries[entry] << " [" << entry + 1 << "]     ";
		}
		else {
			std::cout << menuEntries[entry] << " [X]" << std::endl;
		}
		
	}
}

// creates and prints the menu through createMenu();
void Game::printMenu() {
	system("CLS");
	OUTEND(menuBanner)
	createMenu({"Play","Highscores","Quit"});
}

// gets input from user
char Game::input() {
	
	OUT(">>> ")
	IN(menuChoice)
	//system("CLS");
	//menuChoice = tolower(menuChoice[0]);
	return char(tolower(menuChoice[0]));
}

// handles user input within the menu
void Game::handleInput() {
	inStartMenu = true;
	while (inStartMenu) {
		switch (input()) {
		case '1':
			inStartMenu = false;
			system("CLS");
			startGame();
			
			break;
		case '2':
			OUTEND("Currently unavailable")
			system("pause");
			system("CLS");
			printMenu();
			break;
		case 'x':
			inStartMenu = false;
			endGame = true;
			system("CLS");
			OUTEND(exitBanner)

			break;

		default:
			printMenu();
			handleInput();
		}
	}
	
}

void Game::menu() {
	printMenu();
	handleInput();

}

void Game::generateBanners() {
	Banner menuBanner("Guessing Game", "#-<>~&%$§!?", 13, 7, 2);
	Banner exitBanner("Thanks for playing", "#-<>~&%$§!?", 13, 7, 2);
	

	Game::menuBanner = menuBanner.createBanner();
	Game::exitBanner = exitBanner.createBanner();
	
}

void Game::generateGuessBanner(std::string text) {
	Banner guessBanner(text, "#-<>~&%$§!?", 15, 7, 2);
	Game::guessBanner = guessBanner.createBanner();
	OUTEND(Game::guessBanner)
}

// starts the program
void Game::start() {
	generateBanners();
	while (!endGame) {
		menu();
	}

}

// DEBUG-LOG Variables
void Game::debug() {

	DEBUG("randomInt", randomInt)

	DEBUG("userGuess", userGuess)

	DEBUG("tries", tries)
}