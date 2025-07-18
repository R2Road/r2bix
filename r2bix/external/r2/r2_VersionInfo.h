#pragma once

namespace r2
{

	//
	// 2022.05.06 by R
	//
	// �������� �ʰ� ��̰� �۾��� �̾�� �� �ֵ��� ��� ����� ������ ��.
	//

	constexpr struct
	{

		const char* const String4NameSpaceRule =
					"## Name Space Rule ##"
			"\n"
			"\n"	"[   r2    ] ��� ������ �Լ��� ����"
			"\n"	"[r2utility] �Լ��θ� ����"
		;



		const char VersionNumber_1 = '0';
		const char VersionNumber_2 = '2';
		const char VersionNumber_3 = '6';
		const char VersionNumber_4 = '1';
		const char VersionNumber_5 = '0';

		const char* const String4VersionRule =
					"### Version Rule ###"
			"\n"
			"\n"	"> " "1.0.0.0.0"  " : "  "�ϼ�?"
			"\n"	"> " "0.1.0.0.0"  " : "  "Road �Ϸ�"
			"\n"	"> " "0.0.1.0.0"  " : "  "Road �۾� ��� 1�� �Ϸ�"
			"\n"	"> " "0.0.0.1.0"  " : "  "���� ����.���� ��� ����"
			"\n"	"> " "0.0.0.0.1"  " : "  "����ڰ� ���� ������ ���� �Ǵ� ��ȭ"
		;

		const char String4Version[16] = { 'r', '2', ' ', ':', ' ', 'v', VersionNumber_1, '.', VersionNumber_2, '.', VersionNumber_3, '.', VersionNumber_4, '.', VersionNumber_5, '\0' };




		const char* const String4Road2Version_0_3_0_0_0 =
			"### Road 2 Version 0.3.0.0.0 ###"
			"\n"

			"\n"	"[o] " "Update Helper  : r2helper::STDPrinter4Point : ��� ��� ����"
			"\n"	"[o] " "Update Helper  : r2helper::STDPrinter4Size : ��� ��� ����"
			"\n"	"[o] " "Update Helper  : r2helper::STDPrinter4Vector4 : ��� ��� ����"
			"\n"	"[o] " "Update Helper  : r2helper::STDPrinter4Vector3 : ��� ��� ����"
			"\n"	"[o] " "Update Helper  : r2helper::STDPrinter4Vector2 : ��� ��� ����"
			"\n"	"[o] " "Update struct  : Vector3 : �Լ� �߰� : length, normalize, dot, cross"
			"\n"	"[o] " "Add Struct     : Quaternion"
			"\n"	"[o] " "Add Helper     : r2helper::STDPrinter4Degree"
			"\n"	"[o] " "Add Helper     : r2helper::STDPrinter4Radian"
			"\n"	"[o] " "Add Class      : Degree"
			"\n"	"[o] " "Add Class      : Radian"
			"\n"
			"\n"	"----------------------------------"
			"\n"
			"\n"	"[ ] " "Vector2"
			"\n"
			"\n"	"----------------------------------"
			"\n"
			"\n"	"[ ] " "Crypto Machine"
		;

		const char* const String4Road2Version_0_2_0_0_0 =
			"### Road 2 Version 0.2.0.0.0 ###"
			"\n"
			"\n"	"[o] " "Add Method     : r2::Point : PlusX, PlusY, MinusX, MinusY"
			"\n"	"[o] " "Add Class      : r2::RectIterator"
			"\n"	"[o] " "Update Class   : r2::Point : Add Support Type - short, unsigned short"
			"\n"	"[o] " "Add Class      : r2::Signal, Slot"
			"\n"	"[o] " "Add Class      : r2::TaskQueue"
			"\n"	"[o] " "Add Class      : r2::Value"
			"\n"	"[o] " "Update Class   : r2::Value : Add Method - IsChanged"
			"\n"	"[o] " "Update Class   : r2::Value : Add Method - Minus"
			"\n"	"[o] " "Update Class   : r2::Value : Rename Method - Add > Plus"
			"\n"	"[o] " "Add Class      : r2::ValueAccumulator"
			"\n"	"[o] " "Update Class   : r2::Value : Remove Config - None Copy"
			"\n"	"[o] " "Update Class   : r2::ValueAccumulator : User Define Type ��� ����"
			"\n"	"[o] " "Update Class   : r2::Signal, Slot : std::function ó�� ���� �κп� () �ְ� ����"
			"\n"	"[o] " "ETC            : MS Code Analysis �Ѱ� ���� ����"
			"\n"	"[o] " "Update Class   : r2::Value : Rename Function - Clear > Init"
			"\n"	"[o] " "Update Class   : r2::Value : Add Function - Clean"
			"\n"	"[o] " "Update Class   : r2::Value : �� ���� ó��"
			"\n"	"[o] " "ETC            : MS Code Analysis ����"
			"\n"
			"\n"	"----------------------------------"
			"\n"
			"\n"	"[o] " "Vector4"
			"\n"	"[o] " "Matrix4"
			"\n"	"[o] " "Transform"
		;

		const char* const String4Road2Version_0_1_0_0 =
					"### Road 2 Version 0.1.0.0 ###"
			"\n"
			"\n"	"[o] " "Grid ��� �����̳ʿ� Template Parameter�� Coordinate Type �߰�"
			"\n"	"[o] " "GridIndexConverter �� Template �� �����ϰ�, Parameter�� Coordinate Type, Linear Type �߰�"
			"\n"	"[o] " "Add            : r2helper - STDPrinter4Direction8BitwiseLimited"
			"\n"	"[o] " "Add            : r2helper - STDPrinter4Direction8Sequential"
			"\n"	"[o] " "Update         : r2 - CountLimiter"
			"\n"	"[o] " "Add            : r2 - Counter"
			"\n"	"[o] " "Add            : r2helper - TMPrinter4RectGuide"
			"\n"	"[o] " "Add            : r2helper - TMPrinter4RectGuide_Color"
			"\n"	"[o] " "Update Method  : r2 - Rect - Distance"
			"\n"	"[o] " "Add Method     : r2 - Rect - GetMax, GetMid"
			"\n"	"[o] " "Add            : r2utility - Point2PointStraightLinePath"
			"\n"	"[o] " "Add Method     : r2 - Rect - Clamp"
		;

		const char* const String4Road2Version_0_0_9_0 =
					"### Road 2 Version 0.0.9.0 ###"
			"\n"
			"\n"	"[o] " "Update      : r2 - ListBasedOnGrid - Add Method : Full"
			"\n"	"[o] " "Refactoring : r2 - Size"
			"\n"	"[o] " "Remove      : r2 - PointFloat"
			"\n"	"[o] " "Update      : r2 - ListBasedOnGrid - Add Method : Full"
			"\n"	"[o] " "Update      : r2helper - TMPrinter4Rect - apply template"
			"\n"	"[o] " "Add         : r2helper - TMPrinter4Rect_Color"
			"\n"	"[o] " "Add         : r2helper - STDPrinter4Point"
			"\n"	"[o] " "Add         : r2helper - STDPrinter4Size"
			"\n"	"[o] " "Add         : r2helper - STDPrinter4PivotAndSize"
			"\n"	"[o] " "Add         : r2helper - STDPrinter4Vector2"
			"\n"	"[o] " "Add         : r2helper - STDPrinter4Vector3"
			"\n"	"[o] " "Add         : r2helper - STDPrinter4Range"
			"\n"	"[o] " "Add         : r2utility - STDFileUtility"
			"\n"	"[o] " "Add         : r2utility - CFileUtility"
		;

		const char* const String4Road2Version_0_0_8_0 =
					"### Road 2 Version 0.0.8.0 ###"
			"\n"
			"\n"	"[o] " "Remove : r2 - Point<float>"
			"\n"	"[o] " "Add : r2 - Direction4BitwiseState"
			"\n"	"[o] " "Add : r2 - Direction8BitwiseState"
			"\n"	"[o] " "Add : r2 - Direction8BitwiseLimitedState"
			"\n"	"[o] " "Refactoring : r2 - Direction8BitwiseLimited"
			"\n"	"[o] " "Add : r2 - Direction4BitwiseLimitedState"
			"\n"	"[o] " "Refactoring : r2 - Direction4BitwiseLimited"
			"\n"	"[o] " "Update : r2 - ListBasedOnGrid - Overload Method : Reset"
		;

		const char* const String4Road2Version_0_0_7_0 =
					"### Road 2 Version 0.0.7.0 ###"
			"\n"
			"\n"	"[o] " "Add : r2 - ValueWithHistory1AndCallback"
			"\n"	"[o] " "Add : r2 - Direction4SequentialState"
			"\n"	"[o] " "Add : r2 - Direction4Sequential"
			"\n"	"[o] " "Add : r2 - Direction8SequentialState"
			"\n"	"[o] " "Add : r2 - Direction8Sequential"
			"\n"
			"\n"	"----------------------------------"
			"\n"
			"\n"	"[o] " "Add : r2 - ArrayIterator"
			"\n"	"[o] " "Add : r2 - RemovePointer"
			"\n"	"[o] " "Add : r2 - BitSet"
			"\n"
			"\n"	"----------------------------------"
			"\n"
			"\n"	"[o] " "Update : r2 - ListBasedOnGrid - Overload Constructor, Overload Method : Erase"
		;

		const char* const String4Road2Version_0_0_6_0 =
					"### Road 2 Version 0.0.6.0 ###"
			"\n"
			"\n"	"[o] " "Node4GridConstIterator �߰�"
			"\n"	"[o] " "Node4GridConstReverseIterator �߰�"
			"\n"	"[o] " "ListBasedOnGrid �� Const Iterator ����"
			"\n"	"[o] " "Node4ListConstIterator �߰�"
			"\n"	"[o] " "Node4ListConstReverseIterator �߰�"
			"\n"	"[o] " "ListBasedOnArray �� Const Iterator ����"
			"\n"	"[o] " "ListBasedOnVector �� Const Iterator ����"
			"\n"	"[o] " "LinkedQueueBasedOnArray �� Const Iterator ����"
			"\n"	"[o] " "LinkedQueueBasedOnVector �� Const Iterator ����"
			"\n"	"[o] " "LinkedQueueBasedOnGrid �� Const Iterator ����"
		;

		const char* const String4Road2Version_0_0_5 =
					"### Road 2 Version 0.0.5.0 ###"
			"\n"
			"\n"	"[o] " "Linked List Based On Vector"
			"\n"	"[o] " "Linked Queue Based On Vector"
			"\n"	"[o] " "ListNode Allocator Based On Vector"
		;

		const char* const String4Road2Version_0_0_4_1 =
			"### Road 2 Version 0.0.4.1 ###"
			"\n"
			"\n"	"[o] " "Fix : GridIndexConverter"
		;

		const char* const String4Road2Version_0_0_4 =
					"### Road 2 Version 0.0.4 ###"
			"\n"
			"\n"	"[o] " "Linked List Based On Grid"
			"\n"	"[o] " "Grid Based On Array"
		;

		const char* const String4Road2Version_0_0_3 =
					"### Road 2 Version 0.0.3 ###"
			"\n"
			"\n"	"[o] " "Linked Queue Based On Array"
			"\n"	"[o] " "Linked Queue Based On Grid"
			"\n"	"[o] " "Grid : Test �ۼ�"
		;

		const char* const String4Road2Version_0_0_2 =
					"### Road 2 Version 0.0.2 ###"
			"\n"
			"\n"	"[o] " "Value with Tracking"
			"\n"	"[o] " "Value with Dirty"
			"\n"	"[o] " "Value with Dirty and Tracking"
		;

		const char* const String4Road2Version_0_0_1 =
					"### Road 2 Version 0.0.1 ###"
			"\n"
			"\n"	"[o] " "Index Enumerator"
		;

		const char* const String4Road2Version_0_0_0 =
					"### Road 2 Version 0.0.0 ###"
			"\n"
			"\n"	"[o] " "Make Project"
			"\n"	"[o] " "Cleanup"
		;



		const char* const String4Road2NextVersion = String4Road2Version_0_3_0_0_0;

	} VersionInfo;
}