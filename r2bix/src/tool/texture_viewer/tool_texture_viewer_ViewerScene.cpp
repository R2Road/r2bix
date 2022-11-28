#include "tool_texture_viewer_ViewerScene.h"

#include "r2bix/r2bix_Director.h"

#include "r2bix/r2bix_component_LabelSComponent.h"
#include "r2bix/r2bix_node_LabelSNode.h"

namespace tool_texture_viewer
{
	r2bix_node::SceneNodeUp ViewerScene::Create( r2bix::Director& director )
	{
		auto ret( r2bix_node::SceneNode::Create( director ) );
		if( ret )
		{
			auto node = ret->AddChild<r2bix_node::LabelSNode>();
			node->GetComponent<r2bix_component::LabelSComponent>()->SetString( "Texture Viewer" );

			node->mTransformComponent->SetPosition(
				director.GetScreenBufferSize().GetWidth() * 0.5f
				, director.GetScreenBufferSize().GetHeight() * 0.5f
			);
		}

		return ret;
	}
}