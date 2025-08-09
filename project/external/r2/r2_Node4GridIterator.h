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

#include "r2_Node4Grid.h"

namespace r2
{
	template<typename Coordinate_T, typename Value_T>
	class Node4GridIterator
	{
	public:
		using ValueT = Value_T;
		using NodeT = Node4Grid<Coordinate_T, ValueT>;



		Node4GridIterator( NodeT* target_node ) : mTargetNode( target_node )
		{}



		Node4GridIterator& operator++()
		{
			mTargetNode = mTargetNode->pNext;
			return ( *this );
		}
		Node4GridIterator& operator--()
		{
			mTargetNode = mTargetNode->pPrev;
			return ( *this );
		}



		bool operator==( const Node4GridIterator& other ) const
		{
			return mTargetNode == other.mTargetNode;
		}
		bool operator!=( const Node4GridIterator& other ) const
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
	class Node4GridConstIterator
	{
	public:
		using ValueT = Value_T;
		using NodeT = Node4Grid<Coordinate_T, ValueT>;



		Node4GridConstIterator( const NodeT* target_node ) : mTargetNode( target_node )
		{}



		Node4GridConstIterator& operator++()
		{
			mTargetNode = mTargetNode->pNext;
			return ( *this );
		}
		Node4GridConstIterator& operator--()
		{
			mTargetNode = mTargetNode->pPrev;
			return ( *this );
		}



		bool operator==( const Node4GridConstIterator& other ) const
		{
			return mTargetNode == other.mTargetNode;
		}
		bool operator!=( const Node4GridConstIterator& other ) const
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
	class Node4GridReverseIterator
	{
	public:
		using ValueT = Value_T;
		using NodeT = Node4Grid<Coordinate_T, ValueT>;



		Node4GridReverseIterator( NodeT* target_node ) : mTargetNode( target_node )
		{}



		Node4GridReverseIterator& operator++()
		{
			mTargetNode = mTargetNode->pPrev;
			return ( *this );
		}
		Node4GridReverseIterator operator++() const
		{
			return Node4GridReverseIterator{ mTargetNode->pPrev };
		}
		Node4GridReverseIterator& operator--()
		{
			mTargetNode = mTargetNode->pNext;
			return ( *this );
		}
		Node4GridReverseIterator operator--() const
		{
			return Node4GridReverseIterator{ mTargetNode->pNext };
		}



		bool operator==( const Node4GridReverseIterator& other ) const
		{
			return mTargetNode == other.mTargetNode;
		}
		bool operator!=( const Node4GridReverseIterator& other ) const
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
	class Node4GridConstReverseIterator
	{
	public:
		using ValueT = Value_T;
		using NodeT = Node4Grid<Coordinate_T, ValueT>;



		Node4GridConstReverseIterator( const NodeT* target_node ) : mTargetNode( target_node )
		{}



		Node4GridConstReverseIterator& operator++()
		{
			mTargetNode = mTargetNode->pPrev;
			return ( *this );
		}
		Node4GridConstReverseIterator operator++() const
		{
			return Node4GridConstReverseIterator{ mTargetNode->pPrev };
		}
		Node4GridConstReverseIterator& operator--()
		{
			mTargetNode = mTargetNode->pNext;
			return ( *this );
		}
		Node4GridConstReverseIterator operator--() const
		{
			return Node4GridConstReverseIterator{ mTargetNode->pNext };
		}



		bool operator==( const Node4GridConstReverseIterator& other ) const
		{
			return mTargetNode == other.mTargetNode;
		}
		bool operator!=( const Node4GridConstReverseIterator& other ) const
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