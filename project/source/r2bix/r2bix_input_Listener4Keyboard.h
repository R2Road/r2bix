#pragma once

#include <functional>

#include "r2bix_input_ObservationKeyList.hpp"

namespace r2bix_input
{
	class Listener4Keyboard
	{
	public:
		using Callback4KeyStatusChangedT = std::function<bool( eKeyStep )>;
		using Container4KeyStatusChangedCallbackT = std::vector<Callback4KeyStatusChangedT>;



		Listener4Keyboard();
		explicit Listener4Keyboard( const int order );



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
		void SetCallback4KeyStatusChanged( const r2bix_input::eKeyCode key_code, const Callback4KeyStatusChangedT& callback );



		//
		//
		//
		bool Listen( const r2bix_input::KeyCodeTypeT key_code, const r2bix_input::eKeyStep key_step );



	private:
		const int mOrder;

		bool mbActivate;

		ObservationKeyList mObservationKeyList;
		Container4KeyStatusChangedCallbackT mContainer4KeyStatusChangedCallback;
	};
}