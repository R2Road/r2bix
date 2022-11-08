#include "r2bix_node_SpriteNode.h"

#include "r2bix_Director.h"
#include "r2bix_component_TextureFrameRenderComponent.h"

namespace r2bix_node
{
	r2bix_node::NodeUp SpriteNode::Create( r2bix::Director& director )
	{
		auto ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{
			ret->AddComponent<r2bix_component::TextureFrameRenderComponent>();
		}

		return ret;
	}
}