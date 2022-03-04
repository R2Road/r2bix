#pragma once

#include <memory>

namespace r2test
{
	using MenuUp = std::unique_ptr<class Menu>;

	class Director;
}

class TextureMenu
{
private:
	TextureMenu() = delete;

public:
	static const char* GetTitle() { return "Texture"; }
	static r2test::MenuUp Create( r2test::Director& director );
};