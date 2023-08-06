//
// # Version Rule
// - 1.0.0 : ��� ����
// - 0.1.0 : ����ڰ� �ڵ带 �ٲ� ������ ��ȭ
// - 0.0.1 : ������ ��ȭ
//
// # Last Update		: 2023.08.06 PM.03.40
// # Version			: 1.0.0
//

#pragma once

namespace r2
{
	class NoneCopyable
	{
	public:
		NoneCopyable() = default;

	private:
		// none copy
		NoneCopyable( const NoneCopyable& ) = delete;
		NoneCopyable( NoneCopyable&& ) = delete;
		NoneCopyable& operator=( const NoneCopyable& ) = delete;
		NoneCopyable& operator=( NoneCopyable&& ) = delete;
	};
}