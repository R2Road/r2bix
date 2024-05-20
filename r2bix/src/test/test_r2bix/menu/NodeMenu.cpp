#include "NodeMenu.h"

#include "r2tm/r2tm_Director.h"

#include "test/test_r2bix/item/node_test.h"

#include "test/test_r2bix/R2bixMenu.h"

r2tm::TitleFunctionT NodeMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "Node";
	};
}
r2tm::DescriptionFunctionT NodeMenu::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}
r2tm::WriteFunctionT NodeMenu::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* ret )
	{
		ret->AddItem( '1', node_test::Basic() );
		ret->AddItem( '2', node_test::Child_Count() );
		ret->AddItem( '3', node_test::Child_Sequence() );



		ret->AddLineFeed();



		ret->AddItem( 'w', node_test::LabelS() );
		ret->AddItem( 'e', node_test::LabelM() );
		ret->AddItem( 'r', node_test::Sprite() );
		ret->AddItem( 't', node_test::SpriteAnimation() );
		ret->AddItem( 'y', node_test::CustomeTexture() );



		ret->AddLineFeed();



		ret->AddItem( 'a', node_test::UIPannel_ComponentCheck() );
		ret->AddItem( 's', node_test::UIPannel_CursorResponse() );
		ret->AddItem( 'd', node_test::UIButton() );
		ret->AddItem( 'f', node_test::UIButton_CursorResponse() );
		ret->AddItem( 'g', node_test::UISimpleButton_CursorResponse() );



		ret->AddLineFeed();



		ret->AddItem( 'z', node_test::Pivot() );
		ret->AddItem( 'x', node_test::Rect() );



		ret->AddSplit();



		ret->AddMenu( 27, R2bixMenu() );
	};
}