#include "pch.h"
#include "p2048mini_StageViewNode.h"

#include <numeric>

#include "base/r2base_Director.h"

#include "component/r2component_CustomTextureComponent.h"
#include "component/r2component_TextureRenderComponent.h"
#include "node/r2node_CustomTextureNode.h"
#include "node/r2node_PivotNode.h"

namespace p2048mini
{
	r2base::NodeUp StageViewNode::Create( r2base::Director& director )
	{
		auto ret( r2base::Node::Create( director ) );
		if( ret )
		{
			//
			// Background
			//
			{
				auto node = ret->AddChild<r2node::CustomTextureNode>();
			}

			//
			// Debug
			//
			{
				ret->AddChild<r2node::PivotNode>( std::numeric_limits<int>::max() );
			}
		}

		return ret;
	}
}