#include "r2bix_node_HollowRectNode.h"

#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_HollowRectComponent.h"
#include "r2bix_component_TextureRenderComponent.h"

namespace r2bix_node
{
	r2bix_node::NodeUp HollowRectNode::Create( r2bix::Director& director )
	{
		auto ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{

			//
			// 생성
			//
			r2bix_component::TextureRenderComponent* texture_render_component = ret->AddComponent<r2bix_component::TextureRenderComponent>();
			r2bix_component::CustomTextureComponent* custom_texture_component = ret->AddComponent<r2bix_component::CustomTextureComponent>();
			r2bix_component::HollowRectComponent* hollow_rect_component = ret->AddComponent<r2bix_component::HollowRectComponent>();



			//
			// 설정
			//
			texture_render_component->SetTexture( custom_texture_component->GetTexture() );

			hollow_rect_component->SetCustomTextureComponent( custom_texture_component );
			hollow_rect_component->SetTextureRenderComponent( texture_render_component );



			//
			// 활성화
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