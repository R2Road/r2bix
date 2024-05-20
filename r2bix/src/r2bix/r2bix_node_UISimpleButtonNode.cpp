#include "r2bix_node_UISimpleButtonNode.h"

#include "r2bix_Director.h"

#include "r2bix_component_CustomTextureComponent.h"

#include "r2bix_component_UIControlComponent.h"
#include "r2bix_component_UISimpleButtonComponent.h"

#include "r2bix_component_TextureRenderComponent.h"

namespace r2bix_node
{
	r2bix_node::NodeUp UISimpleButtonNode::Create( r2bix::Director& director )
	{
		auto ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{

			//
			// 생성
			//
			auto ui_simple_button_component = ret->AddComponent<r2bix_component::UISimpleButtonComponent>();
			auto ui_control_component = ret->AddComponent<r2bix_component::UIControlComponent>();
			auto custome_texture_component = ret->AddComponent<r2bix_component::CustomTextureComponent>();
			auto texture_render_component = ret->AddComponent<r2bix_component::TextureRenderComponent>();



			//
			// 설정
			//
			ui_simple_button_component->SetMyUIControlComponent( ui_control_component );
			ui_simple_button_component->SetMyCustomTextureComponent( custome_texture_component );
			ui_simple_button_component->SetMyTextureRenderComponent( texture_render_component );

			texture_render_component->SetTexture( custome_texture_component->GetTexture() );



			//
			// 활성화
			//
			if( true )
			{
				ui_simple_button_component->Activate();
			}
			if( true )
			{
				ui_control_component->Activate();
			}
			if( true )
			{
				custome_texture_component->Activate();
			}
			if( true )
			{
				texture_render_component->Activate();
			}

		}

		return ret;
	}
}