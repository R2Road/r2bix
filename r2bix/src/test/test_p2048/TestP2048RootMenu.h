#pragma once

#include <memory>

namespace r2cm
{
	using MenuUp = std::unique_ptr<class Menu>;

	class Director;
}

class TestP2048MiniRootMenu
{
private:
	TestP2048MiniRootMenu() = delete;

public:
	static const char* GetTitle() { return "Test P2048 Mini"; }
	static r2cm::MenuUp Create( r2cm::Director& director );
};