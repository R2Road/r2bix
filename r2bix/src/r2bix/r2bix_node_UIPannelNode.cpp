#include "r2bix_node_UIPannelNode.h"

#include "r2bix_Director.h"
#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_TextureRenderComponent.h"
#include "r2bix_component_UIPannelComponent.h"

namespace r2bix_node
{
	r2bix_node::NodeUp UIPannelNode::Create( r2bix::Director& director )
	{
		auto ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{

			//
			// 생성
			//
			auto custom_texture_component = ret->AddComponent<r2bix_component::CustomTextureComponent>();
			auto texture_render_component = ret->AddComponent<r2bix_component::TextureRenderComponent>();
			auto ui_pannel_component = ret->AddComponent<r2bix_component::UIPannelComponent>();


			//
			// 설정
			//
			texture_render_component->SetTexture( custom_texture_component->GetTexture() );
			texture_render_component->SetPivotPoint( 0.f, 0.f );

			ui_pannel_component->SetCustomTextureComponent( custom_texture_component );
			ui_pannel_component->SetTextureRenderComponent( texture_render_component );


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
			if( true )
			{
				ui_pannel_component->Activate();
			}

		}

		return ret;
	}
}