#include "UIMenu.h"

#include "r2tm/r2tm_Director.h"

#include "r2bix/r2bix_Director.h"
#include "r2bix/r2bix_component_CustomTextureComponent.h"
#include "r2bix/r2bix_component_TextureRenderComponent.h"
#include "r2bix/r2bix_component_UIPannelComponent.h"
#include "r2bix/r2bix_node_CustomTextureNode.h"
#include "r2bix/r2bix_node_UIPannelNode.h"


#include "test/test_r2bix/R2bixMenu.h"

r2tm::TitleFunctionT UIMenu::GetTitleFunction() const
{
	return []()->const char*
	{
		return "UI";
	};
}
r2tm::DescriptionFunctionT UIMenu::GetDescriptionFunction() const
{
	return []()->const char*
	{
		return "";
	};
}
r2tm::WriteFunctionT UIMenu::GetWriteFunction() const
{
	return []( r2tm::MenuProcessor* ret )
	{
			ret->AddItem(
				32
				, []()->const char* { return "UI Test Scene"; }
				, []()->r2tm::eDoLeaveAction
				{
					r2bix::Director director( { 50, 50, r2bix_director::Config::eScheduleType::Sleep, 30, 60, 2, 1 } );

					//
					// Scene
					//
					r2bix_node::SceneNode* scene;
					{
						auto temp = r2bix_node::SceneNode::Create( director );
						scene = temp.get();

						director.Setup( std::move( temp ) );
					}

					//
					// Background
					//
					{
						auto node = scene->AddChild<r2bix_node::CustomTextureNode>();
						node->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->Reset( 50, 50, ' ', r2bix::ColorValue( r2bix::eBackgroundColor::BG_Gray ) );
						node->GetComponent<r2bix_component::TextureRenderComponent>()->SetPivotPoint( 0.f, 0.f );
					}

					//
					// Pannel 1
					//
					{
						auto node = scene->AddChild<r2bix_node::UIPannelNode>();
						node->GetComponent<r2bix_component::UIPannelComponent>()->SetSize( 10, 5, '1' );
						node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 10, 10 );
					}

					//
					// Pannel 2
					//
					{
						auto node = scene->AddChild<r2bix_node::UIPannelNode>();
						node->GetComponent<r2bix_component::UIPannelComponent>()->SetSize( 10, 5, '2' );
						node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 13, 13 );
					}

					//
					// Process
					//
					director.Run();

					//
					// Terminate
					//
					director.Terminate();

					return r2tm::eDoLeaveAction::None;
				}
			);



		ret->AddSplit();



		ret->AddMenu( 27, R2bixMenu() );
	};
}