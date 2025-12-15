#pragma once

#include <functional>

#include "r2bix_input_ObservationKeyList.hpp"

namespace r2bix_input
{
	class Listener4Mouse
	{
	public:
		using Callback4CursorMovedT = std::function<bool( CursorPoint )>;
		using Callback4KeyStepChangedT = std::function<bool( int, eKeyStep )>;



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
		void SetCallback4KeyStepChanged( const Callback4KeyStepChangedT& callback );
		void AddObservationKey( const r2bix_input::eKeyCode key_code );



		//
		//
		//
		bool Listen4Cursor( const r2bix_input::CursorPoint cursor_point );
		bool Listen4Key( const int key_index, const r2bix_input::eKeyStep key_step );



	private:
		const int mOrder;

		bool mbActivate;

		Callback4CursorMovedT mCallback4CursorMoved;
		Callback4KeyStepChangedT mCallback4KeyStepChanged;
		ObservationKeyList mObservationKeyList;
	};
}