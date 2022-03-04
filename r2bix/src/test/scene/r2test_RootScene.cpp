#include "pch.h"
#include "r2test_RootScene.h"

#include "base/r2base_Director.h"
#include "test/r2test_eTestEndAction.h"

namespace r2test
{
	r2node::SceneNodeUp RootScene::Create( r2base::Director& )
	{
		return nullptr;
	}
}