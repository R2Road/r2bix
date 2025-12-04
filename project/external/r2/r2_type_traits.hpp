//
// # Version Rule
// - 1.0.0 : 사용 가능
// - 0.1.0 : 사용자가 코드를 바꿀 정도의 변화
// - 0.0.1 : 자잘한 변화
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

namespace r2
{
	template<class T>
	struct is_const
	{
		static constexpr bool value = false;
	};

	template<class T>
	struct is_const<const T>
	{
		static constexpr bool value = true;
	};

	template<class T>
	constexpr bool is_const_v = is_const<T>::value;
}

namespace r2
{
	template<typename Func_T>
	struct func_type;

	template<typename Ret_T, typename ... Args_T>
	struct func_type<Ret_T( Args_T ... )>
	{
		using RetT = Ret_T;
		using MemberPointerT = RetT(*)( Args_T ... );
	};

	template<typename Owner_T, typename Ret_T, typename ... Args_T>
	struct func_type<Ret_T( Owner_T::* )( Args_T ... )>
	{
		using OwnerT = Owner_T;
		using RetT = Ret_T;
		using MemberPointerT = RetT( OwnerT::* )( Args_T ... );
	};
}