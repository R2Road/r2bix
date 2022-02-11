#pragma once

#include <memory>

namespace r2
{
	using MenuUp = std::unique_ptr<class Menu>;

	class Director;

	class VisibleResourceMenu
	{
	private:
		VisibleResourceMenu() = delete;

	public:
		static const char* GetTitle() { return "Visible Resource"; }
		static MenuUp Create( Director& director );
	};
}