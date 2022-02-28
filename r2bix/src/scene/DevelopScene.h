#pragma once

#include <memory>

namespace r2base
{
	using NodeUp = std::unique_ptr<class Node>;

	class Director;
}

class DevelopScene
{
private:
	DevelopScene() = delete;

public:
	static const char* GetTitle() { return "Develop"; }
	static r2base::NodeUp Create( r2base::Director& director );
};