#include "pch.h"
#include "TestRootMenu.h"

#include "r2cm/r2cm_Director.h"
#include "r2cm/r2cm_eTestEndAction.h"

#include "test/test_r2bix/menu/ActionMenu.h"
#include "test/test_r2bix/menu/CameraMenu.h"
#include "test/test_r2bix/menu/InputMenu.h"
#include "test/test_r2bix/menu/ComponentMenu.h"
#include "test/test_r2bix/menu/NodeMenu.h"
#include "test/test_r2bix/menu/TextureMenu.h"

#include "test/test_r2bix/item/console_screen_buffer_test.h"
#include "test/test_r2bix/item/console_screen_buffer_manager_test.h"
#include "test/test_r2bix/item/rect_test.h"
#include "test/test_r2bix/item/render_test.h"

#include "test/test_r2bix/item/visible_resource_research.h"

#include "test/TestMainMenu.h"

r2cm::MenuUp TestR2bixRootMenu::Create( r2cm::Director& director )
{
	r2cm::MenuUp ret( new ( std::nothrow ) r2cm::Menu(
		director
		, GetTitle(),
				"> Inprogress : Action"
		"\n"	"> ..."
	) );

	{
		ret->AddItem( '1', console_screen_buffer_test::Basic::GetInstance() );
		ret->AddItem( '2', console_screen_buffer_manager_test::Basic::GetInstance() );
		ret->AddItem(
			'3'
			, []()->const char* { return InputMenu::GetTitle(); }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( InputMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);
		ret->AddItem( '4', rect_test::Basic::GetInstance() );



		ret->AddLineFeed();
		ret->AddLineFeed();



		ret->AddItem(
			'q'
			, []()->const char* { return TextureMenu::GetTitle(); }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( TextureMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);
		ret->AddItem(
			'w'
			, []()->const char* { return CameraMenu::GetTitle(); }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( CameraMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);
		ret->AddItem( 'e', render_test::Basic::GetInstance() );
		ret->AddItem(
			'r'
			, []()->const char* { return ComponentMenu::GetTitle(); }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( ComponentMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);
		ret->AddItem(
			't'
			, []()->const char* { return ActionMenu::GetTitle(); }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( ActionMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);
		ret->AddItem(
			'y'
			, []()->const char* { return NodeMenu::GetTitle(); }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( NodeMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);


		ret->AddSplit();


		ret->AddItem( 'z', visible_resource_research::DrawWithPosition::GetInstance() );


		ret->AddSplit();


		ret->AddItem(
			27
			, []()->const char* { return TestMainMenu::GetTitle(); }
			, [&director]()->r2cm::eTestEndAction
			{
				director.Setup( TestMainMenu::Create( director ) );
				return r2cm::eTestEndAction::None;
			}
		);
	}

	return ret;
}