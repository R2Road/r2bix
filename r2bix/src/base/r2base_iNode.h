#pragma once

#include <list>
#include <memory>

#include "r2base_iComponent.h"

//
// # 2022.02.28 by R2Road
//
// ������Ʈ ��� �ý����� �ẻ ������ ������ ����� �� ������ ������ ���⼭ �غ���.
//
// ���� ������Ʈ�� �����Ͽ� Ư�� ����� ���� ǥ�� ��带 �����Ѵ�.
// ����� ���� ����� ������ ������ ������ �������.
//

namespace r2base
{
	class Director;

	using NodeUp = std::unique_ptr<class iNode>;
	class iNode
	{
	protected:
		using ComponentContainerT = std::list<ComponentUp>;

		using ChildContainerT = std::list<r2base::NodeUp>;

		iNode( Director& director ) : mDirector( director ), mComponentContainer(), mChildContainer() {}
	public:
		virtual ~iNode() {}

	public:
		virtual bool Init() = 0;
		virtual void Update() = 0;

		void AddComponent( r2base::ComponentUp component )
		{
			mComponentContainer.push_back( std::move( component ) );
		}

		void AddChild( r2base::NodeUp child_node )
		{
			mChildContainer.push_back( std::move( child_node ) );
		}

	protected:
		Director& mDirector;
		ComponentContainerT mComponentContainer;
		ChildContainerT mChildContainer;
	};
}