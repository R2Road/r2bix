#include "pch.h"
#include "p2048mini_StageViewComponent.h"

#include "component/r2component_LabelComponent.h"
#include "component/r2component_TextureRenderComponent.h"

#include "p2048mini_NumberComponent.h"
#include "p2048mini_NumberNode.h"
#include "p2048mini_Stage.h"

namespace p2048mini
{
	StageViewComponent::StageViewComponent( r2base::Node& owner_node ) : r2base::Component( owner_node )
		, mStage( nullptr )
		, mWidth( 0u )
		, mHeight( 0u )
		, mLabelContainer()
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

	void StageViewComponent::Setup( const p2048mini::Stage* const stage )
	{
		mStage = stage;

		const uint32_t NUMBER_WIDTH = 8;
		const uint32_t NUMBER_HEIGHT = 3;
		const uint32_t SPACING_WIDTH = 1;
		const uint32_t SPACING_HEIGHT = 1;

		mWidth = ( mStage->GetWidth() * NUMBER_WIDTH ) + ( ( mStage->GetWidth() - 1 ) * SPACING_WIDTH );
		mHeight = ( mStage->GetHeight() * NUMBER_HEIGHT ) + ( ( mStage->GetHeight() - 1 ) * SPACING_HEIGHT );

		mLabelContainer.clear();
		mLabelContainer.reserve( mStage->GetWidth() * mStage->GetHeight() );
		for( uint32_t y = 0; mStage->GetHeight() > y; ++y )
		{
			for( uint32_t x = 0; mStage->GetWidth() > x; ++x )
			{
				auto node = mOwnerNode.AddChild<p2048mini::NumberNode>();

				auto number_component = node->GetComponent<p2048mini::NumberComponent>();
				number_component->SetNumber( 2048 );
				mLabelContainer.push_back( number_component );

				node->GetComponent<r2component::TransformComponent>()->SetPosition(
					4 + static_cast<int>( x * ( NUMBER_WIDTH + SPACING_WIDTH ) )
					, 1 + static_cast<int>( y * ( NUMBER_HEIGHT + SPACING_HEIGHT ) )
				);
			}
		}
	}

	void StageViewComponent::UpdateView()
	{
		uint32_t label_index = 0;
		for( const auto cell : *mStage )
		{
			mLabelContainer[label_index]->GetOwnerNode().SetVisible( ( 0 < cell.number ) );
			mLabelContainer[label_index]->SetNumber( cell.number );
			++label_index;
		}
	}
}