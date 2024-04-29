#include "r2bix_node_UITextFieldNode.h"

#include "r2bix_Director.h"

#include "r2bix_component_UIControlComponent.h"
#include "r2bix_component_UITextFieldComponent.h"

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
			auto ui_text_field_component = ret->AddComponent<r2bix_component::UITextFieldComponent>();
			auto ui_control_component = ret->AddComponent<r2bix_component::UIControlComponent>();



			//
			// 설정
			//
			ui_text_field_component->SetUIControlComponent( ui_control_component );



			//
			// 활성화
			//
			if( true )
			{
				ui_text_field_component->Activate();
			}

		}

		return ret;
	}
}