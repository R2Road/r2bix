#pragma once

#include <memory>

namespace r2cm
{
	class Director;
	using MenuUp = std::unique_ptr<class Menu>;
}

class PSnakeMenu
{
private:
	PSnakeMenu() = delete;

public:
	static const char* GetTitle() { return "PSnake Menu( In Progress )"; }
	static r2cm::MenuUp Create( r2cm::Director& director );
};