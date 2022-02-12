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
		int input = 0;
		while( true )
		{
			switch( mNode->Do() )
			{
			case r2base::eTestEndAction::None:
				system( "cls" );
				break;

			case r2base::eTestEndAction::Pause:
				std::cout << r2::linefeed;
				system( "pause" );

				system( "cls" );
				break;

			//case r2base::eTestEndAction::ChangeScene:
				//break;

			case r2base::eTestEndAction::Exit:
				return;
			}
		}
	}
}