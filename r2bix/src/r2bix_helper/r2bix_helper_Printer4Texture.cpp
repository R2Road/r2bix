#include "r2bix_helper_Printer4Texture.h"

#include <iomanip>

#include "r2tm/r2tm_ostream.h"
#include "r2tm/r2tm_WindowUtility.h"
#include "r2bix_render_TextureFrame.h"

namespace r2bix_helper
{
	r2tm::eColor Convert_R2bixForegroundColor_to_R2CMColor( r2bix::ColorValue color_value )
	{
		const auto fgc = r2bix::GetForegroundColor( color_value );

		switch( fgc )
		{
		case r2bix::eForegroundColor::FG_Black:			return r2tm::eColor::FG_Black;
		case r2bix::eForegroundColor::FG_Blue:			return r2tm::eColor::FG_Blue;
		case r2bix::eForegroundColor::FG_Green:			return r2tm::eColor::FG_Green;
		case r2bix::eForegroundColor::FG_Aqua:			return r2tm::eColor::FG_Aqua;
		case r2bix::eForegroundColor::FG_Red:			return r2tm::eColor::FG_Red;
		case r2bix::eForegroundColor::FG_Purple:		return r2tm::eColor::FG_Purple;
		case r2bix::eForegroundColor::FG_Yellow:		return r2tm::eColor::FG_Yellow;
		case r2bix::eForegroundColor::FG_White:			return r2tm::eColor::FG_White;
		case r2bix::eForegroundColor::FG_Gray:			return r2tm::eColor::FG_Gray;
		case r2bix::eForegroundColor::FG_LightBlue:		return r2tm::eColor::FG_LightBlue;
		case r2bix::eForegroundColor::FG_LightGreen:	return r2tm::eColor::FG_LightGreen;
		case r2bix::eForegroundColor::FG_LightAqua:		return r2tm::eColor::FG_LightAqua;
		case r2bix::eForegroundColor::FG_LightRed:		return r2tm::eColor::FG_LightRed;
		case r2bix::eForegroundColor::FG_LightPurple:	return r2tm::eColor::FG_LightPurple;
		case r2bix::eForegroundColor::FG_LightYellow:	return r2tm::eColor::FG_LightYellow;
		case r2bix::eForegroundColor::FG_BrightWhite:	return r2tm::eColor::FG_BrightWhite;
		}

		return r2tm::eColor::FG_White;
	}

	r2tm::eColor Convert_R2bixBackgroundColor_to_R2CMColor( r2bix::ColorValue color_value )
	{
		const auto bgc = r2bix::GetBackgroundColor( color_value );

		switch( bgc )
		{
		case r2bix::eBackgroundColor::BG_Black:			return r2tm::eColor::BG_Black;
		case r2bix::eBackgroundColor::BG_Blue:			return r2tm::eColor::BG_Blue;
		case r2bix::eBackgroundColor::BG_Green:			return r2tm::eColor::BG_Green;
		case r2bix::eBackgroundColor::BG_Aqua:			return r2tm::eColor::BG_Aqua;
		case r2bix::eBackgroundColor::BG_Red:			return r2tm::eColor::BG_Red;
		case r2bix::eBackgroundColor::BG_Purple:		return r2tm::eColor::BG_Purple;
		case r2bix::eBackgroundColor::BG_Yellow:		return r2tm::eColor::BG_Yellow;
		case r2bix::eBackgroundColor::BG_White:			return r2tm::eColor::BG_White;
		case r2bix::eBackgroundColor::BG_Gray:			return r2tm::eColor::BG_Gray;
		case r2bix::eBackgroundColor::BG_LightBlue:		return r2tm::eColor::BG_LightBlue;
		case r2bix::eBackgroundColor::BG_LightGreen:	return r2tm::eColor::BG_LightGreen;
		case r2bix::eBackgroundColor::BG_LightAqua:		return r2tm::eColor::BG_LightAqua;
		case r2bix::eBackgroundColor::BG_LightRed:		return r2tm::eColor::BG_LightRed;
		case r2bix::eBackgroundColor::BG_LightPurple:	return r2tm::eColor::BG_LightPurple;
		case r2bix::eBackgroundColor::BG_LightYellow:	return r2tm::eColor::BG_LightYellow;
		case r2bix::eBackgroundColor::BG_BrightWhite:	return r2tm::eColor::BG_BrightWhite;
		}

		return r2tm::eColor::FG_White;
	}

	void Printer4Texture::DrawTexture( const r2bix_render::Texture& texture )
	{
		const auto pivot_point = r2tm::WindowUtility::GetCursorPoint();

		for( int y = 0; y < texture.GetHeight(); ++y )
		{
			for( int x = 0; x < texture.GetWidth(); ++x )
			{
				r2tm::WindowUtility::FillCharacter( { static_cast<short>( pivot_point.x + x ), static_cast<short>( pivot_point.y + y ) }, texture.GetCharacter( x, y ) );
				r2tm::WindowUtility::FillColor( { static_cast<short>( pivot_point.x + x ), static_cast<short>( pivot_point.y + y ) }, texture.GetColor( x, y ) );
			}
		}

		r2tm::WindowUtility::MoveCursorPoint( { static_cast<short>( pivot_point.x ), static_cast<short>( pivot_point.y + texture.GetHeight() ) } );
	}
	void Printer4Texture::DrawTextureCharacter( const r2bix_render::Texture& texture )
	{
		const auto pivot_point = r2tm::WindowUtility::GetCursorPoint();

		for( int y = 0; y < texture.GetHeight(); ++y )
		{
			for( int x = 0; x < texture.GetWidth(); ++x )
			{
				r2tm::WindowUtility::FillCharacter( { static_cast<short>( pivot_point.x + x ), static_cast<short>( pivot_point.y + y ) }, texture.GetCharacter( x, y ) );
			}
		}

		r2tm::WindowUtility::MoveCursorPoint( { static_cast<short>( pivot_point.x ), static_cast<short>( pivot_point.y + texture.GetHeight() ) } );
	}
	void Printer4Texture::DrawTextureColor( const r2bix_render::Texture& texture )
	{
		std::size_t x = 0;
		for( const auto color : texture.GetColorContainer() )
		{
			std::cout << std::setw( 3 ) << color << " ";

			++x;
			if( texture.GetWidth() <= x )
			{
				x = 0u;
				LF();
			}
		}
		if( 0u != x )
		{
			LF();
		}
	}
	void Printer4Texture::DrawTextureDisuse( const r2bix_render::Texture& texture )
	{
		std::size_t x = 0;
		for( const auto disuse : texture.GetCharacterDisuseContainer() )
		{
			std::cout << std::setw( 3 ) << disuse << " ";

			++x;
			if( texture.GetWidth() <= x )
			{
				x = 0u;
				LF();
			}
		}
		if( 0u != x )
		{
			LF();
		}
	}

	void Printer4Texture::DrawTextureFrame( const r2bix_render::TextureFrame& frame )
	{
		const auto pivot_point = r2tm::WindowUtility::GetCursorPoint();

		for( int y = 0; y < frame.GetHeight(); ++y )
		{
			for( int x = 0; x < frame.GetWidth(); ++x )
			{
				r2tm::WindowUtility::FillCharacter( { static_cast<short>( pivot_point.x + x ), static_cast<short>( pivot_point.y + y ) }, frame.GetCharacter( x, y ) );
				r2tm::WindowUtility::FillColor( { static_cast<short>( pivot_point.x + x ), static_cast<short>( pivot_point.y + y ) }, frame.GetColor( x, y ) );
			}
		}

		r2tm::WindowUtility::MoveCursorPoint( { static_cast<short>( pivot_point.x ), static_cast<short>( pivot_point.y + frame.GetHeight() ) } );
	}
}