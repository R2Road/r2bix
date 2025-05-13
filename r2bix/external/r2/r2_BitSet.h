//
// # Version Rule
// - 1.0.0 : 사용 가능
// - 0.1.0 : 사용자가 코드를 바꿀 정도의 변화
// - 0.0.1 : 자잘한 변화
//
// # Last Update		: 2023.08.31 AM.08.00
// # Version			: 1.0.0
//

#pragma once

#include <cstring>

#include "r2_Assert.h"
#include "r2_ArrayIterator.h"

namespace r2
{
	template<int REQUIRED_SIZE>
	class BitSet
	{
	public:
		static_assert( 0 < REQUIRED_SIZE );



		//
		// Base
		//
		using MyT = BitSet<REQUIRED_SIZE>;

		using SizeT = unsigned long long; // size
		using CoordinateT = unsigned int; // linear

	private:
		using ValueT = char;
		static constexpr SizeT UNIT_SIZE = sizeof( ValueT ) * 8;
		static constexpr ValueT UNIT_MASK = -1; // 0b11111111

		static constexpr SizeT BIT_COUNT = REQUIRED_SIZE;
		static constexpr SizeT BYTE_COUNT = ( ( REQUIRED_SIZE / UNIT_SIZE ) + ( ( REQUIRED_SIZE % UNIT_SIZE ) > 0 ? 1 : 0 ) );

		using ContainerT = ValueT[BYTE_COUNT];

	public:
		using IteratorT = r2::ArrayIterator<ValueT, BYTE_COUNT>;
		using ConstIteratorT = r2::ConstArrayIterator<ValueT, BYTE_COUNT>;



		//
		//
		//
		BitSet() : mContainer()
		{
			memset( mContainer, 0, BYTE_COUNT );
		}
		template<typename T>
		explicit BitSet( const T& bits ) : mContainer()
		{
			operator=( bits );
		}
		explicit BitSet( const ValueT* bits, const SizeT size ) : mContainer()
		{
			memcpy( mContainer, bits, ( BYTE_COUNT > size ? size : BYTE_COUNT ) );
		}



		//
		//
		//
		IteratorT begin()
		{
			return IteratorT( mContainer );
		}
		IteratorT end()
		{
			return IteratorT( mContainer, BYTE_COUNT );
		}
		ConstIteratorT begin() const
		{
			return ConstIteratorT( mContainer );
		}
		ConstIteratorT end() const
		{
			return ConstIteratorT( mContainer, BYTE_COUNT );
		}



		//
		//
		//
		template<typename T>
		void operator=( const T& bits )
		{
			//
			// 컨테이너 크기에 맞게 크기 제한
			//
			const SizeT byte_count = sizeof( bits ) > BYTE_COUNT ? BYTE_COUNT : sizeof( bits );
			const ValueT* byte_ptr = reinterpret_cast<const ValueT*>( &bits );

			//
			// Copy
			//
			for( SizeT b = 0; byte_count > b; ++b )
			{
				const ValueT temp = ( ( *( byte_ptr + b ) ) & UNIT_MASK );
				mContainer[b] = temp;
			}
		}



		//
		//
		//
		void SetBlock( const CoordinateT block, const ValueT& bits )
		{
			R2ASSERT( BYTE_COUNT > block, "" );

			mContainer[block] = bits;
		}



		//
		//
		//
		SizeT GetBitCount() const
		{
			return BIT_COUNT;
		}
		SizeT GetByteCount() const
		{
			return BYTE_COUNT;
		}
		ValueT GetBlock( const CoordinateT block ) const
		{
			R2ASSERT( BYTE_COUNT > block, "" );

			return mContainer[block];
		}
		bool Test( const CoordinateT coordinate ) const
		{
			const auto block = ( 0 == coordinate ? 0 : coordinate / UNIT_SIZE );
			const auto position = ( 0 == coordinate ? 0 : coordinate % UNIT_SIZE );

			return ( mContainer[block] & ( 1 << position ) );
		}



	private:
		ContainerT mContainer;
	};
}