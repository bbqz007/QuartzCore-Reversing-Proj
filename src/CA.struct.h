/**
MIT License
Copyright (c) 2016 bbqz007 <https://github.com/bbqz007, http://www.cnblogs.com/bbqzsl>
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#pragma once
#ifndef _CA_struct__H_
#define _CA_struct__H_

#include "typedefs.h"
#include "CA.oc.h"
#include "CA.ops.h"

enum CATransactionPhase {};

struct CABackingStoreBuffer;
struct CABackingStore
{
	pthread_mutex_t _10;
	pthread_cond_t _50;
	int64_t _80;					// width
	int64_t _88;					// height
	CGColorSpace* _90;
	CABackingStoreBuffer* _138;
	void* _150;						// ?? CGSBoundingShape*
	CGSRegionObject* _158;
	uintptr_t _160;
	pthread_t _168;
	uint32_t _174;
};

struct CABackingStoreBuffer
{
	CABackingStoreBuffer* _0;		// next
	CGColorSpaceRef _8;
	CA::Render::Shmem* _10;
	CGSRegionObject* _18;
	unsigned int _20;
	uintptr_t _28;
};

typedef double CGFloat;
struct CGPoint
{
	CGFloat x;		// _0@pt, _0@rc
	CGFloat y;		// _8@pt, _8@rc
};
struct CGSize
{
	CGFloat width;		// _0@sz, _10@rc
	CGFloat height;		// _8@sz, _18@rc
};
struct CGRect
{
	CGPoint position;
	CGSize size;
};
struct CGAffineTransform {
	CGFloat a, b, c, d;
	CGFloat tx, ty;
};
struct CATransform3D
{
	CGFloat m11, m12, m13, m14;
	CGFloat m21, m22, m23, m24;
	CGFloat m31, m32, m33, m34;
	CGFloat m41, m42, m43, m44;
};

namespace CA
{
	template<typename _T>
	struct Vec2
	{
		_T vec[2];
	};

	template<typename _T>
	struct Mat4
	{
		_T Mat[4];
	};

	// by hand
	struct Mat4Impl
	{
		static Mat4<double> mat4_identity_double;
		static Mat4<double> mat4_identity_double;
		static bool mat4_is_equal(double const*, double const*);
		static void mat4_assign(double*, double const*);
	};
}

namespace X
{
	template<typename _T> struct List
	{

	};
	template<typename _T> struct Ref 
	{
		_T* _Ptr;
		void operator= (_T*);
	};

	template<typename _T>
	struct Weak
	{
		Weak(_T*);
	};

	struct WeakDetails
	{
		struct Ptr
		{
			void clear();
		};
	};
}

#endif // _CA_struct__H_