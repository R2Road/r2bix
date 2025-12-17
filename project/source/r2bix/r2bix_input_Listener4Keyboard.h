#pragma once

#include <functional>

#include "r2bix_input_ObservationKeyList.hpp"

namespace r2bix_input
{
	class Listener4Keyboard
	{
	public:
		using Callback4KeyStepChangedT = std::function<bool( eKeyStep )>;
		using Container4KeyStepChangedCallbackT = std::vector<Callback4KeyStepChangedT>;



		Listener4Keyboard();
		explicit Listener4Keyboard( const int order, const eListenMode mode );



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
		void SetCallback4KeyStepChanged( const r2bix_input::eKeyCode key_code, const Callback4KeyStepChangedT& callback );



		//
		//
		//
		void Listen( const r2bix_input::KeyCodeTypeT key_code, const bool key_signal_flag );



	private:
		const int mOrder;
		const eListenMode mMode;

		bool mbActivate;

		ObservationKeyList mObservationKeyList;
		Container4KeyStepChangedCallbackT mContainer4KeyStepChangedCallback;
	};
}