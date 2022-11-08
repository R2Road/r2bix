#include "p_mini_adv_CompanyScene.h"

#include <conio.h>

#include "r2bix/r2bix_Director.h"
#include "r2bix/r2component_LabelSComponent.h"
#include "r2bix/r2component_TextureRenderComponent.h"
#include "r2bix/r2bix_node_LabelSNode.h"

#include "p_mini_adv_VersionInfo.h"

namespace p_mini_adv
{
	CompanyScene::CompanyScene( r2bix::Director& director ) : r2bix_node::SceneNode( director )
	{}

	r2bix_node::SceneNodeUp CompanyScene::Create( r2bix::Director& director )
	{
		r2bix_node::SceneNodeUp ret( new ( std::nothrow ) CompanyScene( director ) );
		if( !ret || !ret->Init() )
		{
			ret.reset();
		}

		return ret;
	}

	bool CompanyScene::Init()
	{
		if( !r2bix_node::Node::Init() )
		{
			return false;
		}

		{
			auto node = AddChild<r2bix_node::LabelSNode>();
			node->GetComponent<r2component::LabelSComponent>()->SetString( VersionInfo.String4Summury );

			node->mTransformComponent->SetPosition(
				mDirector.GetScreenBufferSize().GetWidth() * 0.5f
				, mDirector.GetScreenBufferSize().GetHeight() * 0.3f
			);
		}

		{
			auto node = AddChild<r2bix_node::LabelSNode>();
			node->GetComponent<r2component::LabelSComponent>()->SetString( VersionInfo.String4Road2Version_0_0_1 );

			node->mTransformComponent->SetPosition(
				mDirector.GetScreenBufferSize().GetWidth() * 0.5f
				, mDirector.GetScreenBufferSize().GetHeight() * 0.6f
			);
		}

		return true;
	}
	void CompanyScene::Update( const float delta_time )
	{
		if( _kbhit() )
		{
			auto input = _getch();
			if( 27 == input )
			{
				mDirector.RequestAbort();
			}
		}

		r2bix_node::SceneNode::Update( delta_time );
	}
}