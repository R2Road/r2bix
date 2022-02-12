#pragma once

#include <memory>

namespace r2base
{
	enum class eTestEndAction; 

	class Director;

	using NodeUp = std::unique_ptr<class iNode>;
	class iNode
	{
	protected:
		iNode( Director& director ) : mDirector( director ) {}
	public:
		virtual ~iNode() {}

		virtual void ShowInformation() const = 0;
		virtual eTestEndAction Do() = 0;

	protected:
		Director& mDirector;
	};
}