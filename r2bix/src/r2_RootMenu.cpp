#include "pch.h"
#include "r2_RootMenu.h"

#include "r2_Director.h"
#include "r2_eTestResult.h"

#include "key_test.h"
#include "rect_test.h"
#include "visibleresource_test.h"
#include "renderer_test.h"
#include "camera_test.h"
#include "animation_test.h"

namespace r2
{
	MenuUp RootMenu::Create( Director& director )
	{
		MenuUp ret( new ( std::nothrow ) Menu(
			director
			, GetTitle()
			, "> Inprogress : Renderer"
		) );

		{
			ret->AddChild( '1', key_test::Basic::GetInstance() );


			ret->AddSplit();


			ret->AddChild( '2', visibleresource_test::FillAll::GetInstance() );
			ret->AddChild( '3', visibleresource_test::Fill::GetInstance() );
			ret->AddChild( '4', visibleresource_test::DrawWithPosition::GetInstance() );
			ret->AddChild( '5', visibleresource_test::InitWithChars::GetInstance() );
			ret->AddChild( '6', visibleresource_test::VisibleRect::GetInstance() );


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
				27
				, []()->const char* { return "Exit"; }
				, []()->eTestResult { return eTestResult::Exit; }
			);
		}

		return ret;
	}
}