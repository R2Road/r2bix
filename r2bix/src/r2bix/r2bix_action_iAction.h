#pragma once

#include <memory>

namespace r2bix_node
{
	class Node;
}

namespace r2bix_action
{
	using ActionUp = std::unique_ptr<class iAction>;
	class iAction
	{
	public:
		iAction() : mOwnerNode( nullptr ) {}
		virtual ~iAction() {}

		void SetOwnerNode( r2bix_node::Node* const owner_node )
		{
			mOwnerNode = owner_node;
		}

		//
		// Interface
		//
		virtual void Enter() = 0;
		virtual bool Update( const float delta_time ) = 0;

	protected:
		r2bix_node::Node* mOwnerNode;
	};
}