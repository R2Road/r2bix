#pragma once

#include "r2bix_component_Component.h"

#include "r2bix_input_Listener4Mouse.hpp"

namespace r2bix_component
{
	class InputMouseComponent : public r2bix_component::Component<InputMouseComponent>
	{
	public:
		InputMouseComponent( r2bix::Director& director, r2bix_node::Node& owner_node );



		//
		// Override
		//
	private:
		void activateProcess() override;
		void deactivateProcess() override;



	public:
		//
		// Mouse
		//
		void SetMouseCursorCallback( const r2bix_input::Listener4Mouse::Callback4CursorMovedT& callback )
		{
			mListener4Mouse.SetCallback4CursorMoved( callback );
		}
		void SetMouseCallback( const r2bix_input::eKeyCode key_code, const r2bix_input::Listener4Mouse::Callback4KeyStepChangedT& callback )
		{
			mListener4Mouse.SetCallback4KeyStepChanged( key_code, callback );
		}



	private:
		r2bix_input::Listener4Mouse mListener4Mouse;
	};
}