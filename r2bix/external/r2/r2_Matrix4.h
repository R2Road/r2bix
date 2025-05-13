#pragma once

// REF : https://learn.microsoft.com/en-us/windows/win32/api/directxmath/ns-directxmath-xmmatrix?source=recommendations

namespace r2
{
	struct Matrix4
	{
		float _11 = 0.f;
		float _12 = 0.f;
		float _13 = 0.f;
		float _14 = 0.f;

		float _21 = 0.f;
		float _22 = 0.f;
		float _23 = 0.f;
		float _24 = 0.f;

		float _31 = 0.f;
		float _32 = 0.f;
		float _33 = 0.f;
		float _34 = 0.f;

		float _41 = 0.f;
		float _42 = 0.f;
		float _43 = 0.f;
		float _44 = 0.f;
	};
}