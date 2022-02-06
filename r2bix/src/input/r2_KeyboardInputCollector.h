#pragma once

namespace r2
{
	class KeyboardInputCollector
	{
	public:
		KeyboardInputCollector();

		//
		// Getter
		//
		bool IsPressed( const int key_code ) const;

		void Collect();

		bool mbPressed;
	};
}