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

		ret->AddItem( 'q', component_test::TextureRenderComponentTest_1() );
		ret->AddItem( 'w', component_test::TextureRenderComponentTest_2() );
		ret->AddItem( 'e', component_test::TextureRenderComponentTest_3() );

		ret->AddLineFeed();

		ret->AddItem( 'r', component_test::CustomTextureComponentTest() );

		ret->AddLineFeed();

		ret->AddItem( 't', component_test::LabelSComponentTest() );
		ret->AddItem( 'y', component_test::LabelMComponentTest() );

		ret->AddLineFeed();
		ret->AddLineFeed();

		ret->AddItem( 'a', component_test::TextureFrameRenderComponentTest_1() );
		ret->AddItem( 's', component_test::TextureFrameRenderComponentTest_2() );

		ret->AddLineFeed();

		ret->AddItem( 'd', component_test::TextureFrameAnimationComponentTest_1() );
		ret->AddItem( 'f', component_test::TextureFrameAnimationComponentTest_2() );

		ret->AddLineFeed();
		ret->AddLineFeed();

		ret->AddItem( 'g', component_test::ActionProcessComponentTest() );


		ret->AddSplit();


		ret->AddMenu( 27, R2bixMenu() );
	};
}