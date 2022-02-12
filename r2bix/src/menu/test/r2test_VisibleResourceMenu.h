#pragma once

#include <memory>

namespace r2
{
	using NodeUp = std::unique_ptr<class iNode>;

	class Director;
}

namespace r2test
{
	class VisibleResourceMenu
	{
	private:
		VisibleResourceMenu() = delete;

	public:
		static const char* GetTitle() { return "Visible Resource"; }
		static r2::NodeUp Create( r2::Director& director );
	};
}