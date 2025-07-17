//
// # Version Rule
// - 1.0.0.0 : ��� ����
// - 0.1.0.0 : ��� �߰�/����
// - 0.0.1.0 : ��� ����/����
// - 0.0.0.1 : ������ ��ȭ
//
// # Last Update		: 2025.07.15 PM.03.50
// # Version			: 1.0.0.0
//

#pragma once

namespace r2
{
	class Degree
	{
	public:
		Degree() : mValue( 0.f )
		{}
		explicit Degree( const float new_value ) : mValue( new_value )
		{}

		Degree operator*( const float value ) const
		{
			return Degree( mValue * value );
		}

		float Get() const
		{
			return mValue;
		}
		void Set( const float new_value )
		{
			mValue = new_value;
		}

	private:
		float mValue;
	};
}