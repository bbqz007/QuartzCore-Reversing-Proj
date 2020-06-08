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
#include "CA.ops.h"
#include "OSAtomic.h"
#include "CA.oc.h"

void CA::Layer::set_visible(unsigned int visibleFlags)
{
	r15d = visibleFlags;
	rbx = this;
	CA::Transaction*& transaction = r14;
	// 20 call
	transaction = CA::Transaction::ensure_compat();
	// 33
	if (!(this->_8 == 0x0)) { // 28 (rbx->_8 == 0x0)
		extern Class NSException;
		eax = 0;
		// 69 call
		objc_msgSend(NSException, "raise:format:", __cfs("CALayerInvalid"),
			__cfs("layer %@ has a superlayer; so cannot be added to a context"), (CALayer*)this->_10);
	} // 75
	eax = 0x800 & this->_84;
	// 89
	if (!(0 == visibleFlags)) { // 86 (0 == r15d)
		r13d = this->_a4;
		// 100
		if (0 == (0x800 & this->_84)) // 98 (0 == eax)
			goto _f189;
		// 105
		if (this->_a4 == visibleFlags) { // 102 (r13d == r15d)
			// inline jmp 174
			return;
		}
		else { // 105 next
			eax = 0;
			return objc_msgSend(NSException, "raise:format:", __cfs("CALayerInvalid"),
				__cfs("cannot add layer to one context while visible in another"));
		}
	} // 157
	  // 159
	if (!(0 == eax)) { // 157 (0 == eax)
			 // 164 call
		transaction->lock();
		r12d = 0;
		// 172
		// goto _f298; inline #0
		// 308 call
		// %edx = r12b
		this->mark_visible(transaction, false);
		return transaction->unlock();
	} // 174


_f189:	 // from 100
		 // 192 call
	transaction->lock();
	r12b = 0x1;
	// 203
	if (!(r13d == r15d)) { // 200 (r13d == r15d)
		this->_8 = 0x0;
		this->_a4 = visibleFlags;
		// 226 call
		transaction->remove_root((CA::Layer*)this);
		// 237 call
		this->mark_context_changed(transaction);
		r15 = (CA::Render::ShmemPtr<CA::Render::LayerShmem>*) this->_b8;
		// 252
		if (!(0 == this->_b8)) { // 249 (0 == r15)
			this->_b8 = 0x0;
			this->_b4 = 0x0;
			// 281
			if (!(0 == this->_b8->_Ptr)) { // 278 (0 == rdi)
				// 283 call
				((CA::Render::Object*)this->_b8->_Ptr)->unref();
			} // 288
			// 293 call
			x_mem_dealloc_bucket(0, this->_b8);
		} // 298
	} // 298
_f298:	 // from 172
	// 308 call
	// %edx = r12b
	this->mark_visible(transaction, true);
	return transaction->unlock();
}


void CA::Layer::set_position(CA::Vec2<double> const& position, bool bAnima)
{
	ebx = bAnima;
	r15 = &position;
	r14 = this;
	// 41
	if (!(0 == __isnand((double&)position.vec[1] + (double&)position.vec[0]))) { // 39 (0 == eax)
			 // 46
		if (!(true == (bAnima ^ true))) {
			// 60
			if (0 != __isnand((double&)position.vec[0])) { // 58 (0 != eax)
				// gen jmp 77
				goto _f77;
			} // 75
			else if (0 == __isnand((double&)position.vec[1])) { // 73 (0 == eax)
				// gen jmp 152
				goto _f152;
			}
		_f77:	 // from 60
			  // 77 testl $0x60000, 0x4(%r14)
			  // 85
			if (0x60000 & this->_4) { // 77 (0x60000 & r14->_4)
				// gen jmp 152
				goto _f152;
			} // 99
			else if (false == _CFExecutableLinkedOnOrAfter(0x3ef)) { // 97 (0 == al)
				// inline jmp 331
				al = 0x2;
				// 351 call
				NSLog(__cfs("CALayer position contains NaN: [%g %g]"), (double&)position.vec[0], (double&)position.vec[1]);
				(double&)_40 = position.vec[0];
				// 377
				if (!(0 != __isnand(position.vec[0]))) { // 371 (0 != eax)
					xmm0.sd = (double&)_40;
				} // 384
				else {
					xmm0 = 0.;
				}
				(double&)_40 = xmm0.sd;
				(double&)_48 = (double&)position.vec[1];
				// 411
				if (!(0 != __isnand((double&)position.vec[1]))) { // 405 (0 != eax)
					xmm0.sd = (double&)_48; ;
				} // 418
				else {
					xmm0 = 0.;
				}
				xmm1.sd = (double&)_40;
				(double&)_30 = xmm1.sd;
				(double&)_28 = xmm0.sd;
				// 442 call
				this->set_position((CA::Vec2<double> const&)*(CA::Vec2<double> const*)&_30, false);
				return;
			}
			else { // 99 next
				extern Class NSException;
				al = 0x2;
				// 146 call
				objc_msgSend(NSException, "raise:format:", __cfs("CALayerInvalidGeometry"), __cfs("CALayer position contains NaN: [%g %g]"),
					position.vec[0], position.vec[1]);
			} // 152
		} // 152
	} // 152
_f152:	 // from 85
_f152:	 // from 75
	CA::Transaction*& transaction = r12;
	// 152 call
	transaction = CA::Transaction::ensure_compat();
	// 163 call
	transaction->lock();
	// 176
	if (!(0 == ((0x40 << 8) & this->_84))) { // 168 (0 == ((0x40<<8) & r14->_84))
		// 183 call
		this->fetch_geometry(transaction);
	} // 188
	  // 199
	if ((double&)this->_30 != (double&)position.vec[0]) { // 194 (xmm0.sd != (double&)r15->_0)
		// gen jmp 215
		goto _f215;
	} // 213
	else if ((double&)this->_38 == (double&)position.vec[1]) { // 207 (xmm0.sd == (double&)r15->_8)
		// inline jmp 325
		rbx = (CA::Layer::State*) &this->_28;
		// 329
   // goto _b284; inline #1
		CA::Layer::State*& state = rbx;
		// 288
		if (!((0x10 << 8) & state->_60)) { // 284 ((0x10<<8) & rbx->_60)
			CA::Layer::State*& state = rax;
			// 296 call
			state = this->writable_state(transaction);
			state->_60 |= 0x10 << 8;
		} // 305
		return transaction->unlock();
	}
_f215:	 // from 199
  // 230 call
	this->begin_change(transaction, (unsigned int)0x163, (objc_object*&)*(objc_object**)&_38);
	CA::Layer::State*& state = rbx;
	// 241 call
	state = this->writable_state(transaction);
	state->_8.vec[1] = position.vec[1];
	state->_8.vec[0] = position.vec[0];
	// 279 call
	this->end_change(transaction, (unsigned int)0x163, (objc_object*)_38);
_b284:	 // from 329, not a loop
		 // 288
	if (!((0x10 << 8) & state->_60)) { // 284 ((0x10<<8) & rbx->_60)
		CA::Layer::State*& state = rax;
		// 296 call
		state = this->writable_state(transaction);
		state->_60 |= 0x10 << 8;
	} // 305
	return transaction->unlock();
}


void CA::Layer::set_next_animation_time(CA::Transaction* transaction, double nextTime1, double nextTime2)
{
	extern int64_t ent_off__0x6cd4e;	// animation_state (.2) + 7
	extern double ent_off__0x3bea6;
	extern double ent_off__0x3bebe;
	(double&)_8 = nextTime1;
	// 21
	if (!(ent_off__0x6cd4e == 0x0)) { // 13 (rip->_6cd39 == 0x0)
		(double&)_10 = nextTime2;
		// 28 call
		this->collect_non_visible_animations(transaction);
		xmm1.sd = (double&)_10; ;
	} // 38
	  // 46
	if (!(nextTime2 >= (double&)ent_off__0x3bea6)) { // 38 (xmm1.sd >= (double&))
			 // 74 call
		CA::call_at_time((void(*)(double, void*))&CA::Layer::animation_heart_beat,
			max((double&)ent_off__0x3bebe + nextTime1, nextTime2),
			(void*)0);
	} // 79
	extern int64_t ent_off__0x6cd46;	// animation_state (.1) + 7
	extern int64_t ent_off__0x6cd36;	// animation_state (.0)
	extern int64_t ent_off__0x6cd3e;	// animation_state (.1)
	  // 87
	if (!(ent_off__0x6cd46 != 0x0) // 79 (rip->_6ccef != 0x0)
		// 99
		&& !(0 != ent_off__0x6cd36) // 96 (0 != rax)
		// 111
		&& !(0 != ent_off__0x6cd3e)) { // 108 (0 != rax)
		return;
	} // 119

	extern bool dont_dispatch_animation_callbacks;
	// 131 $(124 call)
	if (0 == _CFExecutableLinkedOnOrAfter(0x3f2)) { // 129 (0 == al)
		// inline jmp 143
		return CA::call_at_time((void(*)(double, void*))&CA::Layer::run_animation_callbacks_compat,
			nextTime1, (void*)0);
	} // 141
	else if (0 == dont_dispatch_animation_callbacks) { // 139 (0 == al)
		// inline jmp 167
		return dispatch_async_f(_dispatch_main_q, 0, &CA::Layer::run_animation_callbacks);
	}
	return CA::call_at_time((void(*)(double, void*))&CA::Layer::run_animation_callbacks_compat,
		nextTime1, (void*)0);
}


void CA::Layer::set_needs_layout()
{
	rbx = this;
	// 17
	if (!(0 == (0x60000 & this->_4))) { // 10 (0 == (0x60000 & rbx->_4))
		return;
	}
	CA::Transaction*& transaction = r14;
	// 24 call
	transaction = CA::Transaction::ensure_compat();
	// 35 call
	// %rdi = r14
	transaction->lock();

	uint32_t*& thread_flags_place = rax;							// &=rax, invalidate until 58
	uint32_t& thread_flags = ecx;
	rax = (int64_t)(int32_t&)transaction->_8;
	// 47
	if (!(0 > transaction->_8)) { // 44 (0 > rax)
		thread_flags = ((int32_t*)&this->_a8)[transaction->_8];
		// 58
		if (!(0 == thread_flags)) { // 56 (0 == ecx)
			thread_flags_place = &((int32_t*)&this->_a8)[transaction->_8];
			// 68
			goto _f83;
		} // 70
	} // 70
	  // 76 call
	thread_flags_place = (uint32_t*)this->thread_flags_(transaction);
	thread_flags = *(uint32_t*)thread_flags_place;
_f83:	 // from 68
		 // 86
	if (!(0x20 & (thread_flags & 0xff))) { // 83 (0x20 & cl)
		*thread_flags_place = thread_flags | 0x20;
		// 96 call
		this->invalidate_layout();

		uint32_t*& thread_flags_place = rcx;							// &=rcx, invalidate until 58
		uint32_t& thread_flags = edx;									// &=edx
		CA::Layer*& itLayer = rbx;					// &=rbx, begin at this
		itLayer = this;								// fake

		for (;;) {
		_b101:	 // from 174
			itLayer = itLayer->_8;
			// 108
			if (0 == itLayer) { // 105 (0 == rbx)
				break;
			}
			rax = (int64_t)(int32_t&)transaction->_8;
			// 117
			if (!(0 > transaction->_8)) { // 114 (0 > rax)
				thread_flags = ((int32_t*)&itLayer->_a8)[transaction->_8];
				// 128
				if (!(0 == thread_flags)) { // 126 (0 == edx)
					thread_flags_place = &((int32_t*)&itLayer->_a8)[transaction->_8];
					// 138
					goto _f156;
				} // 140
			} // 140
			  // 146 call
			thread_flags_place = (uint32_t*)itLayer->thread_flags_(transaction);
			thread_flags = *thread_flags_place;
		_f156:	 // from 138
				 // 159
			if (0x40 & (thread_flags & 0xff)) { // 156 (0x40 & dl)
				break;
			}
			*thread_flags_place = thread_flags | 0x40;
			// 169 call
			itLayer->invalidate_layout();
			// 174
			goto _b101;
		}	// end for, named _b101
	} // 195


	return transaction->unlock();
}


void CA::Layer::set_needs_display_in_rect(CGRect const& rect)
{
	rbx = &rect;
	r12 = this;

	CA::Transaction*& transaction = r14;				// &=r14, whole scope
	CALayer*& ocLayer = r13;							// &=r13, whole scope
	CGImage*& cgImage = _58;							// &=_58,
	// 32
	if (!(0x60000 & this->_4)) { // 23 (0x60000 & r12->_4)
			 // 38 call
		transaction = CA::Transaction::ensure_compat();
		// 49 call
		transaction->lock();
		xmm0 = 0.;
		// 58 ucomisd 0x10(%rbx), %xmm0
		// 63
		if (!(0. == (double&)rect.size.height)) { // 58 (xmm0.sd == (double&)rbx->_10)
				 // 74
			if (!(0. == (double&)rect.size.width)) { // 69 (xmm0.sd == (double&)rbx->_18)
				ocLayer = this->_10;
				// 95 call
				cgImage = objc_msgSend(ocLayer, "contents");
				// 110
				if (!(cgImage == 0x0)) { // 105 (_58 == 0x0)
					// 136 (120 call) != (128 call)
					if (!(CFGetTypeID(cgImage) != CABackingStoreGetTypeID())) { // 133 (r15 != rax)
						CGRect& invalidateRect = *(CGRect*)_50;		

						invalidateRect.position.x = rect.position.x - this->_40;
						invalidateRect.position.y = rect.position.y - this->_48;
						invalidateRect.size.height = rect.size.height;
						invalidateRect.size.width = rect.size.width;

						// 187
						if (!((0x1 << 24) & this->_84)) { // 178 ((0x1<<24) & r12->_84)
							xmm0.sd = rect.size.height;		// via rax
							xmm1.sd = rect.size.width;			// via rcx
							// 199
							goto _f254;
						} // 201
						else {
							double& scale = xmm0.sd;
							// 211 call
							scale = objc_msgSend(ocLayer, "contentsScale");
							invalidateRect.position.x *= scale;
							invalidateRect.position.y *= scale;
							invalidateRect.size.height *= scale;
							invalidateRect.size.width *= scale;
							xmm1.pd[0] = invalidateRect.size.height;
							xmm1.pd[1] = invalidateRect.size.width;
						}
					_f254:	 // from 199
						extern double ent_off__0x49cde;
						CABackingStoreInvalidate(cgImage,
							(xmm0.sd > (double&)ent_off__0x49cde)
							? 0 : ((xmm1.sd > (double&)ent_off__0x49cde) ? 0 : (CGRect*)&invalidateRect));
					} // 293
				} // 293
			} // 293
		} // 293
		  // 309 call
		this->mark(transaction, (unsigned int)0x100, (unsigned int)0x200);
		// 317 call
		transaction->unlock();
	} // 322

	return;
}


uint32_t* CA::Layer::thread_flags_(CA::Transaction* transaction)
{
	uint32_t*& thread_flags = r15;								// &=r15
	rbx = transaction;
	r14 = this;
	// 27
	if (!(0 != transaction->_0->_10)) {
		// 32 call
		transaction->ensure_implicit();
	} // 37
	  // 40 call
	transaction->lock();
	// 52
	if (transaction->_8 < 0) {
		// gen jmp 75
		// goto _f75; inline #0
	_f75:	// from 52
			// 84 call
		thread_flags = (uint32_t*)x_hash_table_lookup(transaction->_10, this, 0);
		// 95
		if (!(0 == thread_flags)) {
		_f97:	// from 73
				// 100 call
			transaction->unlock();
			// 105
			// goto _f344; inline #0
			return thread_flags;
		} // 110 natural flow
		goto _f110;
	} // 63
	else if (0 == this->_a8[transaction->_8]) {
		// gen jmp 110
		goto _f110;
	}
	else { // 63 next
		thread_flags = (uint32_t*) &this->_a8[transaction->_8];
		   // 73
		// goto _f97; inline #0
		// 100 call
		transaction->unlock();
		// 105
		// goto _f344; inline #1
		return thread_flags;
	} // 75


_f110:	// from 63
	  // 117
	if (0 == (CALayer*)this->_10) {
		// gen jmp 169
		// goto _f169; inline #0
		// 172 call
		transaction->unlock();
		thread_flags = (uint32_t*)&this->_4;
		// 184
		// goto _f344; inline #1
		return thread_flags;
	}

	CA::Transaction::Shared*& shared = r12;						// &=r12
	shared = transaction->_0;
	// do {
_b129:	// from 143
	eax = this->_10->_attr._0;
		// 137
	if ((this->_10->_attr._0 + 1) < 0x2) {
		// gen jmp 169
		// goto _f169; inline #0
		// 172 call
		transaction->unlock();
		thread_flags = (uint32_t*)&this->_4;
		// 184
		// goto _f344; inline #1
		return thread_flags;
	} 
	// 143
	if (false == OSAtomicCompareAndSwap32(this->_10->_attr._0, this->_10->_attr._0 + 1, (volatile int32_t*)&this->_10->_attr._0))
		goto _b129;
	// } while(OSAtomicCompareAndSwap32(old, old+1, &target));


	/***
	* allocate a quadword for thread_flags from heap or inline buffering.
	* 
	*/
	// 152
	if (transaction->_8 < 0) {
		// gen jmp 189
		// goto _f189; inline #0
	_f189:	// from 152
		rdi = shared->_50;
		rax = shared->_50->_10;
		// 202
		if (!(shared->_50->_10 >= 0x8)) {
			// 209 call
			thread_flags = (uint32_t*)x_heap_malloc_small_(shared->_50, 0x8);
		} // 219
		else {
			thread_flags = shared->_50->_8;
			shared->_50->_10 = shared->_50->_10 - 0x8;
			shared->_50->_8 = thread_flags + 1;
		} // 239
		r13 = &shared->_50;
		// 254 call
		x_hash_table_insert(transaction->_10, this, thread_flags);
		// natural flow to 259
		goto _f259;
	}
	else { // 152 next
		thread_flags = (uint32_t*)&this->_a8[transaction->_8];
		r13 = &shared->_50;
		   // 167
		goto _f259;
	} // 169

	  /***
	  * allocate a quadword for slist from heap or inline buffering.
	  * use slist add this to the slist of CA::Layer
	  */
_f259:	// from 167
	rdi = shared->_50;											// via *r13;
	rcx = shared->_50->_10;
		// 271
	if (!(shared->_50->_10 >= 0x10)) {
		// 278 call
		rax = (uint32_t*) x_heap_malloc_small_(shared->_50, 0x10);
	} // 285
	else {
		rax = shared->_50->_8;
		shared->_50->_10 -= 0x10;
		shared->_50->_8 = (uint32_t*)rax + 2;
	} // 305
	*((uint32_t*)rax + 1) = shared->_70;
	*(uint32_t*)rax = this;
	shared->_70 = rax;

		// 325 call
	transaction->unlock();
	// 339 call
	this->latch_thread_flags(transaction, (unsigned int*)thread_flags);
	return thread_flags;
}

void CA::Layer::set_model_layer(CA::Transaction* transaction, CA::Layer* modelLayer)
{
	r15 = modelLayer;
	r14 = this;
	// 27
	if (transaction->_8 < 0) {
		// gen jmp 40
		goto _f40;
	} // 38
	else if (0 != this->_a8[transaction->_8]) {
		// gen jmp 51
		goto _f51;
	}
_f40:	// from 27
	  // 46 call
	modelLayer->thread_flags_(transaction);
_f51:	// from 38
	CA::Transaction::Shared*& shared = rbx;						// &=rbx
	shared = transaction->_0;
		// 64
	if (!(x_hash_table*)shared->_80) {
		r12 = shared->_50;
		// 92 call (,,,,, $(73 call))
		shared->_80 = x_hash_table_new_(0, 0, 0, 0, shared->_50, shared->hash_pool());
	} // 107
	return x_hash_table_insert(shared->_80, this, modelLayer);
}


void CA::Layer::set_mask(CALayer* maskLayer)
{
	CA::Transaction*& transaction = r14;						// &=14
	rbx = this;
	r15 = maskLayer;
	// 20 call
	transaction = CA::Transaction::ensure_compat();
	// 35
	if (!(0 == (0x60000 & this->4))) {
		extern Class NSException;
		eax = 0;
		// 71 call
		// %rcx = @"expecting model layer not copy: %@"
		// %rdx = @"CALayerInvalidTree"
		// %rsi = "raise:format:"
		// %rdi = (void *)0x0000000103d130d0: NSException
		objc_msgSend(NSException, "raise:format:", __cfs("CALayerInvalidTree"), __cfs("expecting model layer not copy: %@"), (CALayer*)this->_10);
	} // 77

	  // 81
	if (!(0 == (maskLayer == this->_20))) {
		// 90 call
		transaction->lock();
		// 98
		if (!(0 == maskLayer)) {
			// 119
			if (!(0 == maskLayer->_attr._8->_8)) {
				// 127 call
				((CA::Layer*)maskLayer->_attr._8->_8)->remove_sublayer(transaction, maskLayer);;
				// 132
				goto _f159;
			} // 134
			  // 137 call
			CFRetain(maskLayer);
			// 154 call
			((CA::Layer*)maskLayer->_attr._8)->remove_from_context();;
		} // 159
	_f159:	// from 132

		objc_object*& token = _30;								 // &=_30
		  // 174 call
		this->begin_change(transaction, (unsigned int)0x12a, (objc_object*&)token);

		CA::Layer*& itLayer = rcx;								// &=rcx
		CA::Layer*& tailLayer = rax;							// &=rax
		itLayer = this;
		// do {
	_b182:	// from 192
		tailLayer = itLayer;
		itLayer = itLayer->_8;
			// 192
		if (itLayer)
			goto _b182;
		// }while ( = itLayer->_8);
		r13d = tailLayer->_a4;

		CALayer*& oldMaskLayer = r12;							// &=r12
		oldMaskLayer = this->_20;
		// 208
		if (!(0 == oldMaskLayer)) {
			// 228 call
			((CA::Layer*)oldMaskLayer->_attr._8)->update_removed_sublayer(transaction, (unsigned int)r13d);
		} // 233

		  // 236
		if (!(0 == maskLayer)) {
			// 259 call
			((CA::Layer*)maskLayer->_attr._8)->update_added_sublayer(transaction, (CA::Layer*)this, (unsigned int)r13d);
			CA::Layer*& underlyingLayer = rdi;					// &=rdi;
			unsigned int& thread_flags = rdx;					// &=rdx;
			rdi = maskLayer->_attr._8;
			// 283
			if (transaction->_8 < 0) {
				// gen jmp 296
				goto _f296;
			} // 294
			else if (0 != (thread_flags = underlyingLayer->_a8[transaction->_8])) {
				// gen jmp 306
				goto _f306;
			}
		_f296:	// from 283
			  // 299 call
			thread_flags = underlyingLayer->thread_flags_(transaction);
		_f306:	// from 294
				// 312 call
			this->update_for_changed_sublayers(transaction, (unsigned int)thread_flags);
		} // 317

		this->_20 = maskLayer;
		  // 336 call
		this->end_change(transaction, (unsigned int)0x12a, (objc_object*)token);
		// 344 call
		transaction->unlock();
		// 352
		if (!(0 == oldMaskLayer)) {
			// 374 tail jmp 
			return transaction->release_object((void const*)oldMaskLayer);
		} // 379
	} // 379
	return;
}

void CA::Layer::set_bit_int(unsigned int flag1, unsigned int flag2, unsigned int flag3, unsigned int flag4, unsigned int flag5)
{
	ebx = flag5;						// only used once, then un-avaiable
	r12d = flag4;
	_40 = flag3;
	r14d = flag2;
	_3c = flag1;
	r13 = this;

	CA::Transaction*& transaction = r15;
	// 35 call
	transaction = CA::Transaction::ensure_compat();
	// 46 call
	transaction->lock();
	ebx = flag5 & flag4;
	r14d = flag2 & 0x1f;
	eax = (((int32_t*)&this->_80)[flag2 >> 0x5] >> (flag2 & 0x1f)) & flag4;
	// 85
	if (!((((int32_t*)&this->_80)[flag2 >> 0x5] >> (flag2 & 0x1f)) & flag4)
		!= (flag5 & flag4)) { // 83 (eax != ebx)
		_38 = r15;							// save r15 (transaction)
		r15 = &this->_28;
		// 95
		goto _f188;
	} // 97
	else {
		_48 = rdx;						// save rdx (flag2 >> 0x5)
		_38 = r15;						// save r15 (transaction)
										// 118 call
		this->begin_change(transaction, flag1, (objc_object*&)*(objc_object**)&_30);

		CA::Layer::State*& state = r15;					// &=r15, since 130
														// 130 call
		state = this->writable_state(transaction);
		ebx = ((flag5 & flag4) << (flag2 & 0x1f))
			| (~(flag4 << ((flag2 & 0x1f) & 0xff)) & ((int32_t*)&state->_58)[flag2 >> 0x5]);
		((int32_t*)&state->_58)[flag2 >> 0x5] = ebx;
		// 183 call
		this->end_change(transaction, flag1, (objc_object*)_30);
	}
_f188:	 // from 95
	ebx = flag3 >> 0x5;
	eax = ((int32_t*)&state->_58)[flag3 >> 0x5];
	r14d = 0x1 << (flag3 & 0xff);
	ecx = (uint32_t)(uint8_t&)(flag3 & 0xff & 0x1f);
	// 219 btl %ecx, %eax
	// 222
	if (!(0 != (((int32_t*)&state->_58)[flag3 >> 0x5]
		& (1 << (flag3 & 0xff & 0x1f))))) { // 219 (0 != (eax & (1<<ecx)))
		CA::Layer::State*& state = rax;					// &=rax, short temporary
														// 231 call
		state = this->writable_state(transaction);
		((int32_t*)&state->_58)[flag3 >> 0x5] |= 0x1 << (flag3 & 0xff);
	} // 243
	return transaction->unlock()
}

void CA::Layer::set_bit(unsigned int flag1, unsigned int flag2, unsigned int flag3, bool bWhat, void(CA::Layer::*callback)(CA::Transaction*))
/**
* flag1, flag2, bWhat work together.
* flag1 is an atom of string, which indicate what will be changed. used by begin_change and end_change
* flag2 is a compression dword with pos and which bit. the low 5 bits are which bit to be set. it work at CA::Layer::State::_58;
* bWhat is a control whether run the set-bit or clean-bit.
* flag3 is a compression dword with pos and which bit. the low 5 bits are which bit to be set. it work at CA::Layer::State::_58;
*/
{
	// _60 to _30, 0x38 B
	r15 = this;										// r15(122, 140), then r12; r15(178, 186), then r12
	CA::Transaction*& transaction = _38;			// r12(53, 128), then _38
	objc_object*& token = _30;						// &=_30
	CA::Layer::State*& state = rdx;					// &=rdx, not validate until 161
	// 48 call
	transaction = CA::Transaction::ensure_compat();;
	// 59 call
	transaction->lock();
	r14d = flag2 >> 0x5;
	eax = ((uint32_t*)&this->_80)[r14d];
	r13d = 1 << (flag2 & 0xff);
	ecx = (flag2 & 0x1f);							// 0x1f is mask for 32-1,
	ebx = bWhat;
	al = (eax & (1 << (flag2 & 0x1f)));						// via "btl    %ecx, %eax"
	al ^= bWhat;									// al ^= bl;
	eax = (uint32_t)al;
	// 116
	if (true == (bool)eax) {
		// gen jmp 178
		// goto _f178; inline #0
	_f178:	// from 116
		_38 = r12;									// save transaction
		state = (CA::Layer::State*)&this->_28;
		r12 = r15;									// from now on, r12 is this
		r15d = 0x1;
		// 195
		goto _f281;
	} 
	else {
		_38 = r12;									// save transaction
		// 135 call
		this->begin_change(transaction, (unsigned int)flag1, (objc_object*&)token);
		r12 = r15;									// from now on, r12 is this
		r15d = 0x1;
		// 156 call
		state = CA::Layer::writable_state(transaction);
		// 166
		if (false == bWhat) {
			// gen jmp 197
			// goto _f197; inline #0
		_f197:	// from 166
			r13d ~= r13d;
			eax = r14d;
			state->_58[rax] &= r13d;
			// natural flow to 208
			goto _f208;
		}
		else { // 166 next
			eax = r14d;
			state->_58[rax] |= r13d;
			   // 176
			goto _f208;
		}
	}// 178

	struct cxx_member_method_pointer
	{
		uintptr_t poly_offset;
		union 
		{
			uintptr_t method_location;
			struct
			{
				uintptr_t isVirtualFunc : 1;
				uintptr_t pad : 2;
				uintptr_t vtbl_method_offset : 29;
			};
		};
	};
	cxx_member_method_pointer& cxx_member_method_pointer__callback = *(cxx_member_method_pointer*)&_58;
	::_50;											// 0x10(%rbp)
	::_58;											// 0x18(%rbp)
_f208:	// from 176
		// 215
	if (!(0 == cxx_member_method_pointer__callback.method_location)) {
		CA::Layer* poly = (CA::Layer*) ((uintptr_t)this + cxx_member_method_pointer__callback.poly_offset);
		r14 = rdx;									// save rdx;
		// 233
		if (!(0 == (0x1 & cxx_member_method_pointer__callback.isVirtualFunc))) {
			callback = (*(cpp_virtbl*)poly).virmethod[cxx_member_method_pointer__callback.vtbl_method_offset >> 3];
		} // 243
		  // 251 call
		poly->(*callback)(transaction);
		rdx = r14;									// restore rdx;
	} // 256
	rbx = rdx;										// save rdx;
	  // 273 call
	this->end_change(transaction, (unsigned int)flag1, (objc_object*)token);
	rdx = rbx;										// restore rdx;
_f281:	// from 195
	ebx = flag3 >> 0x5;
	eax = state->_58[flag3 >> 0x5];
	r15d = 1 << (flag3 & 0xff);
	ecx = (flag3 & 0x1f);
		// 308
	if (!(state->_58[flag3 >> 0x5] & (1 << (flag3 & 0x1f)))) {
		// 317 call
		this->writable_state(transaction)->_58[flag3 >> 0x5] |= r15d;
	} // 329
	  // 359 call
	transaction->unlock();
	return;
}

void CA::Layer::set_animations(Animation* anima)
{
	r14 = anima;
	rbx = this;
	// 20
	if (!(0x800 & this->_84)) {
		// 32
		if (!(0 == anima)) {
			// 37
			if (!(Animation*)this->_98) {
				// 42 call
				add_non_visible_animating_layer(this);
				// 47
				// goto _f79; inline #0
				this->_98 = anima;
				return;
			} // 49
		} // 49

		extern __CFSet* non_visible_animating_layers;
		  // 52
		if (!anima) {
			// 57
			if (!(0 == (Animation*)this->_98)) {
				// 69
				if (!(0 == non_visible_animating_layers)) {
					// 74 call
					CFSetRemoveValue(non_visible_animating_layers, this);
				} // 79
			} // 79
		} // 79
	} // 79
_f79:	// from 47
	this->_98 = anima;
	return;
}

void CA::Layer::set_commit_needed(CA::Transaction* transaction, unsigned int flag)
{
	r15d = flag;			// via edx
	r14 = transaction;		// via rsi
	rbx = this;
	// 26
	if (!((this->_4 & 0x60000) == 0)) {
		return;
	}
	// 39
		// 42 call
	transaction->lock();
	// 54
	if (!(this->_84 & (0x80<<8))) {
		((CA::Layer::State*)&this->_28)->_4 |= flag & 0xfffffffe;
		// 91 call
		this->mark(transaction, (unsigned int)(((flag & 0x1) << 0xa) | 0x8), (unsigned int)0x10);
	} // 98
	else {
		// 102 call
		rax = CALayerPortalGetDestination((CALayer*)this->_10);
		// 110
		if (!(rax == 0)) {
			// 130 call
			// %rcx = CALayer._attr
			CA::Layer* layer = (CA::Layer*) ((uintptr_t)&((CALayer*)this->_10)->_attr + (uintptr_t)0x8 + (uintptr_t)rax);
			layer->set_commit_needed(transaction, flag);
			return transaction->unlock();
		} // 135
	} // 135
}

void CA::Layer::set_bounds(CA::Rect const& rect, bool anim)
{
	// _70 to _28 total 0x50 bytes, 10 quadwords for local variables
	ebx = anim;			// via edx,  validate before 300
	r12 = &rect;		// via rsi
	r14 = this;
	(double&)xmm0 = rect.y + rect.x + rect.width + rect.height;
	// 50 call
	;
	// 57
	if (!(__isnand((double)xmm0) == 0)) {
		bl = anim ^ true;
		// 66
		if (!((anim ^ true) == true)) {
			// 85 (// 78 call)
			if (!(__isnand(rect.x) != 0)) {
				// 101 (// 94 call)
				if (!(__isnand(rect.y) != 0)) {
					// 117 (// 110 call)
					if (!(__isnand(rect.width) != 0)) {
						// 133 (// 126 call)
						if (__isnand(rect.height) == 0) {
							// gen jmp 226
							goto _f226;
						}
					} // 135
				} // 135
			} // 135
		_f135:	 // from 117
				 // 143
			if (this->_4 & 0x60000) {
				// gen jmp 226
				goto _f226;
			}
			else {
				// 150 call
				;
				// 157
				if (_CFExecutableLinkedOnOrAfter(0x3ef) == false) {
					// gen jmp 473 line
				// 473

						 // 509 call
						 // %rdi = @"CALayer bounds contains NaN: [%g %g; %g %g]"
					al = 0x4;
					NSLog(__cfs("CALayer bounds contains NaN : [%g %g; %g %g]"), rect.x, rect.y, rect.width, rect.height);
					_50 = rect.x;
					// 525 call
					;
					// 536
					if (__isnand(rect.x) != 0) {
						(double&)_50 = 0.;
					} // 543
					(double&)_58 = rect.y;
					  // 560 call
					;
					// 571
					if (__isnand(rect.y) != 0) {
						(double&)_58 = 0.;
					} // 578
					(double&)_60 = rect.width;
					  // 595 call
					;
					// 606
					if (__isnand(rect.width) != 0) {
						(double&)_60 = 0.f;
					} // 613
					(double&)_68 = rect.height;
					  // 630 call
					;
					// 641
					if (__isnand(rect.height) != 0) {
						(double&)_68 = 0.;
					} // 648
					(double&)_40 = (double&)_50;
					(double&)_38 = (double&)_58;
					(double&)_30 = (double&)_60;
					(double&)_28 = (double&)_68;

					return this->set_bounds((CA::Rect*)&_40, 0);
				}
				else { 
					extern objc_object* NSException;
					al = 0x4;
					// 220 call
					// rsi = "raise:format:"
					objc_msgSend((id)NSException, "raise:format:"
						, __cfs("CALayerInvalidGeometry")
						, __cfs("CALayer bounds contains NaN : [%g %g; %g %g]")
						, rect.x, rect.y, rect.width, rect.height);
				} // 226
			} // 226
		} // 226
	} // 226
_f226:	 // from 143
_f226:	 // from 133
	CA::Transaction*& transaction = r15;
	  // 226 call
	r15 = CA::Transaction::ensure_compat();
		 // 237 call
	transaction->lock();
	// 254
	if (!(rect.x != this->_40)) {
		// 269
		if (!(rect.y != this->_48)) {
			// 284
			if (rect.width == this->_50) {
				// gen jmp 305
				goto _f305;
			} 
			else {
				// 299
				if (rect.height == this->_58) {
				// gen jmp 467 inline
				// 467
					rbx = (CA::Layer::State*)&this->_28;				// skip CA::Layer::writable_state to get CA::Layer::State in piece between 305 and 426
					// 471
					goto _b426;
				}
				else {
				}// 305
			} // 305
		} // 305
	} // 305
_f305:	 // from 284
		 // 320 call
	this->begin_change(transaction, (unsigned int)0x3f, (objc_object**)&_48);
	CA::Layer::State*& state = rbx;					// validate before 450
	// 331 call
	rbx = (CA::Layer::State*)this->writable_state(transaction);
	state->_18 = rect.x;			// via r12, and xmm0 with pack double.
	state->_20 = rect.y;
	state->_28 = rect.width;
	state->_30 = rect.height;
	state->_5c = (rect.y != 0. || rect.x != 0) ? (state->_5c | 0x40000) : (state->_5c & 0xfffbffff);
	eax = this->_4;
	// 421 call
	this->end_change(transaction, (unsigned int)0x3f, (objc_object*)_48);
_b426:	 // from 471	a loop
		 // 430
	if (!(((CA::Layer::State*)rbx)->_60 & (0x20<<8))) {
		// 438 call
		((CA::Layer::State*)this->writable_state(transaction))->_60 |= 0x20<<8;
	} // 447
	return transaction->unlock();
}

void CA::Layer::set_delegate(objc_object* delegate)
{
	r15 = delegate;
	r14 = this;
	CA::Transaction*& transaction = rbx;
	// 21 call
	transaction->ensure_compat();
	// 32 call
	transaction->lock();
	// 41
	CA::Layer::State*& state = r12;
	if (!(this->_60 == delegate)) {
		// 58 call
		this->begin_change(transaction, (unsigned int)0x80, (objc_object**)&_28);
		// 69 call
		r12 = (CA::Layer::State*)this->writable_state(transaction);
		// 86 call
		((CA::Layer::State*)r12)->set_delegate(transaction, (objc_object*)delegate);
		// 106 call
		this->end_change(transaction, (unsigned int)0x80, (objc_object*)_28);
	} // 113
	else {
		r12 = (CA::Layer::State*)&this->_28;
	}
_f117:	 // from 111
		 // 123
	if (!(state->_60 & (0x40 << 8))) {
		// 131 call
		((CA::Layer::State*) this->writable_state(transaction))->_60 &= (0x40<<8);
	} // 140
}

void CA::Layer::set_sublayers(__CFArray const* sublayers)
{
	// 
	// _50 to _30 total 0x28 bytes, 5 quadwords for local viriables.

	// _50 is the buffer size allocated for CALayer**;
	// _40 is an array of CALayer*, using the buffer allocated with size of _50;
	// r13 saves the rdi until offset 500

	extern void** __stack_chk_guard;
	r14 = sublayers;	// via rsi
	r13 = this;			// via rdi
	_30 = (uintptr_t)*__stack_chk_guard;
	CA::Transaction* transaction = r12 = CA::Transaction::ensure_compat();

	// 53
	extern Class NSException;
	if (this->_4 & 0x60000) {
		objc_msgSend((Class)NSException, "raise:format:", @ "CALayerInvalidTree",  @ "expecting model layer not copy: %@", this->_10];
	} // 95
	  // 99
	if (this->_18 != sublayers) {
		/***
		* r15 is sublayers;
		*/
		transaction->lock();
		r15 = sublayers;	// via r14
		r14d = 0;
		// 127
		if (sublayers != 0) {
			rbx = CFArrayGetCount(sublayers);
			r14d = 0;
			// 155
			if (rbx != 0) {
				rdx = rbx * 8;		// leaq (, %rbx, 8), %rdx
				// 176
				if (rdx <= 0x1000) {
					// expand stack frame
#if 0
					rcx = rsp;
					rax = rdx + 0xf;
					rax &= (int64_t)0xfff0;	// -0x10
					rcx -= rax;
					rsp = rcx;
#else
					rcx = alloca((rdx + 0xf) & (int64_t)0xfff0);
#endif
					// 199
					goto _f233;
				} // 201
				rdi = rdx;
				_50 = rdx;					// via rdi;
				  // 208 call
				rcx = malloc(rdx);
				eax = 0;
				// 227
				if (rcx != 0) {
				_f233:
					/***
					* _40 is an array of CALayer*, maybe allocated from stack if total-count less than 0x1000/8, or heap;
					* r15 is a integer iterator for the loop, which will get starting below.
					* _48 saves the r12, which is transaction;
					* r14 is used in the loop soon, with initialized value of 0;
					*/
					_40 = rcx;
					/**
					* 1.get the array with retaining the object in the array.
					* 2.in the loop, each object in the array will be linked to a slist,
					* 3.after the loop, each object linked to the slist will be released.
					*/
					// 245 call
					CFArrayGetValues(sublayers, 0, rbx, _40);		// via r15 is sublayers, rcx is _40;
					_48 = r12;										// save the r12 before loop.
					r14d = 0;
					r15d = 0;
				_b260:
					r12 = rbx;								// save the rbx
					rax = _40;
					rax = ((CALayer*)rbx)->_attr._8;
					rbx = ((CALayer**)_40)[r15];			// movq   (%rax,%r15,8), %rbx
					rdi = ((CALayer*)rbx)->_attr._8->_8;
					// access to CALayer._attr;
					// 290
					if (((CALayer*)rbx)->_attr._8->_8 != 0) {			// via rdi
						// 295
						if (((CALayer*)rbx)->_attr._8->_8 == this) {
							// 301
							if (this->_20 != (CALayer*)rbx) {
								goto _346;
							}
						} // 303
						  // 310 call
						((CA::Layer*)((CALayer*)rbx)->_attr._8->_8)->remove_sublayer((CA::Transaction*)_48, ((CALayer**)_40)[r15]);			// via rdx = rbx is _40[r15]

						rcx = alloca(0x10);							// allocate a slist_entry { void* p; slist_entry* next };
						rcx->_0 = ((CALayer**)_40)[r15];			// via rbx
						rcx->_8 = r14;
						r14 = rcx;
						// 336
						goto _f346;
					} // 338
					  // 341 call
					  ((CA::Layer*)((CALayer*)rbx)->_attr._8)->remove_from_context();			// ??? via rax
				  _f346:
					  ++r15;
					  rbx = r12;							// restore rbx to count of sublayers;
					  // 355
					if (r15 < rbx)
						goto _b260;							// do { ... } while(i < count);
					// 375 call
					r12 = _48;								// restore r12 to transaction, after leaving loop.
					r15 = [[CALayerArray alloc] init];
					// 412 call
					CALayerArrayInsertValues((CALayerArray*)r15, 0, (CALayer**)_40);
					// 425
					if (_50 >= 0x1001) {
						// 431 call
						free(_40);
					} // 436
					rax = r15;								// unused.
				} // 439
			} // 439
		} // 439
		rcx = &_38;
		  // 457 call
		this->begin_change(transaction, (unsigned int)0x1b8, (objc_object*&)_38);
		r13 = this->_18;
		// 481 call
		this->update_sublayers(transaction, (CALayerArray*)this->_18, (CALayerArray*)r15);
		(CALayerArray*&)this->_18 = (CALayerArray*)r15;
		// 505 call
		this->end_change(transaction, (unsigned int)0x1b8, (objc_object*)_38);
		// 513 call
		transaction->unlock();
		// 521
		if (r13 != 0) {						// old value of this->_18;
			// 529 call
			transaction->release_object((void const*)r13);
		} // 534
		r15 = *__stack_chk_guard;			// via rbx;
		  // 550
		if (r14) {							// a slist;
		_b552:
			// 558 call
			transaction->release_object((void const*)r14->_0);
			r14 = r14->_8;
			// 570
			if (r14)
				goto _b552;
		} // 572
	} // 572
	  // 576
	if (r15 != _30) {
		// 593
		// goto _f599; inline
		// 599
		/**
		// 606 call
		CA::Transaction::unlock();
		// 614 call
		_Unwind_Resume;
		// 619 call
		__stack_chk_fail;
		*/
		// 619 end inline
	} 
	// 592
	return;

}

void CA::Layer::setter(unsigned int hkey, _CAValueType type, void const* value)
{
	// 
	// _c0 to _30 total 0x98 bytes, 19 quadwords for local variables.

	// r15 is this;
	// rbx is transaction;

	_c0 = value;			// via rcx;
	r13d = type;			// via edx;
	r14d = hkey;			// via esi;
	r15 = this;				// via rdi; 
	extern void** __stack_chk_guard;
	_30 = *__stack_chk_guard;
	CA::Transaction*& transaction = rbx;
	  // 50 call
	rbx = CA::Transaction::ensure_compat();
	// 61 call
	((CA::Transaction*)rbx)->lock();
	rdi = this->_78;
	// 73
	if (this->_78 == 0) {
		// gen jmp 97
		 // goto _f97; inline
		 // 113 call
		CA::Layer::default_value((unsigned int)hkey, (_CAValueType)type, (void*)&_b0);
	}
	else {
		// 88 call
		;
		// 95
		if (!((CA::AttrList*)this->_78)->get((unsigned int)hkey, (_CAValueType)type, (void*)&_b0) == true) {
			// natural flow inline
			// 113 call
			this->default_value((unsigned int)hkey, (_CAValueType)type, (void*)&_b0);
		}
	}// 118
_f118:	 // from 95
		 // 135 call
	;
	// 142
	if (!(CAValueEqual((_CAValueType)type, &_b0, value) == true)) {
		// 160 call
		this->begin_change(transaction, (unsigned int)hkey, (objc_object**)&_b8);
		// 171 call
		r12 = this->writable_state(transaction);
		rdi = (CA::AttrList*)r12->_50;
		// 187
		if (!(r12->_50 != 0)) {
			// 191 call
			rdi = x_mem_alloc0_bucket(0);
		} // 199
		  // 212 call
		(CA::AttrList*)r12->_50 = ((CA::AttrList*)rdi)->set((unsigned int)hkey, (_CAValueType)type, (void const*)value);
		// 238 call
		this->end_change(transaction, (unsigned int)hkey, (objc_object*)_b8);
	} // 243
	// 246 call
	transaction->unlock();

	  // 265
	if (*__stack_chk_guard != _30)
		goto _f304;
	return;
	/**
	// 291 call
	CA::Transaction::unlock();
	// 299 call
	_Unwind_Resume;
	// 304 call
	__stack_chk_fail;
_f304:	 // from 265
*/

}