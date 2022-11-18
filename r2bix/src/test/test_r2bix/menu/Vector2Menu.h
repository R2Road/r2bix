#pragma once

#include <memory>

namespace r2cm
{
	class Director;
	using MenuUp = std::unique_ptr<class Menu>;
}

class Vector2Menu
{
private:
	Vector2Menu() = delete;

public:
	static const char* GetTitle() { return "Vector2 Menu"; }
	static r2cm::MenuUp Create( r2cm::Director& director );
};