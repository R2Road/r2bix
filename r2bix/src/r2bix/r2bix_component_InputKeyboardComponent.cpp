#include "r2bix_component_InputKeyboardComponent.h"

#include "r2bix_Director.h"
#include "r2bix_node_Node.h"

namespace r2bix_component
{
	InputKeyboardComponent::InputKeyboardComponent( r2bix::Director& director, r2bix_node::Node& owner_node ) : r2bix_component::Component<InputKeyboardComponent>( director, owner_node )
		, mListener()
	{}



	void InputKeyboardComponent::activateProcess()
	{
		GetOwnerNode().GetDirector().GetInputManager().AddListener( &mListener );
	}
	void InputKeyboardComponent::deactivateProcess()
	{
		GetOwnerNode().GetDirector().GetInputManager().RemoveListener( &mListener );
	}
}