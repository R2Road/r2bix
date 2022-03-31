#pragma once

#include "base/r2base_Component.h"
#include "base/r2base_ComponentStaticID.h"

namespace p2048mini
{
	class Stage;

	class StageViewComponent : public r2base::Component
	{
	private:
		StageViewComponent( r2base::Node& owner_node );

	public:
		int GetStaticID() const override { return r2base::ComponentStaticID<StageViewComponent>::Get(); }
		static std::unique_ptr<StageViewComponent> Create( r2base::Node& owner_node );

		void Setup( p2048mini::Stage* const stage );

		//
		//
		//
		int32_t GetWidth() const { return mWidth; }
		int32_t GetHeight() const { return mHeight; }

	private:
		p2048mini::Stage* mStage;
		int32_t mWidth;
		int32_t mHeight;
	};
}