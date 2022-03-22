#pragma once

#include "base/r2base_Component.h"
#include "base/r2base_ComponentStaticID.h"

#include "render/r2render_Texture.h"

namespace r2component
{
	class PivotComponent : public r2base::Component
	{
	private:
		PivotComponent( r2base::Node& owner_node );

	public:
		int GetStaticID() const override { return r2base::ComponentStaticID<PivotComponent>::Get(); }
		static std::unique_ptr<PivotComponent> Create( r2base::Node& owner_node );

		//
		//
		//
		const r2render::Texture* const GetTexture() const { return &mTexture; }

	private:
		const r2render::Texture mTexture;
	};
}