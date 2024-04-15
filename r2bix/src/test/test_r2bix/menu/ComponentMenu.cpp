#include "ComponentMenu.h"

#include "r2tm/r2tm_Director.h"
#include "r2tm/r2tm_ostream.h"

#include "test/test_r2bix/R2bixMenu.h"

#include "test/test_r2bix/item/component_test.h"

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
	return []( r2tm::MenuProcessor* ret )
	{
		ret->AddItem( '1', component_test::ComponentID() );
		ret->AddItem( '2', component_test::Component_Add_Get() );

		ret->AddLineFeed();
		ret->AddLineFeed();

		ret->AddItem( 'q', component_test::TextureRender_1() );
		ret->AddItem( 'w', component_test::TextureRender_2() );
		ret->AddItem( 'e', component_test::TextureRender_3() );

		ret->AddLineFeed();

		ret->AddItem( 'r', component_test::CustomTexture() );

		ret->AddLineFeed();

		ret->AddItem( 't', component_test::LabelS() );
		ret->AddItem( 'y', component_test::LabelM() );

		ret->AddLineFeed();
		ret->AddLineFeed();

		ret->AddItem( 'a', component_test::TextureFrameRender_1() );
		ret->AddItem( 's', component_test::TextureFrameRender_2() );

		ret->AddLineFeed();

		ret->AddItem( 'd', component_test::TextureFrameAnimation_1() );
		ret->AddItem( 'f', component_test::TextureFrameAnimation_2() );

		ret->AddLineFeed();
		ret->AddLineFeed();

		ret->AddItem( 'g', component_test::ActionProcess() );

		ret->AddLineFeed();
		ret->AddLineFeed();

		ret->AddItem( 'z', component_test::UIControl() );
		ret->AddItem( 'x', component_test::UIPannel() );
		ret->AddItem( 'c', component_test::UIPannel_InputListener_Regist() );
		ret->AddItem( 'v', component_test::UIPannel_Cursor_Response() );
		ret->AddItem( 'b', component_test::UIButton() );




		ret->AddSplit();


		ret->AddMenu( 27, R2bixMenu() );
	};
}