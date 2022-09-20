#include "R2bixMenu.h"

#include "r2cm/r2cm_ostream.h"
#include "r2cm/r2cm_Director.h"

#include "menu/ActionMenu.h"
#include "menu/CameraMenu.h"
#include "menu/ColorMenu.h"
#include "menu/ComponentMenu.h"
#include "menu/InputMenu.h"
#include "menu/NodeMenu.h"
#include "menu/TextureMenu.h"
#include "menu/UtilityMenu.h"

#include "item/console_screen_buffer_test.h"
#include "item/console_screen_buffer_manager_test.h"
#include "item/render_test.h"

#include "item/visible_resource_research.h"

#include "DevelopmentMenu.h"

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
		ret->AddMenu<ColorMenu>( '4' );
		ret->AddMenu<UtilityMenu>( '5' );



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



		ret->AddMenu<DevelopmentMenu>( 27 );
	}

	return ret;
}