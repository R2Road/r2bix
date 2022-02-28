#pragma once

#include <list>
#include <memory>

namespace r2base
{
	class Director;

	using NodeUp = std::unique_ptr<class iNode>;
	class iNode
	{
	protected:
		using ChildContainerT = std::list<r2base::NodeUp>;

		iNode( Director& director ) : mDirector( director ), mChildContainer() {}
	public:
		virtual ~iNode() {}

	public:
		virtual bool Init() = 0;
		virtual void Update() = 0;

		void AddChild( r2base::NodeUp child_node )
		{
			mChildContainer.push_back( std::move( child_node ) );
		}

	protected:
		Director& mDirector;
		ChildContainerT mChildContainer;
	};
}