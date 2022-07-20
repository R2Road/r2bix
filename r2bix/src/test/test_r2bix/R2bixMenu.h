#pragma once

#include <memory>

namespace r2cm
{
	using MenuUp = std::unique_ptr<class Menu>;

	class Director;
}

class TestR2bixRootMenu
{
private:
	TestR2bixRootMenu() = delete;

public:
	static const char* GetTitle() { return "R2bix Menu"; }
	static r2cm::MenuUp Create( r2cm::Director& director );
};