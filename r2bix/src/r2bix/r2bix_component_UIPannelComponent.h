#pragma once

#include "r2_SizeInt.h"

#include "r2bix_component_Component.h"
#include "r2bix_input_Listener4Mouse.h"
#include "r2bix_ui_Constant.h"

namespace r2bix_ui
{
	class UIInputListener;
}

namespace r2bix_component
{
	class UIPannelComponent : public r2bix_component::Component<UIPannelComponent>
	{
	public:
		using Callback4CursorResponseT = std::function<void( r2bix_ui::eCursorStatus )>;
		using Callback4KeyResponseT = std::function<bool( int, r2bix_ui::eKeyStatus )>;

		using UIInputListenerContainer = std::list<r2bix_ui::UIInputListener*>;



		UIPannelComponent( r2bix_node::Node& owner_node );



		//
		//
		//
	private:
		bool InitProcess() override;
		void ActivateProcess() override;
		void DeactivateProcess() override;



		//
		//
		//
	public:
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
		r2bix_input::Listener4Mouse* const GetListener4Mouse()
		{
			return &mListener4Mouse;
		}
		const r2bix_input::Listener4Mouse* const GetListener4Mouse() const
		{
			return &mListener4Mouse;
		}
		
		

		//
		//
		//
		r2bix_ui::eCursorStatus GetState() const
		{
			return mCursorState;
		}



		//
		// Callback
		//
		void SetCursorResponseCallback( const Callback4CursorResponseT& callback )
		{
			mCursorResponseCallback = callback;
		}
		void SetCallback4KeyResponse( const Callback4KeyResponseT& callback )
		{
			mCallback4KeyResponse = callback;
		}



		//
		// UI Input Listener
		//
		void AddListener( r2bix_ui::UIInputListener* const listener );
		void RemoveListener( r2bix_ui::UIInputListener* const listener );
		void OnCursorResponse( const r2bix_input::CursorPoint cursor_point );



	private:
		r2::SizeInt mSize;

		r2bix_input::Listener4Mouse mListener4Mouse;
		Callback4CursorResponseT mCursorResponseCallback;
		Callback4KeyResponseT mCallback4KeyResponse;

		r2bix_ui::eCursorStatus mCursorState;
		r2bix_ui::eKeyStatus mKeyStatus;

		UIInputListenerContainer mUIInputListenerContainer;
	};
}