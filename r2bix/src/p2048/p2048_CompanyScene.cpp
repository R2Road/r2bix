#include "pch.h"
#include "p2048_CompanyScene.h"

#include <cassert>
#include <conio.h>
#include <utility> // std::move

#include "base/r2base_Director.h"
#include "component/r2component_TextRenderComponent.h"
#include "component/r2component_TransformComponent.h"
#include "node/r2node_LabelNode.h"
#include "node/r2node_SpriteNode.h"
#include "p2048table_TextureTable.h"

namespace p2048
{
	CompanyScene::CompanyScene( r2base::Director& director ) : r2node::SceneNode( director )
		, mLabelNode( nullptr )
		, mSpriteNode( nullptr )
	{}

	r2node::SceneNodeUp CompanyScene::Create( r2base::Director& director )
	{
		r2node::SceneNodeUp ret( new ( std::nothrow ) CompanyScene( director ) );
		if( !ret->Init() )
		{
			assert( false );
		}

		return ret;
	}

	bool CompanyScene::Init()
	{
		if( !r2base::Node::Init() )
		{
			return false;
		}

		{
			auto node = r2node::LabelNode::Create( mDirector );
			node->mTransformComponent->SetPosition( 5, 5 );
			node->SetRect( 0, 0, 30, 0 );
			node->SetString( "# " "2048 Game Scene" " #" );
			mLabelNode = node.get();
			AddChild( std::move( node ) );
		}

		{
			auto node = r2node::SpriteNode::Create( mDirector, p2048table::TextureTable::GetInstance().GetTitleTexture() );
			mSpriteNode = node.get();
			AddChild( std::move( node ) );
		}

		return true;
	}
	void CompanyScene::Update()
	{
		if( _kbhit() )
		{
			auto input = _getch();
			if( 27 == input )
			{
				mDirector.RequestAbort();
			}
		}

		r2node::SceneNode::Update();
	}
}