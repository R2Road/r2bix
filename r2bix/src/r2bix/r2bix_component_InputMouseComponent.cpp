#include "r2bix_component_InputMouseComponent.h"

#include "r2bix_Director.h"
#include "r2bix_node_Node.h"

namespace r2bix_component
{
	InputMouseComponent::InputMouseComponent( r2bix::Director& director, r2bix_node::Node& owner_node ) : r2bix_component::Component<InputMouseComponent>( director, owner_node )
		, mListener4Mouse()
	{}



	void InputMouseComponent::activateProcess()
	{
		GetOwnerNode().GetDirector().GetInputManager().AddListener( &mListener4Mouse );
	}
	void InputMouseComponent::deactivateProcess()
	{
		GetOwnerNode().GetDirector().GetInputManager().RemoveListener( &mListener4Mouse );
	}
}