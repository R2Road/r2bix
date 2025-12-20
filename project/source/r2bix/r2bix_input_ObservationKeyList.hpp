#pragma once

#include <vector>

#include "r2_assert.hpp"

#include "r2bix_input_KeyStatus.hpp"

namespace r2bix_input
{
	class ObservationKey
	{
	public:
		ObservationKey() : 
			  key_index( 0 )
			, key_code( 0 )
			, key_status()
		{}

		ObservationKey( const KeyIndexTypeT key_index, const KeyCodeTypeT key_code ) :
			  key_index( key_index )
			, key_code( key_code )
			, key_status()
		{}

		inline KeyIndexTypeT GetIndex() const
		{
			return key_index;
		}
		inline KeyCodeTypeT GetCode() const
		{
			return key_code;
		}
		inline bool GetChanged() const
		{
			return key_status.GetChanged();
		}
		inline r2bix_input::eKeyStep GetStep() const
		{
			return key_status.GetStep();
		}
		inline void Update( const bool signal_flag )
		{
			key_status.Update( signal_flag );
		}

	private:
		KeyIndexTypeT key_index;
		KeyCodeTypeT key_code;
		KeyStatus key_status;
	};

	class ObservationKeyList
	{
	public:
		using KeyCodeT = KeyCodeTypeT;

		using ValueT = ObservationKey;
		using ContainerT = std::vector<ValueT>;
		using ConstIteratorT= ContainerT::const_iterator;


		//
		//
		//
		ObservationKeyList() : mContainer()
		{}
		ObservationKeyList( std::initializer_list<uint8_t> list )
		{
			uint8_t i = 0;
			for( const auto key_code : list )
			{
				mContainer.push_back( { i, key_code } );
				++i;
			}
		}


		//
		//
		//
		ConstIteratorT begin() const
		{
			return mContainer.begin();
		}
		ConstIteratorT end() const
		{
			return mContainer.end();
		}


		//
		//
		//
		ObservationKey& operator[]( const std::size_t key_index )
		{
			return mContainer[key_index];
		}
		const ObservationKey& operator[]( const std::size_t key_index ) const
		{
			return mContainer[key_index];
		}


		//
		//
		//
		bool Empty() const
		{
			return mContainer.empty();
		}
		std::size_t Size() const
		{
			return mContainer.size();
		}


		//
		//
		//
		void Add( const KeyCodeT key_code )
		{
			for( const auto& k : mContainer )
			{
				if( k.GetCode() == key_code )
				{
					R2ASSERT( false, "ObservationKeyList::Add 동일한 키를 반복 등록 시도" );
					return;
				}
			}

			mContainer.push_back( ValueT{ static_cast<uint8_t>( mContainer.size() ), key_code } );
		}

		bool Has( const r2bix_input::KeyCodeTypeT key_code ) const
		{
			for( const auto& o : mContainer )
			{
				if( o.GetCode() == key_code )
				{
					return true;
				}
			}

			return false;
		}

		ValueT& GetByKeycode( const r2bix_input::KeyCodeTypeT key_code )
		{
			for( auto& o : mContainer )
			{
				if( o.GetCode() == key_code )
				{
					return o;
				}
			}

			static ValueT dummy;
			return dummy;
		}


	private:
		ContainerT mContainer;
	};
}