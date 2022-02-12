#pragma once

#include <memory>

namespace r2
{
	using NodeUp = std::unique_ptr<class iNode>;

	class Director;

	class DevelopMenu
	{
	private:
		DevelopMenu() = delete;

	public:
		static const char* GetTitle() { return "Develop"; }
		static NodeUp Create( Director& director );
	};
}