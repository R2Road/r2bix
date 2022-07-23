#include "R2bixMenu.h"

#include "r2cm/r2cm_ostream.h"
#include "r2cm/r2cm_Director.h"

#include "test/test_r2bix/menu/ActionMenu.h"
#include "test/test_r2bix/menu/CameraMenu.h"
#include "test/test_r2bix/menu/ColorMenu.h"
#include "test/test_r2bix/menu/ComponentMenu.h"
#include "test/test_r2bix/menu/InputMenu.h"
#include "test/test_r2bix/menu/NodeMenu.h"
#include "test/test_r2bix/menu/TextureMenu.h"

#include "test/test_r2bix/item/console_screen_buffer_test.h"
#include "test/test_r2bix/item/console_screen_buffer_manager_test.h"
#include "test/test_r2bix/item/rect_test.h"
#include "test/test_r2bix/item/render_test.h"
#include "test/test_r2bix/item/utility_test.h"

#include "test/test_r2bix/item/visible_resource_research.h"

#include "test/TestMenu.h"

r2cm::MenuUp R2bixMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle(),
				"> Inprogress : ..."
		"\n"	"> ..."
	) );

	{
		ret->AddItem( '1', console_screen_buffer_test::Basic::GetInstance() );
		ret->AddItem( '2', console_screen_buffer_manager_test::Basic::GetInstance() );
		ret->AddMenu<InputMenu>( '3' );
		ret->AddItem( '4', rect_test::Basic::GetInstance() );
		ret->AddMenu<ColorMenu>( '5' );
		ret->AddItem( '6', utility_test::StringSize::GetInstance() );
		ret->AddItem( '7', utility_test::StringDecomposition::GetInstance() );



		ret->AddLineFeed();
		ret->AddLineFeed();



		ret->AddMenu<TextureMenu>( 'q' );
		ret->AddMenu<CameraMenu>( 'w' );
		ret->AddItem( 'e', render_test::Basic::GetInstance() );
		ret->AddMenu<ComponentMenu>( 'r' );
		ret->AddMenu<ActionMenu>( 't' );
		ret->AddMenu<NodeMenu>( 'y' );



		ret->AddSplit();



		ret->AddItem( 'z', visible_resource_research::DrawWithPosition::GetInstance() );



		ret->AddSplit();



		ret->AddMenu<TestMenu>( 27 );
	}

	return ret;
}