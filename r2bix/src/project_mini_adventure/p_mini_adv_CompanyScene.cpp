#include "p_mini_adv_CompanyScene.h"

#include "r2bix_Director.h"

#include "r2bix_component_InputKeyboardComponent.h"
#include "r2bix_component_LabelSComponent.h"

#include "r2bix_node_LabelSNode.h"

#include "p_mini_adv_VersionInfo.h"

namespace p_mini_adv
{
	r2bix_node::NodeUp CompanyScene::Create( r2bix::Director& director )
	{
		r2bix_node::NodeUp ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{
			{
				auto node = ret->AddChild<r2bix_node::LabelSNode>();
				node->GetComponent<r2bix_component::LabelSComponent>()->SetString( VersionInfo.String4Summury );

				node->mTransformComponent->SetPosition(
					  director.GetScreenSize().GetWidth() * 0.5f
					, director.GetScreenSize().GetHeight() * 0.3f
				);
			}

			{
				auto node = ret->AddChild<r2bix_node::LabelSNode>();
				node->GetComponent<r2bix_component::LabelSComponent>()->SetString( VersionInfo.String4Road2Version_0_0_1 );

				node->mTransformComponent->SetPosition(
					  director.GetScreenSize().GetWidth() * 0.5f
					, director.GetScreenSize().GetHeight() * 0.6f
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