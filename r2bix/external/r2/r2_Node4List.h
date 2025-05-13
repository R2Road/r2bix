//
// # Version Rule
// - 1.0.0 : ��� ����
// - 0.1.0 : ����ڰ� �ڵ带 �ٲ� ������ ��ȭ
// - 0.0.1 : ������ ��ȭ
//
// # Last Update		: 2023.11.16 PM.00.22
// # Version			: 1.0.0
//

#pragma once

namespace r2
{
	template<typename T>
	struct Node4List
	{
		using ValueT = T;
		using MyT = Node4List<ValueT>;

		ValueT MyValue;
		MyT* pPrev = nullptr;
		MyT* pNext = nullptr;
	};

	template<typename T>
	class Node4ListCleaner_ClearValue
	{
	public:
		void operator()( Node4List<T>* node )
		{
			node->pNext = nullptr;
			node->pPrev = nullptr;
			node->MyValue = {};
		}
	};

	template<typename T>
	class Node4ListCleaner_StayValue
	{
	public:
		void operator()( Node4List<T>* node )
		{
			node->pNext = nullptr;
			node->pPrev = nullptr;
		}
	};
}