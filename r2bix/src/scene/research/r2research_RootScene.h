#pragma once

#include <memory>

namespace r2base
{
	using NodeUp = std::unique_ptr<class iNode>;

	class Director;
}

namespace r2research
{
	class RootScene
	{
	private:
		RootScene() = delete;

	public:
		static const char* GetTitle() { return "Research"; }
		static r2base::NodeUp Create( r2base::Director& director );
	};
}