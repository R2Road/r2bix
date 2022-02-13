#include "pch.h"
#include "r2game_RootScene.h"

#include "base/r2base_Director.h"

#include "scene/GameScene.h"

namespace r2game
{
	r2base::NodeUp RootScene::Create( r2base::Director& director )
	{
		r2base::NodeUp ret( new ( std::nothrow ) GameScene( director ) );
		return ret;
	}
}