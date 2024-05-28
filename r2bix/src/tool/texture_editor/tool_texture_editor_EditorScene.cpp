#include "tool_texture_editor_EditorScene.h"

#include "r2bix_Director.h"

#include "r2bix_component_HollowRectComponent.h"
#include "r2bix_component_InputKeyboardComponent.h"
#include "r2bix_component_LabelSComponent.h"
#include "r2bix_component_RectComponent.h"
#include "r2bix_component_UIPannelComponent.h"

#include "r2bix_node_HollowRectNode.h"
#include "r2bix_node_LabelSNode.h"
#include "r2bix_node_RectNode.h"
#include "r2bix_node_UIPannelNode.h"

#include "tool_texture_editor_EditorComponent.h"

#include "tool_texture_editor_FileMakeNSelectScene.h"

namespace tool_texture_editor
{
	r2bix_node::NodeUp EditorScene::Create( r2bix::Director& director )
	{
		r2bix_node::NodeUp ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{

			//
			// Background
			//
			{
				auto node = ret->AddChild<r2bix_node::RectNode>();
				node->mTransformComponent->SetPivot( 0.f, 0.f );
				node->GetComponent<r2bix_component::RectComponent>()->Set(
					  director.GetScreenSize().GetWidth()
					, director.GetScreenSize().GetHeight()
					, ' '
					, r2bix::eBackgroundColor::BG_Gray
				);
			}
			//
			// Exit
			//
			{
				auto component = ret->AddComponent<r2bix_component::InputKeyboardComponent>();
				component->SetCallback(
					  r2bix_input::eKeyCode::VK_ESCAPE
					, [&director](r2bix_input::eKeyStatus s)->bool
					{
						if( r2bix_input::eKeyStatus::Push == s )
						{
							director.Setup( tool_texture_editor::FileMakeNSelectScene::Create( director ) );
							return true;
						}

						return false;
					}
				);
				component->Activate();
			}
			//
			// File Name View
			//
			{
				auto node = ret->AddChild<r2bix_node::LabelSNode>();
				node->SetName( "file_name_view" );
				node->GetComponent<r2bix_component::TransformComponent>()->SetPosition(
					  director.GetScreenSize().GetWidth()
					, director.GetScreenSize().GetHeight()
				);
				node->mTransformComponent->SetPivot( 1.f, 1.f );
			}
			//
			//
			//
			auto editor_component = ret->AddComponent<tool_texture_editor::EditorComponent>();
			editor_component->Activate();



			//
			// Canvas
			//
			{
				const uint32_t canvas_width = 80;
				const uint32_t canvas_height = 40;

				auto canvas_node = ret->AddChild<r2bix_node::UIPannelNode>();
				canvas_node->SetName( "canvas" );
				canvas_node->mTransformComponent->SetPosition(
					  ( director.GetScreenSize().GetWidth() * 0.5f ) - ( canvas_width * 0.5f )
					, ( director.GetScreenSize().GetHeight() * 0.5f ) - ( canvas_height * 0.5f )
				);
				canvas_node->mTransformComponent->SetPivot( 0.f, 0.f );
				canvas_node->GetComponent<r2bix_component::UIPannelComponent>()->SetSize( canvas_width, canvas_height );
				{
					auto texture_view_node = canvas_node->AddChild<r2bix_node::RectNode>();
					texture_view_node->SetName( "texture" );
					texture_view_node->mTransformComponent->SetPivot( 0.f, 0.f );
					texture_view_node->GetComponent<r2bix_component::RectComponent>()->Set( canvas_width, canvas_height, ' ', r2bix::eBackgroundColor::BG_Green );
				}

				//
				//
				//
				editor_component->SetCanvas( canvas_node );
			}
		}

		return ret;
	}
}