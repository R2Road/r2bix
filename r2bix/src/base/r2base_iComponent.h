#pragma once

namespace r2base
{
	class Node;

	using ComponentUp = std::unique_ptr<class iComponent>;
	class iComponent
	{
	protected:
		iComponent( Node& owner_node ) : mOwnerNode( owner_node ) {}
	public:
		virtual ~iComponent() {}

	public:
		virtual bool Init() = 0;
		virtual void Update() = 0;

	protected:
		Node& mOwnerNode;
	};
}