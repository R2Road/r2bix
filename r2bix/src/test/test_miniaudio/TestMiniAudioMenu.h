#pragma once

#include <memory>

namespace r2cm
{
	using MenuUp = std::unique_ptr<class Menu>;
	class Director;
}

class TestMiniAudioMenu
{
private:
	TestMiniAudioMenu() = delete;

public:
	static const char* GetTitle() { return "Test Mini Audio"; }
	static r2cm::MenuUp Create( r2cm::Director& director );
};