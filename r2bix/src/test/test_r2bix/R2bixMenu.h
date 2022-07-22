#pragma once

#include <memory>

namespace r2cm
{
	class Director;
	using MenuUp = std::unique_ptr<class Menu>;
}

class R2bixMenu
{
private:
	R2bixMenu() = delete;

public:
	static const char* GetTitle() { return "R2bix Menu"; }
	static r2cm::MenuUp Create( r2cm::Director& director );
};