#include "pch.h"
#include "p2048_CompanyScene.h"

#include <conio.h>
#include <utility> // std::move

#include "base/r2base_Director.h"
#include "render/r2render_iRenderable.h"

#include "scene/DevelopScene.h"

namespace r2game
{
	class LabelNode : public r2game::Node, public r2render::iRenderable
	{
	public:
		LabelNode( r2base::Director& director ) : r2game::Node( director )
			, mPosition()
			, mRect()
			, mTexture( "" )
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
		bool Init() override { return true; }
	public:
		void Render( const r2render::Camera* const camera, r2render::iRenderTarget* const render_target ) override
		{
		}

		//
		//
		//
		void SetPosition( const int new_x, const int new_y )
		{
			mPosition.Set( new_x, new_y );
		}
		void SetRect( const int x, const int y, const int width, const int height )
		{
			mRect.Set( x, y, width, height );
		}
		void SetString( const std::string_view str )
		{
			mTexture.Reset( str );
		}

	private:
		r2::PointInt mPosition;
		r2::RectInt mRect;
		r2render::Texture mTexture;
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
		return ret;
	}

	bool CompanyScene::Init()
	{
		auto label_node = r2game::LabelNode::Create( mDirector );
		label_node->SetPosition( 5, 5 );
		label_node->SetRect( 0, 0, 10, 1 );
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