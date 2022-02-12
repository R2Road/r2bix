#include "pch.h"
#include "r2base_Director.h"

#include <conio.h>
#include <utility>

#include "r2base_eTestEndAction.h"
#include "r2base_iNode.h"

namespace r2base
{
	Director::Director() : mNode()
	{}

	void Director::Setup( NodeUp node )
	{
		mNode = std::move( node );
	}

	void Director::Update()
	{
		while( r2base::eTestEndAction::Exit != mNode->Do() )
		{}
	}
}