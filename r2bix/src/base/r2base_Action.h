#pragma once

#include <memory>

namespace r2base
{
	class Node;

	using ActionUp = std::unique_ptr<class Action>;
	class Action
	{
	public:
		Action() : mOwnerNode( nullptr ) {}
		virtual ~Action() {}

		void SetOwnerNode( r2base::Node* const owner_node )
		{
			mOwnerNode = owner_node;
		}

		//
		// Interface
		//
		virtual void Enter() = 0;
		virtual bool Update() = 0;

	protected:
		r2base::Node* mOwnerNode;
	};
}