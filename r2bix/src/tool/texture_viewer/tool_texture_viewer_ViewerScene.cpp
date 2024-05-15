#include "tool_texture_viewer_ViewerScene.h"

#include "r2bix_Director.h"
#include "r2bix_node_Node.h"

#include "r2bix_component_LabelSComponent.h"
#include "r2bix_node_LabelSNode.h"

namespace tool_texture_viewer
{
	r2bix_node::NodeUp ViewerScene::Create( r2bix::Director& director )
	{
		auto ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{
			auto node = ret->AddChild<r2bix_node::LabelSNode>();
			node->GetComponent<r2bix_component::LabelSComponent>()->SetString( "Texture Viewer" );

			node->mTransformComponent->SetPosition(
				director.GetScreenSize().GetWidth() * 0.5f
				, director.GetScreenSize().GetHeight() * 0.5f
			);
		}

		return ret;
	}
}