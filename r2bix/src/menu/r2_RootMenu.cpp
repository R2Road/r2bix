#include "pch.h"
#include "r2_RootMenu.h"

#include "base/r2_Director.h"
#include "base/r2_eTestResult.h"

#include "menu/r2_ResearchMenu.h"

#include "test/framebuffer_test.h"
#include "test/key_test.h"
#include "test/rect_test.h"
#include "test/visible_resource_test.h"
#include "test/renderer_test.h"
#include "test/camera_test.h"
#include "test/animation_test.h"

namespace r2
{
	MenuUp RootMenu::Create( Director& director )
	{
		MenuUp ret( new ( std::nothrow ) Menu(
			director
			, GetTitle(),
			"\n" "> Inprogress : flickering check"
			"\n" "> To do : Command - Double Buffering"
			"\n" "> To do : Renderer"
		) );

		{
			ret->AddChild( '1', key_test::Basic::GetInstance() );


			ret->AddSplit();


			ret->AddChild( '2', framebuffer_test::Basic::GetInstance() );
			ret->AddChild( '3', framebuffer_test::DrawAtOnce::GetInstance() );


			ret->AddLineFeed();


			ret->AddChild( '4', visible_resource_test::FillAll::GetInstance() );
			ret->AddChild( '5', visible_resource_test::Fill::GetInstance() );
			ret->AddChild( '6', visible_resource_test::DrawWithPosition::GetInstance() );
			ret->AddChild( '7', visible_resource_test::InitWithChars::GetInstance() );
			ret->AddChild( '8', visible_resource_test::VisibleRect::GetInstance() );


			ret->AddLineFeed();


			ret->AddChild( 'q', renderer_test::TestRenderable::GetInstance() );
			ret->AddChild( 'w', renderer_test::TestRenderer::GetInstance() );


			ret->AddLineFeed();


			ret->AddChild( 'a', rect_test::Basic::GetInstance() );
			ret->AddChild( 's', camera_test::CameraRect::GetInstance() );
			ret->AddChild( 'd', camera_test::CameraMove1::GetInstance() );
			ret->AddChild( 'f', camera_test::CameraMove2::GetInstance() );


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