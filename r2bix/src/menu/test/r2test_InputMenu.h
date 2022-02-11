#pragma once

#include <memory>

namespace r2
{
	using MenuUp = std::unique_ptr<class Menu>;

	class Director;
}

namespace r2test
{
	class InputMenu
	{
	private:
		InputMenu() = delete;

	public:
		static const char* GetTitle() { return "Input"; }
		static r2::MenuUp Create( r2::Director& director );
	};
}