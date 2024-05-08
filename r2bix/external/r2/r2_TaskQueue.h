//
// # Version Rule
// - 1.0.0 : ��� ����
// - 0.1.0 : ����ڰ� �ڵ带 �ٲ� ������ ��ȭ
// - 0.0.1 : ������ ��ȭ
//
// # Last Update		: 2024.05.08 PM.03.38
// # Version			: 1.0.0
//

#pragma once

#include <functional>
#include <list>

namespace r2
{
	class TaskQueue
	{
	public:
		using Task = std::function<void()>;
		using ContainerT = std::list<Task>;
		using SizeT = typename ContainerT::size_type;



		TaskQueue();



		//
		// None Copy
		//
		TaskQueue( const TaskQueue& ) = delete;
		TaskQueue( TaskQueue&& ) = delete;
		TaskQueue& operator=( const TaskQueue& ) = delete;
		TaskQueue& operator=( TaskQueue&& ) = delete;



		void Add( const Task& task );



		void Update();



		SizeT Size() const
		{
			return mContainer.size();
		}
		bool Empty() const
		{
			return mContainer.empty();
		}



	private:
		ContainerT mContainer;
	};
}