#include "pch.h"
#include "r2test_RootMenu.h"

#include "base/r2_Director.h"
#include "base/r2_eTestEndAction.h"

#include "menu/r2_DevelopMenu.h"

#include "r2test_CameraMenu.h"
#include "r2test_FrameBufferMenu.h"
#include "r2test_InputMenu.h"
#include "r2test_RendererMenu.h"
#include "r2test_VisibleResourceMenu.h"

#include "test/rect_test.h"
#include "test/animation_test.h"

namespace r2test
{
	r2::MenuUp RootMenu::Create( r2::Director& director )
	{
		r2::MenuUp ret( new ( std::nothrow ) r2::Menu(
			director
			, GetTitle(),
					"> Inprogress : Update Camera Test"
			"\n"	"> To do : Command - Double Buffering"
			"\n"	"> To do : Renderer"
		) );

		{
			ret->AddChild(
				'1'
				, []()->const char* { return r2test::InputMenu::GetTitle(); }
				, [&director]()->r2::eTestEndAction
				{
					director.Setup( r2test::InputMenu::Create( director ) );
					return r2::eTestEndAction::ChangeScene;
				}
			);
			ret->AddChild( '2', rect_test::Basic::GetInstance() );


			ret->AddLineFeed();


			ret->AddChild(
				'q'
				, []()->const char* { return r2test::FrameBufferMenu::GetTitle(); }
				, [&director]()->r2::eTestEndAction
				{
					director.Setup( r2test::FrameBufferMenu::Create( director ) );
					return r2::eTestEndAction::ChangeScene;
				}
			);
			ret->AddChild(
				'w'
				, []()->const char* { return r2test::VisibleResourceMenu::GetTitle(); }
				, [&director]()->r2::eTestEndAction
				{
					director.Setup( r2test::VisibleResourceMenu::Create( director ) );
					return r2::eTestEndAction::ChangeScene;
				}
			);
			ret->AddChild(
				'e'
				, []()->const char* { return r2test::CameraMenu::GetTitle(); }
				, [&director]()->r2::eTestEndAction
				{
					director.Setup( r2test::CameraMenu::Create( director ) );
					return r2::eTestEndAction::ChangeScene;
				}
			);
			ret->AddChild(
				'r'
				, []()->const char* { return r2test::RendererMenu::GetTitle(); }
				, [&director]()->r2::eTestEndAction
				{
					director.Setup( r2test::RendererMenu::Create( director ) );
					return r2::eTestEndAction::ChangeScene;
				}
			);


			ret->AddSplit();


			ret->AddChild( 'z', animation_test::Basic::GetInstance() );


			ret->AddSplit();


			ret->AddChild(
				27
				, []()->const char* { return "Return To Develop Menu"; }
				, [&director]()->r2::eTestEndAction
				{
					director.Setup( r2::DevelopMenu::Create( director ) );
					return r2::eTestEndAction::ChangeScene;
				}
			);
		}

		return ret;
	}
}