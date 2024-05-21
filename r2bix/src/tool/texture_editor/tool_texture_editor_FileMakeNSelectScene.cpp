#include "tool_texture_editor_FileMakeNSelectScene.h"

#include "r2bix_Director.h"

#include "r2bix_component_HollowRectComponent.h"
#include "r2bix_component_InputKeyboardComponent.h"
#include "r2bix_component_RectComponent.h"
#include "r2bix_component_TransformComponent.h"
#include "r2bix_component_UIControlComponent.h"
#include "r2bix_component_UISimpleButtonComponent.h"

#include "r2bix_node_HollowRectNode.h"
#include "r2bix_node_RectNode.h"
#include "r2bix_node_UIPannelNode.h"
#include "r2bix_node_UISimpleButtonNode.h"

namespace tool_texture_editor
{
	r2bix_node::NodeUp FileMakeNSelectScene::Create( r2bix::Director& director )
	{
		r2bix_node::NodeUp ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{
			//
			// Background
			//
			{
				auto node = ret->AddChild<r2bix_node::HollowRectNode>();
				node->GetComponent<r2bix_component::HollowRectComponent>()->Set(
					  r2::Vector2{ 0.f, 0.f }
					, director.GetScreenSize().GetWidth()
					, director.GetScreenSize().GetHeight()
					, '#'
					, ' '
				);
			}


			//
			//
			//
			{
				//
				// Pannel
				//
				auto pn_node = ret->AddChild<r2bix_node::UIPannelNode>();
				{
					pn_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 28, 12 );
					pn_node->GetComponent<r2bix_component::UIControlComponent>()->SetSize( 50, 15 );
					pn_node->GetComponent<r2bix_component::UIControlComponent>()->SetPivotPoint( 0.f, 0.f );
					{
						auto rect_node = pn_node->AddChild<r2bix_node::RectNode>();
						rect_node->GetComponent<r2bix_component::RectComponent>()->Set(
							r2::Vector2{ 0.f, 0.f }
							, pn_node->GetComponent<r2bix_component::UIControlComponent>()->GetWidth()
							, pn_node->GetComponent<r2bix_component::UIControlComponent>()->GetHeight()
							, "Pannel "
						);
					}
				}

				//
				// Button
				//
				{
					auto button_node = pn_node->AddChild<r2bix_node::UISimpleButtonNode>();
					button_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 5, 3 );
					button_node->GetComponent<r2bix_component::UISimpleButtonComponent>()->Set( 0.f, 0.f, 40, 3 );
				}

				{
					auto button_node = pn_node->AddChild<r2bix_node::UISimpleButtonNode>();
					button_node->GetComponent<r2bix_component::TransformComponent>()->SetPosition( 5, 9 );
					button_node->GetComponent<r2bix_component::UISimpleButtonComponent>()->Set( 0.f, 0.f, 40, 3 );
				}
			}


			// 
			//
			// Exit
			//
			{
				auto component = ret->AddComponent<r2bix_component::InputKeyboardComponent>();
				component->SetCallback(
					  r2bix_input::eKeyCode::VK_ESCAPE
					, [&director]( r2bix_input::eKeyStatus s )->bool
					{
						if( r2bix_input::eKeyStatus::Push == s )
						{
							director.RequestAbort();
							return true;
						}

						return false;
					}
				);
				component->Activate();
			}
		}

		return ret;
	}
}