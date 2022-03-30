#include "pch.h"
#include "p2048mini_StageViewComponent.h"

#include "component/r2component_LabelComponent.h"

namespace p2048mini
{
	StageViewComponent::StageViewComponent( r2base::Node& owner_node ) : r2base::Component( owner_node )
		, mStage( nullptr )
	{}

	std::unique_ptr<StageViewComponent> StageViewComponent::Create( r2base::Node& owner_node )
	{
		std::unique_ptr<StageViewComponent> ret( new ( std::nothrow ) StageViewComponent( owner_node ) );
		if( !ret || !ret->Init() )
		{
			ret.reset();
		}

		return ret;
	}

	void StageViewComponent::Setup( p2048mini::Stage* const stage )
	{
		mStage = stage;
	}
}