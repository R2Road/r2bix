#pragma once

#include <memory>

namespace r2
{
	using MenuUp = std::unique_ptr<class Menu>;

	class Director;

	class FrameBufferMenu
	{
	private:
		FrameBufferMenu() = delete;

	public:
		static const char* GetTitle() { return "Frame Buffer"; }
		static MenuUp Create( Director& director );
	};
}