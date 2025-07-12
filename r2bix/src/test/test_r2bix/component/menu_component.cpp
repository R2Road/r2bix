#include "menu_component.h"

#include "r2tm/r2tm_MenuProcessor.h"

#include "../menu_r2bix.h"

#include "test_component.h"
#include "test_component___static_mesh.h"

r2tm::TitleFunctionT Menu_Component::GetTitleFunction() const
{
	return []()->const char*
	{
		return "Component";
	};
}
r2tm::DescriptionFunctionT Menu_Component::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}
r2tm::WriteFunctionT Menu_Component::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddItem( '1', test_component::ComponentID() );
		mp->AddItem( '2', test_component::Component_Add_Get() );
		mp->AddItem( '3', test_component::Transform_Basic() );
		mp->AddItem( '4', test_component::Transform_PivotPoint() );


		mp->AddLineFeed();
		mp->AddLineFeed();


		mp->AddItem( 'q', test_component::TextureRender_1() );
		mp->AddItem( 'w', test_component::TextureRender_2() );
		mp->AddItem( 'e', test_component::TextureRender_3() );

		mp->AddLineFeed();

		mp->AddItem( 'r', test_component::CustomTexture() );

		mp->AddLineFeed();

		mp->AddItem( 't', test_component::LabelS() );
		mp->AddItem( 'y', test_component::LabelM() );



		mp->AddLineFeed();
		mp->AddLineFeed();



		mp->AddItem( 'a', test_component::TextureFrameRender_1() );
		mp->AddItem( 's', test_component::TextureFrameRender_2() );

		mp->AddLineFeed();

		mp->AddItem( 'd', test_component::TextureFrameAnimation_1() );
		mp->AddItem( 'f', test_component::TextureFrameAnimation_2() );



		mp->AddLineFeed();
		mp->AddLineFeed();



		mp->AddItem( 'g', test_component::ActionProcess() );



		mp->AddLineFeed();
		mp->AddLineFeed();



		mp->AddItem( 'z', test_component::UIControl() );
		mp->AddItem( 'x', test_component::UIPannel() );
		mp->AddItem( 'c', test_component::UIPannel_InputListener_Regist() );
		mp->AddItem( 'v', test_component::UIPannel_Cursor_Response() );
		mp->AddItem( 'b', test_component::UIButton() );



		mp->AddLineFeed();
		mp->AddLineFeed();



		mp->AddItem( 'n', test_component___static_mesh::Basic() );



		mp->AddSplit();



		mp->AddMenu( 27, Menu_R2bix() );
	};
}