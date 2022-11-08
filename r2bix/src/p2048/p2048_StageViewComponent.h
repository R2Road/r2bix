#pragma once

#include <vector>

#include "r2bix/r2bix_component_Component.h"
#include "r2bix/r2bix_component_ComponentStaticID.h"

namespace p2048
{
	class NumberComponent;
	class Stage;

	class StageViewComponent : public r2bix_component::Component<StageViewComponent>
	{
	public:
		StageViewComponent( r2bix_node::Node& owner_node );

		void Setup( const p2048::Stage& stage );
		void SetBackgroundNode( r2bix_node::Node* const background_node )
		{
			mBackgroundNode = background_node;
		}
		void UpdateView();

		//
		//
		//
		int32_t GetWidth() const { return mWidth; }
		int32_t GetHeight() const { return mHeight; }

	private:
		const p2048::Stage* mStage;
		int32_t mWidth;
		int32_t mHeight;
		std::vector<p2048::NumberComponent*> mNumberComponentContainer;

		r2bix_node::Node* mBackgroundNode;
	};
}