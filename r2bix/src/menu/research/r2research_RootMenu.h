#pragma once

#include <memory>

namespace r2
{
	using MenuUp = std::unique_ptr<class Menu>;

	class Director;
}

namespace r2research
{
	class RootMenu
	{
	private:
		RootMenu() = delete;

	public:
		static const char* GetTitle() { return "Research"; }
		static r2::MenuUp Create( r2::Director& director );
	};
}