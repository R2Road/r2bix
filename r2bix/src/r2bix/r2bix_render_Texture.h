#pragma once

#include <string_view>
#include <vector>

#include "r2bix_ColorValue.h"
#include "r2bix_render_iRenderTarget.h"

#include "r2_GridIndexConverter.h"
#include "r2_RectInt.h"

namespace r2bix_render
{
	class Texture : public iRenderTarget
	{
	public:
		using ValueT = char;
		using ContainerT = std::vector<ValueT>;
		using ConstIteratorT = typename ContainerT::const_iterator;

		using ColorContainerT = std::vector<r2bix::ColorValue>;

		using DisuseContainerT = std::vector<bool>;



		explicit Texture( const std::string_view str );
		explicit Texture( const uint32_t width, const std::string_view str );
		explicit Texture( const uint32_t width, const uint32_t height );
		explicit Texture( const uint32_t width, const uint32_t height, const char fill_char );
		explicit Texture( const uint32_t width, const uint32_t height, const char fill_char, const r2bix::ColorValue color_value );
		explicit Texture( const uint32_t width, const uint32_t height, const std::string_view str );
		explicit Texture( const uint32_t width, const uint32_t height, const char fill_char, const std::string_view str );



		//
		// Iteration
		//
		ConstIteratorT begin() const
		{
			return mChars.begin();
		}
		ConstIteratorT end() const
		{
			return mChars.end();
		}



		//
		// Getter
		//
		int GetWidth() const
		{
			return mGridIndexConverter.GetWidth();
		}
		int GetHeight() const
		{
			return mGridIndexConverter.GetHeight();
		}

		int GetXEnd() const
		{
			return mGridIndexConverter.GetWidth() - 1;
		}
		int GetYEnd() const
		{
			return mGridIndexConverter.GetHeight() - 1;
		}

		int GetLength() const
		{
			return static_cast<int>( mChars.size() );
		}

		const ContainerT& GetCharacterContainer() const
		{
			return mChars;
		}
		ValueT GetCharacter( const uint32_t x, const uint32_t y ) const;
		std::string_view GetCharacterLine( const uint32_t y ) const;

		const ColorContainerT& GetColorContainer() const
		{
			return mColors;
		}
		r2bix::ColorValue GetColor( const uint32_t x, const uint32_t y ) const;
		const r2bix::ColorValue* GetColorLine( const uint32_t y ) const;

		const DisuseContainerT& GetCharacterDisuseContainer() const
		{
			return mCharDisuses;
		}
		bool GetCharacterDisuse( const uint32_t x, const uint32_t y ) const;



		//
		//
		//
		void Reset( const std::string_view str );

		void Reset( const uint32_t width, const std::string_view str );
		void Reset( const uint32_t width, const std::string_view str, const r2bix::ColorValue color_value );

		void Reset( const uint32_t width, const uint32_t height );
		void Reset( const uint32_t width, const uint32_t height, const char fill_char );
		void Reset( const uint32_t width, const uint32_t height, const char fill_char, const r2bix::ColorValue color_value );



		//
		// Override
		//
		void FillCharacterAll( const char c ) override;
		void FillCharacter( const uint32_t x, const uint32_t y, const char c ) override;
		void FillStringAll( const char* const str ) override;
		void FillString( const char* const str ) override;
		void FillColorAll( const r2bix::ColorValue color_value ) override;
		void FillColor( const uint32_t x, const uint32_t y, const r2bix::ColorValue color_value ) override;
		void FillColorWithMask( const uint32_t x, const uint32_t y, const r2bix::ColorValue color_value, const r2bix::ColorMaskOption color_mask_option ) override;
		void BlendColor( const uint32_t x, const uint32_t y, const r2bix::ColorValue color_value ) override;
		r2::RectInt GetRect() const override
		{
			return r2::RectInt( 0, 0, GetWidth(), GetHeight() );
		};



		//
		//
		//
		void FillCharacterDisuse( const uint32_t x, const uint32_t y, const bool disuse );



	private:
		r2::GridIndexConverter<int, int> mGridIndexConverter;
		ContainerT mChars;
		ColorContainerT mColors;
		DisuseContainerT mCharDisuses;
	};
}