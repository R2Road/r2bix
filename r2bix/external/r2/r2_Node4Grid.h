//
// # Version Rule
// - 1.0.0 : ��� ����
// - 0.1.0 : ����ڰ� �ڵ带 �ٲ� ������ ��ȭ
// - 0.0.1 : ������ ��ȭ
//
// # Last Update		: 2023.07.05 PM.04.39
// # Version			: 1.0.0
//

#pragma once

namespace r2
{
	template<typename Coordinate_T, typename Value_T>
	struct Node4Grid
	{
		using CoordinateT = Coordinate_T;
		using ValueT = Value_T;
		using MyT = Node4Grid<CoordinateT, ValueT>;

		ValueT MyValue = {};

		CoordinateT x = 0;
		CoordinateT y = 0;

		MyT* pPrev = nullptr;
		MyT* pNext = nullptr;
	};

	template<typename Coordinate_T, typename Value_T>
	class Node4GridCleaner_ClearValue
	{
	public:
		void operator()( Node4Grid<Coordinate_T, Value_T>* node )
		{
			node->pNext = nullptr;
			node->pPrev = nullptr;
			node->MyValue = {};
		}
	};

	template<typename Coordinate_T, typename Value_T>
	class Node4GridCleaner_StayValue
	{
	public:
		void operator()( Node4Grid<Coordinate_T, Value_T>* node )
		{
			node->pNext = nullptr;
			node->pPrev = nullptr;
		}
	};
}