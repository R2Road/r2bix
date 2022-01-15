#include "pch.h"
#include "r2_RootMenu.h"

#include "base/r2_Director.h"
#include "base/r2_eTestResult.h"

#include "menu/r2_CameraMenu.h"
#include "menu/r2_RendererMenu.h"
#include "menu/r2_ResearchMenu.h"
#include "menu/r2_VisibleResourceMenu.h"

#include "test/framebuffer_test.h"
#include "test/key_test.h"
#include "test/rect_test.h"
#include "test/camera_test.h"
#include "test/animation_test.h"

namespace r2
{
	MenuUp RootMenu::Create( Director& director )
	{
		MenuUp ret( new ( std::nothrow ) Menu(
			director
			, GetTitle(),
					"> Inprogress : Update Camera Test"
			"\n"	"> To do : Command - Double Buffering"
			"\n"	"> To do : Renderer"
		) );

		{
			ret->AddChild( '1', key_test::Basic::GetInstance() );
			ret->AddChild( '2', rect_test::Basic::GetInstance() );


			ret->AddLineFeed();


			ret->AddChild( '3', framebuffer_test::Basic::GetInstance() );
			ret->AddChild( '4', framebuffer_test::DrawAtOnce::GetInstance() );


			ret->AddLineFeed();


			ret->AddChild(
				'q'
				, []()->const char* { return r2::VisibleResourceMenu::GetTitle(); }
				, [&director]()->eTestResult
				{
					director.Setup( r2::VisibleResourceMenu::Create( director ) );
					return eTestResult::ChangeScene;
				}
			);
			ret->AddChild(
				'w'
				, []()->const char* { return r2::CameraMenu::GetTitle(); }
				, [&director]()->eTestResult
				{
					director.Setup( r2::CameraMenu::Create( director ) );
					return eTestResult::ChangeScene;
				}
			);
			ret->AddChild(
				'e'
				, []()->const char* { return r2::RendererMenu::GetTitle(); }
				, [&director]()->eTestResult
				{
					director.Setup( r2::RendererMenu::Create( director ) );
					return eTestResult::ChangeScene;
				}
			);


			ret->AddSplit();


			ret->AddChild( 'z', animation_test::Basic::GetInstance() );


			ret->AddSplit();


			ret->AddChild(
				32
				, []()->const char* { return r2::ResearchMenu::GetTitle(); }
				, [&director]()->eTestResult
				{
					director.Setup( r2::ResearchMenu::Create( director ) );
					return eTestResult::ChangeScene;
				}
			);


			ret->AddSplit();


			ret->AddChild(
				27
				, []()->const char* { return "Exit"; }
				, []()->eTestResult { return eTestResult::Exit; }
			);
		}

		return ret;
	}
}