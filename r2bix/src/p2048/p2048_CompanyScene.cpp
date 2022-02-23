#include "pch.h"
#include "p2048_CompanyScene.h"

#include <conio.h>

#include "base/r2base_Director.h"
#include "render/r2render_iRenderable.h"

#include "scene/DevelopScene.h"

namespace
{
	class LabelNode : public r2game::Node, public r2render::iRenderable
	{
	public:
		LabelNode( r2base::Director& director ) : r2game::Node( director )
		{}

		static r2game::NodeSp Create( r2base::Director& director )
		{
			std::shared_ptr<LabelNode> ret( new ( std::nothrow ) LabelNode( director ) );
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
	};
}

namespace p2048
{
	CompanyScene::CompanyScene( r2base::Director& director ) : r2game::Scene( director )
	{}

	r2base::NodeUp CompanyScene::Create( r2base::Director& director )
	{
		r2base::NodeUp ret( new ( std::nothrow ) CompanyScene( director ) );
		return ret;
	}

	bool CompanyScene::Init()
	{
		AddChild( LabelNode::Create( mDirector ) );

		return true;
	}
	void CompanyScene::Update()
	{
		std::cout << "# " << "2048 Game Scene" << " #" << r2::linefeed;

		auto input = _getch();
		if( 27 == input )
		{
			mDirector.Setup( DevelopScene::Create( mDirector ) );
		}

		system( "cls" );
	}
}