#pragma once

#include "r2_SizeInt.h"

#include "r2bix_component_Component.h"
#include "r2bix_input_Listener4Mouse.h"
#include "r2bix_ui_Constant.h"

namespace r2bix_input
{
	class UIInputListener;
}

namespace r2bix_component
{
	class UIPannelComponent : public r2bix_component::Component<UIPannelComponent>
	{
	public:
		using Callback4CursorResponseT = std::function<void( r2bix_ui::eCursorStatus )>;
		using UIInputListenerContainer = std::list<r2bix_input::UIInputListener*>;



		UIPannelComponent( r2bix_node::Node& owner_node );



		//
		//
		//
	private:
		void ActivateProcess() override;
		void DeactivateProcess() override;

		void Update( const float delta_time ) override final;



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
		void SetCursorResponseCallback( const Callback4CursorResponseT& callback )
		{
			mCursorResponseCallback = callback;
		}



		//
		//
		//
		r2bix_ui::eCursorStatus GetState() const
		{
			return mCursorState;
		}



		//
		// UI Input Listener
		//
		void AddListener( r2bix_input::UIInputListener* const listener );
		void RemoveListener( r2bix_input::UIInputListener* const listener );
		void OnCursorResponse( const r2bix_ui::eCursorStatus cursor_state );



	private:
		r2::SizeInt mSize;

		r2bix_input::Listener4Mouse mListener4Mouse;
		Callback4CursorResponseT mCursorResponseCallback;

		r2bix_ui::eCursorStatus mCursorState;

		UIInputListenerContainer mUIInputListenerContainer;
	};
}