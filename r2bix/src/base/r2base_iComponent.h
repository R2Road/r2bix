#pragma once

namespace r2base
{
	class iNode;

	using ComponentUp = std::unique_ptr<class iComponent>;
	class iComponent
	{
	protected:
		iComponent( iNode& owner_node ) : mOwnerNode( owner_node ) {}
	public:
		virtual ~iComponent() {}

	public:
		virtual bool Init() = 0;
		virtual void Update() = 0;

	protected:
		iNode& mOwnerNode;
	};
}