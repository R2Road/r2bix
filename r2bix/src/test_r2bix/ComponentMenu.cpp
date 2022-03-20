#include "pch.h"
#include "ComponentMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "test_r2bix/TestRootMenu.h"

#include "component_test.h"

r2cm::MenuUp ComponentMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
	) );

	{
		ret->AddItem( '1', component_test::ComponentID::GetInstance() );
		ret->AddItem( '2', component_test::Component_Add_Get::GetInstance() );

		ret->AddLineFeed();
		ret->AddLineFeed();

		ret->AddItem( 'q', component_test::TextureRenderComponentTest_1::GetInstance() );
		ret->AddItem( 'w', component_test::TextureRenderComponentTest_2::GetInstance() );
		ret->AddItem( 'e', component_test::TextureRenderComponentTest_3::GetInstance() );

		ret->AddLineFeed();

		ret->AddItem( 'r', component_test::LabelComponentTest::GetInstance() );

		ret->AddLineFeed();
		ret->AddLineFeed();

		ret->AddItem( 'a', component_test::TextureFrameRenderComponentTest_1::GetInstance() );
		ret->AddItem( 's', component_test::TextureFrameRenderComponentTest_2::GetInstance() );

		ret->AddLineFeed();

		ret->AddItem( 'd', component_test::TextureFrameAnimationComponentTest_1::GetInstance() );
		ret->AddItem( 'f', component_test::TextureFrameAnimationComponentTest_2::GetInstance() );

		ret->AddLineFeed();
		ret->AddLineFeed();

		ret->AddItem( 'z', component_test::ActionProcessComponentTest_With_TickAction::GetInstance() );
		ret->AddItem( 'x', component_test::ActionProcessComponentTest_With_DelayAction::GetInstance() );
		ret->AddItem( 'c', component_test::ActionProcessComponentTest_With_SequenceAction::GetInstance() );
		ret->AddItem( 'v', component_test::ActionProcessComponentTest_With_MoveByAction::GetInstance() );
		ret->AddItem( 'b', component_test::ActionProcessComponentTest_With_RepeatAction::GetInstance() );
		ret->AddItem( 'n', component_test::ActionProcessComponentTest_With_BlinkAction::GetInstance() );
		ret->AddItem( 'm', component_test::ActionProcessComponentTest_With_CallbackAction::GetInstance() );
		ret->AddItem( ',', component_test::ActionProcessComponentTest_With_AnimationRequestAction::GetInstance() );


		ret->AddSplit();


		ret->AddItem(
			27
			, []()->const char* { return "Return To Root"; }
			, [&director]()->r2cm::eTestEndAction
			{
			director.Setup( TestRootMenu::Create( director ) );
			return r2cm::eTestEndAction::None;
			}
		);
	}

	return ret;
}