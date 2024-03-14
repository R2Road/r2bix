#pragma once

#include <bitset>

#include "r2bix_input_ObservationKeys.h"

namespace r2bix_input
{
	class KeyboardInputListener
	{
	public:
		enum class eKeyStatus
		{
			None,
			Push,
			Pressed,
			Release,
		};



		KeyboardInputListener();
		KeyboardInputListener( std::initializer_list<uint8_t> list );



		//
		// Getter
		//
		const ObservationKeys& GetObservationKeys() const
		{
			return mObservationKeys;
		}

		eKeyStatus Get( const std::size_t key_index ) const
		{
			return mKeyStatusContainer[key_index];
		}
		bool IsPushed( const std::size_t key_index ) const
		{
			return ( eKeyStatus::Push == mKeyStatusContainer[key_index] );
		}
		bool IsRelease( const std::size_t key_index ) const
		{
			return ( eKeyStatus::Release == mKeyStatusContainer[key_index] );
		}
		bool HasInput( const std::size_t key_index ) const
		{
			return ( eKeyStatus::None < mKeyStatusContainer[key_index] );
		}



		//
		//
		//
		void Update( const std::bitset<255>& observation_key_states );



	private:
		ObservationKeys mObservationKeys;
		std::vector<eKeyStatus> mKeyStatusContainer;
	};
}