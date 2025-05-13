//
// # Version Rule
// - 1.0.0 : 사용 가능
// - 0.1.0 : 사용자가 코드를 바꿀 정도의 변화
// - 0.0.1 : 자잘한 변화
//
// # Last Update		: 2023.08.03 PM.10.39
// # Version			: 1.0.0
//

#pragma once

//
// ON/OFF
//
#define R2_DEBUG_PROCESS_ENABLE 1

//
// Process
//
#if defined( R2_DEBUG_PROCESS_ENABLE ) && R2_DEBUG_PROCESS_ENABLE == 1

	#define	R2_DEBUG_PROCESS( condition )														\
	do {																						\
		{ condition; }																			\
	} while( false )

#else

	#define R2_DEBUG_PROCESS( ... )       do {} while ( 0 )

#endif
