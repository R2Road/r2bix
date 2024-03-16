#include "r2bix_node_CustomTextureNode.h"

#include <numeric>

#include "r2bix_Director.h"
#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_TextureRenderComponent.h"

namespace r2bix_node
{
	r2bix_node::NodeUp CustomTextureNode::Create( r2bix::Director& director )
	{
		auto ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{

			//
			// 생성
			//
			auto custome_texture_component = ret->AddComponent<r2bix_component::CustomTextureComponent>();
			auto texture_render_component = ret->AddComponent<r2bix_component::TextureRenderComponent>();



			//
			// 설정
			//
			texture_render_component->SetTexture( custome_texture_component->GetTexture() );



			//
			// 활성화
			//
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