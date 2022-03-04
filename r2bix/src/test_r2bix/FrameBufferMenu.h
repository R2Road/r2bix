#pragma once

#include <memory>

namespace r2cm
{
	using MenuUp = std::unique_ptr<class Menu>;

	class Director;
}

class FrameBufferMenu
{
private:
	FrameBufferMenu() = delete;

public:
	static const char* GetTitle() { return "Frame Buffer"; }
	static r2cm::MenuUp Create( r2cm::Director& director );
};