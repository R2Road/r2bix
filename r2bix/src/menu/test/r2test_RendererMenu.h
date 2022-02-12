#pragma once

#include <memory>

namespace r2
{
	using MenuUp = std::unique_ptr<class TestMenu>;

	class Director;
}

namespace r2test
{
	class RendererMenu
	{
	private:
		RendererMenu() = delete;

	public:
		static const char* GetTitle() { return "Renderer"; }
		static r2::MenuUp Create( r2::Director& director );
	};
}