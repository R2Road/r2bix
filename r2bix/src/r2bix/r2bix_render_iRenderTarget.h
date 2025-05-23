#pragma once

#include <stdint.h>


#include "r2_RectInt.h"
#include "r2bix_ColorValue.h"
#include "r2bix_ColorMaskOption.h"

namespace r2bix_render
{
	class iRenderTarget
	{
	public:
		virtual void FillCharacterAll( const char c ) = 0;
		virtual void FillCharacter( const uint32_t x, const uint32_t y, const char c ) = 0;
		virtual void FillStringAll( const char* const str ) = 0;
		virtual void FillString( const char* const str ) = 0;
		virtual void FillColorAll( const r2bix::ColorValue color_value ) = 0;
		virtual void FillColor( const uint32_t x, const uint32_t y, const r2bix::ColorValue color_value ) = 0;
		virtual void FillColorWithMask( const uint32_t x, const uint32_t y, const r2bix::ColorValue color_value, const r2bix::ColorMaskOption color_mask_option ) = 0;
		virtual void BlendColor( const uint32_t x, const uint32_t y, const r2bix::ColorValue color_value ) = 0;

		virtual r2::RectInt GetRect() const = 0;
	};
}