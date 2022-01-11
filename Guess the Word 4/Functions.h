#pragma once
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <codecvt>
#include <fcntl.h>
#include <regex>

#pragma warning(disable : 4996)

class Functions
{
public:
	static std::wstring WideStringReplace(std::wstring WholeString, std::string Word, std::string Replace);
	static std::string MakeLenght(std::string string, int lenght, bool LeftRight);
    static void ClearScreen();
	static std::string LowerString(std::string Input);
	static bool isNumber(const std::string& str);
	static int Game(bool Multi);
    static void SingleGame();
    static void MultiGames();
    static void Exit();
};

