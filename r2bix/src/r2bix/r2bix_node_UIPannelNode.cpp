#include "r2bix_node_UIPannelNode.h"

#include "r2bix_Director.h"
#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_TextureRenderComponent.h"
#include "r2bix_component_UIButtonComponent.h"

namespace r2bix_node
{
	r2bix_node::NodeUp UIPannelNode::Create( r2bix::Director& director )
	{
		auto ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{
			auto custome_texture_component = ret->AddComponent<r2bix_component::CustomTextureComponent>();
			auto texture_render_component = ret->AddComponent<r2bix_component::TextureRenderComponent>();
			auto ui_button_component = ret->AddComponent<r2bix_component::UIButtonComponent>();

			texture_render_component->SetTexture( custome_texture_component->GetTexture() );

			ui_button_component->SetCustomTextureComponent( custome_texture_component );
			ui_button_component->SetTextureRenderComponent( texture_render_component );
		}

		return ret;
	}
}