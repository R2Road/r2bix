#pragma once

#include <functional>
#include <vector>

#include "r2_SizeInt.h"

#include "r2bix_input_Constant.h"
#include "r2bix_ui_Constant.h"

namespace r2bix_input
{
	class UIInputListener
	{
	public:
		using KeyValueT = KeyCodeTypeT;
		using KeyContainerT = std::vector<KeyValueT>;

		using CursorResponseCallbackT = std::function<bool( r2bix_ui::eCursorStatus )>;
		using Callback4KeyResponseT = std::function<bool( eKeyStatus )>;
		using Container4KeyStatusChangedCallbackT = std::vector<Callback4KeyResponseT>;



		UIInputListener();
		explicit UIInputListener( const int order );



		//
		//
		//
		int GetOrder() const
		{
			return mOrder;
		}



		//
		//
		//
		int GetWidth() const
		{
			return mSize.GetWidth();
		}
		int GetHeight() const
		{
			return mSize.GetHeight();
		}

		void SetSize( const uint32_t width, const uint32_t height )
		{
			mSize.Set( width, height );
		}



		//
		//
		//
		const KeyContainerT& GetObservationKeyContainer() const
		{
			return mObservationKeyContainer;
		}

		void SetCallback4CursorResponse( const CursorResponseCallbackT& callback );
		void SetCallback4KeyResponse( const r2bix_input::eKeyCode key_code, const Callback4KeyResponseT& callback );

		void OnCursorResponse( const r2bix_ui::eCursorStatus cursor_state );



	private:
		const int mOrder;

		r2::SizeInt mSize;

		bool mbCursorResponse;
		KeyContainerT mObservationKeyContainer;

		CursorResponseCallbackT mCursorResponseCallback;
		Container4KeyStatusChangedCallbackT mContainer4KeyStatusChangedCallback;
	};
}