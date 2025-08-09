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

#include "r2_ListBasedOnGrid.h"
#include "r2_NoneCopyable.h"
#include "r2tm/r2tm_WindowsUtility.h"

namespace r2helper
{
	class TMPrinter4ListBasedOnGrid_Char : private r2::NoneCopyable
	{
	private:
		TMPrinter4ListBasedOnGrid_Char() = delete;

	public:
		template<typename CleanerT>
		inline static void Print( short pivot_x, short pivot_y, const short offset_x, const short offset_y, uint16_t space_h, uint16_t space_v, const r2::ListBasedOnGrid<char, char, CleanerT>& container )
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
			for( char cy = 0; cy < container.GetHeight(); ++cy )
			{
				for( char cx = 0; cx < container.GetWidth(); ++cx )
				{
					if( nullptr != container.GetNode( cx, cy ).pNext )
					{
						r2tm::WindowsUtility::FillColor(
							{
									static_cast<short>( pivot_x + ( cx * space_h ) )
								,	static_cast<short>( pivot_y + ( cy * space_v ) )
							}
							, r2tm::WindowsUtility::eColor::BG_Blue | r2tm::WindowsUtility::eColor::FG_White
						);
						r2tm::WindowsUtility::FillCharacter(
							{
									static_cast<short>( pivot_x + ( cx * space_h ) )
								,	static_cast<short>( pivot_y + ( cy * space_v ) )
							}
							, container.GetNode( cx, cy ).MyValue
						);
					}
					else
					{
						r2tm::WindowsUtility::FillCharacter(
							{
									static_cast<short>( pivot_x + ( cx * space_h ) )
								,	static_cast<short>( pivot_y + ( cy * space_v ) )
							}
							, 'x'
						);
					}
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

		template<typename CleanerT>
		inline static void Print( const short offset_x, const short offset_y, uint16_t space_h, uint16_t space_v, const r2::ListBasedOnGrid<char, char, CleanerT>& container )
		{
			const auto pivot_point = r2tm::WindowsUtility::GetCursorPoint();
			Print( pivot_point.x, pivot_point.y, offset_x, offset_y, space_h, space_v, container );
		}

		template<typename CleanerT>
		inline static void Print( const short offset_x, const short offset_y, const r2::ListBasedOnGrid<char, char, CleanerT>& container )
		{
			Print( offset_x, offset_y, 2, 1, container );
		}

		template<typename CleanerT>
		inline static void Print( const r2::ListBasedOnGrid<char, char, CleanerT>& container )
		{
			Print( 0, 0, 2, 1, container );
		}
	};
}