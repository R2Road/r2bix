#pragma once

#include "base/r2base_Component.h"

#include "r2/r2_RectInt.h"
#include "render/r2render_Texture.h"

namespace r2component
{
	class TransformComponent;

	class TextRenderComponent : public r2base::Component
	{
	private:
		TextRenderComponent( r2base::Node& owner_node );

	public:
		static std::unique_ptr<TextRenderComponent> Create( r2base::Node& owner_node );

		//
		// Override
		//
		void Render( const r2render::Camera* const camera, r2render::iRenderTarget* const render_target, r2::PointInt offset ) override;

		//
		// Getter
		//
		r2::RectInt GetRect() const { return mRect; }
		const r2render::Texture& GetTexture() const { return mTexture; }

		//
		// Setter
		//
		void SetRect( const int x, const int y, const int width, const int height )
		{
			mRect.Set( x, y, width, height );
		}
		void SetString( const std::string_view str )
		{
			mTexture.Reset( str );
		}

	private:
		r2::RectInt mRect;
		r2render::Texture mTexture;
	};
}