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
		using Callback4KeyStatusChangedT = std::function<bool( eKeyStatus )>;



		Listener4Mouse();
		explicit Listener4Mouse( const int order );



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
		const std::vector<eKeyStatus>& GetKeyStatusContainer() const
		{
			return mKeyStatusContainer;
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
			if( cursor_moved_callback )
			{
				mbMousePositionUse = true;
			}
			else
			{
				mbMousePositionUse = false;
			}

			mCursorMovedCallback = cursor_moved_callback;
		}
		void SetKeyStatusChangedCallback( const r2bix_input::eKeyCode key_code, const Callback4KeyStatusChangedT& callback );



		//
		//
		//
		void UpdateCursor( const r2bix_input::CursorPoint cursor_point );
		void UpdateKey( const int key_index, const bool key_flag );



	private:
		const int mOrder;

		bool mbMousePositionUse;
		r2bix_input::CursorPoint mCursorPoint_Current;
		r2bix_input::CursorPoint mCursorPoint_Last;

		ObservationKeys mObservationKeys;
		std::vector<eKeyStatus> mKeyStatusContainer;

		CursorMovedCallbackT mCursorMovedCallback;
		Callback4KeyStatusChangedT mCallback4KeyStatusChanged;
	};
}