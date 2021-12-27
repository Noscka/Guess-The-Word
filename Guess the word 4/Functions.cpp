#include "Functions.h"

/// <summary>
/// Replace things in wide string
/// </summary>
/// <param name="WholeString">Wide string to edit</param>
/// <param name="Word">Replace word</param>
/// <param name="Replace">Replace with</param>
/// <returns>Edited String</returns>
std::wstring Functions::WideStringReplace(std::wstring WholeString, std::string Word, std::string Replace)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

	return converter.from_bytes(std::regex_replace(converter.to_bytes(WholeString), std::regex(Word), Replace));
}

/// <summary>
/// fill rest of string with whitespace
/// </summary>
/// <param name="string">String to edit</param>
/// <param name="lenght">String Lenght</param>
/// <param name="LeftRight">True = Left of string \n False = Right of string</param>
/// <returns>WhiteSpace String</returns>
std::string Functions::MakeLenght(std::string string, int lenght, bool LeftRight)
{
	if(LeftRight)
	{
		return std::string(lenght - string.length(), ' ') + string;
	}
	else
	{
		return string + std::string(lenght - string.length(), ' ');
	}
	
}

/// <summary>
/// Clear screen Function - Got from StackOverflow
/// </summary>
void Functions::ClearScreen()
{
	// Get the Win32 handle representing standard output.
	// This generally only has to be done once, so we make it static.
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD topLeft = {0, 0};

	// std::cout uses a buffer to batch writes to the underlying console.
	// We need to flush that to the console because we're circumventing
	// std::cout entirely; after we clear the console, we don't want
	// stale buffered text to randomly be written out.
	std::cout.flush();

	// Figure out the current width and height of the console window
	if(!GetConsoleScreenBufferInfo(hOut, &csbi))
	{
		// TODO: Handle failure!
		abort();
	}
	DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

	DWORD written;

	// Flood-fill the console with spaces to clear it
	FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

	// Reset the attributes of every character to the default.
	// This clears all background colour formatting, if any.
	FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

	// Move the cursor back to the top left for the next sequence of writes
	SetConsoleCursorPosition(hOut, topLeft);
}

/// <summary>
/// Makes string lower case as standard c++ doesn't have that or I couldn't find it
/// </summary>
/// <param name="Input">String to lower</param>
/// <returns>Fully lowered string</returns>
std::string Functions::LowerString(std::string Input)
{
	std::string Output;

	for(char c : Input)
	{
		Output += tolower(c);
	}

	return Output;
}

/// <summary>
/// Check if String is just numbers
/// </summary>
/// <param name="str">String to Check</param>
/// <returns>True if only numbers, False if not just numbers</returns>
bool Functions::isNumber(const std::string& str)
{
	for(char const& c : str)
	{
		if(std::isdigit(c) == 0) return false;
	}
	return true;
}

/// <summary>
/// The game function
/// </summary>
/// <returns>Who won or if it was ended</returns>
int Functions::Game(bool Multi)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

#pragma region VariablesOfGame
	std::string SecretWord, LetterStore, WordShow, CurrentGuess;
	bool FirstValidation = true, SecondValidation = true, ThirdValidation = false, InfGuess = false;
	int LetterCount = 0, CurrentIterartion = 0, ReturnInt, Difficulty= 0, GuessCount = 0;
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
#pragma endregion

	while(FirstValidation)
	{
		std::wcout << 
LR"(════════════╗
 Difficulty ║ 
────────────╢  
╌╌╌╌╌╌╌╌┐   ╚═══════╗
Options ┆           ║
╌╌╌╌╌╌╌╌┘           ║
╭────────╼━╾────────╢
│        (1)        ║
│  Word count: 6-10 ║
│    Guesses: 8     ║
├────────╼━╾────────╢
│        (2)        ║
│ Word count: 11-15 ║
│    Guesses: 6     ║
├────────╼━╾────────╢
│        (3)        ║
│ Word Count: 16-20 ║
│    Guesses: 4     ║
├────────╼━╾────────╢
│        (4)        ║
│  Word Count: inf  ║
│    Guesses: inf   ║
├────────╼━╾────────╢
│        (5)        ║
│  Word Count: inf  ║
│    Guesses: 10    ║
╰────────╼━╾────────╢
════════════════════╝
)";

		std::wcout << "Pick: ";

		// use Secretword as it means I don't need to make a new var and use more memory
		std::getline(std::cin, SecretWord);

		if(!SecretWord.empty())
		{
			if(isNumber(SecretWord)) // check if input string is just numbers
			{
				Difficulty = std::stoi(SecretWord);
			
				if(Difficulty >= 0 && Difficulty <= 5) //check if number is in range of 0 to 5
				{
					FirstValidation = false;
				}
				else
				{
					std::wcout << "Please Input a Value that is inbetween 0 and 5" << std::endl;
				}
			}
		}
		else
		{
			std::wcout << "Please Input a value" << std::endl;
		}

	}

	FirstValidation = true;

	ClearScreen();

	std::wcout << R"(     ___           ___           ___           ___                    ___           ___           ___
    /\__\         /\  \         /\__\         /\  \                  /\__\         /\  \         /\__\    
   /:/  /        /::\  \       /::|  |       /::\  \                /::|  |       /::\  \       /::|  |   
  /:/__/        /:/\:\  \     /:|:|  |      /:/\:\  \              /:|:|  |      /:/\:\  \     /:|:|  |   
 /::\  \ ___   /::\~\:\  \   /:/|:|  |__   /:/  \:\  \            /:/|:|__|__   /::\~\:\  \   /:/|:|  |__ 
/:/\:\  /\__\ /:/\:\ \:\__\ /:/ |:| /\__\ /:/__/_\:\__\          /:/ |::::\__\ /:/\:\ \:\__\ /:/ |:| /\__\
\/__\:\/:/  / \/__\:\/:/  / \/__|:|/:/  / \:\  /\ \/__/          \/__/~~/:/  / \/__\:\/:/  / \/__|:|/:/  /
     \::/  /       \::/  /      |:/:/  /   \:\ \:\__\                  /:/  /       \::/  /      |:/:/  / 
     /:/  /        /:/  /       |::/  /     \:\/:/  /                 /:/  /        /:/  /       |::/  /  
    /:/  /        /:/  /        /:/  /       \::/  /                 /:/  /        /:/  /        /:/  /   
    \/__/         \/__/         \/__/         \/__/                  \/__/         \/__/         \/__/    )" << std::endl;

	std::wcout << "============================================================================================================" << std::endl;
	std::wcout << "Player 1 has to choose 1 word" << std::endl;
	std::wcout << "Once choose, player 2 has infinite guesses to guess the letters" << std::endl;
	std::wcout << "Player 2 has to enter \"guess\" to guess the word" << std::endl;
	std::wcout << "If Player 2 guess all the letters, you must guess the word" << std::endl;
	std::wcout << "============================================================================================================" << std::endl;

	std::wcout << L"══════════╗" << std::endl;
	std::wcout << L" Player 1 ║" << std::endl;
	std::wcout << L"══════════╩═══╗" << std::endl;
	std::wcout << L" Difficulty " << Difficulty << L" ║" << std::endl;
	std::wcout << L"══════════════╝" << std::endl;

	while(FirstValidation)
	{
		std::wcout << L"┅┅┅┅┅┅┅┅┅┅┅┅┅┅" << std::endl;
		std::wcout << "Enter the word: ";

		// Get whole line (from input start to end, not all text on line)
		std::getline(std::cin, SecretWord);

		std::wcout << L"┅┅┅┅┅┅┅┅┅┅┅┅┅┅" << std::endl;

		//Validation to make sure it only 1 word (if it contains any white spaces, it is considered multiword)
		FirstValidation = false;

		for(char letter : SecretWord)
		{
			if(isspace(letter))
			{
				std::wcout << "Enter only 1 word" << std::endl;
				FirstValidation = true;
				break;
			}
		}

		// no point doing secondary search if first one failed
		if(!FirstValidation)
		{
			switch(Difficulty)
			{
			case 1:
			case 2:
			case 3:
			//Using letter count as to not create more vars
				LetterCount = (5 * Difficulty) + 5;
				if(SecretWord.length() > LetterCount || SecretWord.length() < LetterCount-4)
				{
					FirstValidation = true;
					std::wcout << "Your word has to be between " << LetterCount-4 << "-" << LetterCount << std::endl;
					std::wcout << "Your word was: " << SecretWord.length() << " Letters long" << std::endl;
				}
				GuessCount = (-2*Difficulty)+10;
				break;
			case 5:
				GuessCount = 10;
				break;
			default:
				break;
			}
		}

	}
	
	//Lower case for easier comparing
	SecretWord = LowerString(SecretWord);
	//reuse variable for better memory optimasation
	FirstValidation = true;

	ClearScreen();

	std::wcout << L"══════════╗" << std::endl;
	std::wcout << L" Player 2 ║" << std::endl;
	std::wcout << L"══════════╝" << std::endl;
	std::wcout << "You have Infinite Guesses for the word" << std::endl;
	std::wcout << "Once you guess all the letters, you have to guess the word" << std::endl;
	std::wcout << std::endl;
	std::wcout << "Enter \"guess\" to start guessing the word" << std::endl;
	std::wcout << "Enter \"show\" to show the secret word |MOSTLY FOR TESTING AND SHOWING PURPOSES|" << std::endl;
	if(Multi)
	{
		std::wcout << "Write \"end\" to end the game and show results" << std::endl;
	}

	std::wcout << std::endl;
	std::wcout << "--------------------------------------------------------------------------------------------" << std::endl;
	std::wcout << std::endl;

#pragma region Guess_count_Logic

	if(GuessCount == 0)
	{
		InfGuess=true;
	}

#pragma endregion

	while(FirstValidation)
	{
#pragma region Reset_Variables
		WordShow = "";
		LetterCount = 0;
		FirstValidation = false;
		SecondValidation = true;
#pragma endregion

		std::wcout << L"══════════╗" << std::endl;
		std::wcout << L" Player 2 ║" << std::endl;
		std::wcout << L"══════════╝" << std::endl;


		//check what letters of the word they have found
		for(char WordLetter : SecretWord)
		{
			if(LetterStore.find(WordLetter) == std::string::npos)
			{

				FirstValidation = true;
				WordShow += "_";
			}
			else
			{
				WordShow += WordLetter;
			}
		}

		// Just so it doesn't go through another cycle when it doesn't need to
		if(!FirstValidation)
		{
			break;
		}

		WordShow += "\n";

		// set cursor (print position) to the right side for the word to show
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD(csbi.srWindow.Right - WordShow.size() + 1, 14 + (CurrentIterartion * 5)));
		wprintf(converter.from_bytes(WordShow).c_str());


		while(SecondValidation)
		{
			std::wcout << "Guess: ";
			std::getline(std::cin, CurrentGuess);
			//Lower case for easier comparing
			CurrentGuess = LowerString(CurrentGuess);

			SecondValidation = false;

			if(CurrentGuess == "show")
			{
				std::wcout << "Secret word is: " << converter.from_bytes(SecretWord).c_str() << std::endl;
				//Continues the current iteration so you don't loose a guess
				SecondValidation = true;
			}
			else if(CurrentGuess == "guess")
			{
				// Break out of outter loop
				std::wcout << "You now have to guess the word" << std::endl;
				FirstValidation = false;
				break;

			}
			else if(CurrentGuess == "end")
			{
				// 3 means ended game
				return 3;
			}
			else
			{
				if(CurrentGuess.length() == 1)
				{
					ThirdValidation = true;

					for(char Prev : LetterStore)
					{
						if(Prev == CurrentGuess[0])
						{
							std::wcout << "You have already used this letter before" << std::endl;
							ThirdValidation = false;
							break;
						}
					}

					if(ThirdValidation)
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
						std::wcout << "The word has " << LetterCount << " " << CurrentGuess[0] << "'s" << std::endl;

						//add the letter to the list
						LetterStore.push_back(CurrentGuess[0]);
					}
				}
				else
				{
					// "error" for if input is not letter or show
					std::wcout << "Enter only 1 letter or show" << std::endl;

					//Continues the current iteration so you don't loose a guess
					SecondValidation = true;
				}
			}
		}

		if(GuessCount <= CurrentIterartion && !InfGuess)
		{
			break;
		}

		CurrentIterartion += 1;
	}

	ClearScreen();

	std::wcout << L"══════════╗" << std::endl;
	std::wcout << L" Player 2 ║" << std::endl;
	std::wcout << L"══════════╝" << std::endl;

	std::wcout << "Guess the word" << std::endl;
	std::wcout << "--------------" << std::endl;

	std::wcout << "Word guess: ";

	wprintf(converter.from_bytes(WordShow).c_str());
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD(12, 5));

	std::getline(std::cin, CurrentGuess);
	std::wcout << std::endl << L"══════════════════════════════" << std::endl;

	if(CurrentGuess == SecretWord)
	{
		std::wcout << "Player 2 wins" << std::endl;
		std::wcout << "You deserve yourself a beer" << std::endl;
		// 1 means Player 2 won
		ReturnInt = 1;
	}
	else
	{
		std::wcout << "Player 1 wins" << std::endl;
		std::wcout << "You deserve yourself a beer" << std::endl;
		// 2 means Player 1 won
		ReturnInt = 2;
	}

	std::wcout << "The word was: " << converter.from_bytes(SecretWord).c_str() << std::endl << L"══════════════════════════════" << std::endl;

	return ReturnInt;
}

/// <summary>
/// Single Player Function
/// </summary>
void Functions::SingleGame()
{
	Game(false);

	std::wcout << "Press ENTER to continue to main Menu";
	std::cin.ignore();
}

/// <summary>
/// Multiplayer Function
/// </summary>
void Functions::MultiGames()
{
	int PlayerOne = 0, PlayerTwo = 0, ReturnValue;
	bool Continue = true;
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

	std::wstring ScoreTable = LR"(
╔══════════════════════════════╗
║           Scores             ║
║ ╭──────────────────╮         ║
║ │Player 1: P1S     │         ║
║ ╰──────────────────╯         ║
║ ╭──────────────────╮         ║
║ │Player 2: P2S     │         ║
║ ╰──────────────────╯         ║
║ ╭──────────────────╮         ║
║ │Total Round: TRS  │         ║
║ ╰──────────────────╯         ║
╚══════════════════════════════╝

)";

	while(Continue)
	{
		ClearScreen();

		ReturnValue = Game(true);
		
		switch(ReturnValue)
		{
			case 1:
				PlayerTwo += 1;
				break;
			case 2:
				PlayerOne += 1;
				break;
			case 3:
				Continue = false;
				break;
		}
	}

	ClearScreen();

	ScoreTable = WideStringReplace(ScoreTable, "P1S", MakeLenght(std::to_string(PlayerOne), 3, true));
	ScoreTable = WideStringReplace(ScoreTable, "P2S", MakeLenght(std::to_string(PlayerTwo), 3, true));
	ScoreTable = WideStringReplace(ScoreTable, "TRS", MakeLenght(std::to_string(PlayerTwo + PlayerOne), 3, true));

	std::wcout << ScoreTable << std::endl;

	std::wcout << "Press ENTER to continue to Main Menu";
	std::cin.ignore();
}

/// <summary>
/// Exit Function
/// </summary>
void Functions::Exit()
{
	exit(0);
}