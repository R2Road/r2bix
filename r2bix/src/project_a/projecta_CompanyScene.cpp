#include "projecta_CompanyScene.h"

#include "r2bix_Director.h"
#include "r2bix_component_InputKeyboardComponent.h"
#include "r2bix_component_LabelSComponent.h"
#include "r2bix_component_TextureRenderComponent.h"
#include "r2bix_node_LabelSNode.h"
#include "r2bix_utility_InputUtil.h"

namespace projecta
{
	CompanyScene::CompanyScene( r2bix::Director& director ) : r2bix_node::Node( director )
	{}

	r2bix_node::NodeUp CompanyScene::Create( r2bix::Director& director )
	{
		r2bix_node::NodeUp ret( new ( std::nothrow ) CompanyScene( director ) );
		if( !ret || !ret->Init() )
		{
			ret.reset();
		}

		return ret;
	}

	bool CompanyScene::Init()
	{
		if( !r2bix_node::Node::Init() )
		{
			return false;
		}

		//
		//
		//
		{
			auto node = AddChild<r2bix_node::LabelSNode>();
			node->GetComponent<r2bix_component::LabelSComponent>()->SetString( CompanyScene::GetTitle() );
			node->GetComponent<r2bix_component::TransformComponent>()->SetPosition(
				  mDirector.GetScreenBufferSize().GetWidth() * 0.5f
				, mDirector.GetScreenBufferSize().GetHeight() * 0.5f
			);
		}

		//
		// Exit
		//
		{
			auto component = AddComponent<r2bix_component::InputKeyboardComponent>();
			component->SetCallback(
					r2bix_input::eKeyCode::VK_ESCAPE
				,	[this]( r2bix_input::eKeyStatus s )->bool
				{
					if( r2bix_input::eKeyStatus::Release == s )
					{
						r2bix_utility::ClearCInputBuffer();
						mDirector.RequestAbort();
						return true;
					}

					return false;
				}
			);
			component->Activate();
		}

		return true;
	}
}