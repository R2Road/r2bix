#include "r2bix_node_SceneNode.h"

#include "r2bix_Director.h"
#include "r2bix_component_TransformComponent.h"

namespace r2bix_node
{
	SceneNode::SceneNode( r2bix::Director& director ) : r2bix_node::Node( director )
	{}

	SceneNodeUp SceneNode::Create( r2bix::Director& director )
	{
		SceneNodeUp ret( new ( std::nothrow ) SceneNode( director ) );
		if( !ret || !ret->Init() )
		{
			ret.reset();
		}

		return ret;
	}
}