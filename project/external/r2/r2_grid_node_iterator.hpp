//
// # Version Rule
// - 1.0.0 : 사용 가능
// - 0.1.0 : 사용자가 코드를 바꿀 정도의 변화
// - 0.0.1 : 자잘한 변화
//
// # Last Update		: 2023.07.05 PM.04.39
// # Version			: 1.0.0
//

#pragma once

#include <memory>

#include "r2_grid_node.hpp"

namespace r2
{
	template<typename Coordinate_T, typename Value_T>
	class GridNodeIterator
	{
	public:
		using ValueT = Value_T;
		using NodeT = GridNode<Coordinate_T, ValueT>;



		GridNodeIterator( NodeT* target_node ) : mTargetNode( target_node )
		{}



		GridNodeIterator& operator++()
		{
			mTargetNode = mTargetNode->pNext;
			return ( *this );
		}
		GridNodeIterator& operator--()
		{
			mTargetNode = mTargetNode->pPrev;
			return ( *this );
		}



		bool operator==( const GridNodeIterator& other ) const
		{
			return mTargetNode == other.mTargetNode;
		}
		bool operator!=( const GridNodeIterator& other ) const
		{
			return !operator==( other );
		}



		ValueT& operator*() const
		{
			return mTargetNode->MyValue;
		}
		ValueT* operator->() const
		{
			return std::addressof( *( *this ) ); // call : operator*()
		}



		NodeT* mTargetNode;
	};



	template<typename Coordinate_T, typename Value_T>
	class GridNodeConstIterator
	{
	public:
		using ValueT = Value_T;
		using NodeT = GridNode<Coordinate_T, ValueT>;



		GridNodeConstIterator( const NodeT* target_node ) : mTargetNode( target_node )
		{}



		GridNodeConstIterator& operator++()
		{
			mTargetNode = mTargetNode->pNext;
			return ( *this );
		}
		GridNodeConstIterator& operator--()
		{
			mTargetNode = mTargetNode->pPrev;
			return ( *this );
		}



		bool operator==( const GridNodeConstIterator& other ) const
		{
			return mTargetNode == other.mTargetNode;
		}
		bool operator!=( const GridNodeConstIterator& other ) const
		{
			return !operator==( other );
		}



		const ValueT& operator*() const
		{
			return mTargetNode->MyValue;
		}
		const ValueT* operator->() const
		{
			return std::addressof( *( *this ) ); // call : operator*()
		}



		const NodeT* mTargetNode;
	};



	template<typename Coordinate_T, typename Value_T>
	class GridNodeReverseIterator
	{
	public:
		using ValueT = Value_T;
		using NodeT = GridNode<Coordinate_T, ValueT>;



		GridNodeReverseIterator( NodeT* target_node ) : mTargetNode( target_node )
		{}



		GridNodeReverseIterator& operator++()
		{
			mTargetNode = mTargetNode->pPrev;
			return ( *this );
		}
		GridNodeReverseIterator operator++() const
		{
			return GridNodeReverseIterator{ mTargetNode->pPrev };
		}
		GridNodeReverseIterator& operator--()
		{
			mTargetNode = mTargetNode->pNext;
			return ( *this );
		}
		GridNodeReverseIterator operator--() const
		{
			return GridNodeReverseIterator{ mTargetNode->pNext };
		}



		bool operator==( const GridNodeReverseIterator& other ) const
		{
			return mTargetNode == other.mTargetNode;
		}
		bool operator!=( const GridNodeReverseIterator& other ) const
		{
			return !operator==( other );
		}



		ValueT& operator*() const
		{
			return mTargetNode->MyValue;
		}
		ValueT* operator->() const
		{
			return std::addressof( *( *this ) ); // call : operator*()
		}



		NodeT* mTargetNode;
	};



	template<typename Coordinate_T, typename Value_T>
	class GridNodeConstReverseIterator
	{
	public:
		using ValueT = Value_T;
		using NodeT = GridNode<Coordinate_T, ValueT>;



		GridNodeConstReverseIterator( const NodeT* target_node ) : mTargetNode( target_node )
		{}



		GridNodeConstReverseIterator& operator++()
		{
			mTargetNode = mTargetNode->pPrev;
			return ( *this );
		}
		GridNodeConstReverseIterator operator++() const
		{
			return GridNodeConstReverseIterator{ mTargetNode->pPrev };
		}
		GridNodeConstReverseIterator& operator--()
		{
			mTargetNode = mTargetNode->pNext;
			return ( *this );
		}
		GridNodeConstReverseIterator operator--() const
		{
			return GridNodeConstReverseIterator{ mTargetNode->pNext };
		}



		bool operator==( const GridNodeConstReverseIterator& other ) const
		{
			return mTargetNode == other.mTargetNode;
		}
		bool operator!=( const GridNodeConstReverseIterator& other ) const
		{
			return !operator==( other );
		}



		const ValueT& operator*() const
		{
			return mTargetNode->MyValue;
		}
		const ValueT* operator->() const
		{
			return std::addressof( *( *this ) ); // call : operator*()
		}



		const NodeT* mTargetNode;
	};
}