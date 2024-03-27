#pragma once

#include "r2bix_component_Component.h"
#include "r2bix_input_UIInputListener.h"

namespace r2bix_component
{
	class UIPannelComponent;

	class UIButtonComponent : public r2bix_component::Component<UIButtonComponent>
	{
	public:
		using Callback4CursorResponseT = r2bix_input::UIInputListener::Callback4CursorResponseT;
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
			return mUIInputListener.GetWidth();
		}
		int GetHeight() const
		{
			return mUIInputListener.GetHeight();
		}

		void SetSize( const uint32_t width, const uint32_t height )
		{
			mUIInputListener.SetSize( width, height );
		}



		//
		//
		//
		void SetCallback4CursorResponse( const Callback4CursorResponseT& callback );
		void SetCallback4KeyResponse( const r2bix_input::eKeyCode key_code, const Callback4KeyResponseT& callback );



	private:
		UIPannelComponent* mUIPannelComponent;
		r2bix_input::UIInputListener mUIInputListener;
	};
}