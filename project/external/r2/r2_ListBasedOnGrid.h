//
// # Version Rule
// - 1.0.0 : 사용 가능
// - 0.1.0 : 사용자가 코드를 바꿀 정도의 변화
// - 0.0.1 : 자잘한 변화
//
// # Last Update		: 2023.07.07 PM.07.25
// # Version			: 1.4.2
//

#pragma once

#include "r2_Assert.h"
#include "r2_GridBasedOnVector.h"
#include "r2_Node4GridIterator.h"

namespace r2
{
	template<typename Coordinate_T, typename Value_T, typename NodeCleaner = Node4GridCleaner_StayValue<Coordinate_T, Value_T>>
	class ListBasedOnGrid
	{
	public:
		using MyT = ListBasedOnGrid<Coordinate_T, Value_T, NodeCleaner>;
		using ValueT = Value_T;
		using CleanerT = NodeCleaner;


		using NodeT = Node4Grid<Coordinate_T, ValueT>;
		using ContainerT = r2::GridBasedOnVector<Coordinate_T, NodeT>;
		using SizeT = typename ContainerT::SizeT; // size, linear
		using CoordinateT = typename ContainerT::CoordinateT; // x, y, width, height
		using PointT = typename ContainerT::PointT;


		using IteratorT             = Node4GridIterator<Coordinate_T, ValueT>;
		using ConstIteratorT        = Node4GridConstIterator<Coordinate_T, ValueT>;
		using ReverseIteratorT      = Node4GridReverseIterator<Coordinate_T, ValueT>;
		using ConstReverseIteratorT = Node4GridConstReverseIterator<Coordinate_T, ValueT>;



		ListBasedOnGrid() : mContainer(), mCleaner(), mEndNode(), mSize( 0u )
		{
			Reset();
		}
		explicit ListBasedOnGrid( const CoordinateT width, const CoordinateT height ) : mContainer( width, height ), mCleaner(), mEndNode(), mSize( 0u )
		{
			Reset();
		}
		explicit ListBasedOnGrid( const CoordinateT width, const CoordinateT height, const std::initializer_list<ValueT> data ) : mContainer( width, height ), mCleaner(), mEndNode(), mSize( 0u )
		{
			Reset();

			auto cur = mContainer.begin();
			if( mContainer.end() != cur )
			{
				for( const auto& d : data )
				{
					PushBack( cur->x, cur->y, d );

					++cur;
					if( mContainer.end() == cur )
					{
						break;
					}
				}
			}
		}



		//
		// Iteration
		//
		IteratorT begin()
		{
			return IteratorT( mEndNode.pNext );
		}
		IteratorT end()
		{
			return IteratorT( &mEndNode );
		}
		ConstIteratorT begin() const
		{
			return ConstIteratorT( mEndNode.pNext );
		}
		ConstIteratorT end() const
		{
			return ConstIteratorT( &mEndNode );
		}

		ReverseIteratorT rbegin()
		{
			return ReverseIteratorT( mEndNode.pPrev );
		}
		ReverseIteratorT rend()
		{
			return ReverseIteratorT( &mEndNode );
		}
		ConstReverseIteratorT rbegin() const
		{
			return ConstReverseIteratorT( mEndNode.pPrev );
		}
		ConstReverseIteratorT rend() const
		{
			return ConstReverseIteratorT( &mEndNode );
		}



		//
		//
		//
		void Reset()
		{
			mContainer.Reset( mContainer.GetWidth(), mContainer.GetHeight() );
			fiilCoordinate();

			mEndNode.pPrev = &mEndNode;
			mEndNode.pNext = &mEndNode;

			mSize = 0u;
		}
		void Reset( const CoordinateT width, const CoordinateT height )
		{
			mContainer.Reset( width, height );
			fiilCoordinate();

			mEndNode.pPrev = &mEndNode;
			mEndNode.pNext = &mEndNode;

			mSize = 0u;
		}
	private:
		void fiilCoordinate()
		{
			CoordinateT x = 0;
			CoordinateT y = 0;
			for( auto& i : mContainer )
			{
				i.x = x;
				i.y = y;

				++x;
				if( mContainer.GetWidth() <= x )
				{
					x = 0;
					++y;
				}
			}
		}



	public:
		//
		//
		//
		SizeT Capacity() const
		{
			return static_cast<SizeT>( mContainer.GetSize() );
		}
		SizeT Size() const
		{
			return mSize;
		}
		bool Empty() const
		{
			return ( 0u == mSize );
		}
		bool Full() const
		{
			return ( Capacity() == Size() );
		}



		//
		//
		//
		CoordinateT GetWidth() const
		{
			return mContainer.GetWidth();
		}
		CoordinateT GetHeight() const
		{
			return mContainer.GetHeight();
		}
		CoordinateT GetMaxX() const
		{
			return ( 0 == mContainer.GetWidth() ? 0 : mContainer.GetWidth() - 1 );
		}
		CoordinateT GetMaxY() const
		{
			return ( 0 == mContainer.GetHeight() ? 0 : mContainer.GetHeight() - 1 );
		}



		//
		//
		//
		bool IsIn( const SizeT linear_index ) const
		{
			return ( Capacity() > linear_index );
		}
		bool IsIn( const CoordinateT x, const CoordinateT y ) const
		{
			return ( 0 <= x && GetWidth() > x )
				&& ( 0 <= y && GetHeight() > y );
		}
		bool IsIn( const PointT& p ) const
		{
			return IsIn( p.GetX(), p.GetY() );
		}
		bool IsOut( const SizeT linear_index ) const
		{
			return !IsIn( linear_index );
		}
		bool IsOut( const CoordinateT x, const CoordinateT y ) const
		{
			return !IsIn( x, y );
		}
		bool IsOut( const PointT& p ) const
		{
			return !IsIn( p.GetX(), p.GetY() );
		}



		//
		//
		//
		void PushFront( const CoordinateT x, const CoordinateT y, const ValueT& value )
		{
			Insert( begin(), x, y, value );
		}
		void PushBack( const CoordinateT x, const CoordinateT y, const ValueT& value )
		{
			Insert( end(), x, y, value );
		}
		IteratorT Insert( IteratorT pivot, const CoordinateT x, const CoordinateT y, const ValueT& value )
		{
			R2ASSERT( nullptr == GetNode( x, y ).pPrev, "" );

			auto& node = mContainer.Get( x, y );
			node.MyValue = value;

			//
			// ### pivot 의 앞에 새 노드를 배치한다.
			//

			//
			// 새 노드의 전, 후 설정
			//
			node.pPrev = pivot.mTargetNode->pPrev;
			node.pNext = pivot.mTargetNode;

			//
			// 이전 노드와 새 노드 연결
			//
			node.pPrev->pNext = &node;

			//
			// Pivot Node 와 새 노드 연결
			//
			pivot.mTargetNode->pPrev = &node;

			//
			//
			//
			++mSize;

			return IteratorT( pivot.mTargetNode->pPrev );
		}
		void PopFront()
		{
			Erase( begin() );
		}
		void PopBack()
		{
			Erase( --end() );
		}
		IteratorT Erase( IteratorT target )
		{
			if( end() == target )
			{
				return end();
			}

			auto node = target;
			++node;

			//
			// 다음 노드와 이전 노드 연결
			//
			node.mTargetNode->pPrev = target.mTargetNode->pPrev;

			//
			// 이전 노드와 다음 노드 연결
			//
			target.mTargetNode->pPrev->pNext = node.mTargetNode;

			//
			// Clear
			//
			mCleaner( target.mTargetNode );

			//
			//
			//
			--mSize;

			return node;
		}
		IteratorT Erase( const CoordinateT x, const CoordinateT y )
		{
			R2ASSERT( nullptr != GetNode( x, y ).pPrev, "" );

			auto& node = GetNode( x, y );

			return Erase( IteratorT( &node ) );
		}



		//
		//
		//
		void Move( const CoordinateT x1, const CoordinateT y1, const CoordinateT x2, const CoordinateT y2 )
		{
			R2ASSERT( nullptr != GetNode( x1, y1 ).pPrev, "" );
			R2ASSERT( nullptr == GetNode( x2, y2 ).pPrev, "" );

			auto& node_1 = GetNode( x1, y1 );

			auto temp = node_1.MyValue;

			Erase( IteratorT( &node_1 ) );
			PushBack( x2, y2, temp );
		}



		//
		// Get Node
		//
		const NodeT& FrontNode() const
		{
			return *mEndNode.pNext;
		}
		const NodeT& BackNode() const
		{
			return *mEndNode.pPrev;
		}
		const NodeT& EndNode() const
		{
			return mEndNode;
		}
		NodeT& GetNode( const CoordinateT x, const CoordinateT y )
		{
			return mContainer.Get( x, y );
		}
		const NodeT& GetNode( const CoordinateT x, const CoordinateT y ) const
		{
			return const_cast<MyT*>( this )->GetNode( x, y );
		}



		//
		// Get Value
		//
		const ValueT& Front() const
		{
			return mEndNode.pNext->MyValue;
		}
		const ValueT& Back() const
		{
			return mEndNode.pPrev->MyValue;
		}
		ValueT& GetValue( const CoordinateT x, const CoordinateT y )
		{
			return mContainer.Get( x, y ).MyValue;
		}
		const ValueT& GetValue( const CoordinateT x, const CoordinateT y ) const
		{
			return const_cast<MyT*>( this )->GetValue( x, y );
		}



	private:
		ContainerT mContainer;
		CleanerT mCleaner;

		NodeT mEndNode;
		SizeT mSize;
	};
}