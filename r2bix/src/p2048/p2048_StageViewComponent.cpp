#include "p2048_StageViewComponent.h"

#include "r2_Assert.h"
#include "r2bix_component_CustomTextureComponent.h"
#include "r2bix_component_LabelSComponent.h"
#include "r2bix_component_TextureRenderComponent.h"

#include "p2048_NumberComponent.h"
#include "p2048_NumberNode.h"
#include "p2048_Stage.h"

namespace p2048
{
	StageViewComponent::StageViewComponent( r2bix::Director& director, r2bix_node::Node& owner_node ) : r2bix_component::Component<StageViewComponent>( director, owner_node )
		, mStage( nullptr )
		, mWidth( 0u )
		, mHeight( 0u )
		, mNumberComponentContainer()
		, mBackgroundNode( nullptr )
	{}

	void StageViewComponent::Setup( const p2048::Stage& stage )
	{
		if( !mNumberComponentContainer.empty() )
		{
			//
			// # 2022.05.06 by R
			//
			// 여러번 불려도 괜찮도록 코드를 갱신 하는 것이 맞지만 귀찮고 구현 목표에 맞지도 않는다.
			// 이후 r2base - Node 에 RemoveChild method가 추가된다면 구현 가능하다.
			// 다음 버전에서 추가될 예정이다.
			//
			R2ASSERT( false, "p2048 - StageViewComponent::Setup : Must be call once" );
			return;
		}

		mStage = &stage;

		const uint32_t NUMBER_WIDTH = 8;
		const uint32_t NUMBER_HEIGHT = 3;
		const uint32_t SPACING_WIDTH = 1;
		const uint32_t SPACING_HEIGHT = 1;

		mWidth = ( mStage->GetWidth() * NUMBER_WIDTH ) + ( ( mStage->GetWidth() - 1 ) * SPACING_WIDTH );
		mHeight = ( mStage->GetHeight() * NUMBER_HEIGHT ) + ( ( mStage->GetHeight() - 1 ) * SPACING_HEIGHT );

		mNumberComponentContainer.reserve( mStage->GetWidth() * mStage->GetHeight() );
		for( uint32_t y = 0; mStage->GetHeight() > y; ++y )
		{
			for( uint32_t x = 0; mStage->GetWidth() > x; ++x )
			{
				auto node = mOwnerNode.AddChild<p2048::NumberNode>();

				auto number_component = node->GetComponent<p2048::NumberComponent>();
				number_component->SetNumber( 2048, false, false );
				mNumberComponentContainer.push_back( number_component );

				node->GetComponent<r2bix_component::TransformComponent>()->SetPosition(
					4 + static_cast<int>( x * ( NUMBER_WIDTH + SPACING_WIDTH ) )
					, 1 + static_cast<int>( y * ( NUMBER_HEIGHT + SPACING_HEIGHT ) )
				);
			}
		}

		//
		// Background
		//
		R2ASSERT( nullptr != mBackgroundNode, "WTF" );
		mBackgroundNode->GetComponent<r2bix_component::CustomTextureComponent>()->GetTexture()->Reset( mWidth + 2u, mHeight + 2u, '=' );
		mBackgroundNode->GetComponent<r2bix_component::TextureRenderComponent>()->ResetVisibleRect();
	}

	void StageViewComponent::UpdateView()
	{
		uint32_t label_index = 0;
		for( const auto cell : *mStage )
		{
			mNumberComponentContainer[label_index]->GetOwnerNode().SetVisible( ( 0 < cell.number ) );
			mNumberComponentContainer[label_index]->SetNumber( cell.number, cell.merge_lock, cell.newcomer );
			++label_index;
		}
	}
}