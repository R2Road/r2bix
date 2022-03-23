#include "pch.h"
#include "InputMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "test/test_r2bix/TestR2bixRootMenu.h"

#include "test/test_r2bix/item/key_test.h"
#include "test/test_r2bix/item/window_input_test.h"

r2cm::MenuUp InputMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
	) );

	{
		ret->AddItem( '1', key_test::Basic::GetInstance() );
		ret->AddItem( '2', window_input_test::TestKeyboardInputCollector::GetInstance() );


		ret->AddSplit();


		ret->AddItem(
			27
			, []()->const char* { return "Return To Root"; }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( TestR2bixRootMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);
	}

	return ret;
}