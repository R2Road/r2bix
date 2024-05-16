#include "tool_texture_editor_EntryScene.h"

#include "r2bix_Director.h"
#include "r2bix_component_InputKeyboardComponent.h"
#include "r2bix_component_LabelSComponent.h"
#include "r2bix_component_TextureRenderComponent.h"
#include "r2bix_node_LabelSNode.h"
#include "r2bix_utility_InputUtil.h"

namespace tool_texture_editor
{
	EntryScene::EntryScene( r2bix::Director& director ) : r2bix_node::Node( director )
	{}

	r2bix_node::NodeUp EntryScene::Create( r2bix::Director& director )
	{
		r2bix_node::NodeUp ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{
			//
			//
			//
			{
				auto node = ret->AddChild<r2bix_node::LabelSNode>();
				node->GetComponent<r2bix_component::LabelSComponent>()->SetString( EntryScene::GetTitle() );
				node->GetComponent<r2bix_component::TransformComponent>()->SetPosition(
					  director.GetScreenSize().GetWidth() * 0.5f
					, director.GetScreenSize().GetHeight() * 0.5f
				);
			}

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
							r2bix_utility::ClearCInputBuffer();
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