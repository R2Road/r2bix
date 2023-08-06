//
// # Version Rule
// - 1.0.0 : ��� ����
// - 0.1.0 : ����ڰ� �ڵ带 �ٲ� ������ ��ȭ
// - 0.0.1 : ������ ��ȭ
//
// # Last Update		: 2023.08.02 AM.03.52
// # Version			: 1.0.0
//

#pragma once

namespace r2
{
	template<class T1, class T2>
	struct is_same
	{
		static constexpr bool value = false;
	};

	template<class T>
	struct is_same<T, T>
	{
		static constexpr bool value = true;
	};

	template<class T1, class T2>
	constexpr bool is_same_v = is_same<T1, T2>::value;
}