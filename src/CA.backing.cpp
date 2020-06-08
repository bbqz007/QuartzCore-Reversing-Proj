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
#include "CA.struct.h"
#include "CA.func.h"

typedef void(*fn_backing_store_callback)(double, void*);

void CABackingStoreCollect_(double curMediaTime, bool flag)
{
	extern double rip_0x142f8c;
	r14d = flag;
	_4c = r14d;								// save r14d
	_30 = xmm1.sd = curMediaTime;
	xmm0.sd = rip_0x142f8c + curMediaTime;
	struct gc_params
	{
		double _0;
		double _8;
	};
	extern struct gc_params* gc_harder_params;
	extern struct gc_params* gc_standard_params;
	struct gc_params*& gc_params = r13;						// &=r13
	extern pthread_mutex_t buffer_list_mutex;

	// 45 call
	gc_params = (CA::Render::check_memory_warning(rip_0x142f8c + curMediaTime)) ? gc_harder_params : gc_standard_params;
	// 77 call
	pthread_mutex_lock(&buffer_list_mutex);
	_40 = curMediaTime;
	_38 = curMediaTime;
	// 100
	if (!flag) {
		_40 = curMediaTime - gc_params->_0;
		_38 = curMediaTime - gc_params->_8;
	} // 133

	extern double ent_off_0x142f8d;
	extern double ent_off_0x142fad;

	extern CABackingStore* buffer_list;
	CABackingStore*& itCABackingStore = r12;				// &=r12
	itCABackingStore = buffer_list;
	  // 143
	if (0 == itCABackingStore) {
		// goto _f702; inline #0
		double& rip_0x142ce7 = ent_off_0x142fad;
		_48 = rip_0x142ce7;
		pthread_mutex_unlock(&buffer_list_mutex);
		return _48;
	}

	double& rip_0x142ef0 = ent_off_0x142f8d;
	_58 = rip_0x142ef0 + curMediaTime;
	double& rip_0x142efe = ent_off_0x142fad;
	_48 = rip_0x142efe;
_b180:	// from 694
	do {
		// 183
		if (!flag) {							// via r14b
			/**
			* flag is false, do nothing but collect the min media timing
			*
			*/
			xmm0.sd = itCABackingStore->_160;
			// 204
			if (!(curMediaTime >= itCABackingStore->_160)) {
				_48 = min(_48, itCABackingStore->_160);
				// 220
				// goto _f683; inline #0
				itCABackingStore = itCABackingStore->_98;
				if (itCABackingStore)
					goto _b180;				// continue;
				// 700
				// goto _f715; inline #1
				pthread_mutex_unlock(&buffer_list_mutex);
				// 746
				return (double&)_48;
			} // 225
		} // 225

		// 240
		if (!pthread_mutex_trylock(&itCABackingStore->_10)) {		// !$(233 call)
			itCABackingStore->_160 = inf;
			CABackingStoreBuffer*& cabsBuffer = rbx;				// &=rbx
			cabsBuffer = itCABackingStore->_138;

			/**
			* <<LOOP>>
			* foreach buffer in one backing store
			*
			*/
#if 0
#elif 0
			// 275
			if (!(0 == cabsBuffer)) {
				eax = 0;
				// 283
				goto _f340;

				do {
#else
			if (!(0 == cabsBuffer)) {
				eax = 0;
				// 283
				goto _f340;
				for (
					; 0 != cabsBuffer			// 566
					; cabsBuffer = cabsBuffer->_0) {			// 560
#endif
				_f340:	// from 283
				_b340:	// from 566
					r14b = al;					// save the al
					xmm0.sd = cabsBuffer->_28;
					// 356
					if (!(0. != cabsBuffer->_28)) {
						cabsBuffer->_28 = xmm0.sd = _30;
					} // 368

					/**
					* a buffer without share-memory will be skip
					*
					*/
					CA::Render::Shmem*& shmem = rcx;			// &=rcx
					shmem = cabsBuffer->_10;
					// 375
					if (0 == shmem) {
						// goto _f577; inline
						al = r14b;
						continue;	// goto _f560;
					}

					// 389
					if (!(itCABackingStore->_138 == cabsBuffer)) {
						/**
						* closure:
						* if current buffer is not the specially kept one
						* a buffer can be one of three cases:
						* 1.in the past, it should be deleted
						* 2.not coming yet, skip it
						* 3.just at the time, update the timing of CABackingStore
						*/
						// 396
						if (cabsBuffer->_28 <= _38) {
							// inline jmp 549
								// 552 call
							CABackingStoreDeleteBuffer(cabsBuffer);
							// natural flow to 557
							// goto _f557; inline #1
							al = r14b;
							continue;	// goto _f560;
						}

						// 407
						if (cabsBuffer->_28 > _40) {
							// inline jmp 519
								// 535
							if (!(gc_params->_0 >= itCABackingStore->_160)) {
								itCABackingStore->_160 = cabsBuffer->_28;
								// 547
								// goto _f557; inline #0
								al = r14b;
								continue;	// goto _f560;
							}
							else {
								// goto _f557; inline #0
								al = r14b;
								continue;	// goto _f560;
							}
						}

						/**
						* a specially kept buffer's media timing is at the range between _38 and _40
						*
						*
						*/
						// 420
						if (!(0 != itCABackingStore->_168)) {
							CA::Render::ShmemBitmap*& shmemBitmap = rcx;
							shmemBitmap = shmem->_18;
							// 429
							if (!(0 != shmemBitmap)) {
								// 437 call
								make_buffer_volatile((CABackingStore*)itCABackingStore, (CABackingStoreBuffer*)cabsBuffer);
								xmm0.sd = cabsBuffer->_28;
								al = r14b;
							} // 450
						} // 450
						xmm0.sd = cabsBuffer->_28 + gc_params->_8;
						// 466
						if ((cabsBuffer->_28 + gc_params->_8) >= itCABackingStore->_160)
							// gen jmp 560
							continue;		// goto _f560;
						itCABackingStore->_160 = cabsBuffer->_28 + gc_params->_8;
						// 478				
						continue;			// goto _f560;
					} // 480
					else {
						/**
						* closure:
						* if current buffer is just the specially kept one, by CABackingStore::_138
						* check if needed to release images in this CABackingStore
						*/
						// 489
						if (!(0 == (itCABackingStore->_174 & 0x100))) {
							// 494 call
							CABackingStoreReleaseImages(itCABackingStore);
							// 513
							if (cabsBuffer->_28 > _40) {
								goto _b285;
							_b285:	// from 513					// not a loop
								al = true;
								// 296
								if (0 != (pthread_t)itCABackingStore->_168) {
									continue;	// goto _f560; with al = ture;
								}
								// 309
								if (!(0 == (CA::Render::Shmem*)cabsBuffer->_10)
									// 318
									&& 0 != ((CGSRegionObject*)cabsBuffer->_18)->_0) {
									// gen jmp 560
									continue;	// goto _f560; with al = true;
								}
							_f324:	// from 309
									// 330 call
								::make_buffer_volatile(itCABackingStore, cabsBuffer);
								// 335
								// goto _f557; inline #0
								al = r14b;
								continue;	// goto _f560;
							}
						} // 557
					}
				_f557:	// from 375
				_f557:	// from 547
				_f557:	// from 335
					al = r14b;				// restore al
				_f560:	// from 296
				_f560:	// from 478
				_f560:	// from 466
				_f560:	// from 318
#if 0
					// 560
					cabsBuffer = cabsBuffer->_0;
					// 566
#if 0
					if (cabsBuffer)
						goto _b340;
#else
				} while (cabsBuffer);
#endif
#else
				} // end for
#endif
				/***
				* al is a bool flag which will be changed in the inner loop
				* where a specially kept buffer is found.
				*/

				r14d = flag;					// restore r14b, set to flag, via _4c.
				// 578
				if (!(0 == (true & al))) {
					/**
					* a specially kept buffer has been already found in the inner loop
					*
					*/
					// 591
					if (!(0 == (itCABackingStore->_174 & 0xff))) {
						// 608
						if (!(_58 >= itCABackingStore->_160)) {
							itCABackingStore->_160 = (double&)_58;
						} // 625
						  // 628
						if (!(0 != r14b)) {
							(short&)itCABackingStore->_174 = (((itCABackingStore->_174 & 0xffff) + 0xff) & 0xff) | ((itCABackingStore->_174 & 0xffff) & 0xffffff00);
						} // 655
					} // 655
				} // 655
			} // 655
			(double&)_48 = min((double&)_48, itCABackingStore->_160);
			// 678 call
			pthread_mutex_unlock(&buffer_list_mutex);
		} // 683
	_f683:	// from 220
		  // 694
#if 0
		if (0 != itCABackingStore)
			goto _b180;
#else
	} while (0 != itCABackingStore);
#endif
	// 700
	goto _f715;

_f715:	// from 700
		// 722 call
		// %rdi = buffer_list_mutex
	pthread_mutex_unlock(&buffer_list_mutex);
	return _48;
}

void CABackingStoreCollect(double curMediaTime)
{
	extern int64_t gpu_access_allowed__6;
	extern double next_collect_time;
	
	// 16
	if (!(0 == gpu_access_allowed__6)) {
		// 25 call
		CABackingStoreCollect_(curMediaTime, false);
		extern double rip_0x142ff3;
		// 43
		if (!(curMediaTime >= rip_0x142ff3)) {
			extern double& validateTime = xmm0.sd;
			extern double rip_0x142fc9;
			validateTime = ((curMediaTime + rip_0x142fc9) > curMediaTime) ? (curMediaTime + rip_0x142fc9) : curMediaTime;
			// 72
			if (0. == next_collect_time) {
				// goto _f86; inline #0
				next_collect_time = validateTime;
				return CA::call_at_time((fn_backing_store_callback)&backing_store_callback, double, (void*)0);
			}

			// 78
			if (next_collect_time == validateTime) {
				// goto _f86; inline #0
				next_collect_time = validateTime;
				return CA::call_at_time((fn_backing_store_callback)&backing_store_callback, double, (void*)0);
			}
		} // 80
	} // 80
	return;
}

void backing_store_callback(double, void*)
{
	CA::Transaction*& transaction = rax;				// &=rax
	extern int64_t buffer_list__4;
	buffer_list__4 = 0;
	transaction = CA::Transaction::ensure();
	// 27
	if (0 == transaction->_0->_10) {
		// goto _f31; inline #0
		return transaction->ensure_implicit();
	}
	return;
}

CA::call_at_time(fn_backing_store_callback backing_store_callback, double curMediaTime, void* unknown)
{
	rbx = backing_store_callback;
	r14 = unknown;
	(double&)_18 = curMediaTime;
	// 29 call
	// %rdi = CA::callback_lock
	OSSpinLockLock(&CA::callback_lock);
	struct x_list_callback
	{
		x_list_callback* _0;	// next
		fn_backing_store_callback _8;	// callback func
		void* _10;		// callback arg2
		double _18;		// callback arg1
	};
	x_list_callback*& targetCallback = rax;				// &=rax, invalidate until 102
	// 44
	if (!(0 == (rax = CA::callbacks))) {
		x_list_callback*& it = rax;						// &=rax
		x_list_callback**& prev = rcx;					// &=rcx
		prev = &CA::callbacks;
	_b53:	// from 74
			// 57
		if (backing_store_callback != it->_8) {
			// gen jmp 65
			goto _f65;
		} // 63
		else if (unknow == it->_10) {
			// gen jmp 96
			// goto _f96; inline #0
			// natural flow to 102
			*(prev) = it->_0;
			// it as input to _f102
			targetCallback = it;			// fake
			goto _f102;
		}
	_f65:	// from 57
		prev = &it->_0;						// via rcx = &rax->_0;
		it = it->_0;					// via rax = rax->_0;
		  // 74
		if (it)
			goto _b53;
	} // 76
	x_list_callback*& newListCallback = rax;
	  // 81 call
	newListCallback = (x_list_callback*) x_mem_alloc_bucket(0x1);
	newListCallback->_8 = backing_store_callback;
	newListCallback->_10 = unknow;
	targetCallback = newListCallback;					// fake
	// 94
	goto _f102;
_f102:	// from 94
	targetCallback->_18 = curMediaTime;
		// 122
	if (!(0 == (rdx = CA::callbacks))) {
		x_list_callback*& it = rdx;						// &=rdx
		x_list_callback**& prev = rcx;					// &=rcx
		prev = &CA::callbacks;
	_b131:	// from 147
			// 136
		if (!(curMediaTime < it->_18)) {
			prev = &it->_0;					// via movq   %rdx, %rcx
			it = it->_0;
			// 147
			if (it)
				goto _b131;
		} // 149
		targetCallback->_0 = *(prev);
		*(prev) = targetCallback;
		  // 168
		if (prev != &CA::callbacks) {
			// gen jmp 194
			// goto _f194; inline #0
			return OSSpinLockUnlock(&CA::callback_lock);
		}
	} // 172
	else {
		targetCallback->_0 = CA::callbacks;
		CA::callback_lock = targetCallback;
	} // 189
	  // 189 call
	CA::update_timer();
_f194:	// from 168
		// 224 call
		// %rdi = CA::callback_lock
	return OSSpinLockUnlock(&CA::callback_lock);
}

void async_collect_callback(void*)
{
	double& curMediaTime = _8;
	// 8 call
	curMediaTime = CACurrentMediaTime();
	extern char rip_0x173281;				// CABackingStoreGetTypeID::type + 7
	rip_0x173281 = 0;
	extern bool marked_volatile;
	extern double next_collect_time;
	extern int unknow;						// next_collect_time + 4
	// 25 call
	CABackingStoreCollect(curMediaTime);
	// 40
	if (!(true != marked_volatile)) {
		// 58
		if (!(0. == next_collect_time)
			&& next_collect_time >= curMediaTime) {			// 69
			// gen jmp 98
			// goto _f98; inline #0
			unknow = 0;
			return;
		}
	_f71:	// from 58
		next_collect_time = curMediaTime;
		  // 93 call
		  // %rdi = backing_store_callback(double, void*)
		CA::call_at_time((void(*)(double, void*))&backing_store_callback, curMediaTime, (void*)0);
	} // 98
_f98:	// from 69
	unknow = 0;
	return;
}