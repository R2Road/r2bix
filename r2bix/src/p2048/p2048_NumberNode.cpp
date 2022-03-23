#include "pch.h"
#include "p2048_NumberNode.h"

#include <numeric>

#include "base/r2base_Director.h"
#include "component/r2component_LabelComponent.h"
#include "component/r2component_PivotComponent.h"
#include "component/r2component_TextureFrameRenderComponent.h"
#include "node/r2node_LabelNode.h"
#include "node/r2node_PivotNode.h"
#include "node/r2node_SpriteNode.h"

#include "p2048table_TextureTable.h"

namespace p2048
{
	r2base::NodeUp NumberNode::Create( r2base::Director& director )
	{
		auto ret( r2base::Node::Create( director ) );
		if( ret )
		{
			//
			// Frame
			//
			{
				auto node = ret->AddChild<r2node::SpriteNode>( std::numeric_limits<int>::min() );
				node->GetComponent<r2component::TextureFrameRenderComponent>()->SetTextureFrame(
					p2048table::TextureTable::GetInstance().GetTextureFrame( "number_frame_0" )
				);
			}

			//
			// Label
			//
			{
				auto node = ret->AddChild<r2node::LabelNode>( std::numeric_limits<int>::min() );
				node->GetComponent<r2component::LabelComponent>()->SetString( "2048" );
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