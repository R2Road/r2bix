//
// # Version Rule
// - 1.0.0 : 사용 가능
// - 0.1.0 : 사용자가 코드를 바꿀 정도의 변화
// - 0.0.1 : 자잘한 변화
//
// # Last Update		: 2023.07.07 PM.07.21
// # Version			: 1.2.3
//

#pragma once

#include <array>

#include "r2_GridIndexConverter.h"
#include "r2_PointInt.h"

namespace r2
{
	template<typename Coordinate_T, typename Value_T, Coordinate_T GRID_WIDTH, Coordinate_T GRID_HEIGHT>
	class GridBasedOnArray
	{
	public:
		//
		// Base
		//
		using SizeT           = std::size_t; // size, linear
		using CoordinateT     = Coordinate_T; // x, y, width, height
		using IndexConverterT = r2::GridIndexConverter<CoordinateT, SizeT>;
		using PointT          = r2::Point<CoordinateT>;



		//
		//
		//
		const SizeT GRID_SIZE = GRID_WIDTH * GRID_HEIGHT;



		//
		// Value, Container
		//
		using CellT          = Value_T;
		using ContainerT     = std::array<CellT, GRID_WIDTH * GRID_HEIGHT>;
		using IteratorT      = typename ContainerT::iterator;
		using ConstIteratorT = typename ContainerT::const_iterator;



		//
		//
		//
		GridBasedOnArray() :
			  mContainer()
			, mIndexConverter( GRID_WIDTH, GRID_HEIGHT )
		{}

		GridBasedOnArray( const CellT& value ) :
			  mContainer()
			, mIndexConverter( GRID_WIDTH, GRID_HEIGHT )
		{
			mContainer.fill( value );
		}

		GridBasedOnArray( const std::initializer_list<CellT> data ) :
			  mContainer()
			, mIndexConverter( GRID_WIDTH, GRID_HEIGHT )
		{
			memcpy_s(
				  &mContainer[0]
				, mContainer.size() * sizeof( CellT )
				, &( *data.begin() )
				, ( data.size() > mContainer.size() ? mContainer.size() * sizeof( CellT ) : data.size() * sizeof( CellT ) )
			);
		}



		//
		// Iteration
		//
		ConstIteratorT begin() const
		{
			return mContainer.begin();
		}
		ConstIteratorT end() const
		{
			return mContainer.end();
		}
		IteratorT begin()
		{
			return mContainer.begin();
		}
		IteratorT end()
		{
			return mContainer.end();
		}



		//
		//
		//
		CoordinateT GetWidth() const
		{
			return GRID_WIDTH;
		}
		CoordinateT GetHeight() const
		{
			return GRID_HEIGHT;
		}
		SizeT GetSize() const
		{
			return GRID_SIZE;
		}
		CoordinateT GetMaxX() const
		{
			return GetWidth() - 1;
		}
		CoordinateT GetMaxY() const
		{
			return GetHeight() - 1;
		}



		//
		//
		//
		const IndexConverterT& GetIndexConverter() const
		{
			return mIndexConverter;
		}



		//
		//
		//
		bool IsIn( const SizeT linear_index ) const
		{
			return ( GetSize() > linear_index );
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
		void Reset()
		{
			mContainer.fill( CellT{} );
		}
		void Reset( const CellT& fill_data )
		{
			mContainer.fill( fill_data );
		}
		void Reset( const std::initializer_list<CellT> data )
		{
			Reset( CellT{} );
			memcpy_s(
				  &mContainer[0]
				, mContainer.size() * sizeof( CellT )
				, &( *data.begin() )
				, ( data.size() > mContainer.size() ? mContainer.size() * sizeof( CellT ) : data.size() * sizeof( CellT ) )
			);
		}



		//
		// Getter
		//
		CellT& Get( const SizeT linear_idx )
		{
#if defined( DEBUG ) || defined( _DEBUG )
			if( linear_idx >= mContainer.size() )
			{
				static CellT dummy;
				return dummy;
			}
#endif

			return mContainer[linear_idx];
		}
		CellT& Get( const CoordinateT x, const CoordinateT y )
		{
			return Get( mIndexConverter.To_Linear( x, y ) );
		}
		CellT& Get( const PointT& p )
		{
			return Get( mIndexConverter.To_Linear( p.GetX(), p.GetY() ) );
		}
		const CellT& Get( const SizeT linear_idx ) const
		{
#if defined( DEBUG ) || defined( _DEBUG )
			if( linear_idx >= mContainer.size() )
			{
				static CellT dummy;
				return dummy;
			}
#endif

			return mContainer[linear_idx];
		}
		const CellT& Get( const CoordinateT x, const CoordinateT y ) const
		{
			return Get( mIndexConverter.To_Linear( x, y ) );
		}
		const CellT& Get( const PointT& p ) const
		{
			return Get( mIndexConverter.To_Linear( p.GetX(), p.GetY() ) );
		}



		//
		// Setter
		//
		void Set( const SizeT linear_idx, const CellT& new_value )
		{
#if defined( DEBUG ) || defined( _DEBUG )
			if( linear_idx >= mContainer.size() )
			{
				return;
			}
#endif

			mContainer[linear_idx] = new_value;
		}
		void Set( const CoordinateT x, const CoordinateT y, const CellT& new_value )
		{
			Set(
				  mIndexConverter.To_Linear( x, y )
				, new_value
			);
		}
		void Set( const PointT& p, const CellT& new_value )
		{
			Set(
				  mIndexConverter.To_Linear( p.GetX(), p.GetY() )
				, new_value
			);
		}



	private:
		ContainerT mContainer;
		IndexConverterT mIndexConverter;
	};
}