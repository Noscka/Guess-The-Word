#include "MenuEntry.h"

MenuEntry::MenuEntry(std::string name, std::function<void()> function)
{
	Name = name;
	Function = function;
}
