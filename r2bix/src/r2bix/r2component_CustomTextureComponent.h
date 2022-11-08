#pragma once

#include "r2base_Component.h"

#include "r2render_Texture.h"

namespace r2bix_component
{
	class CustomTextureComponent : public r2bix_component::Component<CustomTextureComponent>
	{
	public:
		CustomTextureComponent( r2bix_node::Node& owner_node );

		//
		// Getter
		//
		const r2render::Texture* const GetTexture() const
		{
			return &mTexture;
		}
		r2render::Texture* const GetTexture()
		{
			return &mTexture;
		}

	private:
		r2render::Texture mTexture;
	};
}