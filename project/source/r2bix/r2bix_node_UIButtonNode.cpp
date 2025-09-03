#include "r2bix_node_UIButtonNode.h"

#include "r2bix_Director.h"

#include "r2bix_component_UIButtonComponent.h"
#include "r2bix_component_UIControlComponent.h"

namespace r2bix_node
{
	r2bix_node::NodeUp UIButtonNode::Create( r2bix::Director& director )
	{
		auto ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{

			//
			// 생성
			//
			auto ui_button_component = ret->AddComponent<r2bix_component::UIButtonComponent>();
			auto ui_control_component = ret->AddComponent<r2bix_component::UIControlComponent>();



			//
			// 설정
			//
			ui_button_component->SetMyUIControlComponent( ui_control_component );



			//
			// 활성화
			//
			if( true )
			{
				ui_button_component->Activate();
			}
			if( true )
			{
				ui_control_component->Activate();
			}

		}

		return ret;
	}
}