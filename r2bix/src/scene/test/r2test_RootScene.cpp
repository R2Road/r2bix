#include "pch.h"
#include "r2test_RootScene.h"

#include "base/r2base_Director.h"
#include "base/r2base_eTestEndAction.h"

#include "r2test_CameraScene.h"
#include "r2test_FrameBufferScene.h"
#include "r2test_InputScene.h"
#include "r2test_RendererScene.h"
#include "r2test_VisibleResourceScene.h"

#include "scene/DevelopScene.h"
#include "scene/TestScene.h"

#include "test/rect_test.h"
#include "test/animation_test.h"

namespace r2test
{
	r2base::NodeUp RootScene::Create( r2base::Director& director )
	{
		TestSceneUp ret( new ( std::nothrow ) TestScene(
			director
			, GetTitle(),
					"> Inprogress : Update Camera Test"
			"\n"	"> To do : Command - Double Buffering"
			"\n"	"> To do : Renderer"
		) );

		{
			ret->AddChild(
				'1'
				, []()->const char* { return r2test::InputScene::GetTitle(); }
				, [&director]()->r2base::eTestEndAction
				{
					director.Setup( r2test::InputScene::Create( director ) );
					return r2base::eTestEndAction::ChangeScene;
				}
			);
			ret->AddChild( '2', rect_test::Basic::GetInstance() );


			ret->AddLineFeed();


			ret->AddChild(
				'q'
				, []()->const char* { return r2test::FrameBufferScene::GetTitle(); }
				, [&director]()->r2base::eTestEndAction
				{
					director.Setup( r2test::FrameBufferScene::Create( director ) );
					return r2base::eTestEndAction::ChangeScene;
				}
			);
			ret->AddChild(
				'w'
				, []()->const char* { return r2test::VisibleResourceScene::GetTitle(); }
				, [&director]()->r2base::eTestEndAction
				{
					director.Setup( r2test::VisibleResourceScene::Create( director ) );
					return r2base::eTestEndAction::ChangeScene;
				}
			);
			ret->AddChild(
				'e'
				, []()->const char* { return r2test::CameraScene::GetTitle(); }
				, [&director]()->r2base::eTestEndAction
				{
					director.Setup( r2test::CameraScene::Create( director ) );
					return r2base::eTestEndAction::ChangeScene;
				}
			);
			ret->AddChild(
				'r'
				, []()->const char* { return r2test::RendererScene::GetTitle(); }
				, [&director]()->r2base::eTestEndAction
				{
					director.Setup( r2test::RendererScene::Create( director ) );
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
					director.Setup( DevelopScene::Create( director ) );
					return r2base::eTestEndAction::ChangeScene;
				}
			);
		}

		return ret;
	}
}