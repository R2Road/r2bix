#pragma once

#include <functional>

#include "r2bix_input_ObservationKeyContainer.h"

namespace r2bix_input
{
	class Listener4Mouse
	{
	public:
		using Callback4CursorMovedT = std::function<bool( CursorPoint )>;
		using Callback4KeyStatusChangedT = std::function<bool( int, eKeyStatus )>;



		Listener4Mouse();
		explicit Listener4Mouse( const int order );



		//
		// Getter
		//
		int GetOrder() const
		{
			return mOrder;
		}

		bool IsActivated() const
		{
			return mbActivate;
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
		void SetActivate( const bool activate )
		{
			mbActivate = activate;
		}



		//
		//
		//
		void SetCallback4CursorMoved( const Callback4CursorMovedT& callback );
		void SetCallback4KeyStatusChanged( const Callback4KeyStatusChangedT& callback );
		void AddObservationKey( const r2bix_input::eKeyCode key_code );



		//
		//
		//
		bool UpdateCursor( const r2bix_input::CursorPoint cursor_point );
		bool UpdateKey( const int key_index, const bool key_flag );



	private:
		const int mOrder;

		bool mbActivate;

		bool mbMousePositionUse;
		r2bix_input::CursorPoint mCursorPoint_Current;
		r2bix_input::CursorPoint mCursorPoint_Last;

		Callback4CursorMovedT mCallback4CursorMoved;
		Callback4KeyStatusChangedT mCallback4KeyStatusChanged;
		ObservationKeyContainer mObservationKeyContainer;
	};
}