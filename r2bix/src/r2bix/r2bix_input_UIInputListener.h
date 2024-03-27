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
		using ObservationKeyContainerT = std::vector<KeyValueT>;

		using Callback4CursorResponseT = std::function<bool( r2bix_input::CursorPoint )>;
		using Callback4KeyResponseT = std::function<bool( eKeyStatus )>;



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
		const ObservationKeyContainerT& GetObservationKeyContainer() const
		{
			return mObservationKeyContainer;
		}

		void SetCallback4CursorResponse( const Callback4CursorResponseT& callback );
		void SetCallback4KeyResponse( const Callback4KeyResponseT& callback );

		void AddObservationKey( const r2bix_input::eKeyCode key_code );

		bool OnCursorResponse( const r2bix_input::CursorPoint cursor_point );



	private:
		const int mOrder;

		r2::SizeInt mSize;

		bool mbCursorResponse;
		ObservationKeyContainerT mObservationKeyContainer;



		Callback4CursorResponseT mCursorResponseCallback;
		Callback4KeyResponseT mCallback4KeyResponse;
	};
}