#pragma once

#include "base/r2base_Component.h"
#include "base/r2base_ComponentStaticID.h"

#include "r2/r2_RectInt.h"

namespace r2render
{
	class Texture;
}

namespace r2component
{
	class TextureRenderComponent : public r2base::Component
	{
	private:
		TextureRenderComponent( r2base::Node& owner_node );

	public:
		int GetStaticID() const override { return r2base::ComponentStaticID<TextureRenderComponent>::Get(); }
		static std::unique_ptr<TextureRenderComponent> Create( r2base::Node& owner_node );

		//
		// Override
		//
		void Render( const r2render::Camera* const camera, r2render::iRenderTarget* const render_target, r2::PointInt offset ) override;

		//
		// Getter
		//
		r2::RectInt GetRect() const
		{
			return mRect;
		}
		const r2render::Texture* const GetTexture() const
		{
			return mTexture;
		}

		//
		// Setter
		//
		void SetRect( const int x, const int y, const int width, const int height )
		{
			mRect.Set( x, y, width, height );
		}
		void SetTexture( const r2render::Texture* const texture )
		{
			mTexture = texture;
		}

	private:
		r2::RectInt mRect;
		const r2render::Texture* mTexture;
	};
}