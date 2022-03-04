#pragma once

#include <memory>

namespace r2test
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
	static r2test::MenuUp Create( r2test::Director& director );
};