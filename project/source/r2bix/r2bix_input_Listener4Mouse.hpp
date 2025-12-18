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
		explicit Listener4Mouse( const int order, const eListenMode mode );



		//
		// Getter
		//
		int GetOrder() const
		{
			return mOrder;
		}
		const eListenMode GetListenMode() const
		{
			return mMode;
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
		void Listen4Cursor( const r2bix_input::CursorPoint cursor_point );
		void Listen4Key( const int key_index, const r2bix_input::eKeyStep key_step );



	private:
		const int mOrder;
		const eListenMode mMode;

		bool mbActivate;

		Callback4CursorMovedT mCallback4CursorMoved;
		Callback4KeyStepChangedT mCallback4KeyStepChanged;
		ObservationKeyList mObservationKeyList;
	};
}