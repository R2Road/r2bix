//
// # Version Rule
// - 1.0.0.0 : ��� ����
// - 0.1.0.0 : ��� �߰�/����
// - 0.0.1.0 : ��� ����/����
// - 0.0.0.1 : ������ ��ȭ
//
// # Last Update		: 2025.07.15 PM.04.05
// # Version			: 1.0.0.0
//

#pragma once

namespace r2
{
	class Radian
	{
	public:
		Radian() : mValue( 0.f )
		{}
		explicit Radian( const float new_value ) : mValue( new_value )
		{}

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