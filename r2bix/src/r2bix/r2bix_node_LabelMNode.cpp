#include "r2bix_node_LabelMNode.h"

#include "r2bix_Director.h"
#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_TextureRenderComponent.h"
#include "r2bix_component_LabelSComponent.h"

namespace r2bix_node
{
	r2bix_node::NodeUp LabelMNode::Create( r2bix::Director& director )
	{
		auto ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{
			r2bix_component::CustomTextureComponent* custom_texture_component = ret->AddComponent<r2bix_component::CustomTextureComponent>();
			r2bix_component::TextureRenderComponent* texture_render_component = ret->AddComponent<r2bix_component::TextureRenderComponent>();
			r2bix_component::LabelSComponent* label_component = ret->AddComponent<r2bix_component::LabelSComponent>();

			label_component->SetCustomTextureComponent( custom_texture_component );
			label_component->SetTextureRenderComponent( texture_render_component );

			texture_render_component->SetTexture( custom_texture_component->GetTexture() );
		}

		return ret;
	}
}