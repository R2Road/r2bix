#pragma once

#include <memory>

namespace r2
{
	using MenuUp = std::unique_ptr<class TestMenu>;

	class Director;
}

namespace r2test
{
	class FrameBufferMenu
	{
	private:
		FrameBufferMenu() = delete;

	public:
		static const char* GetTitle() { return "Frame Buffer"; }
		static r2::MenuUp Create( r2::Director& director );
	};
}