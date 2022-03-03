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
#include "render/r2render_iRenderable.h"

#include "scene/DevelopScene.h"

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
		{
			auto label_node = r2node::LabelNode::Create( mDirector );
			label_node->mTransformComponent->SetPosition( 5, 5 );
			label_node->SetRect( 0, 0, 30, 1 );
			label_node->SetString( "# " "2048 Game Scene" " #" );
			mLabelNode = label_node.get();
			AddChild( std::move( label_node ) );
		}

		{
			auto sprite_node = r2node::SpriteNode::Create( mDirector );
			mSpriteNode = sprite_node.get();
			AddChild( std::move( sprite_node ) );
		}

		return true;
	}
	void CompanyScene::Update()
	{
		mDirector.ClearScreen();

		mLabelNode->Render( &mCamera, &mRenderTarget );
		mSpriteNode->Render( &mCamera, &mRenderTarget );

		for( int y = 0; mRenderTarget.GetHeight() > y; ++y )
		{
			std::cout << mRenderTarget.GetLine( y );
			std::cout << r2::linefeed;
		}

		auto input = _getch();
		if( 27 == input )
		{
			mDirector.Setup( DevelopScene::Create( mDirector ) );
		}
	}
}