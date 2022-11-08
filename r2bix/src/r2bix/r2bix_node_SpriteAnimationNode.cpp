#include "r2bix_node_SpriteAnimationNode.h"

#include "r2bix_Director.h"
#include "r2bix_component_TextureFrameAnimationComponent.h"
#include "r2bix_component_TextureFrameRenderComponent.h"

namespace r2bix_node
{
	r2bix_node::NodeUp SpriteAnimationNode::Create( r2bix::Director& director )
	{
		auto ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{
			auto frame_render_component = ret->AddComponent<r2bix_component::TextureFrameRenderComponent>();
			auto frame_animation_component = ret->AddComponent<r2bix_component::TextureFrameAnimationComponent>();

			frame_animation_component->SetTextureFrameRenderComponent( frame_render_component );
		}

		return ret;
	}
}