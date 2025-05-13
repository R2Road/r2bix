#pragma once

namespace r2
{
	class Log
	{
	private:
		Log();

	public:
		static Log* GetInstance()
		{
			static Log instance;
			return &instance;
		}

		void Print( const char* format_string, ... );

	private:
		bool mActivate;
	};
}


//
// ON/OFF
//
#define R2LOG_ENABLE_LOG 1


//
// Output Targets
//
#define R2LOG_OUTPUT_TARGET_TYPE___TERMINAL 1
#define R2LOG_OUTPUT_TARGET_TYPE___VS_OUTPUT_WINDOW 2


//
// Select Output Target
//
#define R2LOG_OUTPUT_TARGET R2LOG_OUTPUT_TARGET_TYPE___VS_OUTPUT_WINDOW


//
// Process
//
#if defined( R2LOG_ENABLE_LOG ) && R2LOG_ENABLE_LOG == 1
	#define R2LOG( format, ... )      r2::Log::GetInstance()->Print( format, ##__VA_ARGS__ )
#else
	#define R2Log( ... )       do {} while ( 0 )
#endif


//
// 
//
#define R2LOG_FORCE( format, ... )      r2::Log::GetInstance()->Print( format, ##__VA_ARGS__ )
