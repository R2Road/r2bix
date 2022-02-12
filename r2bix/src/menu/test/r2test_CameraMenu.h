#pragma once

#include <memory>

namespace r2base
{
	using NodeUp = std::unique_ptr<class iNode>;

	class Director;
}

namespace r2test
{
	class CameraMenu
	{
	private:
		CameraMenu() = delete;

	public:
		static const char* GetTitle() { return "Camera"; }
		static r2base::NodeUp Create( r2base::Director& director );
	};
}