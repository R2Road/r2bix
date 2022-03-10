#include "pch.h"
#include "pmr_CompanyScene.h"

#include <conio.h>

#include "base/r2base_Director.h"
#include "component/r2component_LabelComponent.h"
#include "component/r2component_TextureRenderComponent.h"
#include "node/r2node_LabelNode.h"

namespace pmr
{
	CompanyScene::CompanyScene( r2base::Director& director ) : r2node::SceneNode( director )
	{}

	r2node::SceneNodeUp CompanyScene::Create( r2base::Director& director )
	{
		r2node::SceneNodeUp ret( new ( std::nothrow ) CompanyScene( director ) );
		if( !ret || !ret->Init() )
		{
			ret.reset();
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
			auto node = AddChild<r2node::LabelNode>();
			node->GetComponent<r2component::TextureRenderComponent>()->SetRect( 0, 0, 40, 0 );
			node->GetComponent<r2component::LabelComponent>()->SetString( CompanyScene::GetTitle() );
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
	}
}