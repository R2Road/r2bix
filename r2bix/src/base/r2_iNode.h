#pragma once

#include <memory>

namespace r2
{
	enum class eTestEndAction; 

	class Director;

	using NodeUp = std::unique_ptr<class iNode>;
	class iNode
	{
	protected:
		iNode( Director& director ) : mDirector( director )
		{}

	public:
		virtual void ShowInformation() const = 0;
		virtual eTestEndAction Do( const int key_code ) = 0;

	protected:
		Director& mDirector;
	};
}