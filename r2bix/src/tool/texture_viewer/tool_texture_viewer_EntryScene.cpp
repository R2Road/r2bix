#include "tool_texture_viewer_EntryScene.h"

#include "r2bix_node_SceneNode.h"

#include "tool_texture_viewer_EntryComponent.h"

namespace tool_texture_viewer
{
	r2bix_node::SceneNodeUp EntryScene::Create( r2bix::Director& director )
	{
		auto ret( r2bix_node::SceneNode::Create( director ) );
		if( ret )
		{
			ret->AddComponent<EntryComponent>();
		}

		return ret;
	}
}