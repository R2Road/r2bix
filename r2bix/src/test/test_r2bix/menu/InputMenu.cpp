#include "InputMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_ostream.h"

#include "test/test_r2bix/item/key_test.h"
#include "test/test_r2bix/item/window_input_test.h"

#include "test/test_r2bix/R2bixMenu.h"

r2cm::MenuUp InputMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle()
	) );

	{
		ret->AddItem( '1', key_test::Basic::GetInstance() );


		ret->AddLineFeed();


		ret->AddItem( 'q', window_input_test::KeyStatus::GetInstance() );
		ret->AddItem( 'w', window_input_test::TestKeyboardInputCollector::GetInstance() );


		ret->AddSplit();


		ret->AddMenu<R2bixMenu>( 27 );
	}

	return ret;
}