//
// # Version Rule
// - 1.0.0 : ��� ����
// - 0.1.0 : ����ڰ� �ڵ带 �ٲ� ������ ��ȭ
// - 0.0.1 : ������ ��ȭ
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
