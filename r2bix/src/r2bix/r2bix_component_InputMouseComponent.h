#pragma once

#include "r2bix_component_Component.h"

#include "r2bix_input_Listener4Mouse.h"

namespace r2bix_component
{
	class InputMouseComponent : public r2bix_component::Component<InputMouseComponent>
	{
	public:
		InputMouseComponent( r2bix_node::Node& owner_node );



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
		void SetMouseCursorCallback( const r2bix_input::Listener4Mouse::Callback4CursorMovedT& callback )
		{
			mListener4Mouse.SetCallback4CursorMoved( callback );
		}
		void SetMouseCallback( const r2bix_input::Listener4Mouse::Callback4KeyStatusChangedT& callback )
		{
			mListener4Mouse.SetCallback4KeyStatusChanged( callback );
		}
		void AddMouseObservationKey( const r2bix_input::eKeyCode key_code )
		{
			mListener4Mouse.AddObservationKey( key_code );
		}



	private:
		r2bix_input::Listener4Mouse mListener4Mouse;
	};
}