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
			// ����
			//
			auto ui_pannel_component = ret->AddComponent<r2bix_component::UIPannelComponent>();


			//
			// ����
			//


			//
			// Ȱ��ȭ
			//
			if( true )
			{
				ui_pannel_component->Activate();
			}

		}

		return ret;
	}
}