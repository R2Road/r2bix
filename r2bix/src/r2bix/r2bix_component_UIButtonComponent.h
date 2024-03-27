#pragma once

#include "r2_SizeInt.h"

#include "r2bix_component_Component.h"
#include "r2bix_input_UIInputListener.h"

namespace r2bix_component
{
	class UIPannelComponent;

	class UIButtonComponent : public r2bix_component::Component<UIButtonComponent>
	{
	public:
		using CursorResponseCallbackT = r2bix_input::UIInputListener::CursorResponseCallbackT;
		using Callback4KeyResponseT = r2bix_input::UIInputListener::Callback4KeyResponseT;



		UIButtonComponent( r2bix_node::Node& owner_node );


		//
		// Override
		//
	private:
		void EnterProcess() override;
		void ExitProcess() override;



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

		void SetSize( const uint32_t width, const uint32_t height );



		//
		//
		//
		void SetCallback4CursorResponse( const CursorResponseCallbackT& callback );
		void SetCallback4KeyResponse( const r2bix_input::eKeyCode key_code, const Callback4KeyResponseT& callback );



	private:
		r2::SizeInt mSize;

		UIPannelComponent* mUIPannelComponent;
		r2bix_input::UIInputListener mUIInputListener;
	};
}