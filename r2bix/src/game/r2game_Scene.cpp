#include "pch.h"
#include "r2game_Scene.h"

#include "base/r2base_Director.h"

namespace r2game
{
	Scene::Scene( r2base::Director& director ) : r2game::Node( director )
	{}

	bool Scene::Do()
	{
		return true;
	}
}