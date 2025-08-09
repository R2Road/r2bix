#include "tool_texture_viewer_EntryComponent.h"

#include "r2bix_Director.h"
#include "r2bix_node_Node.h"

#include "tool_texture_viewer_ViewerScene.h"

namespace tool_texture_viewer
{
	EntryComponent::EntryComponent( r2bix::Director& director, r2bix_node::Node& owner_node ) : r2bix_component::Component<EntryComponent>( director, owner_node )
	{}

	void EntryComponent::updateProcess( const float delta_time )
	{
		//
		// Load Resources
		//
		{
			//p2048table::TextureTable::GetInstance().Load();
			//p2048table::TextureFrameAnimationTable::GetInstance().Load();
		}

		//
		// Move 2 Company Scene
		//
		GetDirector().Setup( ViewerScene::Create( GetDirector() ) );

		r2bix_component::iComponent::updateProcess( delta_time );
	}
}