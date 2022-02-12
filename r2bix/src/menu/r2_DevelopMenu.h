#pragma once

#include <memory>

namespace r2
{
	using MenuUp = std::unique_ptr<class TestMenu>;

	class Director;

	class DevelopMenu
	{
	private:
		DevelopMenu() = delete;

	public:
		static const char* GetTitle() { return "Develop"; }
		static MenuUp Create( Director& director );
	};
}