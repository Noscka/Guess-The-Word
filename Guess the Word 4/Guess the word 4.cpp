#include <iostream>
#include <conio.h>
#include <windows.h>
#include "MenuEntry.h"
#include "Functions.h"
#include <list>
#include <string>
#include <io.h>
#include <fcntl.h>
#include <codecvt>

#pragma warning(disable : 4996)


#pragma region Variables
int CurrentIndex = 0;

int c, ex;
CONSOLE_SCREEN_BUFFER_INFO csbi;
int columns, rows, counter;
std::string EntryString;

std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

std::list<MenuEntry> EntryList = {
	MenuEntry("Single Game", Functions::SingleGame),
	MenuEntry("Multi Games", Functions::MultiGames),
	MenuEntry("Exit", Functions::Exit)
};

#pragma endregion


#define ARROW_UP    72
#define ARROW_DOWN  80
#define ENTER       13

int main()
{
	//stupid fucking shit because of course who would want to use the modern fucking character set
	//making it so you have to fucking convert and then add L to start of strings

	// sets console to UTF-16
	_setmode(_fileno(stdout), _O_U16TEXT);

	while(true)
	{
	// Set the start of the string to be the "title"
		EntryString = R"(

 /$$   /$$                                     /$$      /$$                    
| $$  | $$                                    | $$$    /$$$                    
| $$  | $$  /$$$$$$  /$$$$$$$   /$$$$$$       | $$$$  /$$$$  /$$$$$$  /$$$$$$$ 
| $$$$$$$$ |____  $$| $$__  $$ /$$__  $$      | $$ $$/$$ $$ |____  $$| $$__  $$
| $$__  $$  /$$$$$$$| $$  \ $$| $$  \ $$      | $$  $$$| $$  /$$$$$$$| $$  \ $$
| $$  | $$ /$$__  $$| $$  | $$| $$  | $$      | $$\  $ | $$ /$$__  $$| $$  | $$
| $$  | $$|  $$$$$$$| $$  | $$|  $$$$$$$      | $$ \/  | $$|  $$$$$$$| $$  | $$
|__/  |__/ \_______/|__/  |__/ \____  $$      |__/     |__/ \_______/|__/  |__/
                               /$$  \ $$
                              |  $$$$$$/
                               \______/
)";
		// Get console widght and heigh for making the text be centered
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

		// for loop using counter to get the index so to add the >< to the selected option
		counter = 0;
		for(MenuEntry Entry : EntryList)
		{
			// Append to string as to make it be 1 print operation, makes it way quicker
			if(counter == CurrentIndex)
			{
				EntryString += std::string((columns / 2) - (1 + Entry.Name.length()) / 2, ' ') + ">" + Entry.Name + "<\n";
			}
			else
			{
				EntryString += std::string((columns / 2) - Entry.Name.length() / 2, ' ') + Entry.Name + "\n";
			}
			counter++;
		}

		// print in 1 operation
		wprintf(converter.from_bytes(EntryString).c_str());

		// get key input for arrow and enter inputs
		c = _getch();

		if(c == ENTER)
		{
			// if enter, get the function of the selected entry and run it
			std::list<MenuEntry>::iterator iterator = EntryList.begin();
			std::advance(iterator, CurrentIndex);

			Functions::ClearScreen();
			((MenuEntry)*iterator).Function();

		}
		else if(!(c && c != 224))
		{
			// if not enter, do second getch as arrows input 2 characters to show they are arrows
			switch(ex = _getch())
			{
			case ARROW_UP:
				if(CurrentIndex > 0) // Decrement only if smaller then List size
				{
					CurrentIndex--; // Decrement the Indenetation
				}
				break;

			case ARROW_DOWN:
				if(CurrentIndex < EntryList.size() - 1) // Increment only if larger the 0
				{
					CurrentIndex++; // Increment the Indenetation
				}
				break;
			}
		}

		Functions::ClearScreen();
	}

	return 0;
}

