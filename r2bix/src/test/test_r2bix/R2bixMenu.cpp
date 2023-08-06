#include "R2bixMenu.h"

#include "r2tm/r2tm_Director.h"

#include "menu/ActionMenu.h"
#include "menu/CameraMenu.h"
#include "menu/ColorMenu.h"
#include "menu/ComponentMenu.h"
#include "menu/DirectorMenu.h"
#include "menu/GeometryMenu.h"
#include "menu/InputMenu.h"
#include "menu/NodeMenu.h"
#include "menu/TextureMenu.h"

#include "item/render_test.h"

#include "item/visible_resource_research.h"

#include "DevelopmentMenu.h"

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
	return []( r2tm::MenuProcessor* ret )
	{
		ret->AddMenu( '1', DirectorMenu() );
		ret->AddMenu( '2', InputMenu() );
		ret->AddMenu( '3', ColorMenu() );



		ret->AddLineFeed();
		ret->AddLineFeed();



		ret->AddMenu( 'q', TextureMenu() );
		ret->AddMenu( 'w', CameraMenu() );
		ret->AddItem( 'e', render_test::Basic() );
		ret->AddMenu( 'r', ComponentMenu() );
		ret->AddMenu( 't', ActionMenu() );
		ret->AddMenu( 'y', NodeMenu() );



		ret->AddLineFeed();
		ret->AddLineFeed();



		ret->AddMenu( 'a', GeometryMenu() );



		ret->AddSplit();



		ret->AddItem( 'z', visible_resource_research::DrawWithPosition() );



		ret->AddSplit();



		ret->AddMenu( 27, DevelopmentMenu() );
	};
}