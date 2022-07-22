#pragma once

#include <memory>

namespace r2cm
{
	using MenuUp = std::unique_ptr<class Menu>;
	class Director;
}

class MiniAudioMenu
{
private:
	MiniAudioMenu() = delete;

public:
	static const char* GetTitle() { return "Mini Audio Menu"; }
	static r2cm::MenuUp Create( r2cm::Director& director );
};