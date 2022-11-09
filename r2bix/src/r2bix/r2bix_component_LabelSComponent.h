#pragma once

#include <string>
#include <string_view>

#include "r2bix_component_Component.h"

#include "r2bix_ColorValue.h"
#include "r2bix_render_Texture.h"

namespace r2bix_render
{
	class Texture;
}

namespace r2bix_component
{
	class CustomTextureComponent;
	class TextureRenderComponent;

	class LabelSComponent : public r2bix_component::Component<LabelSComponent>
	{
	public:
		LabelSComponent( r2bix_node::Node& owner_node );

		//
		//
		//
		CustomTextureComponent* const GetCustomTextureComponent() const { return mCustomTextureComponent; }
		TextureRenderComponent* const GetTextureRenderComponent() const { return mTextureRenderComponent; }
		std::string_view GetString() const { return mText; }
		int32_t GetWidth() const { return static_cast<int32_t>( mText.length() ); }

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
		void SetString( const std::string_view str );
		void SetColor( const r2bix::ColorValue color_value );

	private:
		std::string mText;
		CustomTextureComponent* mCustomTextureComponent;
		TextureRenderComponent* mTextureRenderComponent;

		r2bix::ColorValue mColorValue;
	};
}