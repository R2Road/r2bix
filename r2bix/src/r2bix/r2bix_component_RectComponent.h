#pragma once

#include "r2_Vector2.h"

#include "r2bix_component_Component.h"

namespace r2bix_component
{
	class CustomTextureComponent;
	class TextureRenderComponent;

	class RectComponent : public r2bix_component::Component<RectComponent>
	{
	public:
		RectComponent( r2bix_node::Node& owner_node );



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

		void Set( const r2::Vector2& pivot, const uint32_t width, const uint32_t height, const char fill_char, const short fill_color );
		void Set( const r2::Vector2& pivot, const uint32_t width, const uint32_t height, const char fill_char );
		void Set( const r2::Vector2& pivot, const uint32_t width, const uint32_t height, const char* fill_str );
		void Set( const uint32_t width, const uint32_t height, const char fill_char );
		void Set( const uint32_t width, const uint32_t height, const char* fill_str );
		void Set( const uint32_t width, const uint32_t height );



	private:
		CustomTextureComponent* mCustomTextureComponent;
		TextureRenderComponent* mTextureRenderComponent;
	};
}