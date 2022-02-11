#include "pch.h"
#include "r2_RootMenu.h"

#include "base/r2_Director.h"
#include "base/r2_eTestEndAction.h"

#include "menu/r2_DevelopMenu.h"

#include "r2_CameraMenu.h"
#include "r2_FrameBufferMenu.h"
#include "r2_InputMenu.h"
#include "r2_RendererMenu.h"
#include "r2_VisibleResourceMenu.h"

#include "test/rect_test.h"
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
			ret->AddChild(
				'1'
				, []()->const char* { return r2::InputMenu::GetTitle(); }
				, [&director]()->eTestEndAction
				{
					director.Setup( r2::InputMenu::Create( director ) );
					return eTestEndAction::ChangeScene;
				}
			);
			ret->AddChild( '2', rect_test::Basic::GetInstance() );


			ret->AddLineFeed();


			ret->AddChild(
				'q'
				, []()->const char* { return r2::FrameBufferMenu::GetTitle(); }
				, [&director]()->eTestEndAction
				{
					director.Setup( r2::FrameBufferMenu::Create( director ) );
					return eTestEndAction::ChangeScene;
				}
			);
			ret->AddChild(
				'w'
				, []()->const char* { return r2::VisibleResourceMenu::GetTitle(); }
				, [&director]()->eTestEndAction
				{
					director.Setup( r2::VisibleResourceMenu::Create( director ) );
					return eTestEndAction::ChangeScene;
				}
			);
			ret->AddChild(
				'e'
				, []()->const char* { return r2::CameraMenu::GetTitle(); }
				, [&director]()->eTestEndAction
				{
					director.Setup( r2::CameraMenu::Create( director ) );
					return eTestEndAction::ChangeScene;
				}
			);
			ret->AddChild(
				'r'
				, []()->const char* { return r2::RendererMenu::GetTitle(); }
				, [&director]()->eTestEndAction
				{
					director.Setup( r2::RendererMenu::Create( director ) );
					return eTestEndAction::ChangeScene;
				}
			);


			ret->AddSplit();


			ret->AddChild( 'z', animation_test::Basic::GetInstance() );


			ret->AddSplit();


			ret->AddChild(
				27
				, []()->const char* { return "Return To Develop Menu"; }
				, [&director]()->eTestEndAction
				{
					director.Setup( r2::DevelopMenu::Create( director ) );
					return eTestEndAction::ChangeScene;
				}
			);
		}

		return ret;
	}
}