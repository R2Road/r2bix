#pragma once

#include <memory>

namespace r2base
{
	using NodeUp = std::unique_ptr<class iNode>;

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
		static r2base::NodeUp Create( r2base::Director& director );
	};
}