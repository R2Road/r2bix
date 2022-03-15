#include "pch.h"
#include "p2048_TitleScene.h"

#include <cassert>
#include <conio.h>
#include <utility> // std::move

#include "base/r2base_Director.h"
#include "component/r2component_LabelComponent.h"
#include "component/r2component_TextureFrameRenderComponent.h"
#include "component/r2component_TextureRenderComponent.h"
#include "component/r2component_TransformComponent.h"
#include "node/r2node_LabelNode.h"
#include "node/r2node_SpriteNode.h"

#include "p2048table_TextureFrameAnimationTable.h"
#include "p2048table_TextureTable.h"

namespace p2048
{
	TitleScene::TitleScene( r2base::Director& director ) : r2node::SceneNode( director )
		, mLabelNode( nullptr )
		, mSpriteNode( nullptr )
	{}

	r2node::SceneNodeUp TitleScene::Create( r2base::Director& director )
	{
		r2node::SceneNodeUp ret( new ( std::nothrow ) TitleScene( director ) );
		if( !ret->Init() )
		{
			assert( false );
		}

		return ret;
	}

	bool TitleScene::Init()
	{
		if( !r2base::Node::Init() )
		{
			return false;
		}

		//
		// Logo
		//
		{
			mSpriteNode = AddChild<r2node::SpriteNode>();

			auto frame = p2048table::TextureTable::GetInstance().GetTextureFrame( "title_image" );

			mSpriteNode->GetComponent<r2component::TextureFrameRenderComponent>()->SetTextureFrame( frame );
			mSpriteNode->GetComponent<r2component::TextureFrameRenderComponent>()->MoveRectOrigin(
				-frame->GetWidth() / 2, -frame->GetHeight() / 2
			);

			mSpriteNode->mTransformComponent->SetPosition(
				mDirector.GetScreenBufferSize().GetWidth() * 0.5f
				, mDirector.GetScreenBufferSize().GetHeight() * 0.32f
			);
		}

		//
		// Company Name
		//
		{
			mLabelNode = AddChild<r2node::LabelNode>();

			mLabelNode->GetComponent<r2component::LabelComponent>()->SetStringWithResize( "Press Any Key" );

			mLabelNode->GetComponent<r2component::TextureRenderComponent>()->MoveRectOrigin(
				-mLabelNode->GetComponent<r2component::LabelComponent>()->GetWidth() / 2, 0
			);

			mLabelNode->mTransformComponent->SetPosition(
				mDirector.GetScreenBufferSize().GetWidth() * 0.5f
				, mDirector.GetScreenBufferSize().GetHeight() * 0.65f
			);
		}

		return true;
	}
	void TitleScene::Update( const float delta_time )
	{
		if( _kbhit() )
		{
			auto input = _getch();
			if( 27 == input )
			{
				mDirector.RequestAbort();
			}
		}

		r2node::SceneNode::Update( delta_time );
	}
}