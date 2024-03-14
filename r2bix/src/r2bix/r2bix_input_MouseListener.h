#pragma once

#include <bitset>

#include "r2bix_input_ObservationKeys.h"

namespace r2bix_input
{
	class MouseListener
	{
	public:
		enum class eKeyStatus
		{
			None,
			Push,
			Pressed,
			Release,
		};



		MouseListener();
		MouseListener( const bool position_use, const bool left_click, const bool right_click );



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
		bool mbMousePositionUse;
		ObservationKeys mObservationKeys;
		std::vector<eKeyStatus> mKeyStatusContainer;
	};
}