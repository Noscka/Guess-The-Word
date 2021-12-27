#include <iostream>
#include <sstream>
#include <list>
#include <string>

/// <summary>
/// Makes string lower case as standard c++ doesn't have that or I couldn't find it
/// </summary>
/// <param name="Input">String to lower</param>
/// <returns>Fully lowered string</returns>
std::string LowerString(std::string Input)
{
	std::string Output;

	for(char c : Input)
	{
		Output += tolower(c);
	}

	return Output;
}

int main()
{
#pragma region Variables
	std::string SecretWord, CurrentGuess, PreviousLetters;
	int LetterCount = 0;
	bool ValidationBool = true, GuessWord = true, SecondValidation = true;
#pragma endregion

	std::cout << "     ___           ___           ___           ___                    ___           ___           ___     " << std::endl;
	std::cout << "    /\\__\\         /\\  \\         /\\__\\         /\\  \\                  /\\__\\         /\\  \\         /\\__\\    " << std::endl;
	std::cout << "   /:/  /        /::\\  \\       /::|  |       /::\\  \\                /::|  |       /::\\  \\       /::|  |   " << std::endl;
	std::cout << "  /:/__/        /:/\\:\\  \\     /:|:|  |      /:/\\:\\  \\              /:|:|  |      /:/\\:\\  \\     /:|:|  |   " << std::endl;
	std::cout << " /::\\  \\ ___   /::\\~\\:\\  \\   /:/|:|  |__   /:/  \\:\\  \\            /:/|:|__|__   /::\\~\\:\\  \\   /:/|:|  |__ " << std::endl;
	std::cout << "/:/\\:\\  /\\__\\ /:/\\:\\ \\:\\__\\ /:/ |:| /\\__\\ /:/__/_\\:\\__\\          /:/ |::::\\__\\ /:/\\:\\ \\:\\__\\ /:/ |:| /\\__\\" << std::endl;
	std::cout << "\\/__\\:\\/:/  / \\/__\\:\\/:/  / \\/__|:|/:/  / \\:\\  /\\ \\/__/          \\/__/~~/:/  / \\/__\\:\\/:/  / \\/__|:|/:/  /" << std::endl;
	std::cout << "     \\::/  /       \\::/  /      |:/:/  /   \\:\\ \\:\\__\\                  /:/  /       \\::/  /      |:/:/  / " << std::endl;
	std::cout << "     /:/  /        /:/  /       |::/  /     \\:\\/:/  /                 /:/  /        /:/  /       |::/  /  " << std::endl;
	std::cout << "    /:/  /        /:/  /        /:/  /       \\::/  /                 /:/  /        /:/  /        /:/  /   " << std::endl;
	std::cout << "    \\/__/         \\/__/         \\/__/         \\/__/                  \\/__/         \\/__/         \\/__/    " << std::endl;

	std::cout << "============================================================================================================" << std::endl;
	std::cout << "Player 1 has to choose 1 word" << std::endl;
	std::cout << "Once choose, player 2 has infinte guesses to guess the letters" << std::endl;
	std::cout << "Player 2 has to enter \"guess\" to guess the word" << std::endl;
	std::cout << "If Player 2 guess all the letters, you must guess the word" << std::endl;
	std::cout << "============================================================================================================" << std::endl;


	while(ValidationBool)
	{
		std::cout << "Player 1 Input Secret Word: ";

		// Get whole line (from input start to end, not all text on line)
		std::getline(std::cin, SecretWord);

		//Validation to make sure it only 1 word (if it contains any white spaces, it is considered multiword)
		ValidationBool = false;

		for(char letter : SecretWord)
		{
			if(isspace(letter))
			{
				std::cout << "Enter only 1 word" << std::endl;
				ValidationBool = true;
				break;
			}
		}
	}
	// if all is valid, lower case the secretword
	SecretWord = LowerString(SecretWord);

	// OS-specific but only way I found
	system("cls");

	std::cout << "Player 2, you get to guess the letters of the word 3 times" << std::endl;
	std::cout << "The guesses will give you hints for when you have to guess the whole word after the 3 times" << std::endl;
	std::cout << "If you guess all the letters, you must guess the word" << std::endl;
	std::cout << std::endl;
	std::cout << "Enter \"guess\" to start guessing the word" << std::endl;
	std::cout << "Enter \"show\" to show the secret word |MOSTLY FOR TESTING AND SHOWING PURPOSES|" << std::endl;


	std::cout << std::endl;
	std::cout << "--------------------------------------------------------------------------------------------" << std::endl;
	std::cout << std::endl;

	while(GuessWord)
	{
		ValidationBool = true;
		LetterCount = 0;

		while(ValidationBool)
		{
			std::cout << "Guess: ";
			std::getline(std::cin, CurrentGuess);
			// make string lower case from begining.
			CurrentGuess = LowerString(CurrentGuess);

			ValidationBool = false;

			//check if input is show
			if(CurrentGuess == "show")
			{
				std::cout << "Secret word is: " << SecretWord << std::endl;
				//Continues the current iteration so you don't loose a guess
				ValidationBool = true;
			}
			else if(CurrentGuess == "guess")
			{
				// Break out of outter loop
				std::cout << "You now have to guess the word" << std::endl;
				GuessWord = false;
			}
			else
			{
				// Make sure input is 1 letter
				if(CurrentGuess.length() == 1)
				{
					SecondValidation = true;

					for(char Prev: PreviousLetters)
					{
						if(Prev == CurrentGuess[0])
						{
							std::cout << "You have already used this letter before" << std::endl;
							SecondValidation = false;
							break;
						}
					}

					if(SecondValidation)
					{
                        //Go through string and count each times the letter was found
						for(char c : SecretWord)
						{
							if(c == CurrentGuess[0])
							{
								LetterCount += 1;
							}
						}
						//out put a nice messages to show
						std::cout << "The word has " << LetterCount << " " << CurrentGuess[0] << "'s" << std::endl;

						//add the letter to the list
						PreviousLetters.push_back(CurrentGuess[0]);
					}

					
				}
				else
				{
					// "error" for if input is not letter or show
					std::cout << "Enter only 1 letter or show" << std::endl;

					//Continues the current iteration so you don't loose a guess
					ValidationBool = true;
				}
			}
		}

		GuessWord = false;

		// go through every lettter in the secret word, if they are not found in the list, do nothing
		for(char Wordchar : SecretWord)
		{
			if(PreviousLetters.find(Wordchar) == std::string::npos)
			{
				GuessWord = true;
				break;
			}
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << "Player 2 you now have to guess the word" << std::endl;
	std::cout << "---------------------------------------" << std::endl;

	std::cout << "Word guess: ";
	std::getline(std::cin, CurrentGuess);
	std::cout << std::endl;

	if(CurrentGuess == SecretWord)
	{
		std::cout << "Player 2 wins" << std::endl;
		std::cout << "You deserve yourself a beer" << std::endl;
	}
	else
	{
		std::cout << "Player 1 wins" << std::endl;
		std::cout << "You deserve yourself a beer" << std::endl;
	}

	return 0;
}