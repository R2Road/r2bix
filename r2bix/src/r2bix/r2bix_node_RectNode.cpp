#include "r2bix_node_RectNode.h"

#include "r2bix_Director.h"

#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_RectComponent.h"
#include "r2bix_component_TextureRenderComponent.h"

namespace r2bix_node
{
	r2bix_node::NodeUp RectNode::Create( r2bix::Director& director )
	{
		auto ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{

			//
			// ����
			//
			r2bix_component::TextureRenderComponent* texture_render_component = ret->AddComponent<r2bix_component::TextureRenderComponent>();
			r2bix_component::CustomTextureComponent* custom_texture_component = ret->AddComponent<r2bix_component::CustomTextureComponent>();
			r2bix_component::RectComponent* rect_component = ret->AddComponent<r2bix_component::RectComponent>();



			//
			// ����
			//
			texture_render_component->SetTexture( custom_texture_component->GetTexture() );

			rect_component->SetCustomTextureComponent( custom_texture_component );
			rect_component->SetTextureRenderComponent( texture_render_component );



			//
			// Ȱ��ȭ
			//
			if( true )
			{
				custom_texture_component->Activate();
			}
			if( true )
			{
				texture_render_component->Activate();
			}

		}

		return ret;
	}
}