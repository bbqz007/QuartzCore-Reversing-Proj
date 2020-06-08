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


#include "typedefs.h"
#include "CA.namespace.h"
#include "CA.struct.h"
#include "CA.ops.h"
#include "OSAtomic.h"
#include "CA.oc.h"

CA::Render::Object::Object(CA::Render::Decoder* decoder, unsigned int flag)
{
	r14d = flag;
	rbx = this;
	this->_0 = (uintptr_t)CA::Render::Object::vtable + 0x10;
	this->_8 = ((decoder->decode_int16() & flag) << 0x10) | 0x1;
}

bool CA::Render::Object::caches_encoding()
{
	return false;
}

bool CA::Render::Object::can_mix_with_object(CA::Render::Object*)
{
	return false;
}

double CA::Render::Object::distance_to(CA::Render::Object const*) const
{
	return 0.;
}

short CA::Render::Object::encode(CA::Render::Encoder* encoder) const
{
	return encoder->encode_int16((unsigned short)(this->_8 >> 0x10));
}

CA::Render::Object* CA::Render::Object::external_ref() const
{
	r14 = this;
	// 20 call
	OSSpinLockLock(&CA::Render::Object::_refcount_lock);
	// 35
	if (!(0 != CA::Render::refcount_table)) { // 32 (0 != rdi)
			 // 51 call
		CA::Render::refcount_table = (x_hash_table*)x_hash_table_new_(0, 0, 0, 0, 0, 0);
	} // 66
	int64_t& external_refcnt = rbx;
	CA::Render::Object*& retained_object = r15;
	  // 73 call
	external_refcnt = x_hash_table_lookup((x_hash_table*)CA::Render::refcount_table, (uintptr_t)this, (uintptr_t)&_20);
	// 86
	if (!(_20 != 0x0)) { // 81 (_20 != 0x0)
		external_refcnt = this->_8 & 0x3fff;
		// 112 call
		x_hash_table_insert((x_hash_table*)CA::Render::refcount_table, (uintptr_t)this, (uintptr_t)external_refcnt);
	} // 117
	retained_object = 0;
	// 123
	if (!(0 == external_refcnt)) { // 120 (0 == rbx)
			 // 141 call
		x_hash_table_insert((x_hash_table*)CA::Render::refcount_table, (uintptr_t)this, (uintptr_t)++external_refcnt);
		retained_object = this;
	} // 149
	  // 156 call
	OSSpinLockUnlock(&CA::Render::Object::_refcount_lock);
	return retained_object;
}

bool CA::Render::Object::external_unref() const
{
	r14 = this;
	// 20 call
	OSSpinLockLock(&CA::Render::Object::_refcount_lock);
	// 35
	if (!(0 != CA::Render::refcount_table)) { // 32 (0 != rdi)
			 // 51 call
		CA::Render::refcount_table = x_hash_table_new_(0, 0, 0, 0, 0, 0);
	} // 66
	int64_t& external_refcnt = rbx;
	// 73 call
	external_refcnt = x_hash_table_lookup((x_hash_table*)CA::Render::refcount_table, (uintptr_t)this, (uintptr_t)&_20);
	// 86
	if (!(_20 != 0x0)) { // 81 (_20 != 0x0)
		external_refcnt = this->_8 & 0x3fff;
		// 112 call
		x_hash_table_insert((x_hash_table*)CA::Render::refcount_table, (uintptr_t)this, (uintptr_t)external_refcnt);
	} // 117
	--external_refcnt;
	// 137 call
	x_hash_table_insert((x_hash_table*)CA::Render::refcount_table, (uintptr_t)this, (uintptr_t)external_refcnt);
	// 149 call
	OSSpinLockUnlock(&CA::Render::Object::_refcount_lock);
	return return (0 == external_refcnt);
}

void CA::Render::Object::finalize()
{
	// 7
	if (!(0 == this)) { // 4 (0 == rdi)
		((cpp_virtbl*)this->_0)->virmethod[1]();
	} // 16
	return;
}

uintptr_t CA::Render::Object::ogl_image_key() const
{
	return (uintptr_t)this;
}

CA::Render::Object* CA::Render::Object::ref() const
{
	rdx = &this->_8;
	ecx = 0;
	do {
	_b11:	// from 31
		eax = this->_8;
		ebx = this->_8 + 1;
		// 19
		if (0x4000 & (this->_8 + 1)) { // 16 (0x40 & bh)
			// inline goto _f42;
			return this->external_ref();
		}
		// 25
		if (0 == (0x3fff & this->_8)) { // 21 (0 == (0x3fff & ax))
			return 0;
		} // 36
				 // 31
	} while ((false == OSAtomicCompareAndSwapInt(this->_8, this->_8 + 1, (volatile int32_t*)&this->_8))); // 28 (false == OSAtomicCompareAndSwapInt(eax, ebx, (volatile int32_t*)&rdx->_0))
			// goto _b11;
	return this;
}

int64_t CA::Render::Object::refcount() const
{
	r14 = this;
	ebx = this->_8;
	eax = this->_8 + 1;
	// 24
	if (!(0x400 & (this->_8 + 1))) { // 21 (0x40 & ah)
		ebx = this->_8 & 0x3fff;
		// 32
   // inline goto _f97;
		return this->_8 & 0x3fff;
	} // 34

	int64_t& external_refcnt = rbx;
	  // 41 call
	OSSpinLockLock(&CA::Render::Object::_refcount_lock);
	// 56
	if (!(0 == CA::Render::refcount_table)) { // 53 (0 == rdi)
		// 65 call
		external_refcnt = x_hash_table_lookup((x_hash_table*)CA::Render::refcount_table, (uintptr_t)this, (uintptr_t)&_18);
		// 78
		if (_18 != 0x0) { // 73 (_18 != 0x0)
			// inline jmp 85
			// 92 call
			OSSpinLockUnlock(CA::Render::Object::_refcount_lock);
			return external_refcnt;
		}
	}
	external_refcnt = 0x3fff;
	// 92 call
	OSSpinLockUnlock(CA::Render::Object::_refcount_lock);
	return 0x3fff;
}

int CA::Render::Object::show(unsigned int flag1, unsigned int flag2) const
{
	// 7 call
	eax = ((cpp_virtbl*)this->_0)->virmethod[3](flag1, flag2);
	// 13
	if (!(eax > 0x32)) { // 10 (eax > 0x32)
		rax = eax + eax * 2;
		rcx = &CA::Render::type_names;
		rsi = &((int64_t*)& CA::Render::type_names)[rax];
		// 32
   // inline goto _f41;
		eax = 0;
		return x_log("(%s)", &((int64_t*)& CA::Render::type_names)[rax]);
	} // 34
	eax = 0;
	return x_log("(%s)", "<unknown>");
}