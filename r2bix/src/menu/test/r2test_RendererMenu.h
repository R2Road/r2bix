#pragma once

#include <memory>

namespace r2
{
	using NodeUp = std::unique_ptr<class iNode>;

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
		static r2::NodeUp Create( r2::Director& director );
	};
}