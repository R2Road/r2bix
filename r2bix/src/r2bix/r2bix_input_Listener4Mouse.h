#pragma once

#include <functional>

#include "r2bix_input_ObservationKeyContainer.h"

namespace r2bix_input
{
	class Listener4Mouse
	{
	public:
		using CursorMovedCallbackT = std::function<bool( CursorPoint )>;

		using Callback4KeyStatusChangedT = std::function<bool( eKeyStatus )>;
		using Container4KeyStatusChangedCallbackT = std::vector<Callback4KeyStatusChangedT>;



		Listener4Mouse();
		explicit Listener4Mouse( const int order );



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
		void SetCursorMovedCallback( const CursorMovedCallbackT& cursor_moved_callback );
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

		ObservationKeyContainer mObservationKeyContainer;

		CursorMovedCallbackT mCursorMovedCallback;
		Container4KeyStatusChangedCallbackT mContainer4KeyStatusChangedCallback;
	};
}