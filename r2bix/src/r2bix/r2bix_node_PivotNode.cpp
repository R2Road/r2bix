#include "r2bix_node_PivotNode.h"

#include "r2bix_Director.h"
#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_TextureRenderComponent.h"

namespace r2bix_node
{
	r2bix_node::NodeUp PivotNode::Create( r2bix::Director& director )
	{
		auto ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{
			r2bix_component::TextureRenderComponent* texture_render_component = ret->AddComponent<r2bix_component::TextureRenderComponent>();
			r2bix_component::CustomTextureComponent* custome_texture_component = ret->AddComponent<r2bix_component::CustomTextureComponent>();
			custome_texture_component->GetTexture()->Reset( 1u, 1u, '+' );
			custome_texture_component->GetTexture()->FillColor( 1u, 1u, r2bix::eForegroundColor::FG_Red | r2bix::eBackgroundColor::BG_White );

			texture_render_component->SetTexture( custome_texture_component->GetTexture() );
		}

		return ret;
	}
}