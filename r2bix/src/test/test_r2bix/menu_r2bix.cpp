#include "menu_r2bix.h"

#include "r2tm/r2tm_MenuProcessor.h"

#include "action/menu_action.h"
#include "camera/menu_camera.h"
#include "color/menu_color.h"
#include "component/menu_component.h"
#include "director/menu_director.h"
#include "input/menu_input.h"
#include "geometry/menu_geometry.h"
#include "node/menu_node.h"
#include "ui/menu_ui.h"
#include "texture/menu_texture.h"

#include "variable/test_render.h"
#include "variable/research_visible_resource.h"

#include "menu_dev.h"

r2tm::TitleFunctionT Menu_R2bix::GetTitleFunction() const
{
	return []()->const char*
	{
		return "R2bix";
	};
}
r2tm::DescriptionFunctionT Menu_R2bix::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return
					"### 현재 작업 ###"
			"\n"
			"\n"	"+ " "System"
			"\n"	"\t"	"> "	"Director"
			"\n"	"\t"	"\t"	"[~] " "Add : Root Node"
		;
	};
}
r2tm::WriteFunctionT Menu_R2bix::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddMenu( '1', DirectorMenu() );
		mp->AddMenu( '2', Menu_Input() );
		mp->AddMenu( '3', Menu_Color() );



		mp->AddLineFeed();
		mp->AddLineFeed();



		mp->AddMenu( 'q', Menu_Texture() );
		mp->AddMenu( 'w', Menu_Camera() );
		mp->AddItem( 'e', test_render::Basic() );
		mp->AddMenu( 'r', Menu_Component() );
		mp->AddMenu( 't', Menu_Action() );
		mp->AddMenu( 'y', Menu_Node() );



		mp->AddLineFeed();
		mp->AddLineFeed();



		mp->AddMenu( 'a', GeometryMenu() );
		mp->AddMenu( 's', UIMenu() );



		mp->AddSplit();



		mp->AddItem( 'z', research_visible_resource::DrawWithPosition() );



		mp->AddSplit();



		mp->AddMenu( 27, Menu_Dev() );
	};
}