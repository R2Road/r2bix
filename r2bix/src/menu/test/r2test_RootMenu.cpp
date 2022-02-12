#include "pch.h"
#include "r2test_RootMenu.h"

#include "base/r2base_Director.h"
#include "base/r2base_eTestEndAction.h"
#include "base/r2base_TestMenu.h"

#include "menu/DevelopMenu.h"

#include "r2test_CameraMenu.h"
#include "r2test_FrameBufferMenu.h"
#include "r2test_InputMenu.h"
#include "r2test_RendererMenu.h"
#include "r2test_VisibleResourceMenu.h"

#include "test/rect_test.h"
#include "test/animation_test.h"

namespace r2test
{
	r2base::NodeUp RootMenu::Create( r2base::Director& director )
	{
		r2base::MenuUp ret( new ( std::nothrow ) r2base::TestMenu(
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
				, [&director]()->r2base::eTestEndAction
				{
					director.Setup( r2test::InputMenu::Create( director ) );
					return r2base::eTestEndAction::ChangeScene;
				}
			);
			ret->AddChild( '2', rect_test::Basic::GetInstance() );


			ret->AddLineFeed();


			ret->AddChild(
				'q'
				, []()->const char* { return r2test::FrameBufferMenu::GetTitle(); }
				, [&director]()->r2base::eTestEndAction
				{
					director.Setup( r2test::FrameBufferMenu::Create( director ) );
					return r2base::eTestEndAction::ChangeScene;
				}
			);
			ret->AddChild(
				'w'
				, []()->const char* { return r2test::VisibleResourceMenu::GetTitle(); }
				, [&director]()->r2base::eTestEndAction
				{
					director.Setup( r2test::VisibleResourceMenu::Create( director ) );
					return r2base::eTestEndAction::ChangeScene;
				}
			);
			ret->AddChild(
				'e'
				, []()->const char* { return r2test::CameraMenu::GetTitle(); }
				, [&director]()->r2base::eTestEndAction
				{
					director.Setup( r2test::CameraMenu::Create( director ) );
					return r2base::eTestEndAction::ChangeScene;
				}
			);
			ret->AddChild(
				'r'
				, []()->const char* { return r2test::RendererMenu::GetTitle(); }
				, [&director]()->r2base::eTestEndAction
				{
					director.Setup( r2test::RendererMenu::Create( director ) );
					return r2base::eTestEndAction::ChangeScene;
				}
			);


			ret->AddSplit();


			ret->AddChild( 'z', animation_test::Basic::GetInstance() );


			ret->AddSplit();


			ret->AddChild(
				27
				, []()->const char* { return "Return To Develop Menu"; }
				, [&director]()->r2base::eTestEndAction
				{
					director.Setup( DevelopMenu::Create( director ) );
					return r2base::eTestEndAction::ChangeScene;
				}
			);
		}

		return ret;
	}
}