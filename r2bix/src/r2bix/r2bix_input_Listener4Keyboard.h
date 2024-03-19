#pragma once

#include "r2bix_input_ObservationKeyContainer.h"

namespace r2bix_input
{
	class Listener4Keyboard
	{
	public:
		Listener4Keyboard();
		explicit Listener4Keyboard( const int order, std::initializer_list<uint8_t> list );



		//
		// Getter
		//
		int GetOrder() const
		{
			return mOrder;
		}

		const ObservationKeyContainer& GetObservationKeyContainer() const
		{
			return mObservationKeyContainer;
		}

		eKeyStatus Get( const std::size_t key_index ) const
		{
			return mObservationKeyContainer[key_index].key_status;
		}
		bool IsPushed( const std::size_t key_index ) const
		{
			return ( eKeyStatus::Push == mObservationKeyContainer[key_index].key_status );
		}
		bool IsRelease( const std::size_t key_index ) const
		{
			return ( eKeyStatus::Release == mObservationKeyContainer[key_index].key_status );
		}
		bool HasInput( const std::size_t key_index ) const
		{
			return ( eKeyStatus::None < mObservationKeyContainer[key_index].key_status );
		}



		//
		//
		//
		void UpdateKey( const int key_index, const bool key_flag );



	private:
		const int mOrder;

		ObservationKeyContainer mObservationKeyContainer;
	};
}