#include "pch.h"
#include "r2game_Node.h"

namespace r2game
{
	Node::Node( r2base::Director& director ) : r2base::iNode( director )
		, mNodeFlags( 0 )
		, mChildContainer()
	{}

	void Node::AddChild( NodeSp child_node )
	{
		mChildContainer.push_back( child_node );
	}
}