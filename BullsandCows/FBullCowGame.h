
#pragma once

#include <string>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

#define TMap std::map
#define Vector std::vector

using FString = std::string;
using Uint32 = std::int32_t;
/*
A Enum which represents the various states of the game.
*/
enum EGameStates { End, Lost, Progress };

enum EGuessStatus { InvalidState , IncorrectSize , NotIsogram , Valid };

/*
A Structure which represents the Number of Bulls and Cows.
*/
struct BullsAndCows
{
	Uint32 Bulls;
	Uint32 Cows;
public:
	BullsAndCows();
};

/* 
A Class which represents the Bulls and Cows game.
*/
class FBullCowGame
{
public:
	//Constructor.
	FBullCowGame();

	//Destructor.
	~FBullCowGame();

	// This loop initiates the game and checks whether the game has reached it's end or not.
	void GameLoop();

private:
	// Getter for GuessWord and force checks it's length.
	FString GetGuessWord();

	//Compares the two words and returns the number of bulls and cows.
	BullsAndCows SubmitValidGuess(FString Word);

	bool IsIsogram(FString Word) const;
	EGuessStatus GetGuessValidity(FString Word) const;
	void ValidateGuess(EGuessStatus Status) const;



//Variables.
	Uint32 MaxTries;
	FString HiddenWord;
	EGameStates CurrentState;
	EGuessStatus WordStatus;

	// string of all words
	Vector<std::string>  WordsList;
};

