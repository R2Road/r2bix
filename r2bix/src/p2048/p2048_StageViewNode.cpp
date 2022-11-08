#include "p2048_StageViewNode.h"

#include <numeric>

#include "r2bix/r2bix_Director.h"

#include "r2bix/r2component_CustomTextureComponent.h"
#include "r2bix/r2component_TextureRenderComponent.h"
#include "r2bix/r2bix_node_CustomTextureNode.h"
#include "r2bix/r2bix_node_PivotNode.h"

#include "p2048_Config.h"
#include "p2048_StageViewComponent.h"

namespace p2048
{
	r2bix_node::NodeUp StageViewNode::Create( r2bix::Director& director )
	{
		auto ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{
			auto stage_view_component = ret->AddComponent<p2048::StageViewComponent>();

			//
			// Background
			//
			{
				auto node = ret->AddChild<r2bix_node::CustomTextureNode>( std::numeric_limits<int>::min() );
				node->GetComponent<r2component::TextureRenderComponent>()->SetPivotPoint( 0.f, 0.f );
				node->mTransformComponent->SetPosition( -1, -1 );

				stage_view_component->SetBackgroundNode( node );

				//
				// Debug
				//
				if( p2048::Config::GetNodeConfig().pivot )
				{
					node->AddChild<r2bix_node::PivotNode>( std::numeric_limits<int>::max() );
				}
			}

			//
			// Debug
			//
			if( p2048::Config::GetNodeConfig().pivot )
			{
				ret->AddChild<r2bix_node::PivotNode>( std::numeric_limits<int>::max() );
			}
		}

		return ret;
	}
}