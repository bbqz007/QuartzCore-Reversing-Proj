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
// OC object

struct CAAction;
struct CALayer;
struct CALayerArray
{
	struct {
		CALayer** _0;
		int64_t _8;
	} _ivars;
};
struct CALayer
{
	struct {
		CA::Layer* _8;			// from CA::Layer::collect_layers_
	} _attr;
};
struct CGColorSpace;
struct CGColor;
struct CGBitmapContext;
struct CGImage;
struct CGContext;
struct CGDataProvider;
struct CABackingStore;
struct CABackingStoreBuffer;
struct CGSRegionObject;
struct CGSRect;
typedef void* CFTypeID;
typedef CGColorSpace* CGColorSpaceRef;
typedef CGColor* CGColorRef;
typedef CGCoCGBitmapContextlor* CGBitmapContextRef;
typedef CGImage* CGImageRef;
CGColorSpaceRef CAGetColorSpace(unsigned int);
CGColorSpaceRef CGColorSpaceRetain(CGColorSpaceRef);
CGBitmapContextRef CAGetCachedCGBitmapContext(void*, unsigned int, unsigned int, unsigned int, unsigned int, CGColorSpaceRef);
void CGColorSpaceRelease(CGColorSpaceRef);
void CAReleaseCachedCGContext(CGContext*);
void CGDataProviderRelease(id);
void CFRelease(id);
CGImageRef CGImageCreate(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
CFTypeID CFGetTypeID(id);
CFTypeID CABackingStoreGetTypeID();
id CFRetain(id);
unsigned int CABackingStoreSetDefaultAccelFlags(unsigned int);
void CABackingStoreUpdate_(CGImage*, unsigned int, unsigned int, unsigned int,unsigned int, void(*)(CGContext*, void*),CA::Layer*, void**);
typedef bool boolean;
typedef void* SEL;
typedef void* Method;
struct CGSRect
{
	double x, y, width, height;
};
struct NSObject
{
	Class isa;
};

struct _NSStackBlock;
typedef void(*_NSBlock_Invoke_Func)(_NSStackBlock*);
struct _NSStackBlock
{
	Class isa;
	int32_t flag;
	int32_t refcnt;
	_NSBlock_Invoke_Func invoke;
	uintptr_t(*descriptor)[];
};

struct _NSConcreteStackBlock : public _NSStackBlock {};

typedef _NSStackBlock _NSMallocBlock;

#define MACRO_NSStackBlock_SET_PRIVSTACK(block, offset, type, value)	\
	*(type*)(uintptr_t((struct _NSStackBlock*)block + 1) + offset) = value;


struct NSString;
typedef uint64_t offsst_size_t;


struct UIViewAnimationState
{
	common_obj_layout* _animationID;
	common_obj_layout* _context;
	common_obj_layout* _duration;
};