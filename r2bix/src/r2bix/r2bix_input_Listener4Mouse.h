#pragma once

#include "r2bix_input_ObservationKeys.h"

namespace r2bix_input
{
	class Listener4Mouse
	{
	public:
		enum class eKeyStatus
		{
			None,
			Push,
			Pressed,
			Release,
		};



		Listener4Mouse();
		Listener4Mouse( const bool position_use, const bool left_click, const bool right_click );



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

		CursorPoint GetCursorPoint_Current() const
		{
			return mCursorPoint_Current;
		}
		CursorPoint GetCursorPoint_Last() const
		{
			return mCursorPoint_Last;
		}



		//
		//
		//
		void Update( const ObservationKeyStatesT& observation_key_states, const r2bix_input::CursorPoint cursor_point );



	private:
		bool mbMousePositionUse;
		r2bix_input::CursorPoint mCursorPoint_Current;
		r2bix_input::CursorPoint mCursorPoint_Last;

		ObservationKeys mObservationKeys;
		std::vector<eKeyStatus> mKeyStatusContainer;

	};
}