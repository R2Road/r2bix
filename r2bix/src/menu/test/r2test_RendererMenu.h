#pragma once

#include <memory>

namespace r2base
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
		static r2base::NodeUp Create( r2base::Director& director );
	};
}