#include "p2048_CompanyScene.h"

#include <cassert>
#include <conio.h>
#include <utility> // std::move

#include "r2bix_Director.h"
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
	CompanyScene::CompanyScene( r2bix::Director& director ) : r2bix_node::Node( director )
		, mChangeSceneTimer( 2.f, true )
	{}

	r2bix_node::NodeUp CompanyScene::Create( r2bix::Director& director )
	{
		r2bix_node::NodeUp ret( new ( std::nothrow ) CompanyScene( director ) );
		if( !ret->Init() )
		{
			assert( false );
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
		// Company Name
		//
		{
			auto label_node = AddChild<r2bix_node::LabelSNode>();

			label_node->GetComponent<r2bix_component::LabelSComponent>()->SetString( "R2Road Studio" );

			label_node->mTransformComponent->SetPosition(
				mDirector.GetScreenSize().GetWidth() * 0.5f
				, mDirector.GetScreenSize().GetHeight() * 0.62f
			);
		}

		//
		// Logo
		//
		{
			auto sprite_animation_node = AddChild<r2bix_node::SpriteAnimationNode>( 1 );

			sprite_animation_node->GetComponent<r2bix_component::TextureFrameAnimationComponent>()->LoadAnimation(
				p2048table::TextureFrameAnimationTable::GetInstance().Get( 1 )
			);
			sprite_animation_node->GetComponent<r2bix_component::TextureFrameAnimationComponent>()->RunAnimation_Repeat( r2bix_animation::eIndex::Run_1 );

			sprite_animation_node->mTransformComponent->SetPosition(
				mDirector.GetScreenSize().GetWidth() * 0.5f
				, mDirector.GetScreenSize().GetHeight() * 0.42f
			);
		}

		return true;
	}
	void CompanyScene::Update( const float delta_time )
	{
		if( !mChangeSceneTimer.Update( delta_time ) )
		{
			mDirector.Setup( p2048::TitleScene::Create( mDirector ) );
		}
		else
		{
			if( _kbhit() )
			{
				auto input = _getch();
				if( 27 == input ) // ESC
				{
					mDirector.RequestAbort();
				}
				else if( 32 == input ) // Space
				{
					mDirector.Setup( p2048::TitleScene::Create( mDirector ) );
				}
			}
		}

		r2bix_node::Node::Update( delta_time );
	}
}