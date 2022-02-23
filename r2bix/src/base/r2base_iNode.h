#pragma once

#include <memory>

namespace r2base
{
	class Director;

	using NodeUp = std::unique_ptr<class iNode>;
	class iNode
	{
	protected:
		iNode( Director& director ) : mDirector( director ) {}
	public:
		virtual ~iNode() {}

	protected:
		virtual bool Init() = 0;
	public:
		virtual bool Update() = 0;

	protected:
		Director& mDirector;
	};
}