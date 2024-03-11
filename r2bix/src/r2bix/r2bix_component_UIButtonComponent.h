#pragma once

#include "r2bix_component_Component.h"

namespace r2bix_component
{
	class CustomTextureComponent;
	class TextureRenderComponent;

	class UIButtonComponent : public r2bix_component::Component<UIButtonComponent>
	{
	public:
		UIButtonComponent( r2bix_node::Node& owner_node );

		//
		//
		//
		CustomTextureComponent* const GetCustomTextureComponent() const { return mCustomTextureComponent; }
		TextureRenderComponent* const GetTextureRenderComponent() const { return mTextureRenderComponent; }

		//
		// Setter
		//
		void SetCustomTextureComponent( CustomTextureComponent* const custom_texture_component )
		{
			mCustomTextureComponent = custom_texture_component;
		}
		void SetTextureRenderComponent(	TextureRenderComponent* const texture_render_component )
		{
			mTextureRenderComponent = texture_render_component;
		}

	private:
		CustomTextureComponent* mCustomTextureComponent;
		TextureRenderComponent* mTextureRenderComponent;
	};
}