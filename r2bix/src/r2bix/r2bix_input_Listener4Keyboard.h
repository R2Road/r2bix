#pragma once

#include <functional>

#include "r2bix_input_ObservationKeyContainer.h"

namespace r2bix_input
{
	class Listener4Keyboard
	{
	public:
		using Callback4KeyStatusChangedT = std::function<bool( eKeyStatus )>;
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



		//
		//
		//
		void SetCallback4KeyStatusChanged( const r2bix_input::eKeyCode key_code, const Callback4KeyStatusChangedT& callback );



		//
		//
		//
		void UpdateKey( const int key_index, const bool key_flag );



	private:
		const int mOrder;

		ObservationKeyContainer mObservationKeyContainer;
		Container4KeyStatusChangedCallbackT mContainer4KeyStatusChangedCallback;
	};
}