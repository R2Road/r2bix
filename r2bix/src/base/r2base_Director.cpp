#include "pch.h"
#include "r2base_Director.h"

#include <utility> // std::move

#include "node/r2node_SceneNode.h"

namespace r2base
{
	Director::Director() : mbAbort( false ), mSceneNode()
	{}

	void Director::Setup( r2node::SceneNodeUp node )
	{
		mSceneNode = std::move( node );
	}

	void Director::Update()
	{
		while( !mbAbort )
		{
			mSceneNode->Update();
			mSceneNode->Render();
		}
	}
}