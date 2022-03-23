#pragma once

#include <memory>

namespace r2cm
{
	using MenuUp = std::unique_ptr<class Menu>;

	class Director;
}

class TestP2048RootMenu
{
private:
	TestP2048RootMenu() = delete;

public:
	static const char* GetTitle() { return "Test P2048"; }
	static r2cm::MenuUp Create( r2cm::Director& director );
};