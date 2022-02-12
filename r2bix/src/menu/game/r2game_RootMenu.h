#pragma once

#include <memory>

namespace r2
{
	using MenuUp = std::unique_ptr<class TestMenu>;

	class Director;
}

namespace r2game
{
	class RootMenu
	{
	private:
		RootMenu() = delete;

	public:
		static const char* GetTitle() { return "Game"; }
		static r2::MenuUp Create( r2::Director& director );
	};
}