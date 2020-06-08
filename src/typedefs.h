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


#ifndef _TYPEDEFS_H_
#define _TYPEDEFS_H_

typedef __int64 int64;
typedef __int64 int64_t;
typedef unsigned int64 uint64_t;
#define YES true
#define NO false
#define nil (void*)0
#ifndef _UINTPTR_T_DEFINED
typedef unsigned __int64 uintptr_t;
#endif
typedef int int32_t;
typedef char int8_t;
typedef short int16_t;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

struct common_obj_layout;
struct reg64_t
{
	int64_t reg;
	common_obj_layout* operator ->()
	{
		return (common_obj_layout*)(void*)reg;
	}
	int64_t& operator *()
	{
		return (int64_t&)*(int64_t*)(void*)reg;
	}
	template<typename _T>
	operator _T* ()
	{
		return (_T*)(void*)reg;
	}
	double operator double() { return (double)reg; }
	float operator float() { return (float)reg; }
	int operator int() { return (int)reg; }
	int64_t operator int64_t() { return reg; }
	bool operator !()
	{
		return reg == 0;
	}
};
uintptr_t operator = (uintptr_t& _L, reg64_t& _R)
{
	_L = _R.reg;
	return _L;
}

struct pack_single_pr
{
	float f0, f1, f2, f3;
};
struct pack_double_pr
{
	double d0, d1;
};
struct xmmreg_t
{
	union {
		float _ps[4];
		double _pd[2];
		int _pi[4];
	};
	float ss() { return ps[0]; }
	double sd() { return pd[0]; }
	float& explicit operator float&() { return ps[0]; }
	double& explicit operator double&() { return pd[0]; }
	float explicit operator float() { return ss(); }
	double explicit operator double() { return sd(); }

	xmmreg_t& operator =(pack_single_pr ps) {
		_ps[0] = ps.f0; _ps[1] = ps.f1;
		_ps[2] = ps.f2; _ps[3] = ps.f3;
		return *this;
	}
	xmmreg_t& operator =(pack_double_pr pd) {
		_pd[0] = pd.d0; _pd[1] = pd.d1;
		return *this;
	}
	double operator =(double dbl) {
		return (_pd[0] = dbl);
	}
	float operator =(float flt) {
		return (_ps[0] = flt);
	}
	void unpckldqWithSrc(xmmreg_t& src) {
		if(this != &src) 
		{
			_pd[1] = src._pd[0];
			_pd[0] = _pd[0];
		}
		else
		{
			_pd[1] = _pd[0];
		}
	}
	void unpckhdqWithSrc(xmmreg_t& src) {
		if (this != &src)
		{
			_pd[0] = _pd[1];
			_pd[1] = src._pd[1];
		}
		else
		{
			_pd[0] = _pd[1];
		}
	}
	void unpcklpdWithSrc(xmmreg_t& src) {
		if (this != &src)
		{
			_pd[1] = src._pd[0];
			_pd[0] = _pd[0];
		}
		else
		{
			_pd[1] = _pd[0];
		}
	}
	void unpckhpdWithSrc(xmmreg_t& src) {
		if (this != &src)
		{
			_pd[0] = _pd[1];
			_pd[1] = src._pd[1];
		}
		else
		{
			_pd[0] = _pd[1];
		}
	}
	void haddpdWithSrc(xmmreg_t& src) {
		if (this != &src)
		{
			_pd[0] = _pd[0] + _pd[1];
			_pd[1] = src._pd[0] + src._pd[1];
		}
		else
		{
			_pd[0] = _pd[0] + _pd[1];
			_pd[1] = _pd[0];
		}
	}
	void addpdWithSrc(xmmreg_t& src) {
		if (this != &src)
		{
			_pd[0] += src._pd[0];
			_pd[1] += src._pd[1];
		}
		else
		{
			_pd[0] = _pd[0] + _pd[0];
			_pd[1] = _pd[1] + _pd[1];
		}
	}
	void movddupWithSrc(xmmreg_t& src)
	{
		_pd[0] = src._pd[0];
		_pd[1] = src._pd[1];
	}
};

#define DECL_REG(n)	\
	extern int8_t n##l;	\
	extern int16_t n##x;	\
	extern int32_t e##n##x;	\
	extern int64_t r##n##x;	

#define DECL_REGX(n)	\
	extern int32_t r##n##d;	\
	extern int64_t r##n;	

#define DECL_IREG(n)	\
	extern int16_t n##i;	\
	extern int32_t e##n##i;	\
	extern int64_t r##n##i;	

#define DECL_REGS_	\
	DECL_REG(a)	\
	DECL_REG(b)	\
	DECL_REG(c)	\
	DECL_REG(d)	\
	DECL_REGX(8)	\
	DECL_REGX(9)	\
	DECL_REGX(10)	\
	DECL_REGX(11)	\
	DECL_REGX(12)	\
	DECL_REGX(13)	\
	DECL_REGX(14)	\
	DECL_REGX(15)	\
	DECL_IREG(d)	\
	DECL_IREG(s)

#define DECL_REG2(attr, n)	\
	attr int8_t n##h;	\
	attr int8_t n##l;	\
	attr int16_t n##x;	\
	attr int32_t e##n##x;	\
	attr reg64_t r##n##x;	

#define DECL_REGX2(attr, n)	\
	attr int8_t r##n##b;	\
	attr int32_t r##n##d;	\
	attr reg64_t r##n;	

#define DECL_IREG2(attr, n)	\
	attr int16_t n##i;	\
	attr int32_t e##n##i;	\
	attr reg64_t r##n##i;	

#define DECL_REGS2_	\
	DECL_REG2( ,a)	\
	DECL_REG2( ,b)	\
	DECL_REG2( ,c)	\
	DECL_REG2( ,d)	\
	DECL_REGX2( ,8)	\
	DECL_REGX2( ,9)	\
	DECL_REGX2( ,10)	\
	DECL_REGX2( ,11)	\
	DECL_REGX2( ,12)	\
	DECL_REGX2( ,13)	\
	DECL_REGX2( ,14)	\
	DECL_REGX2( ,15)	\
	DECL_IREG2( ,d)	\
	DECL_IREG2( ,s)

#define DECL_REGS DECL_REGS2_

#define DECL_XMMREG(attr, n)	\
	attr xmmreg_t xmm##n;

#define DECL_XMMREGS	\
	DECL_XMMREG( , 0)
	DECL_XMMREG( , 1)
	DECL_XMMREG( , 2)
	DECL_XMMREG( , 3)
	DECL_XMMREG( , 4)
	DECL_XMMREG( , 5)
	DECL_XMMREG( , 6)
	DECL_XMMREG( , 7)
	
extern "C" {
	DECL_REGS
	DECL_XMMREGS
	reg64_t rsp;
}

// 0x100 per segment
#define DECL_LOCALVAIRABLES_(attr, seg, x)	\
	attr uintptr_t _##seg##x##0;	\
	attr uintptr_t _##seg##x##8;	

#define DECL_LOCALVAIRABLES(attr, seg, _0, _1, _2, _3, _4, _5, _6, _7)	\
	DECL_LOCALVAIRABLES_(attr, seg, _0);		\
	DECL_LOCALVAIRABLES_(attr, seg, _1);		\
	DECL_LOCALVAIRABLES_(attr, seg, _2);		\
	DECL_LOCALVAIRABLES_(attr, seg, _3);		\
	DECL_LOCALVAIRABLES_(attr, seg, _4);		\
	DECL_LOCALVAIRABLES_(attr, seg, _5);		\
	DECL_LOCALVAIRABLES_(attr, seg, _6);		\
	DECL_LOCALVAIRABLES_(attr, seg, _7);		

#define DECL_LOCALVAIRABLES_SEG(attr, seg)		\
	DECL_LOCALVAIRABLES(attr, seg, 0, 1, 2, 3, 4, 5, 6, 7)		\
	DECL_LOCALVAIRABLES(attr, seg, 8, 9, a, b, c, d, e, f)

#define DECL_LOCALVAIRABLES_SEGS(attr, _s0, _s1, _s2, _s3, _s4, _s5, _s6, _s7)	\
	DECL_LOCALVAIRABLES_SEG(attr, _s0)	\
	DECL_LOCALVAIRABLES_SEG(attr, _s1)	\
	DECL_LOCALVAIRABLES_SEG(attr, _s2)	\
	DECL_LOCALVAIRABLES_SEG(attr, _s3)	\
	DECL_LOCALVAIRABLES_SEG(attr, _s4)	\
	DECL_LOCALVAIRABLES_SEG(attr, _s5)	\
	DECL_LOCALVAIRABLES_SEG(attr, _s6)	\
	DECL_LOCALVAIRABLES_SEG(attr, _s7)	

#define DECL_LOCALVAIRABLES_16_SEGS(attr, _sh)	\
	DECL_LOCALVAIRABLES_SEGS(attr, _sh##0, _sh##1, _sh##2, _sh##3, _sh##4, _sh##5, _sh##6, _sh##7)	\
	DECL_LOCALVAIRABLES_SEGS(attr, _sh##8, _sh##9, _sh##a, _sh##b, _sh##c, _sh##d, _sh##e, _sh##f)

#define DECL_LOCALVAIRABLES_16_SEGS_0(attr, _sh)	\
	DECL_LOCALVAIRABLES_SEGS(attr, _sh, _sh##1, _sh##2, _sh##3, _sh##4, _sh##5, _sh##6, _sh##7)	\
	DECL_LOCALVAIRABLES_SEGS(attr, _sh##8, _sh##9, _sh##a, _sh##b, _sh##c, _sh##d, _sh##e, _sh##f)

DECL_LOCALVAIRABLES_(, , )
DECL_LOCALVAIRABLES( ,  ,  , 1, 2, 3, 4, 5, 6, 7)
DECL_LOCALVAIRABLES( ,  , 8, 9, a, b, c, d, e, f)
DECL_LOCALVAIRABLES_16_SEGS_0(, )
DECL_LOCALVAIRABLES_16_SEGS(, 1)
DECL_LOCALVAIRABLES_16_SEGS(, 2)
DECL_LOCALVAIRABLES_16_SEGS(, 3)
DECL_LOCALVAIRABLES_16_SEGS(, 4)
DECL_LOCALVAIRABLES_16_SEGS(, 5)
DECL_LOCALVAIRABLES_16_SEGS(, 6)
DECL_LOCALVAIRABLES_16_SEGS(, 7)
DECL_LOCALVAIRABLES_16_SEGS(, 8)
DECL_LOCALVAIRABLES_16_SEGS(, 9)
DECL_LOCALVAIRABLES_16_SEGS(, a)
DECL_LOCALVAIRABLES_16_SEGS(, b)

struct common_obj_layout
{
	DECL_LOCALVAIRABLES_(, , )
	DECL_LOCALVAIRABLES(, , , 1, 2, 3, 4, 5, 6, 7)
	DECL_LOCALVAIRABLES(, , 8, 9, a, b, c, d, e, f)
	DECL_LOCALVAIRABLES_16_SEGS_0(, )
	DECL_LOCALVAIRABLES_16_SEGS(, 1)
	DECL_LOCALVAIRABLES_16_SEGS(, 2)
	DECL_LOCALVAIRABLES_16_SEGS(, 3)
	DECL_LOCALVAIRABLES_16_SEGS(, 4)
	DECL_LOCALVAIRABLES_16_SEGS(, 5)
	DECL_LOCALVAIRABLES_16_SEGS(, 6)
	DECL_LOCALVAIRABLES_16_SEGS(, 7)
	DECL_LOCALVAIRABLES_16_SEGS(, 8)
	DECL_LOCALVAIRABLES_16_SEGS(, 9)
	DECL_LOCALVAIRABLES_16_SEGS(, a)
	DECL_LOCALVAIRABLES_16_SEGS(, b)
};


struct cpp_virtbl {
	int(*virmethod[]) (...);
};

#ifndef _MAC_OS
struct objc_object { objc_object* isa };
typedef objc_object* id;
typedef objc_object* Class;
typedef objc_object objc_class;
id objc_msgSend(id, const char*, ...);
typedef const void* CFTypeRef;
typedef unsigned long CFTypeID;
void NSLog(__CFString*, ...);
struct __CFArray;
struct __CFAllocatorZone;
struct __CFData;
struct __CFString;
struct __CFSet;
struct __CFDictionary;
struct __CFValue;
struct __CFRunLoop;
struct __CFRunLoopObserver;
struct __CFRunLoopTimer;
typedef common_obj_layout _NSConcreteBlock;
typedef uint32_t mach_port;
typedef int32_t kern_return_t;
typedef kern_return_t mach_msg_return_t;
typedef struct _NSStackBlock* block_pointer;
#define __cfs(str) (__CFString*)0
#else
#define ^block_pointer(); 
#define __cfs(str) @str
#endif

typedef unsigned size_t;
struct x_hash_table;
struct x_list
{
	void* _0;		// val
	x_list* _8;		// next
};
struct x_heap_struct
{
	void* _0;		// head of buffer
	void* _8;		// free buffer
	int64_t _10;	// free size
};
struct x_chain
{
	x_chain* _0;		// next
	uintptr_t _8;		// hobj
	int _10;			// id
};

#if 1
struct _pthread;
typedef _pthread *pthread_t;
struct _pthread_mutex {};
typedef struct _pthread_mutex pthread_mutex_t;
struct _pthread_cond {};
typedef struct _pthread_cond pthread_cond_t;
struct _pthread_key;
typedef _pthread_key* pthread_key_t;
#endif

#if 1
typedef void* dispatch_source_t;
typedef void* dispatch_queue_t;
typedef void* dispatch_once_t;
#endif

#define OFFSET_OF(class, member) ((uintptr_t) &((class*)0)->member)

// 0x3ff0000000000000 is 1.
// 0xBFF0000000000000 is -1.

#endif //_TYPEDEFS_H_