#include "pch.h"
#include "r2game_Node.h"

namespace r2game
{
	Node::Node( r2base::Director& director ) : r2base::iNode( director )
		, mNodeFlags( 0 )
		, mChildContainer()
	{}

	void Node::AddChild( r2base::NodeUp child_node )
	{
		mChildContainer.push_back( std::move( child_node ) );
	}
}