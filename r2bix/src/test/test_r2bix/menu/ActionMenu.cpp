#include "ActionMenu.h"

#include "r2cm/r2cm_Director.h"

#include "test/test_r2bix/R2bixMenu.h"

#include "test/test_r2bix/item/action_test.h"

r2cm::MenuUp ActionMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
	) );

	{
		ret->AddItem( '1', action_test::TickActionTest() );
		ret->AddItem( '2', action_test::DelayActionTest() );
		ret->AddItem( '3', action_test::SequenceActionTest() );
		ret->AddItem( '4', action_test::MoveByActionTest() );
		ret->AddItem( '5', action_test::MoveToActionTest() );

		ret->AddLineFeed();

		ret->AddItem( 'q', action_test::RepeatActionTest() );
		ret->AddItem( 'w', action_test::BlinkActionTest() );
		ret->AddItem( 'e', action_test::CallbackActionTest() );
		ret->AddItem( 'r', action_test::AnimationRequestActionTest() );


		ret->AddSplit();


		ret->AddMenu<R2bixMenu>( 27 );
	}

	return ret;
}