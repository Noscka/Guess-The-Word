#pragma once
#include <string>
#include <functional>

class MenuEntry
{
public:
    std::string Name;
    std::function<void()> Function;

    MenuEntry(std::string name, std::function<void()> function);
};
