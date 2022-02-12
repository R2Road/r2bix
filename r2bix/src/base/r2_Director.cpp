#include "pch.h"
#include "r2_Director.h"

#include <conio.h>
#include <utility>

#include "r2_eTestEndAction.h"

namespace r2
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
			mNode->ShowInformation();
			input = _getch();

			system( "cls" );

			switch( mNode->Do( input ) )
			{
			case eTestEndAction::None:
				system( "cls" );
				break;

			case eTestEndAction::Pause:
				std::cout << r2::linefeed;
				system( "pause" );

				system( "cls" );
				break;

			//case eTestEndAction::ChangeScene:
				//break;

			case eTestEndAction::Exit:
				return;
			}
		}
	}
}