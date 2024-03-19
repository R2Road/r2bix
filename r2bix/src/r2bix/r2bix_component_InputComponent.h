#pragma once

#include "r2bix_component_Component.h"

#include "r2bix_input_Listener4Keyboard.h"
#include "r2bix_input_Listener4Mouse.h"

namespace r2bix_component
{
	class InputComponent : public r2bix_component::Component<InputComponent>
	{
	public:
		InputComponent( r2bix_node::Node& owner_node );



		//
		// Override
		//
	private:
		void ActivateProcess() override;
		void DeactivateProcess() override;



	public:
		//
		// Mouse
		//
		void SetMouseCursorCallback( const r2bix_input::Listener4Mouse::CursorMovedCallbackT& callback )
		{
			mListener4Mouse.SetCursorMovedCallback( callback );
		}
		void SetMouseCallback( const r2bix_input::eKeyCode key_code, const r2bix_input::Listener4Mouse::Callback4KeyStatusChangedT& callback )
		{
			mListener4Mouse.SetKeyStatusChangedCallback( key_code, callback );
		}

		void SetKeyboardCallback( const r2bix_input::eKeyCode key_code, const r2bix_input::Listener4Keyboard::Callback4KeyStatusChangedT& callback )
		{
			mListener4Keyboard.SetKeyStatusChangedCallback( key_code, callback );
		}



	private:
		r2bix_input::Listener4Mouse mListener4Mouse;
		r2bix_input::Listener4Keyboard mListener4Keyboard;
	};
}