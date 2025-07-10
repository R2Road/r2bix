#include "menu_node.h"

#include "r2tm/r2tm_MenuProcessor.h"

#include "test_node.h"
#include "test_node___child.h"

#include "../menu_r2bix.h"

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
		mp->AddItem( '1', test_node::Basic() );
		mp->AddItem( '2', test_node___child::Child_Count() );
		mp->AddItem( '3', test_node___child::Child_Sequence() );



		mp->AddLineFeed();



		mp->AddItem( 'w', test_node::LabelS() );
		mp->AddItem( 'e', test_node::LabelM() );
		mp->AddItem( 'r', test_node::Sprite() );
		mp->AddItem( 't', test_node::SpriteAnimation() );
		mp->AddItem( 'y', test_node::CustomeTexture() );



		mp->AddLineFeed();



		mp->AddItem( 'a', test_node::UIPannel_ComponentCheck() );
		mp->AddItem( 's', test_node::UIPannel_CursorResponse() );
		mp->AddItem( 'd', test_node::UIButton() );
		mp->AddItem( 'f', test_node::UIButton_CursorResponse() );
		mp->AddItem( 'g', test_node::UISimpleButton_CursorResponse() );



		mp->AddLineFeed();



		mp->AddItem( 'z', test_node::Pivot() );
		mp->AddItem( 'x', test_node::Rect() );
		mp->AddItem( 'c', test_node::HollowRect() );



		mp->AddSplit();



		mp->AddMenu( 27, Menu_R2bix() );
	};
}