#include "pch.h"
#include "r2test_TextureScene.h"

#include "base/r2base_Director.h"
#include "base/r2base_eTestEndAction.h"

#include "r2test_RootScene.h"

#include "scene/TestScene.h"

#include "test/texture_test.h"
#include "test/texture_frame_test.h"

namespace r2test
{
	r2base::NodeUp TextureScene::Create( r2base::Director& director )
	{
		TestSceneUp ret( new ( std::nothrow ) TestScene(
			director
			, GetTitle(),
			"> ..."
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
			ret->AddChild( 's', texture_frame_test::VisibleRect::GetInstance() );


			ret->AddSplit();


			ret->AddChild(
				27
				, []()->const char* { return "Return To Root"; }
				, [&director]()->r2base::eTestEndAction
				{
					director.Setup( r2test::RootScene::Create( director ) );
					return r2base::eTestEndAction::None;
				}
			);
		}

		return ret;
	}
}