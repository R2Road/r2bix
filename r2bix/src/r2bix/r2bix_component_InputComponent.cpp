#include "r2bix_component_InputComponent.h"

#include "r2bix_Director.h"
#include "r2bix_node_Node.h"

namespace r2bix_component
{
	InputComponent::InputComponent( r2bix_node::Node& owner_node ) : r2bix_component::Component<InputComponent>( owner_node )
		, mListener4Mouse()
	{}



	void InputComponent::ActivateProcess()
	{
		GetOwnerNode().GetDirector().GetInputManager().AddListener( &mListener4Mouse );
	}
	void InputComponent::DeactivateProcess()
	{
		GetOwnerNode().GetDirector().GetInputManager().RemoveListener( &mListener4Mouse );
	}
}