#pragma once

#include <functional>

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

		using CursorMovedCallbackT = std::function<bool( CursorPoint )>;



		Listener4Mouse();
		explicit Listener4Mouse( const int order, const bool position_use, const bool left_click, const bool right_click );



		//
		// Getter
		//
		int GetOrder() const
		{
			return mOrder;
		}

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
		void SetCursorMovedCallback( const CursorMovedCallbackT& cursor_moved_callback )
		{
			mCursorMovedCallback = cursor_moved_callback;
		}



		//
		//
		//
		void UpdateCursor( const r2bix_input::CursorPoint cursor_point );
		void Update( const ObservationKeyStatesT& observation_key_states );



	private:
		const int mOrder;

		bool mbMousePositionUse;
		r2bix_input::CursorPoint mCursorPoint_Current;
		r2bix_input::CursorPoint mCursorPoint_Last;

		ObservationKeys mObservationKeys;
		std::vector<eKeyStatus> mKeyStatusContainer;

		CursorMovedCallbackT mCursorMovedCallback;
	};
}