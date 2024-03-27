#pragma once

#include <vector>

#include "r2_Assert.h"
#include "r2bix_input_Constant.h"

namespace r2bix_input
{
	class ObservationKeyContainer
	{
	public:
		using KeyValueT = KeyCodeTypeT;
		using ContainerT = std::vector<ObservationKey>;
		using ConstIteratorT= ContainerT::const_iterator;


		//
		//
		//
		ObservationKeyContainer() : mContainer()
		{}
		ObservationKeyContainer( std::initializer_list<uint8_t> list )
		{
			for( const auto key_code : list )
			{
				mContainer.push_back( { key_code } );
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
		std::size_t Size() const
		{
			return mContainer.size();
		}


		//
		//
		//
		void Add( const KeyValueT key_value )
		{
			for( const auto& k : mContainer )
			{
				if( k.key_code == key_value )
				{
					R2ASSERT( false, "ObservationKeyContainer::Add 동일한 키를 반복 등록 시도" );
					return;
				}
			}

			mContainer.push_back( { key_value } );
		}


	private:
		ContainerT mContainer;
	};
}