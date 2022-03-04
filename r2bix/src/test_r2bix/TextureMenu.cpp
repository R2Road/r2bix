#include "pch.h"
#include "TextureMenu.h"

#include "test/r2test_Director.h"
#include "test/r2test_eTestEndAction.h"

#include "test_r2bix/TestRootMenu.h"

#include "texture_test.h"
#include "texture_frame_test.h"

r2test::MenuUp TextureMenu::Create( r2test::Director& director )
{
	r2test::MenuUp ret( new ( std::nothrow ) r2test::Menu(
		director
		, GetTitle()
	) );

	{
		ret->AddChild( '1', texture_test::FillAll::GetInstance() );
		ret->AddChild( '2', texture_test::Fill::GetInstance() );


		ret->AddLineFeed();


		ret->AddChild( 'q', texture_test::InitWithChars_1::GetInstance() );
		ret->AddChild( 'w', texture_test::InitWithChars_2::GetInstance() );
		ret->AddChild( 'e', texture_test::InitWithChars_3::GetInstance() );
		ret->AddChild( 'r', texture_test::InitWithChars_4::GetInstance() );


		ret->AddLineFeed();
		ret->AddLineFeed();


		ret->AddChild( 'a', texture_frame_test::Basic::GetInstance() );
		ret->AddChild( 's', texture_frame_test::VisibleRect_1::GetInstance() );
		ret->AddChild( 'd', texture_frame_test::VisibleRect_2::GetInstance() );
		ret->AddChild( 'f', texture_frame_test::VisibleRect_3::GetInstance() );


		ret->AddSplit();


		ret->AddChild(
			27
			, []()->const char* { return "Return To Root"; }
			, [&director]()->r2test::eTestEndAction
			{
			director.Setup( TestRootMenu::Create( director ) );
				return r2test::eTestEndAction::None;
			}
		);
	}

	return ret;
}