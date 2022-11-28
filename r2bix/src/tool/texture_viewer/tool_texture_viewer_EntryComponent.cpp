#include "tool_texture_viewer_EntryComponent.h"

namespace tool_texture_viewer
{
	EntryComponent::EntryComponent( r2bix_node::Node& owner_node ) : r2bix_component::Component<EntryComponent>( owner_node )
	{}

	void EntryComponent::Update( const float delta_time )
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
		//mDirector.Setup( p2048::CompanyScene::Create( mDirector ) );

		r2bix_component::iComponent::Update( delta_time );
	}
}