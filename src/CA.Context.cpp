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

CA::Context::~Context()
{
	rbx = this;
	// 10 call
	this->destroy();;
	// 25
	if (!(0 == this->_80)) {
		// 27 call
		CFRelease((__CFDictionary*)this->_80);
	} // 32
	// 36 call
	CGColorSpaceRelease(this->_78);
	// 45 call
	pthread_mutex_destroy(&this->_10);
	// 63 call
	memset(this, 0x44, 0xd0);
	  // 94 call
	return ((X::WeakDetails::Ptr*)&this->_50)->clear();
}

void CA::Context::destroy()
{
	rbx = this;
	r14 = (pthread_mutex_t*)&this->_10;	
	// 21 call
	pthread_mutex_lock((pthread_mutex_t*)&this->_10);
	// 33
	if (!(0 == this->_68)) {
		CA::Layer*& layer = rdi;
		// 35 call
		layer = CALayerGetLayer((CALayer*)this->_68);
		// 45 call
		layer->set_visible((unsigned int)0);;
		// 54 call
		CFRelease((CALayer*)this->_68);
		this->_68 = 0;
	} // 67

	  // 70
	if (!(0 != this->_0)) {
		// 79
		if (!(this->_c8 & 0xff & 0x2)) {
			// 88 call
			// %rdi = CA::Context::_lock
			OSSpinLockLock(&CA::Context::_lock);
			// 103
			if (!(0 == (rax = CA::Context::_contexts))) {
				CA::Context**& prev = rcx;							// &=rcx;
				CA::Context*& it = rax;								// &=rax;
				prev = &CA::Context::_contexts;			
				// do {
			_b112:	 // from 130
					 // 115
				if (this == it) {
					// goto _f134;	inline #0
					*(prev) = this->_8;
					// natural flow to 141
					goto _f141;
				}
				prev = &it->_8;
				it = *prev;
				// 130
				if (it)
					goto _b112;
				else // 132
					goto _f141;
				// } while();
			} // 141
		_f141:	 // from 132
			this->_c8 |= 0x2;
			  // 155 call
			  // %rdi = CA::Context::_lock
			OSSpinLockUnlock(&CA::Context::_lock);
		} // 160
	} // 160
	  // 165
	esi = this->_58;
	if (!(0 == this->_58)) {
		// 175
		if (!(0 == this->_90)) {
			// 177 call
			_CASDeleteClient(this->_90, this->_58);
			this->_58 = 0;
			esi = this->_90;
		} // 189
	} // 189
	  // 197
	if (!(0 == esi)) {
		extern mach_port* mach_task_self_;
		// 208 call
		mach_port_deallocate(*mach_task_self_);
		this->_90 = 0;
	} // 223

	r15 = this->_98;
	  // 233
	if (!(0 == this->_98)) {
		// 238 call
		((CA::Render::Encoder::ObjectCache*)this->_98)->~ObjectCache();;
		// 251 call
		x_mem_dealloc_bucket(0x1, this->_98);
		this->_98 = 0;
	} // 267

	  // 277
	if (!(0 == this->_a0)) {
		// 279 call
		dispatch_source_cancel(this->_a0);
		// 291 call
		dispatch_release(this->_a0);
		this->_a0 = 0;
		this->_a8 = 0;
	} // 317
	
	CA::Render::Context*& renderContext = r15;						// &=r15
	  // 327 call
	OSSpinLockLock(&CA::Context::_lock);
	renderContext = this->_70;
	this->_70 = 0;
	// 347 call
	OSSpinLockUnlock(&CA::Context::_lock);
	// 355
	if (!(0 == renderContext)) {
		// 360 call
		renderContext->destroy();;
		// 368 call
		((CA::Render::Object*)renderContext)->unref();
	} // 373
	  // 395 call
	pthread_mutex_unlock((pthread_mutex_t*)&this->_10);
}

CA::Context::Context(__CFDictionary const* dict)
{
	rbx = this;
	r15 = dict;
	this->_0 = 1;
	this->_8 = 0;
	new (&this->_50)
	// 39 call
		X::Weak<void const*>((void const*)0);
	this->_58 = 0;
	this->_60 = 0;
	this->_90 = 0;
	this->_88 = 0;
	this->_80 = 0;
	this->_78 = 0;
	this->_70 = 0;
	this->_68 = 0;
	this->_b0 = 0;
	this->_a8 = 0;
	this->_a0 = 0;
	this->_98 = 0;

	this->_c0 = 0;
	(char&)this->_c8 = (char&)this->_c8 & 0xe0 | 0x10;
	// 209 call
	x_thread_init_mutex(&this->_10, 0x1);
	// 217
	if (!(0 == dict)) {
		this->_80 = dict;
		// 229 call
		CFRetain(dict);
	} // 234
	  // 239 call
	;
	// 247 call
	this->_78 = CGColorSpaceRetain(CAGetColorSpace(0x4));
	// 263 call
	// %rdi = CA::Context::_lock
	OSSpinLockLock(&CA::Context::_lock);

	this->_8 = CA::Context::_contexts;
	CA::Context::_contexts = this;

	this->_5c = ++CA::Context::_last_local_id;
	// 303
	if (!(0 != CA::Context::_last_local_id)) {
		this->_5c = ++CA::Context::_last_local_id;
	} // 322
	OSSpinLockUnlock(&CA::Context::_lock);
	return;
}

CA::Context::set_colorspace(CGColorSpace* colorSpace)
{
	rbx = colorSpace;
	r15 = this;
	// 19
	if (!(0 != colorSpace)) { // 16 (0 != rbx)
		eax = 0;
		// 34 call
		x_log_err("CoreAnimation: NULL color space set on context (%x)\\n", this->_58);
		// 44 call
		colorSpace = CAGetColorSpace(0x4);
	} // 52
	r14 = &this->_10;
	// 59 call
	pthread_mutex_lock((pthread_mutex_t*)&this->_10);
	// 71 call
	CGColorSpaceEqualToColorSpace(this->_78, colorSpace);
	// 78
	if (!) { // 76 (0 != al)
			 // 84 call
		CGColorSpaceRelease(this->_78);
		// 92 call
		this->_78 = CGColorSpaceRetain(colorSpace);
		this->_c8 |= 0x10;
	} // 109
	return pthread_mutex_unlock((pthread_mutex_t*)&this->_10);
}


bool CA::Context::is_secure()
{
	rbx = this;
	CA::Render::Context*& renderContext = rdi;		// &=rdi
	renderContext = this->_70;
	bool& is_secure = bl;		// &=bl, invalidate until 111
	// 16
	if (!(0 == renderContext)) { // 13 (0 == rdi)
		// 22 call
		pthread_mutex_lock((pthread_mutex_t*)&renderContext->_28);
		is_secure = renderContext->_cc;
		// 41 call
		pthread_mutex_unlock((pthread_mutex_t*)&renderContext->_28);
		// 46
		goto _f111;
	} // 48
	else {
		// 55
		if (0x1 & this->_c8) { // 48 (0x1 & rbx->_c8)
				// inline jmp 109
			is_secure = 0;
			goto _f111;
		}
		else {
			_c = 0x0;
			// 77 call
			// 84
			if (0 != _CASGetSecure(this->_90, this->_58, (int32_t*)&_c)) { // 82 (0 != eax)
					 // inline jmp 95
					 // 100
				if (!(eax != 0x10000003)) { // 95 (eax != 0x10000003)
					this->_c8 |= 0x1;
				} // 109
				is_secure = 0;
				goto _f111;
			}
			else { // 84 next
				   // 86 cmpl $0x0, -0xc(%rbp)
				is_secure = ((int32_t&)_c != 0x0);
				// 93
				goto _f111;
			}
		} // 93	 unreachable
	}
_f111:	 // from 93
_f111:	 // from 46
	return is_secure;
}


void CA::Context::invalidate_fences()
{
	// 11
	if (!(0x1 & this->_c8)) { // 4 (0x1 & rdi->_c8)
		return _CASInvalidateFences(this->_90, this->_58);
	} // 28
	return;
}


void CA::Context::invalidate()
{
	rbx = this;
	r14 = &this->_10;
	// 20 call
	pthread_mutex_lock((pthread_mutex_t*)&this->_10);

	CA::Transaction*& transaction = rax;
	CA::Transaction::Shared*& shared = rcx;
	// 25 call
	transaction = CA::Transaction::ensure();
	shared = transaction->_0;
	r15d = shared->_10;
	// 41
	if (!((int32_t&)shared->_10 != 0x0)) { // 37 ((int32_t&)rcx->_10 != 0x0)
			 // 46 call
		((CA::Transaction*)transaction)->ensure_implicit();
	} // 51
	// 58
	if (!(0 == (CALayer*)this->_68)) { // 55 (0 == rdi)
		((CA::Layer*)
			// 60 call
			CALayerGetLayer((CALayer*)this->_68)
			// 70 call
			)->set_visible((unsigned int)0);
		// 79 call
		CFRelease(this->_68);
		this->_68 = 0x0;
	} // 92
	this->_c8 |= 0x8;
	// 102 call
	pthread_mutex_unlock((pthread_mutex_t*)&this->_10);
	// 114
	if (0 == shared->_10) // 111 (0 == r15d)
	// inline goto _f123;
		return CA::Transaction::commit_transaction();
	return;
}


CGColorSpace* CA::Context::current_colorspace(CA::Transaction* transaction)
{
	// 7
	if (!(0 != transaction)) { // 4 (0 != rdi)
			 // 9 call
		transaction = transaction->get();
		// 20
		if (0 == transaction) // 17 (0 == rdi)
			// inline goto _f37;
			return CAGetColorSpace(0x4);
	} // 22
	CA::Context*& caContext = rax;
	caContext = transaction->_50;
	// 29
	if (0 == caContext) // 26 (0 == rax)
	// inline goto _f37;
		return CAGetColorSpace(0x4);
	return caContext->_78;
}


CA::Context* CA::Context::retain_context_with_client_port(unsigned int client_port)
{
	CA::Context*& retContext = r14;						// &=r14
	ebx = client_port;
	// 16 call
	// %rdi = CA::Context::_lock
	OSSpinLockLock(&CA::Context::_lock);
	retContext = 0;
	// 34
	if (!(0 == (rax = CA::Context::_contexts))) {
		retContext = 0;
		CA::Context*& context = rax;					// &=rax
		// do {
	_b39:	 // from 60
			 // 43
		if (!(0 == context->_0)
			&& client_port == context->_a8) {			// 51
			// gen jmp 64
			// goto _f64; inilne #0
		_f64:	 // from 51
			++context->_0;
			retContext = context;
			// natural flow to 71
			goto _f71;
		}
	_f53:	 // from 43
		  // 60
		context = context->_8;
		if (context)
			goto _b39;
		// } while ((context = context->_8));
		// 62
		goto _f71;
	} // 71
_f71:	 // from 62
	OSSpinLockUnlock(&CA::Context::_lock);
	return retContext;
}

CA::Context* CA::Context::retain_context_with_id(unsigned int id)
{
	CA::Context*& retContext = r14;						// &=r14
	ebx = id;
	// 16 call
	// %rdi = CA::Context::_lock
	OSSpinLockLock(&CA::Context::_lock);
	retContext = 0;
	// 34
	if (!(0 ==(rax = CA::Context::_contexts))) {
		CA::Context*& context = rax;							// &=rax
		retContext = 0;
		// do {
	_b39:	 // from 57
			 // 43
		if (0 == context->_0) {
			// gen jmp 50
			goto _f50;
		} // 48
		else if (id == context->_5c) {
			// gen jmp 61
			// goto _f61; inline #0
		_f61:	 // from 48
			++context->_0;
			retContext = context;
			OSSpinLockUnlock(&CA::Context::_lock);
			return retContext;
		}
	_f50:	 // from 43
		context = context->_8;
		  // 57
		if (context)
			goto _b39;
		// } while ((context = context->_8))
		// 59
		goto _f68;
	} // 68
_f68:	 // from 59
	OSSpinLockUnlock(&CA::Context::_lock);
	return retContext;
}

CALayer* CA::Context::retain_layer()
{
	CALayer*& retLayer = rbx;							// &=rbx
	retLayer = this;
	// 17 call
	pthread_mutex_lock(this->_10);
	rdi = this->_68;
	retLayer = 0;
	// 31
	if (!(0 == this->_68)) {
		// 33 call
		retLayer = CFRetain(this->_68);
	} // 41
	pthread_mutex_unlock(this->_10);
	return retLayer;
}

__CFArray* CA::Context::retain_objc_contexts()
{
	// _40 to _30
	extern void** __stack_chk_guard;
	r12 = *__stack_chk_guard;
	_30 = r12;

	CA::Context**& retainedContexts = r14;						// &=r14
	int32_t& retainedContextsLength = r15d;						// &=r15d

	// 39 call
	// %rdi = CA::Context::_lock
	OSSpinLockLock(&CA::Context::_lock);
	CA::Context*& context = rbx;								// &=rbx
	context = CA::Context::_contexts;
	eax = 0;
	// 56
	if (0 == CA::Context::_contexts) {
		// gen jmp 151
		// goto _f151; inline #0
	_f151:	 // from 56
		retainedContexts = (uintptr_t)&_30 - 1;					// ?
		retainedContextsLength = 0;
		// natural flow to 158
		goto _f158;
	} 
	else {
		CA::Context*& it = rcx;
		it = context;
		// do {
	_b61:	 // from 75
		rax -= 1;
		rax -= (it->_0 < 0x1) ? 1 : 0;
		it = it->_8;
			 // 75
		if (it)
			goto _b61;
		// } while ((it = it->_8));

#if 0
		rax = (rax * 9 + 0xf) & 0xfffffffffffffff0;
		rsp -= rax;
		r14 = rsp;
#else
		retainedContexts = alloca((rax * 9 + 0xf) & 0xfffffffffffffff0);
#endif
		retainedContextsLength = 0;
		// 101
		goto _f107;
		// for (;;context = context->_8) {
	_b103:	 // from 149
	_b103:	 // from 132
	_b103:	 // from 115
		context = context->_8;
	_f107:	 // from 101
		// 110
		if (0 == context) {
			// gen jmp 158
			goto _f158;									// break;
		}
		else { // 110 next
			   // 115
			if (0 == context->_0)
				goto _b103;								// continue;
			// 132
			if (0 == objc_loadWeak(context->_50))		// 0 == [124 call]
				goto _b103;								// continue;
			// 137 call
			retainedContexts[retainedContextsLength] = objc_loadWeak(context->_50);
			// movq   %rax, (%r14,%r15,8)
			++retainedContextsLength;
			// 149
			goto _b103;									// continue;
		}
		// } // end for
	}

_f158:	 // from 110
	__CFArray*& retArray = rbx;							// &=rbx
	extern void* kCFTypeArrayCallBacks;
		 // 173 call
		 // %rcx = (void *)0x0000000103d23a90: kCFTypeArrayCallBacks
	retArray = CFArrayCreate(0, retainedContexts, retainedContextsLength, kCFTypeArrayCallBacks);
	// 188 call
	// %rdi = CA::Context::_lock
	OSSpinLockUnlock(&CA::Context::_lock);
	// 197
	if (_30 != *__stack_chk_guard) {
		// goto _f242; inline #0
		__stack_chk_fail();								// raise
	}
	freea(retainedContexts);								// rsp = &_28;		
	return retArray;
}

CA::Render::Context* CA::Context::retain_render_ctx()
{
	// 16 call
	// %rdi = CA::Context::_lock
	OSSpinLockLock(&CA::Context::_lock);
	CA::Render::Context*& retRenderContext = rbx;				// &=rbx
	retRenderContext = 0;
	// 30
	if (!(0 == (CA::Render::Context*)this->_70)) {
		// 32 call
		retRenderContext = ((CA::Render::Object*)this->_70)->ref();
	} // 40
	// 47 call
	OSSpinLockUnlock(&CA::Context::_lock);
	return retRenderContext;
}

CA::Context** CA::Context::retain_all_contexts(bool flag1, CA::Context** contexts, unsigned long& length)
{
	CA::Context**& retContexts = r12;							// &=r12
	CA::Context**& contextsBuffer = r15;						// &=r15
	r14 = &length;
	contextsBuffer = contexts;									// use the given contexts buffer if length is enough, otherwise will allocate buffer from heap.
	ebx = flag1;
	// 26 call
	// %rdi = CA::Context::_lock
	OSSpinLockLock(&CA::Context::_lock);

	int32_t& count = edi;										// &=edi, till 149
	count = 0;
	// 43
	if (!(0 == (rax = CA::Context::_contexts))) {
		CA::Context*& context = rax;							// &=rax
		// do {
	_b45:	 // from 64
			 // 47
		if (true == bl 
			|| !(0 == context->_0)) {
			// 54
			++count;
		}
		// 57
		context = context->_8;
			 // 64
		if (context)
			goto _b45;
		// } while ((context = context->_8));

		// 69
		if (!(count <= length)) {
			rax = count >> 0x3d;							// result the highest 2 bits.
			rcx = count << 0x3 + 0x20;
			retContexts = 0;
			 // 103
			if ((rax & 0xff & 0xf)) {
				eax = 0;
				// gen jmp 212
				// goto _f212; inilne #0 
				length = 0;
				// 222 call
				OSSpinLockUnlock(&CA::Context::_lock);
				return retContexts;
			}
			eax = 0;
			// 112
			if (!(count > 0x190)) {
				// 131 call
				contextsBuffer = x_mem_alloc_bucket(0xfffffffff >> 0x4);
			} 
			else {// 141
			  // 141 call
				contextsBuffer = x_mem_alloc_size(count << 0x3);
			}
		} // 149
	} // 149
_f149:	 // from 139
_f149:	 // from 69
	retContexts = 0;
	int& retLength = eax;
	eax = 0;
	  // 160
	if (!(0 == contextsBuffer)) {
		// 174
		if (!(0 == (rcx = CA::Context::_contexts))) {
			bl = true;
			CA::Context*& context = rcx;					// &=rcx
			// do {
		_b179:	 // from 207
				 // 183
			if (0 != context->_0) {
				// gen jmp 189
				goto _f189;
			} // 187
			else if (true == bl) {
				// gen jmp 200
				goto _f200;
			}
		_f189:	 // from 183
			contextsBuffer[retLength] = context;
			++retLength;
			++context->_0;									// ++refcnt
		_f200:	 // from 187
			context = context->_8;
				 // 207
			if (context)
				goto _b179;
			// } while ((context = context->_8));
		} // 209
		retContexts = contextsBuffer;
	} // 212
_f212:	 // from 103
	length = retLength;
	// 222 call
	OSSpinLockUnlock(&CA::Context::_lock);
	return retContexts;
}


mach_port CA::Context::client_port()
{
	// _60 to _18
	extern mach_port* mach_task_self_;
	rbx = this;
	// 22
	if (!(0 != this->_a8)) {
		mach_port& client_port = _14;						// &=_14;
		client_port = 0;

		// 54 call
		mach_port_allocate((mach_port)*mach_task_self_, 0x1, &client_port);
		// 72 call
		mach_port_insert_right((mach_port)*mach_task_self_, (mach_port)client_port, (mach_port)client_port, 0x14);
		// 84 call
		;
		struct _dispatch_source_type_s;
		extern _dispatch_source_type_s* _dispatch_source_type_mach_recv;
		dispatch_source_t& source = rax;					// &=rax
		// 104 call
		// %rdi = (void *)0x00000001066081b0: _dispatch_source_type_mach_recv
		source = dispatch_source_create(_dispatch_source_type_mach_recv, client_port, 0, (dispatch_queue_t)dispatch_get_global_queue(0x2, 0));
		this->_a0 = source;

		extern Class _NSConcreteStackBlock;
		extern void ___ZN2CA7Context11client_portEv_block_invoke(struct _NSStackBlock*);
		extern uintptr_t(*__block_descriptor_tmp)[];
		struct _NSStackBlock& event_handler = *(struct _NSStackBlock*)&_38;
		event_handler.isa = _NSConcreteStackBlock;
		event_handler.flag = 0xc0000000;
		event_handler.refcnt = 0;
		event_handler.invoke = &___ZN2CA7Context11client_portEv_block_invoke;
		event_handler.descriptor = __block_descriptor_tmp;
		MACRO_NSStackBlock_SET_PRIVSTACK(event_handler, 0, mach_port, client_port);
		// 176 call
		// %rcx = __block_descriptor_tmp
		// %rcx = ___ZN2CA7Context11client_portEv_block_invoke
		dispatch_source_set_event_handler(source, &event_handler);

		extern void ___ZN2CA7Context11client_portEv_block_invoke_2(struct _NSStackBlock*);
		extern uintptr_t(*__block_descriptor_tmp2)[];
		struct _NSStackBlock& cancel_handler = *(struct _NSStackBlock*)&_60;
		cancel_handler.isa = _NSConcreteStackBlock;
		cancel_handler.flag = 0xc0000000;
		cancel_handler.refcnt = 0;
		cancel_handler.invoke = &___ZN2CA7Context11client_portEv_block_invoke_2;
		cancel_handler.descriptor = __block_descriptor_tmp2;
		MACRO_NSStackBlock_SET_PRIVSTACK(cancel_handler, 0, mach_port, client_port);
		// 238 call
		dispatch_source_set_cancel_handler(source, &cancel_handler);
		this->_a8 = (mach_port)client_port;
		// 259 call
		dispatch_resume(source);
	} // 270
	return (mach_port)this->_a8;
}

mach_port CA::Context::create_fence_port()
{
	// _10 to _8
	mach_port& fence_port = _4;								// &=_4
	// 20
	if (!(0 == (CA::Render::Context*)this->_70)) {
		// 22 call
		fence_port = CA::Render::Fence::create_port();
	} // 32
	else {
		fence_port = 0;
		// 41
		if (!(this->_c8 & 0xff & 0x1)) {
			// 53 call
			_CASCreateFencePort(this->_90, &fence_port);
		}
	} // 61
_f61:	// from 30
	return fence_port;
}

#if 0
#pragma mark- slot
#endif

int32_t CA::Context::new_slot()
{
	int32_t& slot = r14d;								// &=r14d or _14
	CA::Render::Context*& renderContext = rdi;			// &=rdi, till 56
	renderContext = (CA::Render::Context*)this->_70;
	// 21
	if (!(0 == renderContext)) {
		// 27 call
		pthread_mutex_lock(&renderContext->_28);
		// 36 call
		slot = renderContext->new_slot();
		// 56 call
		pthread_mutex_unlock(&renderContext->_28);
		// 61
		// goto _f126; inline #0
		return slot;
	} // 63
	else {
		// 70
		if (!(this->_c8 & 0xff & 0x1)) {
			// 85 call
			eax = _CASCreateSlot(this->_90, this->_58, &slot);
			// 95
			if (!(0x10000003 != eax)) {
				// 104
				// goto _f116; inline #0
				slot = 0;
				return slot;
			} // 106
			  // 108
			if (!eax) {
				// 114
				// goto _f126; inline #0
				return slot;
			} // 116
		} // 116
	_f116:	// from 104
		slot = 0;
	}
_f126:	// from 114
_f126:	// from 61
	return slot;
}

int32_t CA::Context::new_image_slot(unsigned int flag1, unsigned int flag2, bool bWhat)
{
	r12d = bWhat;
	r14d = flag2;
	r15d = flag1;
	r13 = this;
	CA::Render::Context*& renderContext = rdi;			// &=rdi, till 76
	renderContext = (CA::Render::Context*)this->_70;
	// 33
	if (!(0 == renderContext)) {
		// 39 call
		pthread_mutex_lock(&renderContext->_28);
		// 58 call
		ebx = renderContext->new_image_slot(flag1, flag2, bWhat);
		// 76 call
		pthread_mutex_unlock(&renderContext->_28);
	} // 83
	else {
		// 91
		if (!(this->_c8 & 0x1)) {
			// 118 call
			eax = _CASCreateImageSlot(this->_90, this->_58, flag1, flag2, bWhat, &_2c);
			// 128
			if (!(0x10000003 != eax)) {
				// 138
				// goto _f149; inline #0
				return 0;
			} // 140
			  // 142
			if (!eax) {
				ebx = _2c;
				// 147
				// goto _f158;
				return ebx;
			} // 149
		} // 149
	_f149:	// from 138
		ebx = 0;
	} 
_f158:	// from 147
_f158:	// from 81
	return ebx;
}

void CA::Context::delete_slot(unsigned int slot)
{
	CA::Transaction::add_command(0xb, this->_5c, slot, 0);
}


bool CA::Context::connect_local()
{
	CA::Render::Context*& renderContext = rbx;						// &=rbx
	bool& isOK = r14d;												// &=r14d
	r15 = this;
	isOK = false;
	// 18 call
	renderContext = new (x_mem_alloc0_bucket(0x14))
	// 43 call
						CA::Render::Context((__CFDictionary const*)this->_80, (unsigned int)0, (unsigned int)0);
	this->_70 = renderContext;
	// 55
	if (!(0 == renderContext)) {
		// 62 call
		;
		// 69
		if (!(true == _CFExecutableLinkedOnOrAfter(0x3eb))) {
			OSAtomicOr32(0x80000, (volatile int32_t*)&renderContext->_8);
		} // 83
		this->_58 = renderContext->_c;
		isOK = true;
	} // 97
	return isOK;
}


bool CA::Context::connect_remote()
{
	// _50 to _30
	
	r13 = this;
	extern void** __stack_chk_guard;
	_30 = *__stack_chk_guard;
	char*& cstrPortName = rbx;											// &=rbx
	cstrPortName = 0;
	// 47
	if (0 == this->_80) {
		// gen jmp 189
		goto _f189;
	} 
	else {
		extern __CFString* kCAContextPortNumber;
		__CFValue*& portNumber = rax;									// &=rax
		// 63 call
		portNumber = CFDictionaryGetValue((__CFDictionary*)this->_80, kCAContextPortNumber);
		// 71
		if (nil == portNumber) {
			// gen jmp 87
			goto _f87;
		}
		else { // 71 next
			   // 76 call
			ebx = CA_CFIntValue(portNumber);
			eax = 0;
			// 85
			goto _f201;
		}
	}// 85
_f87:	// from 71
	ebx = 0;
		// 99
	if (!(0 == this->_80)) {
		extern __CFString* kCAContextPortName;
		__CFString*& portName = r14;									// &=r14
		// 111 call
		portName = CFDictionaryGetValue((__CFDictionary*)this->_80, kCAContextPortName);
		// 124
		if (!(nil == portName)) {
			// 134 call
			cstrPortName = CFStringGetCStringPtr(portName, 0x8000100);
			// 145
			if (cstrPortName) {
				// gen jmp 189
				goto _f189;
			} 
			else {
				cstrPortName = alloca(0x400);
				// 176 call
				;
				// 183
				if (false == CFStringGetCString(portName, cstrPortName, 0x400, 0x8000100)) {
					// gen jmp 486
					// goto _f486; inline #0
					// 488
					// goto _f656; inline #1
					return false;
				}
			}// 189
		} // 189
	} // 189
_f189:	// from 145
_f189:	// from 47
	mach_port& srvPort = ebx;											// &=ebx
	al = true;
	  // 192 call
	srvPort = CARenderServerGetServerPort(cstrPortName);
_f201:	// from 85
		// 203
	if (0 == srvPort) {
		// gen jmp 486
		// goto _f486; inline #0
		// 488
		// goto _f656; inline #1
		return false;
	}
	else { // 203 next
		_34 = true;														// via eax
		__CFData*& plistData = r12;										// &=r12
		   // 217 call
		r15d = (false == _CFExecutableLinkedOnOrAfter(0x3eb));
		plistData = 0;
		// 244
		if (!(0 == this->_80)) {
			extern __CFAllocatorZone* kCFAllocatorMallocZone;
			// 266 call
			plistData = CFPropertyListCreateData(kCFAllocatorMallocZone, this->_80, 0x64, 0, 0);
			// 284
			if (!(0 == this->_80)) {
				extern __CFString* kCAContextClientPortNumber;
				__CFValue*& portNumber = rax;
				// 296 call
				portNumber = CFDictionaryGetValue(this->_80, kCAContextClientPortNumber);
				// 304
				if (!(0 == portNumber)) {
					_38 = srvPort;
					// 312 call
					eax = (mach_port)CA_CFIntValue(portNumber);
					// 317
					goto _f328;
				} // 319
			} // 319
		} // 319
		_38 = srvPort;
		eax = CA::Context::_user_client_port;
	_f328:	// from 317
		_3c = eax;														// CA::Context::_user_client_port or kCAContextClientPortNumber
		r15d <<= 0x3;
			// 338
		if (0 == plistData)
			// gen jmp 493
			goto _f493;
		// 347 call
		_48 = CFDataGetBytePtr(plistData);
		// 359 call
		rbx = CFDataGetLength(plistData);

		extern mach_port* mach_task_self_;
		_4c = r15d;
		r15d = *mach_task_self_;
		// 381 call
		r14d = getpid();
		// 392 call
		;
		// 464 call
		r15d =
		_CASRegisterClientOptions(_38,		// srvPort
			*mach_task_self_,
			getpid(),
			this->client_port(),
			_3c,							// CA::Context::_user_client_port or kCAContextClientPortNumber
			_4c,							// old r15
			_48,							// CFDataGetBytePtr(plistData)
			ebx,							// CFDataGetLength(plistData)
			&this->_90,
			&this->_58,
			&this->_60
			);
		ebx = _38;
		// 479 call
		CFRelease(plistData);
		// 484
		goto _f582;
	} // 486
_f486:	// from 203
_f486:	// from 183
	  // 488
	goto _f656;
	
	/***
	* this closure is in the case of none of plistData
	*
	*
	*/
_f493:	// from 338
	extern mach_port* mach_task_self_;
	r14d = *mach_task_self_;
		// 503 call
	ebx = getpid();
	// 513 call
	this->client_port();
	// 570 call
	r15d =
	_CASRegisterClient(_38,					// srvPort
		*mach_task_self_,
		getpid(),
		this->client_port(),
		_3c,							// CA::Context::_user_client_port or kCAContextClientPortNumber
		_4c,							// old r15
		&this->_90,
		&this->_58,
		&this->_60
		);
	ebx = _38;
_f582:	// from 484
		// 595 call
	;
	// 602 call
	CA::Render::set_minimum_alignment((unsigned long)CARenderServerGetNeededAlignment(ebx));			// ebx is srvPort
	// 612
	if (!(false == _34)) {
		// 625 call
		mach_port_deallocate(*mach_task_self_, ebx);					// ebx is srvPort
	} // 630
	bl = true;
	  // 635
	if (!(0 == r15d)) {													// r15d is the result of _CASRegisterClient or _CASRegisterClientOptions
		eax = 0;
		ebx = 0;
		// 651 call
		// %rdi = @"unable to register with server: 0x%x"
		NSLog(__cfs("unable to register with server: 0x%x"), r15d);
	} // 656
_f656:	// from 488
	return bl;
}

void CA::Context::get_layer_shmem(unsigned long hkey, CA::Render::ShmemPtr<CA::Render::LayerShmem>& shmemPtr)
{
	// _40 to _20
	// 29
	if (!(0 == this->_70)) {
		// 35 call
		pthread_mutex_lock(&this->_28);
		// 50 call
		((CA::Render::Context*)this->_70)->get_layer_shmem((unsigned long)hkey, (CA::Render::ShmemPtr<CA::Render::LayerShmem>&)shmemPtr);
		return pthread_mutex_unlock(&this->_28);
	} // 78
	CA::Render::Shmem*& newShmem = rbx;									// &=rbx, invalidate until 160
	  // 85
	if (!(this->_c8 & 0xff & 0x1)) {
		// 130
		if (0 != (eax = _CASGetLayerShmem(this->_90, this->_58, hkey, &_1c, &_28, &_38, &_30))) {		// 0 != $(123 call)
			// gen jmp 187
			// goto _f187; inline #0
				// 192
			if (!(0x10000003 != eax)) {
				this->_c8 |= 0x1;
				// 201
				// goto _f220; inline #0
				return;
			}
		} // 160
		else if (0 == (newShmem = CA::Render::Shmem::new_shmem((unsigned int)_1c, (unsigned long)_28, (unsigned long long)0, false, (unsigned int)0x1))) {
			// gen jmp 203
			goto _f203;
		}
		else { // 160 next
			   // 172 call
			shmemPtr->set(newShmem, (unsigned long)_38);
			// 180 call
			((CA::Render::Object*)newShmem)->unref();
			// 185
			// goto _f220; inline #0
			return;
		} // 187
		// 187 to 201 is a jmpBlock
	_f203:	// from 160
		extern mach_port* mach_task_self_;				// ipc_space
		// 215 call
		mach_port_deallocate(*mach_task_self_, _1c);
	} // 220
_f220:	// from 201
_f220:	// from 185
	return;
}

bool CA::Context::get_layer_renderer_info(unsigned long flag1, unsigned int flag2, _CARenderRendererInfo* info, unsigned long flag3)
{
	// _50 to _30

	r14 = info;
	r15d = flag2;
	r12 = flag1;
	r13 = this;
	CA::Render::Context*& rndrContext = rbx;							// &=rbx
	// 33
	if (flag3 < 0xc) {
		// goto _215; inline #0
		return false;
	}
	rndrContext = this->_70;
	;
	// 67
	if (!(0 == rndrContext)) {
		bool& isOK = bl;											// &=bl, invaliate until 107
		// 76 call
		pthread_mutex_lock(&rndrContext->_28);
		// 102 call
		isOK = rndrContext->get_layer_renderer_info(flag1, flag2, (int&)_2c, (unsigned int&)_30, (unsigned int&)_34);
		// 112 call
		pthread_mutex_unlock(&(rndrContext->_28);
		// 117
		// goto _f187; inline #0
		// 189
		if (!(false == isOK)) {
			r14->_0 = _2c;
			r14->_4 = _30;
			r14->_8 = _34;
			// 213
			// goto _f217; inline #1
			return true;
		} // 215
		return false;
	} // 119
	  // 127
	if (!(0x1 & this->_c8)) {
		// 162 call
		eax = _CASGetLayerRendererInfo(this->_90, this->_58, flag1, flag2, (int&)_2c, (unsigned int&)_30, (unsigned int&)_34);
		// 172
		if (!(0x10000003 != eax)) {
			this->_c8 |= 0x1;
		} // 182
	_f187:	 // from 117
			 // 189
		if (!(false == (eax == 0))) {
			// 213
			// goto _f217; inline #0
			return true;
		} // 215
	} // 215

	return false;

}

bool CA::Context::get_backdrop_layer_statistics(unsigned long flag, double* unknownF)
{
	// _50 to _28
	// 46
	if (!(0 == this->_70)) {
		CA::Render::Context*& rndrContext = rdi;						// &=rdi
		rndrContext = this->_70;
		// 52 call
		pthread_mutex_lock(&rndrContext->_28);
		// 67 call
		rndrContext->get_backdrop_layer_statistics(flag, (double*)unknownF);
		// 83 call
		pthread_mutex_unlock(&rndrContext->_28);
		// 88
		// goto _f187; inline #0
		return true;
	} // 90
	  // 97
	if (!(0x1 & this->_c8)) {
		// 115 call
		eax = _CASGetBackdropLayerStatistics(this->_90, this->_58, flag, (double*)&_50);
		// 125
		if (!(0x10000003 != eax)) {
			this->_c8 |= 0x1;
			// 134
			// goto _f184; inline #0
			return false;
		} // 136
		  // 138
		if (!eax) {
			memcpy(unknownF, &_50, sizeof(double) * 5);
			// 182
			//goto _f187; inline #0
			return true;
		} // 184
	} // 184
_f184:	 // from 134
	return false;
}

bool CA::Context::synchronize(unsigned int flag1, int flag2)
{
	r13 = this;
	r14 = &this->_10;
	// 29 call
	pthread_mutex_lock(&this->_10);

	r15d = this->_88;
	// 43
	if (!(0 == flag1)) {
		r15d = (this->_88 >= flag1) ? flag1 : this->_88;
	} // 52
	  // 61
	if (!(r15d <= this->_8c)) {
		// 72
		if (!(0 == this->_70)) {
			// 80 call
			((CA::Render::Context*)this->_70)->synchronize(r15d, flag2);;
		} // 85

		  // 94
		if (!(0 == this->_90)) {
			// 104
			if (!(0x1 & this->_c8)) {
				// 116 call
				eax = _CASSynchronize(this->_90, this->_58, r15d, flag2);
				// 126
				if (!(0x10000003 != eax)) {
					this->_c8 |= 0x1;
				} // 136
			} // 141
		} // 141
		  // 143
		if (!(true == (eax == 0x0))) {
			// 147
			// goto _f158; inline #0
			pthread_mutex_unlock(&this->_10);
			return false
		} // 149
		this->_8c = r15d;
	} // 158
_f158:	 // from 147
	pthread_mutex_unlock(&this->_10);
	return true;
}


void CA::Context::set_objc_context(void const* ctx)
{
	OSSpinLockLock(&CA::Context::_lock);
	((X::WeakDetails::Ptr*)&this->_50)->set((objc_object*)ctx);
	OSSpinLockUnlock(&CA::Context::_lock);
}