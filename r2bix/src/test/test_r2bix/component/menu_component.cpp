#include "menu_component.h"

#include "r2tm/r2tm_MenuProcessor.h"

#include "../R2bixMenu.h"

#include "test_component.h"

r2tm::TitleFunctionT ComponentMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "Component";
	};
}
r2tm::DescriptionFunctionT ComponentMenu::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}
r2tm::WriteFunctionT ComponentMenu::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddItem( '1', component_test::ComponentID() );
		mp->AddItem( '2', component_test::Component_Add_Get() );
		mp->AddItem( '3', component_test::Transform_Basic() );
		mp->AddItem( '4', component_test::Transform_PivotPoint() );


		mp->AddLineFeed();
		mp->AddLineFeed();


		mp->AddItem( 'q', component_test::TextureRender_1() );
		mp->AddItem( 'w', component_test::TextureRender_2() );
		mp->AddItem( 'e', component_test::TextureRender_3() );

		mp->AddLineFeed();

		mp->AddItem( 'r', component_test::CustomTexture() );

		mp->AddLineFeed();

		mp->AddItem( 't', component_test::LabelS() );
		mp->AddItem( 'y', component_test::LabelM() );



		mp->AddLineFeed();
		mp->AddLineFeed();



		mp->AddItem( 'a', component_test::TextureFrameRender_1() );
		mp->AddItem( 's', component_test::TextureFrameRender_2() );

		mp->AddLineFeed();

		mp->AddItem( 'd', component_test::TextureFrameAnimation_1() );
		mp->AddItem( 'f', component_test::TextureFrameAnimation_2() );



		mp->AddLineFeed();
		mp->AddLineFeed();



		mp->AddItem( 'g', component_test::ActionProcess() );



		mp->AddLineFeed();
		mp->AddLineFeed();



		mp->AddItem( 'z', component_test::UIControl() );
		mp->AddItem( 'x', component_test::UIPannel() );
		mp->AddItem( 'c', component_test::UIPannel_InputListener_Regist() );
		mp->AddItem( 'v', component_test::UIPannel_Cursor_Response() );
		mp->AddItem( 'b', component_test::UIButton() );



		mp->AddSplit();



		mp->AddMenu( 27, R2bixMenu() );
	};
}