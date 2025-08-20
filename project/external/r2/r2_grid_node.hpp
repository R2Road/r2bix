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

namespace r2
{
	template<typename Coordinate_T, typename Value_T>
	struct GridNode
	{
		using CoordinateT = Coordinate_T;
		using ValueT = Value_T;
		using MyT = GridNode<CoordinateT, ValueT>;

		ValueT MyValue = {};

		CoordinateT x = 0;
		CoordinateT y = 0;

		MyT* pPrev = nullptr;
		MyT* pNext = nullptr;
	};

	template<typename Coordinate_T, typename Value_T>
	class GridNodeCleaner_ClearValue
	{
	public:
		void operator()( GridNode<Coordinate_T, Value_T>* node )
		{
			node->pNext = nullptr;
			node->pPrev = nullptr;
			node->MyValue = {};
		}
	};

	template<typename Coordinate_T, typename Value_T>
	class GridNodeCleaner_StayValue
	{
	public:
		void operator()( GridNode<Coordinate_T, Value_T>* node )
		{
			node->pNext = nullptr;
			node->pPrev = nullptr;
		}
	};
}