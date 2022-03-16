#pragma once

#include <string>
#include <string_view>

#include "base/r2base_Component.h"
#include "base/r2base_ComponentStaticID.h"

#include "render/r2render_Texture.h"

namespace r2component
{
	class TextureRenderComponent;

	class LabelComponent : public r2base::Component
	{
	private:
		LabelComponent( r2base::Node& owner_node );

	public:
		int GetStaticID() const override { return r2base::ComponentStaticID<LabelComponent>::Get(); }
		static std::unique_ptr<LabelComponent> Create( r2base::Node& owner_node );

		//
		//
		//
		const r2render::Texture* const GetTexture() const { return &mTexture; }
		TextureRenderComponent* const GetTextureRenderComponent() const { return mTextureRenderComponent; }
		std::string_view GetString() const { return mText; }
		int32_t GetWidth() const { return static_cast<int32_t>( mText.length() ); }

		//
		// Setter
		//
		void SetTextureRenderComponent(	TextureRenderComponent* const texture_render_component )
		{
			mTextureRenderComponent = texture_render_component;
		}
		void SetString( const std::string_view str );
		void SetStringWithResize( const std::string_view str );

	private:
		std::string mText;
		r2render::Texture mTexture;
		TextureRenderComponent* mTextureRenderComponent;
	};
}