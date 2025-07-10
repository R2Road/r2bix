#include "menu_node.h"

#include "r2tm/r2tm_MenuProcessor.h"

#include "test_node.h"

#include "../R2bixMenu.h"

r2tm::TitleFunctionT Menu_Node::GetTitleFunction() const
{
	return []()->const char*
	{
		return "Node";
	};
}
r2tm::DescriptionFunctionT Menu_Node::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}
r2tm::WriteFunctionT Menu_Node::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* mp )
	{
		mp->AddItem( '1', node_test::Basic() );
		mp->AddItem( '2', node_test::Child_Count() );
		mp->AddItem( '3', node_test::Child_Sequence() );



		mp->AddLineFeed();



		mp->AddItem( 'w', node_test::LabelS() );
		mp->AddItem( 'e', node_test::LabelM() );
		mp->AddItem( 'r', node_test::Sprite() );
		mp->AddItem( 't', node_test::SpriteAnimation() );
		mp->AddItem( 'y', node_test::CustomeTexture() );



		mp->AddLineFeed();



		mp->AddItem( 'a', node_test::UIPannel_ComponentCheck() );
		mp->AddItem( 's', node_test::UIPannel_CursorResponse() );
		mp->AddItem( 'd', node_test::UIButton() );
		mp->AddItem( 'f', node_test::UIButton_CursorResponse() );
		mp->AddItem( 'g', node_test::UISimpleButton_CursorResponse() );



		mp->AddLineFeed();



		mp->AddItem( 'z', node_test::Pivot() );
		mp->AddItem( 'x', node_test::Rect() );
		mp->AddItem( 'c', node_test::HollowRect() );



		mp->AddSplit();



		mp->AddMenu( 27, R2bixMenu() );
	};
}