#include "p2048_NumberNode.h"

#include <numeric>

#include "r2bix/r2base_Director.h"
#include "r2bix/r2component_LabelComponent.h"
#include "r2bix/r2component_PivotComponent.h"
#include "r2bix/r2component_TextureFrameRenderComponent.h"
#include "r2bix/r2node_LabelNode.h"
#include "r2bix/r2node_SpriteNode.h"

#include "p2048_NumberComponent.h"
#include "p2048table_TextureTable.h"

namespace p2048
{
	r2base::NodeUp NumberNode::Create( r2base::Director& director )
	{
		auto ret( r2base::Node::Create( director ) );
		if( ret )
		{
			auto number_component = ret->AddComponent<p2048::NumberComponent>();

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
				auto node = ret->AddChild<r2node::LabelNode>();

				number_component->SetLabelComponent( node->GetComponent<r2component::LabelComponent>() );
			}
		}

		return ret;
	}
}