#pragma once

#include <functional>

#include "r2bix_input_ObservationKeyList.hpp"

namespace r2bix_input
{
	class Listener4Mouse
	{
	public:
		using Callback4CursorMovedT = std::function<bool( CursorPoint )>;
		using Callback4KeyStatusChangedT = std::function<bool( int, eKeyStep )>;



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

		const ObservationKeyList& GetObservationKeyList() const
		{
			return mObservationKeyList;
		}
		bool IsObservationKey( const r2bix_input::KeyCodeTypeT key_code ) const
		{
			return mObservationKeyList.IsObservationKey( key_code );
		}

		eKeyStep Get( const std::size_t key_index ) const
		{
			return mObservationKeyList[key_index].key_step;
		}
		bool IsPushed( const std::size_t key_index ) const
		{
			return ( eKeyStep::Push == mObservationKeyList[key_index].key_step );
		}
		bool IsRelease( const std::size_t key_index ) const
		{
			return ( eKeyStep::Release == mObservationKeyList[key_index].key_step );
		}
		bool HasInput( const std::size_t key_index ) const
		{
			return ( eKeyStep::None < mObservationKeyList[key_index].key_step );
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
		ObservationKeyList mObservationKeyList;
	};
}