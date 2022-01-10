#pragma once

#include <memory>

namespace r2
{
	using MenuUp = std::unique_ptr<class Menu>;

	class Director;

	class ResearchMenu
	{
	private:
		ResearchMenu() = delete;

	public:
		static const char* GetTitle() { return "Research"; }
		static MenuUp Create( Director& director );
	};
}