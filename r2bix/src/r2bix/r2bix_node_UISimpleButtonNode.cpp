#include "r2bix_node_UISimpleButtonNode.h"

#include "r2bix_Director.h"

#include "r2bix_component_CustomTextureComponent.h"

#include "r2bix_component_UIButtonComponent.h"
#include "r2bix_component_UIControlComponent.h"

#include "r2bix_component_TextureRenderComponent.h"

namespace r2bix_node
{
	r2bix_node::NodeUp UISimpleButtonNode::Create( r2bix::Director& director )
	{
		auto ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{

			//
			// ����
			//
			auto ui_button_component = ret->AddComponent<r2bix_component::UIButtonComponent>();
			auto ui_control_component = ret->AddComponent<r2bix_component::UIControlComponent>();
			auto custome_texture_component = ret->AddComponent<r2bix_component::CustomTextureComponent>();
			auto texture_render_component = ret->AddComponent<r2bix_component::TextureRenderComponent>();



			//
			// ����
			//
			ui_button_component->SetMyUIControlComponent( ui_control_component );

			texture_render_component->SetTexture( custome_texture_component->GetTexture() );



			//
			// Ȱ��ȭ
			//
			if( true )
			{
				ui_button_component->Activate();
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