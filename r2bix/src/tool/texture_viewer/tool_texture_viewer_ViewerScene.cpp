#include "tool_texture_viewer_ViewerScene.h"

#include "r2bix_Director.h"

#include "r2bix_component_InputKeyboardComponent.h"
#include "r2bix_component_LabelSComponent.h"

#include "r2bix_node_LabelSNode.h"

namespace tool_texture_viewer
{
	r2bix_node::NodeUp ViewerScene::Create( r2bix::Director& director )
	{
		auto ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{
			//
			// Exit
			//
			{
				auto component = ret->AddComponent<r2bix_component::InputKeyboardComponent>();
				component->SetCallback(
					r2bix_input::eKeyCode::VK_ESCAPE
					, [&director]( r2bix_input::eKeyStatus s )->bool
					{
						if( r2bix_input::eKeyStatus::Release == s )
						{
							director.RequestAbort();
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
			{
				auto node = ret->AddChild<r2bix_node::LabelSNode>();
				node->GetComponent<r2bix_component::LabelSComponent>()->SetString( "Texture Viewer" );

				node->mTransformComponent->SetPosition(
					  director.GetScreenSize().GetWidth() * 0.5f
					, director.GetScreenSize().GetHeight() * 0.5f
				);
			}
		}

		return ret;
	}
}