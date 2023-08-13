#pragma once

#include <iomanip>

#include "r2tm/r2tm_ostream.h"

#include "r2bix_render_Texture.h"

namespace r2bix_render
{
	class Texture;
}

namespace r2bixhelper
{
	class STDPrinter4Texture
	{
	private:
		STDPrinter4Texture() = delete;



	public:
		inline static void DrawTextureColor( const r2bix_render::Texture& texture )
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

		inline static void DrawTextureDisuse( const r2bix_render::Texture& texture )
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
	};
}