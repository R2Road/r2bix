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
			auto custome_texture_component = ret->AddComponent<r2bix_component::CustomTextureComponent>();
			auto texture_render_component = ret->AddComponent<r2bix_component::TextureRenderComponent>();
			auto ui_pannel_component = ret->AddComponent<r2bix_component::UIPannelComponent>();


			//
			// 설정
			//
			texture_render_component->SetTexture( custome_texture_component->GetTexture() );

			ui_pannel_component->SetCustomTextureComponent( custome_texture_component );
			ui_pannel_component->SetTextureRenderComponent( texture_render_component );

		}

		return ret;
	}
}