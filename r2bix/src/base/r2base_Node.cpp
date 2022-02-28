#include "pch.h"
#include "r2base_Node.h"

namespace r2base
{
	Node::Node( Director& director ) :
		mDirector( director )
		, mComponentContainer()
		, mChildContainer()
	{}

	void Node::AddComponent( r2base::ComponentUp component )
	{
		mComponentContainer.push_back( std::move( component ) );
	}

	void Node::AddChild( r2base::NodeUp child_node )
	{
		mChildContainer.push_back( std::move( child_node ) );
	}
}