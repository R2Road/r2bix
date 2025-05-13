//
// # Version Rule
// - 1.0.0 : ��� ����
// - 0.1.0 : ����ڰ� �ڵ带 �ٲ� ������ ��ȭ
// - 0.0.1 : ������ ��ȭ
//
// # Last Update		: 2023.07.06 AM.08.27
// # Version			: 1.0.1
//

#pragma once

#include "r2_Assert.h"
#include "r2_GridBasedOnVector.h"
#include "r2_Node4GridIterator.h"

namespace r2
{
	//
	// FIFO
	//

	//
	// # �� ��Ȳ �м�
	// > �ʿ��� ����� Queue�� ���� ������ ��� �ذ� �ȴ�.
	//
	// # ���ϴ� ��
	// > index �� ���� ���� ������ �޸� ���� �Ҵ����� ���� ������ ������ �ʹ�.
	//
	// # �ذ�å
	// > 1. ����� �Ǿ��� Array ��� Grid �� �����.
	// > 2. Grid�� Cell�� ListNode ������� ���� ���� ���� �� �ְ� �Ѵ�.
	// > 3. Add �Լ��� �Ҹ��� �ش� �׸����� ListNode �� �����ͼ� �ܹ��� List�� ���´�.
	//

	template<typename Coordinate_T, typename Value_T>
	class LinkedQueueBasedOnGrid
	{
	public:
		using ValueT = Value_T;
		using NodeT = Node4Grid<Coordinate_T, ValueT>;

		using ContainerT = r2::GridBasedOnVector<Coordinate_T, NodeT>;
		using SizeT = typename r2::GridBasedOnVector<Coordinate_T, NodeT>::SizeT; // size, linear
		using CoordinateT = typename r2::GridBasedOnVector<Coordinate_T, NodeT>::CoordinateT; // x, y, width, height
		
		using IteratorT             = Node4GridIterator<Coordinate_T, ValueT>;
		using ConstIteratorT        = Node4GridConstIterator<Coordinate_T, ValueT>;
		using ReverseIteratorT      = Node4GridReverseIterator<Coordinate_T, ValueT>;
		using ConstReverseIteratorT = Node4GridConstReverseIterator<Coordinate_T, ValueT>;



		LinkedQueueBasedOnGrid() :
			mContainer( 1, 1 )
			, mEndNode()
			, mSize( 0u )
		{
			FiilCoordinate();

			mEndNode.pPrev = &mEndNode;
			mEndNode.pNext = &mEndNode;
		}
		explicit LinkedQueueBasedOnGrid( const CoordinateT width, const CoordinateT height ) :
			mContainer( width, height )
			, mEndNode()
			, mSize( 0u )
		{
			FiilCoordinate();

			mEndNode.pPrev = &mEndNode;
			mEndNode.pNext = &mEndNode;
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
		void Reset( const CoordinateT width, const CoordinateT height )
		{
			mContainer.Reset( width, height, NodeT{} );
			FiilCoordinate();

			mEndNode.pPrev = &mEndNode;
			mEndNode.pNext = &mEndNode;

			mSize = 0u;
		}
	private:
		void FiilCoordinate()
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
			return mContainer.GetSize();
		}
		SizeT Size() const
		{
			return mSize;
		}
		bool Empty() const
		{
			return ( &mEndNode == mEndNode.pNext );
		}



		//
		// Getter
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
			return mContainer.GetMaxX();
		}
		CoordinateT GetMaxY() const
		{
			return mContainer.GetMaxY();
		}



		//
		//
		//
		bool IsIn( const CoordinateT x, const CoordinateT y ) const
		{
			return mContainer.IsIn( x, y );
		}
		bool IsValid( const CoordinateT x, const CoordinateT y ) const
		{
			return ( nullptr != mContainer.Get( x, y ).pPrev );
		}



		//
		//
		//
		void Push( const CoordinateT x, const CoordinateT y, const ValueT& value )
		{
			R2ASSERT( nullptr == GetNode( x, y ).pPrev, "" );

			auto& node = mContainer.Get( x, y );
			node.MyValue = value;

			//
			// �� ����� ��, �� ����
			//
			node.pPrev = mEndNode.pPrev;
			node.pNext = &mEndNode;

			//
			// ���� ���� ���� �� ���� ��� ����
			//
			node.pPrev->pNext = &node;

			//
			// End Node �� �� ��� ����
			//
			mEndNode.pPrev = &node;

			//
			//
			//
			++mSize;

		}
		void Pop()
		{
			if( Empty() )
			{
				return;
			}

			//
			// ���� ��� ����
			//
			auto target_node = mEndNode.pNext;

			//
			// �� �Ӹ� ���� End Node ����
			//
			( target_node->pNext )->pPrev = &mEndNode;

			//
			// End Node �� �� �Ӹ� ��� ����
			//
			mEndNode.pNext = ( target_node->pNext );

			//
			// Clear
			//
			target_node->MyValue = ValueT{};
			target_node->pPrev = nullptr;
			target_node->pNext = nullptr;

			//
			//
			//
			--mSize;
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
		const NodeT& GetNode( const CoordinateT x, const CoordinateT y ) const
		{
			return mContainer.Get( x, y );
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
		const ValueT& GetValue( const CoordinateT x, const CoordinateT y ) const
		{
			return GetNode( x, y ).MyValue;
		}



	private:
		ContainerT mContainer;
		NodeT mEndNode;
		SizeT mSize;
	};
}