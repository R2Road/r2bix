#include "pch.h"
#include "r2game_Node.h"

namespace r2game
{
	Node::Node( r2base::Director& director ) : r2base::iNode( director )
		, mNodeFlags( 0 )
	{}
}