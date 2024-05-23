#include "tool_texture_editor_EditorScene.h"

#include "r2bix_Director.h"

#include "r2bix_component_HollowRectComponent.h"
#include "r2bix_component_InputKeyboardComponent.h"

#include "r2bix_node_HollowRectNode.h"

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
			//
			//
			auto editor_component = ret->AddComponent<tool_texture_editor::EditorComponent>();
			editor_component->Activate();
		}

		return ret;
	}
}