#include "r2bix_node_UIPannelNode.h"

#include "r2bix_Director.h"
#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_TextureRenderComponent.h"
#include "r2bix_component_UIControlComponent.h"
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
			auto ui_pannel_component = ret->AddComponent<r2bix_component::UIPannelComponent>();
			auto ui_control_component = ret->AddComponent<r2bix_component::UIControlComponent>();


			//
			// 설정
			//
			ui_pannel_component->SetMyUIControlComponent( ui_control_component );



			//
			// 활성화
			//
			if( true )
			{
				ui_pannel_component->Activate();
			}
			if( true )
			{
				ui_control_component->Activate();
			}

		}

		return ret;
	}
}