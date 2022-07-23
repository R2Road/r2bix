#pragma once

#include <memory>

namespace r2cm
{
	using MenuUp = std::unique_ptr<class Menu>;

	class Director;
}

class P2048Menu
{
private:
	P2048Menu() = delete;

public:
	static const char* GetTitle() { return "P2048 Menu( To do )"; }
	static r2cm::MenuUp Create( r2cm::Director& director );
};