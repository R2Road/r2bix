#pragma once

#include "r2_Vector2.h"

#include "r2bix_component_Component.h"

namespace r2bix_component
{
	class CustomTextureComponent;
	class TextureRenderComponent;

	class HollowRectComponent : public r2bix_component::Component<HollowRectComponent>
	{
	public:
		HollowRectComponent( r2bix::Director& director, r2bix_node::Node& owner_node );



		//
		//
		//
	public:
		CustomTextureComponent* const GetCustomTextureComponent() const
		{
			return mCustomTextureComponent;
		}
		TextureRenderComponent* const GetTextureRenderComponent() const
		{
			return mTextureRenderComponent;
		}

		void SetCustomTextureComponent( CustomTextureComponent* const custom_texture_component )
		{
			mCustomTextureComponent = custom_texture_component;
		}
		void SetTextureRenderComponent( TextureRenderComponent* const texture_render_component )
		{
			mTextureRenderComponent = texture_render_component;
		}



		//
		//
		//
		int GetWidth() const;
		int GetHeight() const;

		void Set( const uint32_t width, const uint32_t height, const char rect_char, const short rect_color, const char hollow_char, const short hollow_color );
		void Set( const uint32_t width, const uint32_t height, const char rect_char, const char hollow_char );
		void Set( const uint32_t width, const uint32_t height );
	private:
		void fillTexture( const uint32_t width, const uint32_t height, const char rect_char, const short rect_color, const char hollow_char, const short hollow_color );



	private:
		CustomTextureComponent* mCustomTextureComponent;
		TextureRenderComponent* mTextureRenderComponent;
	};
}