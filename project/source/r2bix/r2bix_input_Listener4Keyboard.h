#pragma once

#include <functional>

#include "r2bix_input_ObservationKeyList.hpp"

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

		bool IsActivated() const
		{
			return mbActivate;
		}

		const ObservationKeyList& GetObservationKeyList() const
		{
			return mObservationKeyList;
		}

		eKeyStatus Get( const std::size_t key_index ) const
		{
			return mObservationKeyList[key_index].key_status;
		}
		bool IsPushed( const std::size_t key_index ) const
		{
			return ( eKeyStatus::Push == mObservationKeyList[key_index].key_status );
		}
		bool IsRelease( const std::size_t key_index ) const
		{
			return ( eKeyStatus::Release == mObservationKeyList[key_index].key_status );
		}
		bool HasInput( const std::size_t key_index ) const
		{
			return ( eKeyStatus::None < mObservationKeyList[key_index].key_status );
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
		bool UpdateKey( const r2bix_input::KeyCodeTypeT key_code, const bool key_flag );



	private:
		const int mOrder;

		bool mbActivate;

		ObservationKeyList mObservationKeyList;
		Container4KeyStatusChangedCallbackT mContainer4KeyStatusChangedCallback;
	};
}