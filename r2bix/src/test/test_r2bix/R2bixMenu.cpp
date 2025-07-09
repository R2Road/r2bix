#include "R2bixMenu.h"

#include "r2tm/r2tm_MenuProcessor.h"

#include "menu/ActionMenu.h"
#include "menu/CameraMenu.h"
#include "menu/ColorMenu.h"
#include "menu/ComponentMenu.h"
#include "director/menu_director.h"
#include "menu/GeometryMenu.h"
#include "menu/InputMenu.h"
#include "menu/NodeMenu.h"
#include "menu/TextureMenu.h"
#include "menu/UIMenu.h"

#include "item/render_test.h"

#include "item/visible_resource_research.h"

#include "menu_dev.h"

r2tm::TitleFunctionT R2bixMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "R2bix";
	};
}
r2tm::DescriptionFunctionT R2bixMenu::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return
					"> Inprogress : ..."
			"\n"	"> ...";
	};
}
r2tm::WriteFunctionT R2bixMenu::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddMenu( '1', DirectorMenu() );
		mp->AddMenu( '2', InputMenu() );
		mp->AddMenu( '3', ColorMenu() );



		mp->AddLineFeed();
		mp->AddLineFeed();



		mp->AddMenu( 'q', TextureMenu() );
		mp->AddMenu( 'w', CameraMenu() );
		mp->AddItem( 'e', render_test::Basic() );
		mp->AddMenu( 'r', ComponentMenu() );
		mp->AddMenu( 't', ActionMenu() );
		mp->AddMenu( 'y', NodeMenu() );



		mp->AddLineFeed();
		mp->AddLineFeed();



		mp->AddMenu( 'a', GeometryMenu() );
		mp->AddMenu( 's', UIMenu() );



		mp->AddSplit();



		mp->AddItem( 'z', visible_resource_research::DrawWithPosition() );



		mp->AddSplit();



		mp->AddMenu( 27, Menu_Dev() );
	};
}