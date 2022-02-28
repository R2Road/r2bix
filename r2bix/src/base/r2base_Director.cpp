#include "pch.h"
#include "r2base_Director.h"

#include <utility> // std::move

#include "r2base_Node.h"

namespace r2base
{
	Director::Director() : mbAbort( false ), mNode()
	{}

	void Director::Setup( NodeUp node )
	{
		mNode = std::move( node );
	}

	void Director::Update()
	{
		while( !mbAbort )
		{
			mNode->Update();
		}
	}
}