#include "pch.h"
#include "p2048_CompanyScene.h"

#include <conio.h>

#include "base/r2base_Director.h"

#include "scene/DevelopScene.h"

namespace
{
	class LabelNode : public r2game::Node
	{
	public:
		LabelNode( r2base::Director& director ) : r2game::Node( director )
		{}

		static r2game::NodeSp Create( r2base::Director& director )
		{
			r2game::NodeSp ret( new ( std::nothrow ) LabelNode( director ) );
			return ret;
		}
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

	bool CompanyScene::Do()
	{
		AddChild( LabelNode::Create( mDirector ) );

		std::cout << "# " << "2048 Game Scene" << " #" << r2::linefeed;

		auto input = _getch();
		if( 27 == input )
		{
			mDirector.Setup( DevelopScene::Create( mDirector ) );
		}

		system( "cls" );

		return true;
	}
}