#include "p2048_CompanyScene.h"

#include "r2_TimerFloat.h"

#include "r2bix_Director.h"

#include "r2bix_component_InputKeyboardComponent.h"
#include "r2bix_component_LabelSComponent.h"
#include "r2bix_component_TextureFrameAnimationComponent.h"
#include "r2bix_component_TextureFrameRenderComponent.h"
#include "r2bix_component_TextureRenderComponent.h"
#include "r2bix_component_TransformComponent.h"

#include "r2bix_node_LabelSNode.h"
#include "r2bix_node_SpriteAnimationNode.h"

#include "p2048_TitleScene.h"
#include "p2048table_TextureFrameAnimationTable.h"
#include "p2048table_TextureTable.h"


namespace p2048
{
	class CompanySceneComponent : public r2bix_component::Component<CompanySceneComponent>
	{
	public:
		CompanySceneComponent( r2bix::Director& director, r2bix_node::Node& owner_node ) : r2bix_component::Component<CompanySceneComponent>( director, owner_node )
			, mChangeSceneTimer( 2.f, true )
		{}


		//
		// Override
		//
		void updateProcess( const float delta_time ) override
		{
			if( !mChangeSceneTimer.Update( delta_time ) )
			{
				GetOwnerNode().GetDirector().Setup( p2048::TitleScene::Create( GetOwnerNode().GetDirector() ) );
			}
		}


	private:
		r2::TimerFloat mChangeSceneTimer;
	};



	r2bix_node::NodeUp CompanyScene::Create( r2bix::Director& director )
	{
		r2bix_node::NodeUp ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{
			//
			// Company Name
			//
			{
				auto label_node = ret->AddChild<r2bix_node::LabelSNode>();

				label_node->GetComponent<r2bix_component::LabelSComponent>()->SetString( "R2Road Studio" );

				label_node->mTransformComponent->SetPosition(
					  director.GetScreenSize().GetWidth() * 0.5f
					, director.GetScreenSize().GetHeight() * 0.62f
				);
			}

			//
			// Logo
			//
			{
				auto sprite_animation_node = ret->AddChild<r2bix_node::SpriteAnimationNode>( 1 );

				sprite_animation_node->GetComponent<r2bix_component::TextureFrameAnimationComponent>()->LoadAnimation(
					p2048table::TextureFrameAnimationTable::GetInstance().Get( 1 )
				);
				sprite_animation_node->GetComponent<r2bix_component::TextureFrameAnimationComponent>()->RunAnimation_Repeat( r2bix_animation::eIndex::Run_1 );

				sprite_animation_node->mTransformComponent->SetPosition(
					  director.GetScreenSize().GetWidth() * 0.5f
					, director.GetScreenSize().GetHeight() * 0.42f
				);
			}

			//
			//
			//
			{
				auto component = ret->AddComponent<CompanySceneComponent>();
				component->Activate();
			}

			//
			// Input
			//
			{
				auto component = ret->AddComponent<r2bix_component::InputKeyboardComponent>();

				//
				// Exit
				//
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

				//
				// Move 2 Title Scene
				//
				component->SetCallback(
					  r2bix_input::eKeyCode::VK_SPACE
					, [&director]( r2bix_input::eKeyStatus s )->bool
					{
						if( r2bix_input::eKeyStatus::Push == s )
						{
							director.Setup( p2048::TitleScene::Create( director ) );
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