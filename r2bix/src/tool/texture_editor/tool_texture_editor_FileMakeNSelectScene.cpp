#include "tool_texture_editor_FileMakeNSelectScene.h"

#include "r2bix_Director.h"

#include "r2bix_component_InputKeyboardComponent.h"

#include "r2bix_node_LabelSNode.h"

#include "r2bix_utility_InputUtil.h"

namespace tool_texture_editor
{
	r2bix_node::NodeUp FileMakeNSelectScene::Create( r2bix::Director& director )
	{
		r2bix_node::NodeUp ret( r2bix_node::Node::Create( director ) );
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