#include "p2048_EntryScene.h"

#include "r2bix_Director.h"

#include "p2048_CompanyScene.h"

#include "p2048table_TextureFrameAnimationTable.h"
#include "p2048table_TextureTable.h"

namespace p2048
{
	class EntrySceneComponent : public r2bix_component::Component<EntrySceneComponent>
	{
	public:
		EntrySceneComponent( r2bix::Director& director, r2bix_node::Node& owner_node ) : r2bix_component::Component<EntrySceneComponent>( director, owner_node ) {}


		//
		// Override
		//
		void updateProcess( const float ) override
		{
			//
			// Load Resources
			//
			{
				p2048table::TextureTable::GetInstance().Load();
				p2048table::TextureFrameAnimationTable::GetInstance().Load();
			}

			//
			// Move 2 Company Scene
			//
			GetDirector().Setup( p2048::CompanyScene::Create( GetDirector() ) );
		}
	};

	r2bix_node::NodeUp EntryScene::Create( r2bix::Director& director )
	{
		r2bix_node::NodeUp ret( r2bix_node::Node::Create( director ) );
		if( ret )
		{
			ret->AddComponent<EntrySceneComponent>();
		}
		
		return ret;
	}
}