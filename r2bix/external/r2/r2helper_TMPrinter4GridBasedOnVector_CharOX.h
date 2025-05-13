//
// # Version Rule
// - 1.0.0 : 사용 가능
// - 0.1.0 : 사용자가 코드를 바꿀 정도의 변화
// - 0.0.1 : 자잘한 변화
//
// # Last Update		: 2023.07.05 PM.04.39
// # Version			: 1.0.0
//

#pragma once

#include "r2_GridBasedOnVector.h"
#include "r2_NoneCopyable.h"

#include "r2tm/r2tm_WindowsUtility.h"

namespace r2helper
{
	class TMPrinter4GridBasedOnVector_CharOX : private r2::NoneCopyable
	{
	private:
		TMPrinter4GridBasedOnVector_CharOX() = delete;

	public:
		using ContainerT = r2::GridBasedOnVector<char, char>;

		inline static void Print( short pivot_x, short pivot_y, const short offset_x, const short offset_y, uint16_t space_h, uint16_t space_v, const ContainerT& container, const unsigned char o_color, const unsigned char x_color )
		{
			//
			//
			//
			pivot_x += offset_x;
			pivot_y += offset_y;

			//
			//
			//
			space_h = ( space_h > 0 ? space_h : 1 );
			space_v = ( space_v > 0 ? space_v : 1 );

			//
			// Draw
			//
			char temp = ' ';
			for( ContainerT::CoordinateT cy = 0; cy < container.GetHeight(); ++cy )
			{
				for( ContainerT::CoordinateT cx = 0; cx < container.GetWidth(); ++cx )
				{
					temp = container.Get( cx, cy );

					r2tm::WindowsUtility::FillCharacter(
						{
								static_cast<short>( pivot_x + ( cx * space_h ) )
							,	static_cast<short>( pivot_y + ( cy * space_v ) )
						}
						, temp
					);

					r2tm::WindowsUtility::FillColor(
						{
								static_cast<short>( pivot_x + ( cx * space_h ) )
							,	static_cast<short>( pivot_y + ( cy * space_v ) )
						}
						, (
							'o' == temp
							? o_color
							: x_color
						)
					);
				}
			}

			//
			// Move Cursor
			//
			r2tm::WindowsUtility::MoveCursorPoint( {
					0
				,	static_cast<short>( pivot_y + ( container.GetMaxY() * space_v ) + 1 )
			} );
		}

		inline static void Print( const short offset_x, const short offset_y, uint16_t space_h, uint16_t space_v, const ContainerT& container, const unsigned char o_color, const unsigned char x_color )
		{
			const auto pivot_point = r2tm::WindowsUtility::GetCursorPoint();
			Print( pivot_point.x, pivot_point.y, offset_x, offset_y, space_h, space_v, container, o_color, x_color );
		}
		inline static void Print( const short offset_x, const short offset_y, uint16_t space_h, uint16_t space_v, const ContainerT& container )
		{
			const auto pivot_point = r2tm::WindowsUtility::GetCursorPoint();
			Print( pivot_point.x, pivot_point.y, offset_x, offset_y, space_h, space_v, container, r2tm::WindowsUtility::FG_Gray, r2tm::WindowsUtility::FG_LightRed );
		}

		inline static void Print( const short offset_x, const short offset_y, const ContainerT& container, const unsigned char o_color, const unsigned char x_color )
		{
			Print( offset_x, offset_y, 2, 1, container, o_color, x_color );
		}
		inline static void Print( const short offset_x, const short offset_y, const ContainerT& container )
		{
			Print( offset_x, offset_y, 2, 1, container, r2tm::WindowsUtility::FG_Gray, r2tm::WindowsUtility::FG_LightRed );
		}

		inline static void Print( const ContainerT& container, const unsigned char o_color, const unsigned char x_color )
		{
			Print( 0, 0, 2, 1, container, o_color, x_color );
		}
		inline static void Print( const ContainerT& container )
		{
			Print( 0, 0, 2, 1, container, r2tm::WindowsUtility::FG_Gray, r2tm::WindowsUtility::FG_LightRed );
		}
	};
}