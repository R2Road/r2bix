#include "pch.h"
#include "p2048_CompanyScene.h"

#include <cassert>
#include <conio.h>
#include <utility> // std::move

#include "base/r2base_Director.h"
#include "component/r2component_TextRenderComponent.h"
#include "component/r2component_TransformComponent.h"
#include "render/r2render_iRenderable.h"

#include "scene/DevelopScene.h"

namespace r2game
{
	class LabelNode : public r2base::Node
	{
	public:
		LabelNode( r2base::Director& director ) : r2base::Node( director )
			, mTransformComponent( nullptr )
			, mTextRenderComponent( nullptr )
		{}

		static std::unique_ptr<LabelNode> Create( r2base::Director& director )
		{
			std::unique_ptr<LabelNode> ret( new ( std::nothrow ) LabelNode( director ) );
			if( !ret || !ret->Init() )
			{
				ret.reset();
			}

			return ret;
		}

		//
		// Override
		//
	private:
		bool Init() override
		{
			auto transform_component = r2component::TransformComponent::Create( *this );
			mTransformComponent = transform_component.get();
			AddComponent( std::move( transform_component ) );

			auto text_render_component = r2component::TextRenderComponent::Create( *this );
			text_render_component->mTransformComponent = mTransformComponent;
			mTextRenderComponent = text_render_component.get();
			AddComponent( std::move( text_render_component ) );

			return true;
		}
	public:
		//
		//
		//
		void SetRect( const int x, const int y, const int width, const int height )
		{
			mTextRenderComponent->SetRect( x, y, width, height );
		}
		void SetString( const std::string_view str )
		{
			mTextRenderComponent->SetString( str );
		}

	public:
		r2component::TransformComponent* mTransformComponent;
		r2component::TextRenderComponent* mTextRenderComponent;
	};
}

namespace p2048
{
	CompanyScene::CompanyScene( r2base::Director& director ) : r2game::Scene( director )
		, mCamera( { 25, 25 }, { 50, 50 } )
		, mRenderTarget( 50, 50, '@' )

		, mLabelNode( nullptr )
	{}

	r2base::NodeUp CompanyScene::Create( r2base::Director& director )
	{
		r2base::NodeUp ret( new ( std::nothrow ) CompanyScene( director ) );
		if( !ret->Init() )
		{
			assert( false );
		}

		return ret;
	}

	bool CompanyScene::Init()
	{
		auto label_node = r2game::LabelNode::Create( mDirector );
		label_node->mTransformComponent->SetPosition( 5, 5 );
		label_node->SetRect( 0, 0, 30, 1 );
		label_node->SetString( "# " "2048 Game Scene" " #" );
		mLabelNode = label_node.get();
		AddChild( std::move( label_node ) );

		return true;
	}
	void CompanyScene::Update()
	{
		mLabelNode->Render( &mCamera, &mRenderTarget );

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

		system( "cls" );
	}
}