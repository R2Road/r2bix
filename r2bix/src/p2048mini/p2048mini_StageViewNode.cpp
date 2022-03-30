#include "pch.h"
#include "p2048mini_StageViewNode.h"

#include <numeric>

#include "base/r2base_Director.h"

#include "node/r2node_CustomTextureNode.h"
#include "node/r2node_PivotNode.h"
#include "p2048mini/p2048mini_StageViewComponent.h"

namespace p2048mini
{
	r2base::NodeUp StageViewNode::Create( r2base::Director& director )
	{
		auto ret( r2base::Node::Create( director ) );
		if( ret )
		{
			ret->AddComponent<p2048mini::StageViewComponent>();

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