#include "r2bix_node_SpriteNode.h"

#include "r2bix_Director.h"
#include "r2bix_component_TextureFrameRenderComponent.h"

namespace r2bix_node
{
	r2bix_node::NodeUp SpriteNode::Create( r2bix::Director& director )
	{
		auto ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{

			//
			// 생성
			//
			r2bix_component::TextureFrameRenderComponent* texture_framerender_component = ret->AddComponent<r2bix_component::TextureFrameRenderComponent>();



			//
			// 설정
			//



			//
			// 활성화
			//
			if( true )
			{
				texture_framerender_component->Activate();
			}

		}

		return ret;
	}
}