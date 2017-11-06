#include <iostream>
#include "FBullCowGame.h"

using namespace std;

int main()
{

	cout << "This is a game of Bulls and Cows.\n";
	cout << "Guess the 4 letter isogram...\n";
	FBullCowGame game;
	game.GameLoop();

	system("PAUSE");
}