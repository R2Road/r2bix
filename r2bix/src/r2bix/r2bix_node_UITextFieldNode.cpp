#include "r2bix_node_UITextFieldNode.h"

#include "r2bix_Director.h"

#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_UIControlComponent.h"
#include "r2bix_component_UITextFieldComponent.h"
#include "r2bix_component_TextureRenderComponent.h"


namespace r2bix_node
{
	r2bix_node::NodeUp UITextFieldNode::Create( r2bix::Director& director )
	{
		auto ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{

			//
			// 생성
			//
			r2bix_component::UITextFieldComponent* ui_text_field_component = ret->AddComponent<r2bix_component::UITextFieldComponent>();
			r2bix_component::UIControlComponent* ui_control_component = ret->AddComponent<r2bix_component::UIControlComponent>();
			r2bix_component::TextureRenderComponent* texture_render_component = ret->AddComponent<r2bix_component::TextureRenderComponent>();
			r2bix_component::CustomTextureComponent* custom_texture_component = ret->AddComponent<r2bix_component::CustomTextureComponent>();



			//
			// 설정
			//
			ui_text_field_component->SetUIControlComponent( ui_control_component );
			ui_text_field_component->SetCustomTextureComponent( custom_texture_component );

			texture_render_component->SetTexture( custom_texture_component->GetTexture() );



			//
			// 활성화
			//
			if( true )
			{
				ui_text_field_component->Activate();
			}
			if( true )
			{
				ui_control_component->Activate();
			}
			if( true )
			{
				texture_render_component->Activate();
			}
			if( true )
			{
				custom_texture_component->Activate();
			}

		}

		return ret;
	}
}