#pragma once

#include <memory>

namespace r2base
{
	class Director;
}

namespace r2node
{
	using SceneNodeUp = std::unique_ptr<class SceneNode>;
}

class DevelopScene
{
private:
	DevelopScene() = delete;

public:
	static const char* GetTitle() { return "Develop"; }
	static r2node::SceneNodeUp Create( r2base::Director& director );
};