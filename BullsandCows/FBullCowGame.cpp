#include "FBullCowGame.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <random>
#include <time.h>
// Creates a random direction
int randomDistribution()
{
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> random(0, 5);
	return random(rng);
}



// Initialing values to variables.
FBullCowGame::FBullCowGame()
{
	CurrentState = EGameStates::Progress;
	WordStatus = EGuessStatus::InvalidState;

	WordsList.push_back("heat");
	WordsList.push_back("fire");
	WordsList.push_back("cave");
	WordsList.push_back("dent");
	WordsList.push_back("hear");
	WordsList.push_back("cold");


	HiddenWord = WordsList[randomDistribution()];

	MaxTries = 4;
	
	//Converts the HiddenWord to lowercase.
	std::transform(HiddenWord.begin(), HiddenWord.end(), HiddenWord.begin(),tolower);
}

// Destructor.
FBullCowGame::~FBullCowGame()
{
	// Nothing to free :)
}
FString FBullCowGame::GetGuessWord()
{
	FString Word;

	std::cout << "Enter the String:\t " << std::endl;
	std::cin >> Word;

	std::transform(Word.begin(), Word.end(), Word.begin(), ::tolower);

	return Word;
}
//Compares the Mysteryword and the given word and returns the number of bulls and cows.
BullsAndCows FBullCowGame::SubmitValidGuess(FString Word)
{
	BullsAndCows Count;
	
	for (int i = 0; i < (int)HiddenWord.length(); i++)
	{
		for (int j = 0; j < (int)Word.length(); j++)
		{
			if (HiddenWord[i] == Word[j]) // If the characters are equal
			{
				if (i == j)   //If their indices are equal,Bulls is incremented
				{
					Count.Bulls++;
				}
				else // Else Cows is incremented.
				{
					Count.Cows++;
				}
			}
		}
	}
	return Count;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1)
	{
		return true;
	}
	TMap <char, bool> LetterSeen;
	
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter] == true)
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}

	return true;
}

EGuessStatus FBullCowGame::GetGuessValidity(FString Word) const
{
	if (Word.length() != HiddenWord.length())
	{
		return EGuessStatus::IncorrectSize;
	}
	else if (IsIsogram(Word) == false)
	{
		return EGuessStatus::NotIsogram;
	} 
	else
	{
		return EGuessStatus::Valid;
	}
}

void FBullCowGame::ValidateGuess(EGuessStatus Status) const
{
	switch (Status)
	{
	case EGuessStatus::IncorrectSize:
		std::cout << "Invalid Size. Please Enter string of valid size.\n";
		break;
	case EGuessStatus::InvalidState:
		std::cout << "String not entered.\n";
		break;
	case EGuessStatus::NotIsogram:
		std::cout << "String entered is not an Isogram.\n";
		break;
	}
}

void FBullCowGame::newGame()
{
	CurrentState = EGameStates::Progress;
	WordStatus = EGuessStatus::InvalidState;
	HiddenWord = WordsList[randomDistribution()];

	MaxTries = 4;

	//Converts the HiddenWord to lowercase.
	std::transform(HiddenWord.begin(), HiddenWord.end(), HiddenWord.begin(), tolower);
}

// Gameloop is the function that should be called from main by the programmer.
void FBullCowGame::GameLoop()
{
	char Reply;
	Uint32 Attempts = 1; // Keeps track of number of attempts made by the user to identify the word.
	BullsAndCows Count;
	FString Word;
	while (CurrentState != EGameStates::End && CurrentState != EGameStates::Lost)//The Game repeats until this loop is satisfied.
	{

		while (WordStatus != EGuessStatus::Valid)
		{		
			Word = GetGuessWord();
			WordStatus = GetGuessValidity(Word);
			ValidateGuess(WordStatus);
		}
		Count = SubmitValidGuess(Word);
		if (WordStatus == EGuessStatus::Valid && Count.Bulls == HiddenWord.length()) // Condition when the Player has won.
		{
			std::cout << "You have won!!" << std::endl;
			std::cout << "\nDo you want to play Again? (y/n): ";
			std::cin >> Reply;
			if (Reply == 'y')
			{
				newGame();
				Attempts = 1;
			}
			else if (Reply == 'n')
			{
				CurrentState = EGameStates::End;
				break;
			}
		}
		else if (Count.Bulls != HiddenWord.length())
		{
			std::cout << "Attempt: " << Attempts << " failed." << std::endl;
			std::cout << "BULLS:  " << Count.Bulls << "\t COWS: " << Count.Cows << std::endl;
			std::cout << "Please guess again..\n";
			Attempts++;
			WordStatus = EGuessStatus::InvalidState;
		}
	   if (Attempts > MaxTries)
		{
			std::cout << "\nReached Max tries.\n" << "\nYou have lost the game.\n";
			CurrentState = EGameStates::Lost;
			std::cout << "\nDo you want to try Again? (y/n): ";
			std::cin >> Reply;
			if (Reply == 'y')
			{
				CurrentState = EGameStates::Progress;
				Attempts = 1;
			}
			else if (Reply == 'n')
			{
				break;
			}

		}
		Count.Bulls = 0;
		Count.Cows = 0;
	}
	
}

// Structure constructor. :D 
BullsAndCows::BullsAndCows()
{
	Bulls = 0;
	Cows = 0;
}
