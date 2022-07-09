#pragma once

#include <memory>

namespace r2cm
{
	class Director;
	using MenuUp = std::unique_ptr<class Menu>;
}

class TextureMenu
{
private:
	TextureMenu() = delete;

public:
	static const char* GetTitle() { return "Texture, Texture Frame, Texture Table Menu"; }
	static r2cm::MenuUp Create( r2cm::Director& director );
};