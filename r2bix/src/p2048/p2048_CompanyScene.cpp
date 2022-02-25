#include "pch.h"
#include "p2048_CompanyScene.h"

#include <conio.h>
#include <utility> // std::move

#include "base/r2base_Director.h"
#include "render/r2render_iRenderable.h"

#include "scene/DevelopScene.h"

namespace
{
	class LabelNode : public r2game::Node, public r2render::iRenderable
	{
	public:
		LabelNode( r2base::Director& director ) : r2game::Node( director ), mTexture( "" )
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
		void Render( const r2render::Camera* const camera, r2render::iRenderTarget* const render_target ) override {}

		//
		//
		//
		void SetString( const std::string_view str )
		{
			mTexture.Reset( str );
		}

	private:
		r2render::Texture mTexture;
	};
}

namespace p2048
{
	CompanyScene::CompanyScene( r2base::Director& director ) : r2game::Scene( director )
		, mCamera( { 25, 25 }, { 50, 50 } )
		, mRenderTarget( 50, 50, '@' )
	{}

	r2base::NodeUp CompanyScene::Create( r2base::Director& director )
	{
		r2base::NodeUp ret( new ( std::nothrow ) CompanyScene( director ) );
		return ret;
	}

	bool CompanyScene::Init()
	{
		auto label_node = LabelNode::Create( mDirector );
		label_node->SetString( "# " "2048 Game Scene" " #" );
		AddChild( std::move( label_node ) );

		return true;
	}
	void CompanyScene::Update()
	{
		std::cout << "# " << "2048 Game Scene" << " #" << r2::linefeed;

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