#pragma once

#include "r2bix_component_Component.h"

#include "r2bix_input_Listener4Keyboard.h"

namespace r2bix_component
{
	class InputKeyboardComponent : public r2bix_component::Component<InputKeyboardComponent>
	{
	public:
		InputKeyboardComponent( r2bix::Director& director, r2bix_node::Node& owner_node );



		//
		// Override
		//
	private:
		void activateProcess() override;
		void deactivateProcess() override;



	public:
		void SetCallback( const r2bix_input::eKeyCode key_code, const r2bix_input::Listener4Keyboard::Callback4KeyStatusChangedT& callback )
		{
			mListener.SetCallback4KeyStatusChanged( key_code, callback );
		}



	private:
		r2bix_input::Listener4Keyboard mListener;
	};
}