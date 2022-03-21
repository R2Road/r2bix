#include "pch.h"
#include "ActionMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "test_r2bix/TestRootMenu.h"

#include "action_test.h"

r2cm::MenuUp ActionMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
	) );

	{
		ret->AddItem( 'a', action_test::ActionProcessComponentTest_With_TickAction::GetInstance() );
		ret->AddItem( 's', action_test::ActionProcessComponentTest_With_DelayAction::GetInstance() );
		ret->AddItem( 'd', action_test::ActionProcessComponentTest_With_SequenceAction::GetInstance() );
		ret->AddItem( 'f', action_test::ActionProcessComponentTest_With_MoveByAction::GetInstance() );
		ret->AddItem( 'g', action_test::ActionProcessComponentTest_With_RepeatAction::GetInstance() );
		ret->AddItem( 'h', action_test::ActionProcessComponentTest_With_BlinkAction::GetInstance() );
		ret->AddItem( 'j', action_test::ActionProcessComponentTest_With_CallbackAction::GetInstance() );
		ret->AddItem( 'k', action_test::ActionProcessComponentTest_With_AnimationRequestAction::GetInstance() );


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