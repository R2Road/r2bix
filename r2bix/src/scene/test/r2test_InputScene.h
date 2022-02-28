#pragma once

#include <memory>

namespace r2base
{
	using NodeUp = std::unique_ptr<class Node>;

	class Director;
}

namespace r2test
{
	class InputScene
	{
	private:
		InputScene() = delete;

	public:
		static const char* GetTitle() { return "Input"; }
		static r2base::NodeUp Create( r2base::Director& director );
	};
}