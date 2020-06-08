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

bool CA::Layer::layout_is_active(CA::Transaction* transaction, bool isActive)
{
	r15d = isActive;
	r14 = transaction;
	rbx = this;
	uint32_t*& thread_flags = rcx;						// &=rcx
	// 26
	if (!(transaction->_8 < 0)) {
		// 36
		if (!(0 == this->_a8[transaction->_8])) {
			thread_flags = (uint32_t*)&this->_a8[transaction->_8]
			// 46
			goto _f62;
		} // 48
	} // 48
	  // 54 call
	thread_flags = (uint32_t*) this->thread_flags_(transaction);
_f62:	// from 46
		// 65
	if (false == isActive) {
		// gen jmp 74
		goto _f74;
	} // 72
	else if (*thread_flags & 0x20) {
		// gen jmp 164
		// goto _f164; inline #0
		return true;
	}
_f74:	// from 65
	  // 81
	if (!(0 == (CA::Transaction::slist*)transaction->_70)) {
		// 87
		if () {
			// gen jmp 98
			goto _f98;
		} // 94
		else if () {
			// gen jmp 164
			goto _f164;
		}
		else { // 94 next
			   // 96
			goto _f162;
		_b98:	// from 140
		_f98:	// from 87
		} // 98
		  // 105
		if () {
			// gen jmp 133
			goto _f133;
		}
		else { // 105 next
		_b111:	// from 131
				// 117
			if ()
				// gen jmp 148
				goto _f148;
			// 122
			if (!) {
				// 131
				if ()
					goto _b111;
			_f133:	// from 105
			} // 133
		} // 133
		  // 140
		if ()
			goto _b98;
		// 142
		goto _f162;
	_b144:	// from 158
	_f148:	// from 117
			// 151
		if (!) {
			// 158
			if ()
				goto _b144;
			// 160
			goto _f164;
		_f162:	// from 142
		_f162:	// from 96
		} // 162
	} // 162
_f164:	// from 160
_f164:	// from 94
_f164:	// from 72
	close
}

void CA::Layer::layout_and_display_if_needed(CA::Transaction* transaction)
{
	r14 = transaction;
	rbx = this;
	do {
		this->layout_if_needed(transaction);
	} while (this->display_if_needed(transaction));
}

void CA::Layer::layout_if_needed(CA::Transaction* transaction)
{
	// _0: rbp; _8: r15; _10: r14; _18: r13; _20: r12; _28: rbx;
	// local variables range between _10c0 to _30;
	r15 = transaction;				// via rsi, validate for whole procedure.
	r13 = this;						// via rdi, validate till 258
	_10a8 = this;					// via r13, unused.
	extern void** __stack_chk_guard;
	_30 = *__stack_chk_guard;		// via rax;
	// 50 call
	transaction->lock();;
	rcx = transaction->_8;
	// 74
	if (!(transaction->_8 < 0) 
		&& !((edx = this->_a8[transaction->_8]) == 0)) {
		rax = (uint32_t*)&this->_a8[transaction->_8];
	} // 86
	else {
		// 92 call
		rax = (uint32_t*)this->thread_flags_(transaction);
		edx = *(uint32_t*)rax;
	} // 99
	_10b0 = rax;		// used in 501 futher 
		// 109
	if (!((dl & 0x60) == 0)) {
		r12 = (char*)"layoutSublayers";

	_b122:	// from 518
			// 139 call
		rbx = (void*)x_heap_new_with_ptr((uint32_t)0x400, (void*)&_1030, (uint32_t)0x1000);			// use _1030 as heap with size of 0x1000, allocate-size if 0x400
		// 152 call
		r14b = (bool)_CFExecutableLinkedOnOrAfter((uint32_t)0x3f7);
		al = r14b == false;
		CA::Layer::CollectLayersData& collectLayerData = *(CA::Layer::CollectLayersData*)&_1070;
		_1070 = 0;
		_1068 = 0;
		_1060 = 0;
		_1058 = transaction;
		_1050 = rbx;
		(int32_t&)_1048 = 0x20;
		_1044 = 0x40;
		_1040 = ((int32_t)(bool)(r14b == false)) << 7;
		// 243 call
		this->collect_layers_((CA::Layer::CollectLayersData*)&_1070);

		struct slist { CA::Layer* _0; struct slist* _8; };

		_10a0 = rbx;
		_1098 = transaction;									// slist::val
		_1090 = rax = transaction->_70;							// slist::next
		_1088 = r13 = (slist*)collectLayerData._0;				// via r13;
		_1078 = (r14b == false);
		rbx = (slist*)collectLayerData._8;						// _1068

		transaction->_70 = (CA::Transaction::slist*)&_1098;			// insert into the head of link.

		// 318 call
		transaction->unlock();;

		r14 = (slist*)collectLayerData._0;
		// 329
		if (collectLayerData._0 == 0) {
			goto _f396;
		}
		else {
			/**
			* << LOOP >>
			* traverse the slist of collectLayerData._0, and layout sublayers of every layer in the slist.
			*/
		_b331:	// from 373
			CA::Layer*& layer = rdi;
			layer = ((slist*)r14)->_0;
			_1080 = layer;										// member of object '_10a0', which linked to transaction->_70
																// 349 call
			CALayer* oclayer = (CALayer*)layer->layer_being_drawn(transaction, (unsigned int)0x1000000);;
			// 360 call
			objc_msgSend(oclayer, "layoutSublayers");
			r14 = ((slist*)r14)->_8;							// slist->next
																// 373
			if (r14)
				goto _b331;

			// 375
			goto _f396;
		}

		// here, a natural flow unreachale.
		/**
		* << LOOP >>
		* traverse the slist of collectLayerData._8, and update the thread_flags of every layer in the slist.
		* and clean the slist.
		* input: rbx = (slist*)collectLayerData._8;	
		*/
	_b377:	// from 444
	_b377:	// from 432
		ecx &= 0xffffff7f;
		*rax = ecx;						// *thread_flags
		((slist*)rbx)->_0 = 0;
		rbx = ((slist*)rbx)->_8;
	_f396:	// from 375
		  // 399
		if (!(rbx == 0)) {
			CA::Layer*& layer = rdi = ((slist*)rbx)->_0;
			rax = transaction->_8;
			// 422
			if (!(transaction->_8 < 0)
				&& !((ecx = layer->_a8[transaction->_8]) == 0)) {
				rax = (uint32_t*)&layer->_a8[transaction->_8];
				// 432
				goto _b377;
			} // 434
			  // 437 call
			rax = (uint32_t*)layer->thread_flags_(transaction);
			ecx = *(uint32_t*)rax;
			// 444
			goto _b377;
		} // 458
#if 0
		_b446:	// from 461
#endif

	/**
	* << LOOP >>
	* traverse the slist of collectLayerData._0, and clean it.
	*/
	_b458:		// from 399
		  // 461
		if (r13) {
			// goto _b446; inline
			// 446
			((slist*)r13)->_0 = 0;
			r13 = ((slist*)r13)->_8;
			// natural flow to 458
			goto _b458;
		}
			
		// 470 call
		x_heap_free((x_heap_struct*)_10a0);				// which is the new heap returned from x_heap_new_with_ptr();
		// 478 call
		transaction->lock();;
		((CA::Transaction*)_1098)->_70 = (CA::Transaction::slist*)_1090;				// de-link, _1090 is **prev, _1098 is *next;
		r13 = _10a8;
		// 518
		if (*(uint32_t*)_10b0 & 0x60)
			goto _b122;
	} // 524										// LOOPBACK to _b122;

	// 527 call
	transaction->unlock();
	  // 546
	if (*__stack_chk_guard != _30)
		goto _f620;
	return;
#if 0
	// 566
	goto _f568;
_b568:	// from 618
_f568:	// from 566
		// 574 call
	CA::Transaction::lock();;
_b597:	// from 616
		// 600 call
	CA::Transaction::unlock();;
	// 608 call
	_Unwind_Resume;;
_b613:	// from 625
		// 616
	goto _b597;
	// 618
	goto _b568;
	// 620 call
	__stack_chk_fail;;
_f620:	// from 546
		// 625
	goto _b613;
#endif
}

void CA::Layer::set_needs_layout()
{
	CA::Layer*& layer = rbx;
	rbx = this;
	if (this->_4 & 0x60000)
	{
		return;
	}
	CA::Transaction*& transaction = r14;
	r14 = CA::Transaction::ensure_compat();
	transaction->lock();
	ecx = ((int32_t*)&this->_a8)[transaction->_8];
	if (transaction->_8 < 0
		|| this->_a8[transaction->_8] == 0)
	{
		// <+70>
		rax = (uint32_t*)this->thread_flags_(transaction);
		ecx = *(int32_t*)rax;
	}
	else
	{
		rax = (int32_t*)&this->_a8[transaction->_8];
	}
	// <+83>
	if ((ecx & 0xff & 0x20) == 0)
	{
		ecx |= 0x20;
		*(int32_t*)rax = ecx;
		this->invalidate_layout();
	_b101:	 // 174 jmp 101; loop of while((rbx = rbx->_8) != NULL) {}
		if ((layer = layer->_8))					// via rbx;
		{
			if (r14->_8 < 0
				|| layer->_a8[transaction->_8] == 0)
			{
				// <+140>
				rcx = (int32_t*)layer->thread_flags_(transaction);
			}
			else
			{
				rcx = (int32_t*)&layer->_a8[r14->_8];
			}
			// <+156>
			edx = *(int32_t*)rcx;
			if ((edx & 0xff & 0x40) == 0)
			{
				edx |= 0x40;
				*(int32_t*)rcx = edx;

				layer->invalidate_layout();
				// <+174> 	
				goto	 _b101; 	// 174	jmp	101
			}
			
		}
	}
	// <+195>
	
_tj202: 
	//jmp CA::Transaction::unlock();
	return transaction->unlock();
/**
	207 	goto	 176; 	// 207	jmp	176
_b176:	 // 207 jmp 176
	182	callq	CA::Transaction::unlock();
	190	callq	symbol stub for : _Unwind_Resume;
	// 
*/
}

#if 0
void CA::Layer::layout_if_needed(CA::Transaction* transaction)
{
	// _0: rbp; _8: r15; _10: r14; _18: r13; _20: r12; _28: rbx;
	// local variables range between _10c0 to _30;
	r15 = transaction; // r15 = rsi; 
	r13 = this;
	_10a8 = this;
	_30 = __stack_chk_guard->_0;
	transaction->lock();
	if(transaction->_8 >= 0
		&& ((int32_t*)&this->_a8)[transaction->_8] != 0)
	{
		edx = ((int32_t*)&this->_a8)[transaction->_8];
		rax = &((int32_t*)&this->_a8)[transaction->_8];
	}
	else // 86
	{
		rax = this->thread_flags_(transaction);
		edx = rax->_0;
	}
	// 99
	_10b0 = rax;			

	/***
	* _10b0 is an location address to flags, either from layer or transaction. the value of location will be modified somewhere else.
	* _10a8 is this;
	* _10a0 to _1070 is a object, which use zone for alloctions.
	* _1070 to _1038 is a object, which use zone for alloctions.
	* _10a0 and _1050 are temporary mem_root based the stack locations.
	* 
	*/
	if (edx & 0xff & 0x60)
	{
		// 115
		r12 = "layoutSublayers";
		
		// the transaction with being locked.
		// some like do { ... } while (_10b0->_0 & 0xff & 0x60);
	_b122:	 // 518 jne 122
		// location from _1030 to _30, just size of 0x1000 bytes.
		// use this 0x1000 bytes as base to build a heap, which allocates pieces size of 0x400 bytes.
		// some like the mem_root which is used in mysql source code.
		// while mach, mem_root means zone.
		rbx = x_heap_new_with_ptr((uint32_t)0x400, &_1030, (uint32_t)0x1000);			// zone.
		r14b = (bool) _CFExecutableLinkedOnOrAfter((uint32_t)0x3f7);					// used by obj _1070.
		al = !!r14b;
		eax &= 1;
		eax <<= 0x7;
		
		/***
		* there may be a constructor of structure
		* a object ranges _1070 to _1038 for alignment.
		*/
		// <+172>: xorps  %xmm0, %xmm0
		// <+175>: movaps %xmm0, -0x1070(%rbp)
#if 0
		*(doulbe*)&_1070 = 0.f;
		*(doulbe*)&_1068 = 0.f;
#else
		// according to codes below, there are not doubles,
		// just set two quadword bytes to 0;
		CA::Layer::CollectLayersData& collectLayerData = *(CA::Layer::CollectLayersData*)&_1070;
		_1070 = 0;
		_1068 = 0;
#endif

		_1060 = 0;
		_1058 = transaction; // r15;
		_1050 = rbx;						// use zone for allocations.
		(uint32_t&)_1048 = 0x20;
		(uint32_t&)_1044 = 0x40;
		(uint32_t&)_1040 = eax;

		// retrieve layers, and store them in _1068 via link, 
		// _1070 may be the count of the length of link.
		this->collect_layers_((CA::Layer::CollectLayersData*)&_1070);

		/***
		* there may be a constructor of structure
		* a object ranges _10a0 to _1070.
		*/
		_10a0 = rbx;						// use zone for allocations.
		_1098 = transaction; // r15;
		_1088 = ((CA::Layer::CollectLayersData*)&_1070)->_0;		// _1070;
		_1078 = (bool)r14b;
		rbx = ((CA::Layer::CollectLayersData*)&_1070)->_8;			// _1068;
		_1090 = transaction->_70;
		transaction->_70 = (CA::Transaction**)&_1098;		// _1098 = transaction;

		transaction->unlock();

		/*** right now
		* r13 = ((CA::Layer::CollectLayersData*)&_1070)->_0;
		* r12 = "layoutSublayers";
		* rbx = ((CA::Layer::CollectLayersData*)&_1070)->_8;
		*/

		r14 = (CA::Layer**)r13;
		if (((CA::Layer::CollectLayersData*)&_1070)->_0 != 0)
		{
			/***
			* r14 as a iterator; begin with ((CA::Layer::CollectLayersData*)&_1070)->_0;
			* I think there is a struct like node{CA::Layer*; node* next;};
			*/
		_b331:	 // 373 jne 331
			_1080 = *(CA::Layer**)r14;
			rax = (CALayer*)((CA::Layer*)_1080)->layer_being_drawn(transaction, (unsigned int)0x1000000);
			[(id)rax layoutSublayers];
			if ((r14 = (CA::Layer*) ((CA::Layer*)r14)->_8) == 0)
			{
				goto	 _b331;	// 373	jne	331
			}
			// jmp <+396>
#if 0
			// piece from <+377> to <+392>
		_b377:	 // 432 jmp 377
		_b377:	 // 444 jmp 377
			ecx &= 0xffffff7f;
			rax->_0 = ecx;
			rbx->_0 = 0;
			rbx = rbx->_8;
		}
		// 396
		if (rbx != 0)
		{
			rdi = rbx->_0;
			rax = transaction->_8;
			if (rax > 0
				&& ((uint32_t*)&rdi->_a8)[rax] != 0)
			{
				rax = &((uint32_t*)&rdi->_a8)[rax];
				goto	 _b377;	// 432	jmp	377
			}
			// 434
			((CA::Layer*)rdi)->thread_flags_(transaction);
			goto	 _b377;	// 444	jmp	377
#else
		}
		while (rbx != 0)
		{
			rdi = rbx->_0;
			rax = transaction->_8;
			if (rax > 0
				&& ((uint32_t*)&rdi->_a8)[rax] != 0)
			{
				rax = &((uint32_t*)&rdi->_a8)[rax];
			}
			// 434
			rax = ((CA::Layer*)rdi)->thread_flags_(transaction);
			goto _b377;		// 444	jmp	377
		_b377:
			ecx &= 0xffffff7f;
			rax->_0 = ecx;
			rbx->_0 = 0;
			rbx = rbx->_8;
		}
#endif
#if 0
			_b446:	 // 461 jne 446
					 r13->_0 = 0;
					 r13 = r13->_8;	// r13->_8 is a link;
		}
		// 458
		if (r13 != 0)
			goto	 446;	// 461	jne	446
#else
		}
		while (r13 != 0)
		{
			r13->_0 = 0;
			r13 = r13->_8;
		}
#endif
		x_heap_free(_10a0);		// _10a0 is a local object, and rbx(zone) is stored in it.

		transaction->lock();
		_1098->_70 = _1090;		// _1098 stores the transaction, see the constructure of _10a0;
		r13 = this;				// _10a8 
		if(_10b0->_0 & 0xff & 0x60)			// some like do {...} while(_10b0->_0 & 0xff & 0x60);
			goto	 _b122;// 518	jne	122
	}
	// 524
	transaction->unlock();

	if (__stack_chk_guard->_0 != _30)
	{
		_Unwind_Resume(__stack_chk_fail());
		transaction->unlock();
	}
}
#endif

class CAAnimation;
class __CFString;
int CA::Layer::add_animation(CAAnimation* anima, __CFString const* key_path)
{
	// _0: rbp; _8: r15; _10: r14; _18:  r13; _20: r12; _28: rbx
	// _68 is location to &CA::Layer::_4;
	// _50 to _30 total 0x28 bytes for local variables;
	// r14 is this;
	// _48 can be sure is a pointer to CATransaction;
	// _40 is anima;
	// _38 is CA::Layer::_98 which is CA::Layer::Animation*
	// _30 something retrieved from CA::Render by key_path
	// CA::Layer::_98 is CA::Layer::Animation
	// CA::Layer::Animation::_10 is the same thing as things retrieved by CA::Render::key_path_set
	// CA::Layer::Animation::_8 is @CAAnimation
	// CAAnimation::_20 is CA::Render::Object
	_50 = r12 = rdx;
	_40 = rbx = rsi;
	r14 = rdi;
	CA::Transaction* transcation /**_48*/ = (CA::Transaction*)r15 = CA::Transaction::ensure();
	CAAnimationSetFlags(anima, (int)1, (int)-1);
	CA::Render::key_path_set((void**)&_30, (__CFString const*)key_path);
	transaction->lock();

	/**
	* rbx stores this;
	* 
	*/
	r15 = this->_98;
	_38 = this->_98;
	rbx = this;
	// 101
	if (this->_98 != 0) {
		r13 = &_38;
		r12d = 0;
		r14 = &_30;
		rsi = &this->_98->_10;	// a fake instruction, right now r15 is this->_98
	_b114:	 // 174 jne 114
		rsi = &r15->_10;
		edx = 0;
		// rdi = r14, 
		al = (bool) CA::Render::key_path_equal((void* const*)&_30, (void* const*)&r15->_10, false);
		// 130
		if (al == true) {
			// 141
			if ((r15->_38 & 0xffff & 0x602) == 0) {
				// 148
				if (r15->_30 == 0) {
					/***
					* find out a already acting CA::Layer::Animation, stop it first;
					*/
					goto _f810;		// break; and enter another loop
				}
			} // 154
			*(short*)&r15->_38 |= 0x8;
			r12b = true;
		} // 165
		r13 = r15;			// save the current validate (nonnull) CA::Layer::Animation
		r15 = r15->_0;		// traverse the CA::Layer::Animation link.
		// 174
		if (r15) 
			goto _b114; 	// 174	jne	114;  do {...} while(? = ?->next);
		
		// 176
		goto _f181;
	} // 178
	r12d = 0;
_f181:
	/**
	* construct a object (CA::Layer::Animation), pointed by r15;
	* r13 is this
	* r14 is transaction
	*/
	r15 = x_mem_alloc_bucket((uint32_t)0x3);
	r14 = transaction;	// _48;
	r13 = this;			// _rbx;
_b201:	 // 845 jmp 201
	/***
	* r15 is CA::Layer::Animation
	* r14 is transaction
	* r13 is this (CA::Layer)
	*/
	rdi = anima;		// _40 which is anima, passed by argument;
	r15->_8 = CFRetain(anima);
	r15->_10 = _30;		// see to CA::Render::key_path_set
#if 0
	eax = 0;
	rdi = _50;
	// 231
	if (_50 != 0) {
		CFRetain(_50);
	} // 238
	r15->_18 = rax;
#else
	r15->_18 = (_50) ? CFRetain(_50) : nil;
#endif
	r15->_20 = 0;
	static int counter = 0;
	r15->_28 = 1 + OSAtomicAdd32(1, (volatile long*)&counter);

	r15->_38 = [(id)_40 isRemovedOnCompletion] | (int(r12b &= 1) << 4) | (r15->_38 & 0xffe0);

	
	edx = r15->_38;
	eax = [(id)((CA::Layer*)r15)->_8 propertyFlagsForLayer: r13->_10];	// [CAAnimation _propertyFlagsForLayer:]
	esi = eax << 6 & 0x40;
	edx &= 0xfe1f;
	ecx = eax << 4 & 0x20;
	edi = eax << 5 & 0x80;
	ebx = edi & 0x80;
	edi &= 0x100;
	ecx |= esi | ebx | edi | edx;
	r15->_38 = cx;
	
	// 406
	if ((eax & 0x6) == 0x6) {
		OSAtomicOr32(0x1000000, (volatile long*)&r13->_4);
		ecx = r15->_38;
	} // 422		
	 // 434
	if ((ecx & 0x120) == 0x120) {
		OSAtomicOr32(0x800000, (volatile long*)&r13->_4);
	} // 445
	rax = [(id)_40 delegate];
	  // 465
	if (rax) {
		eax = lookup_delegate_methods(transaction, (id)[(id)_40 delegate]);
		ecx = r15->_38 & 0xf9ff;
		eax &= 0x60;
		eax <<= 4;
		eax |= ecx;
	} // 499
	  // 497
	else {
		 eax = r15->_38 & 0xf9ff;
	} // 509
	r15->_38 = eax;

	  // 525
	if (transaction->current_continuation()) {
		r15->_30 = transaction->current_continuation()->ref();	//CA::Transaction::Continuation::ref();
	} // 549
	  // 547
	else {
		r15->30 = 0;
	} // 557

	/***
	* initialize an iterator to get ready entering a loop
	* rbx as an iterator, which refers to the object of same type as r15's (CA::Layer::Animation).
	* rbx is CA::Layer::Animation*, as an iterator;
	* _38 is this->_98, which is CA::Layer::Animation*; or in other hand, is the next to the one we stopped in 810.
	*/
	rbx = _38;	// an iterator;
	  // 564
	if (_38 != 0) {
		/***
		* 148 find the working animation same as we want to add
		* goto 810 to stop it and _38 save to that animation's next
		* if _38 is null, that means animation is new, or no next animation to the found one.
		*
		* _40, _50 will be reused.
		* _40 is the CAAnimation we want to add, but then will be replaced to CA::Render::Timing* copyed from it.
		* rbx->_8 is the CAAnimation of CA::Layer::Animation, which we found already working.
		* r12 will be CA::Render::Timing*
		*/
		_40 = r12 = CAMediaTimingCopyRenderTiming(_40);		// CA::Render::Timing* CAMediaTimingCopyRenderTiming(CAAnimation*)
		_50 = r13;											// this
		_48 = transaction;	// r14;
		/**
		* r14 is not transaction any longer.
		*/
		r14 = &_38;			// CA::Layer::Animation**

	_b598:	 // 699 jne 598
		
		rax = CAMediaTimingCopyRenderTiming(rbx->_8);
		xmm0 = xmm1 = 0;
		// 618
		if (r12 != 0) {
			xmm1 = (double&)r12->_20;
		} // 627
		  // 630
		if (rax != 0) {
			xmm0 = (double&)rax->_20;
		} // 637
		  // 641
		if (xmm0 <= xmm1) {
			// 643
			if (xmm0 < xmm1) {
				// 648
				if (rax != 0) {
					((CA::Render::Object*)rax)->unref() const;
				} // 690
			} // 660
			// 658
			else {
				r13d = r15->_28;					// r15 is CA::Layer::Animation*, we want to add
				r12d = rbx->_28;					// rbx is CA::Layer::Animation*, iterator to traverse the link to CA::Layer::_98
				// 671
				if (rax != 0) {
					((CA::Render::Object*)rax)->unref() const;
				} // 681
				  // 688
				if ((uint32_t)r12d > (uint32_t)r13d) {
					r12 = _40;
					goto _f729; // a fake instructment;
				} // 729

				r12 = _40;
			} // 690
			r14 = rbx;					// (CA::Layer::Animation**) &rbx->_0; 
			rbx = rbx->_0;
			// 699 	
			if(rbx != 0)
				goto _b598; 	// 699	jne	598; loop do {...} while(rbx = rbx->next); rbx begin with -0x38(%rbp)

			// 701
			goto _f729;
		} // 716
		goto _f716;		// a fake instructment
	} // 703
	// an evaluated closure from 703 to 707
	else {		
		/**
		* no more CA::Layer::Animation is in one CA::Layer
		*/
		_38 = r15;
		r15->_0 = 0;
	}
	  // 714
		goto _f759;
_f716:
	
	  // 719
	if (rax != 0) {
		((CA::Render::Object*)rax)->unref();
	} // 729
	/***
	* r12 is CA::Render::Timing*;
	* r14 is &CA::Layer::Animation::next, starting from &_38, and stop at the place where CA::Render::Timing is greater than the one we want to add.
	*/
_f729:
	r15->_0 = r14->_0;				// r15->_0 = *(&CA::Layer::Animation::next);
	r14->_0 = r15;					// *(&CA::Layer::Animation::next) = r15;

	r14 = _48;		// transaction;
	r13 = _50;		// this;
	  // 749
	if (r12 != 0) {
		((CA::Render::Object*)r12)->unref();
	} // 759
_f759:
	((CA::Layer*)r13)->set_animations((CA::Layer::Animation*)_38);
	((CA::Layer*)r13)->mark_animations((CA::Transaction*)r14, true);
	((CA::Transaction*)r14)->unlock();
	// 809
	return;
_f810:
	/***
	* r13 is &_38;
	* r15 is CA::Layer::Animation*, searched from CA::Layer::_98;
	*/
	// leaq -0x38(%rbp), r13;
	r13->_0 = r15->_0;			// _38 = ((CA::Layer::Animation*)r15)->next;
	r14 = _48;		// transaction;
	schedule_stop_callback((CA::Layer::Animation*)r15);
	r13 = rbx;		// look back to 148, rbx is still this;
	r12b = 1;
	CA::Layer::free_animation((CA::Layer::Animation*)r15, false);
	// 845 	
	goto _b201; 	// 845	jmp	201; not a loop, just a piece of codes for unlikely closure;

  // 854
	if () {
	} // 856
}


void CA::Layer::set_animations(CA::Layer::Animation* anima)
{
	// _0: rbp; _8: r14; _10: rbx;
	/***
	* we can be sure that CA::Layer::_98 is CA::Layer::Animation*;
	*/
	r14 = rsi;		// anima
	rbx = rdi;		// this
	extern void* non_visible_animating_layers;
	// 20
	if (0 == (this->_0x85 & 0ff & 0x8)) {
		rax = this->_98;
		// 32
		if (anima && this->_98 == 0) {
				add_non_visible_animating_layer((CA::Layer*)this);
				// 47
				goto _f79;
		} // 49
		  // 52
		else if (!anima
			// 57
			&& this->_98 != 0
			// 69
			&& non_visible_animating_layers != 0) {
					CFSetRemoveValue(non_visible_animating_layers, this);
		} // 79
	} // 79
_f79:
	this->_98 = anima;
}


bool CA::Layer::collect_animations__(double arg1, double* arg2, CA::Layer::CollectAnimationsData* data)
{
	/***
	* Summary:
	* total JmpBlock(s): 17
	* noninline block(s): #0, #2, #4, #7, #10, #12, #13, #14, #15, #16
	* inline block(s): #1, #3, #5, #6, #8, #9, #11
	*/


	/***
	* #0<<JmpBlock>>
	* 0 to 143
	* instrs: 40
	* inners: 0
	*
	*/
_f0:
	// _0: rbp; _8: r15; _10: r14; _18: r13; _20: r12; _28: rbx;
	// _70 to _30 are local variables. total 0x48 bytes, 9 quadwords.
	// rdi is this of CA::Layer*						; _70 is temporary to this;
	// xmm0 is 1st arg (which is 1st flow type arg)
	// rsi is 2nd arg, a location address pointing to a double.	; _60 is temporary to 2nd arg.
	// rdx is 3rd arg, CA::Layer::CollectAnimationsData*; #3 to #11 r14 is temporary to the argument

	// _30 is CA::Layer::_98, which is CA::Layer::Animation*
	// _38 is double, temporary to arg1;
	// _40 is CA::Layer::Animation**; and is a temporary double for a short road.
	// _48 is double, with which the arg2 will be filled.
	// _60 is double*, temporary to arg2;
	// _68 is uint32_t*, location to &this->_4
	// _70 is this;


	//  <+20> : movapd %xmm0, %xmm1									; align pack (2) double 
	//	<+24> : movss  0x8(%rdx), %xmm0								; signed single pre, only 32bit float value transferred to.
	//	<+29> : andps  0x3d8de(%rip), %xmm0;.memset_pattern + 560	; pack (4) single pre, and 
	//	<+36>:   orps   0x3d8e7(%rip), %xmm0;.memset_pattern + 576	; pack (4) single pre, or
	//	<+43>:   cvtss2sd %xmm0, %xmm0								; convert float to double, 
	//	<+47> : movsd  %xmm0, -0x48(%rbp)							; signed double, only 64bits double value transferred to.

	extern float memset_pattern_560[];
	extern float memset_pattern_576[];
	rbx = rsi;
	xmm1 = (double)arg1;		// (double) xmm0
	xmm0 = (double) ((float)data->_8 & (float)memset_pattern_560[0] | (float)memset_pattern_576[0]);		// memset_pattern a global variable.
	(double&)_48 = (double)xmm0;
	_30 = this->_98;	// via rax

	// 66
	if (this->_98 == 0) {
		/***
		* #1<<Inline JmpBlock>>
		* 145(145) to 147
		* instrs: 2
		* incomings: 1	; #0
		* outgoings: 1	; #16
		* depth: 1
		*
		*/
		// 145
		eax = 0;
		// 147
		goto _f1162;	// to #16
						// end of inline #1
	} 
	rsi = &this->_4;
	_40 = &_30;			// via rcx
	r12d = 0;
	// 90
	if ((this->_4 & 0x1800000) == 0) {
		goto _f152;	// to #2, BoJ
	}
	_60 = arg2;			// via rbx
	OSAtomicAnd32(0xfe7fffff, (volatile uint32_t*)&this->_4);	// via rsi
	ecx = 0;
	rax = _30;
	// 112
	if (_30 == 0) {
		goto _f812;	// to #13, BoJ
	}
	_68 = &this->_4;	// via rsi;
	r14 = data;			// rdx, now be free, and r14 is temporary to data;
	_50 = ecx = 0;
	_38 = arg1;			// via (double)xmm1
	_70 = this;
	r12d = 0;
	// 143
	goto _f178;	// to #2
				// end of non-inline #0

				/***
				* #2<<JmpBlock>>
				* 152 to 278
				* instrs: 34
				* inners: 0
				*
				*/
_f152:
_f152:	// from #0(90)
	_68 = &this->_4;	// via rsi;
	r14 = data;			// via rdx, now rdx is free, r14 is temporary to data, the 3rd argument;
	_50 = ecx = 0;
	_38 = arg1;			// via (double)xmm1;
	_70 = this;
	_60 = arg2;			// via rbx;
_f178:	// from #0(143, EoJ)
	_58 = ecx = 0;
_b184:	// from #12(732)
	rbx = (CA::Layer::Animation*)this->_98;	// via rax, as an iterator for loop, beginnig with this->_98, which could be CA::Layer::Animation*;
_b187:	// from #4(438)
		// 191
	if ((rbx->_38 & 0xff & 0x2) == 0) {
		goto _f704;	// to #12
	}
	rdi = rbx->_20;
	// 204
	if (rbx->_20 == 0) {
		goto _f704;	// to #12
	}
	(double&)r15 = ((CA::Layer::Animation*)rbx)->_20->_20;	// via rdi
	((CA::Render::Timing*)rbx->_20)->end_time();		// we can assum that CA::Layer::Animation::_20 is CA::Render::Timing*;
	rax = rbx->_20;			// ? unused
	r13d = (int32_t)rbx->_20->_8 << 0x12 & 0xffffff01;
	ecx = (int32_t)rbx->_20->_8 << 0x11 & 0xffffff01;
	xmm1 = (float)data->_8;
	xmm2 = 0.f;
	// <+254>:  ucomiss %xmm1, %xmm2			; unordered compare
	/**
		RESULT  UnorderedCompare(SRC1[63-0] <> SRC2[63-0]) {
		* Set EFLAGS *CASE (RESULT) OF
		UNORDERED: ZF,PF,CF  111;			if float is SNaN 
		GREATER_THAN: ZF,PF,CF  000;
		LESS_THAN: ZF,PF,CF  001;
		EQUAL: ZF,PF,CF  100;
		ESAC;
		OF,AF,SF  0;
	*/

	// 257
	if ((float)data->_8 == 0.f) {
		/***
		* #5<<Inline JmpBlock>>
		* 449(449) to 472
		* instrs: 7
		* incomings: 1	; #2
		* outgoings: 2	; #9, #12
		* depth: 1
		*
		*/
		// 449
		xmm1 = (float&)r15;
		xmm2 = (double&)_38;
		// 467
		if (xmm1 <= xmm2) {
			xmm1 = xmm2;
			al = r13b;
			/***
			* #9<<Inline JmpBlock>>
			* 552(552) to 562
			* instrs: 5
			* incomings: 1	; #5
			* outgoings: 2	; #12
			* depth: 2
			*
			*/
			// 552
			al = true;
			// 558
			if (xmm0 > xmm1) {
				goto _f646;	// to #12
			}
			al = cl;
			// 562
			goto _f646;	// to #12
						// end of inline #9
		}
		xmm2 = xmm1;
		// 472
		goto _f646;	// to #12
					// end of inline #5
	}
	rax = (float)xmm0;

	// 271
	if ((float)data->_8 >= 0.f) {
		/***
		* #3<<Inline JmpBlock>>
		* 280(280) to 328
		* instrs: 14
		* incomings: 2	; #2
		* outgoings: 4	; #4, #6, #7
		* depth: 1
		*
		*/
		// 280
		// input: rax = ?
		// input: r15 = ?
		rdx = r15;
		r15 = rax;
		al = r13b;
		r13b = cl;
		// 300
		if (xmm1 <= xmm2) {
			goto _f333;	// to #4, BoJ
		}
		xmm1 = (double&)_38;
		// 311
		if (xmm0 > (double&)_38) {										// via xmm1
			/***
			* #6<<Inline JmpBlock>>
			* 477(477) to 493
			* instrs: 5
			* incomings: 2	; #3, #4
			* outgoings: 2	; #10, #11
			* depth: 2
			*
			*/
			// 477
			ecx = ((CA::Layer::Animation*)rbx)->_38;
			// 486
			if (0x220 == ((CA::Layer::Animation*)rbx)->_38) {			// via cx
				goto _f564;	// to #10, BoJ
			}
			(double&)_38 = (double)xmm1;
			// 493
			/***
			* #11<<Inline JmpBlock>>
			* 588(598) to 617
			* instrs: 8
			* incomings: 6	; #6, #7, #8, #10
			* outgoings: 2	; #12
			* depth: 3
			* concast #6 to #11
			*
			*/
			// 598
			xmm1 = 0.;
			// 607
			if (0.f >= data->_8) {
				cl = (double)xmm0 < (double&)_48;
				goto _f619;	// to #12, BoJ
			}
			// 617
			goto _f627;	// to #12
						// end of inline #11
						// end of inline #6
		}
		xmm0 = (float&)r15;
		// 326
		if ((float&)r15 <= (double&)_38) {				// via xmm0 <= xmm1
			goto _f363;	// to #4
		}
		// 328
		goto _f495;	// to #7, BoJ
					// end of inline #3
	}
	rdx = (float)xmm0;		// via rax;		xmm0 still equls to _48 right now.
	al = cl;
	// 278
	/***
	* #3<<Inline JmpBlock>>
	* 280(292) to 328
	* instrs: 14
	* incomings: 2	; #2
	* outgoings: 4	; #4, #6, #7
	* depth: 1
	* concast #2 to #3
	*
	*/
	// 292
	xmm0 = (float&)rdx;
	// 300
	if ((float)data->_8 <= 0.f) {
		goto _f333;	// to #4, BoJ
	}
	xmm1 = (double&)_38;
	// 311
	if ((double)xmm0 > (double&)_38) {
		/***
		* #6<<Inline JmpBlock>>
		* 477(477) to 493
		* instrs: 5
		* incomings: 2	; #3, #4
		* outgoings: 2	; #10, #11
		* depth: 2
		*
		*/
		// 477
		ecx = ((CA::Layer::Animation*)rbx)->_38;
		// 486
		if (0x220 == ((CA::Layer::Animation*)rbx)->_38) {
			goto _f564;	// to #10, BoJ
		}
		// 493
		/***
		* #11<<Inline JmpBlock>>
		* 588(598) to 617
		* instrs: 8
		* incomings: 6	; #6, #7, #8, #10
		* outgoings: 2	; #12
		* depth: 3
		* concast #6 to #11
		*
		*/
		// 598
		xmm1 = 0.;
		// 607
		if (0.f >= data->_8) {
			goto _f619;	// to #12, BoJ
		}
		// 617
		goto _f627;	// to #12
					// end of inline #11
					// end of inline #6
	}
	xmm0 = (float&)this->_98->_20->_20;		// via r15;
	// 326
	if ((double)xmm0 <= (double&)_38) {		// xmm1
		goto _f363;	// to #4
	}
	// 328
	// input: xmm0 = (float&)this->_98->_20->_20;	
	// input: xmm1 = (double&)_38;
	goto _f495;	// to #7, BoJ
				// end of inline #3
				// end of non-inline #2

				/***
				* #4<<JmpBlock>>
				* 333 to 444
				* instrs: 25
				* inners: 0
				*
				*/
_f333:
_f333:	// from #3(300, inline)
		/**
		* xmm0 is (float&)data->_8;
		* rbx is this->_98;
		*/
	xmm1 = (double&)_38;
		// 342
	if ((float&)data->_8 < (double&)_38) {						// via xmm0 < xmm1
		/***
		* #6<<Inline JmpBlock>>
		* 477(477) to 493
		* instrs: 5
		* incomings: 2	; #3, #4
		* outgoings: 2	; #10, #11
		* depth: 1
		*
		*/
		// 477
		ecx = ((CA::Layer::Animation*)rbx)->_38;
		// 486
		if (0x220 == ((CA::Layer::Animation*)rbx)->_38) {
			goto _f564;	// to #10, BoJ
		}
		// 493
		/***
		* #11<<Inline JmpBlock>>
		* 588(598) to 617
		* instrs: 8
		* incomings: 6	; #6, #7, #8, #10
		* outgoings: 2	; #12
		* depth: 2
		* concast #6 to #11
		*
		*/
		// 598
		xmm1 = 0.;
		// 607
		if (0. >= data->_8) {
			goto _f619;	// to #12, BoJ
		}
		// 617
		goto _f627;	// to #12
					// end of inline #11
					// end of inline #6
	}
	// 357
	if ((float&)this->_98->_20->_20 < (double&)_38) {
		// input: xmm0 is (float&)data->_8;
		// input: xmm1 = (double&)_38;
		goto _f495;	// to #7, BoJ
	}
_f363:	// from #3(326, inline)
	_38 = xmm1;
	CAAnimationSetFlags(this->_98->_8, 0x2, (uint32_t)0xffffffff);
	schedule_stop_callback((CA::Layer::Animation*)this->_98);
	/***
	* rbx is CA::Layer::Animation*, as iterator.
	*/
		// 399
	if ((((CA::Layer::Animation*)this->_98)->_38 & 0ff & 0x1) == 0) {
		/***
		* #8<<Inline JmpBlock>>
		* 542(542) to 550
		* instrs: 3
		* incomings: 1	; #4
		* outgoings: 1	; #11
		* depth: 1
		*
		*/
		// input: r13b ?
		// 542
		al = r13b;
		xmm0 = (double&)_48;
		// 550
		/***
		* #11<<Inline JmpBlock>>
		* 588(598) to 617
		* instrs: 8
		* incomings: 6	; #6, #7, #8, #10
		* outgoings: 2	; #12
		* depth: 2
		* concast #8 to #11
		*
		*/
		// 598
		xmm1 = 0.;
		// 607
		if (0. > data->_8) {
			goto _f619;	// to #12, BoJ
		}
		// 617
		goto _f627;	// to #12
					// end of inline #11
					// end of inline #8
	}

	*(CA::Layer::Animation**)_40 = ((CA::Layer::Animation*)rbx)->_0;		// via rax
	extern CA::Layer::Animation* global_animation_state0, global_animation_state1;
	((CA::Layer::Animation*)rbx)->_0 = global_animation_state0;
	global_animation_state1 = (CA::Layer::Animation*)rbx;
	rbx = *(CA::Layer::Animation**)_40;
	// 438
	if (rbx != 0) {
		goto _b187;	// to #2
	}
	// 444
	goto _f738;	// to #12
				// end of non-inline #4

				/***
				* #7<<JmpBlock>>
				* 495 to 540
				* instrs: 13
				* inners: 1
				*
				*/
_f495:
_f495:	// from #3(328, inline, EoJ)
		// input: xmm0 = (float&)this->_98->_20->_20;	
		// input: xmm1 = (double&)_38;
_f495:	// from #4(357)
		// input: xmm0 is (float&)data->_8;
		// input: xmm1 = (double&)_38;
		// input: rbx is CA::Layer::Animation*, found in CA::Layer::_98's chain.
	(double&)_40 = (double)xmm0;		// these two statemants should be inline.
	(double&)_38 = (double)xmm1;
	schedule_start_callback((CA::Layer::Animation*)rbx);
	// 517 inner jx
		// 531
	al = true;
	xmm0 = (double&)_48;
	if ((((CA::Layer::Animation*)rbx)->_38 & (0x4<<8) == 0)
		&& ((CA::Layer::Animation*)rbx)->_30 == 0) {
		/***
		* #11<<Inline JmpBlock>>
		* 588(598) to 617
		* instrs: 8
		* incomings: 6	; #6, #7, #8, #10
		* outgoings: 2	; #12
		* depth: 1
		*
		*/
		// 598
		xmm1 = 0.;
		// 607
		if (0. > data->_8) {
			goto _f619;	// to #12, BoJ
		}
		// 617
		goto _f627;	// to #12
					// end of inline #11
	}
	al = true;
	xmm0 = (double&)_40;
	// 540
	/***
	* #11<<Inline JmpBlock>>
	* 588(598) to 617
	* instrs: 8
	* incomings: 6	; #6, #7, #8, #10
	* outgoings: 2	; #12
	* depth: 1
	* concast #7 to #11
	*
	*/
	// input: r14 is arg2, which is an array of double?
	// 598
	xmm1 = 0;
	// 607
	if (0.f >= arg2[1]) {					// via xmm1 and r14
		goto _f619;	// to #12, BoJ
	}
	xmm0 = (double&)_48;
	cl = 0.f < arg2[1];
	// 617
	goto _f627;	// to #12
				// end of inline #11
				// end of non-inline #7

				/***
				* #10<<JmpBlock>>
				* 564 to 586
				* instrs: 7
				* inners: 1
				*
				*/
_f564:
_f564:	// from #6(486, inline)
		// input: cx = ((CA::Layer::Animation*)rbx)->_38;
		// 574
	if ((ch & 0x4) == 0
		&& ((CA::Layer::Animation*)rbx)->_30 == 0) {
		/***
		* #11<<Inline JmpBlock>>
		* 588(588) to 617
		* instrs: 8
		* incomings: 6	; #6, #7, #8, #10
		* outgoings: 2	; #12
		* depth: 1
		*
		*/
		// 588
		xmm1 = 0.;
		// 607
		if (0. > data->_8) {
			goto _f619;	// to #12, BoJ
		}
		// 617
		goto _f627;	// to #12
					// end of inline #11
	}
	(double&)_38 = (double)xmm1;
	xmm0 = r15;						// 1.maybe CA::Render::Timing::_20, 2.maybe #3 input.
	// 586
	/***
	* #11<<Inline JmpBlock>>
	* 588(598) to 617
	* instrs: 8
	* incomings: 6	; #6, #7, #8, #10
	* outgoings: 2	; #12
	* depth: 1
	* concast #10 to #11
	*
	*/
	// 598
	xmm1 = 0;
	// 607
	if (0.f >= arg2[1]) {
		goto _f619;	// to #12, BoJ
	}
	xmm0 = (double&)_48;
	cl = 0.f < arg2[1];
	// 617
	goto _f627;	// to #12
				// end of inline #11
				// end of non-inline #10

				/***
				* #12<<JmpBlock>>
				* 619 to 810
				* instrs: 56
				* inners: 7
				*
				*/
_f619:
_f619:	// from #11(607, inline)
		// input: xmm0
	cl = xmm0 > (double&)_48;
_f627:	// from #11(617, inline, EoJ)
		// input: cl
	xmm1 = (double&)_38;
	if (cl == false) {
		xmm0 = (double&)_48;			// max(xmm0, (double&)_48;
	}
	(double&)_48 = xmm0;
_f646:	// from #5(472, inline, EoJ)
_f646:	// from #9(558, inline)
_f646:	// from #9(562, inline, EoJ)
	if (al == true) {
		ecx = eax = (uint32_t)((CA::Layer::Animation*)rbx)->_38;
		if (((CA::Layer::Animation*)rbx)->_38 & 0x20) {
			if (((CA::Layer::Animation*)rbx)->_38 & 0x80) {					// via cx
				_50 = (bool&)cl = true;
			} // 683
			if (((CA::Layer::Animation*)rbx)->_38 & 0x100) {				// via ax
				_58 = (bool&)al = true;
			} // 699
		} // 699
	} // 699
	(double&)_38 = xmm1;
_f704:	// from #2(191)
_f704:	// from #2(204)
	if (0x63 == CA::Render::key_path_atom((void* const*)&((CA::Layer::Animation*)rbx)->_10, (unsigned long)0)) {
		r12 = rbx;
	}
	_40 = &((CA::Layer::Animation*)rbx->_0;
		// 732
	if (((CA::Layer::Animation*)rbx)->_0) {
		goto _b184;	// to #2
	}
_f738:	// from #4(444, EoJ)
	rsi = _68;						// &this->_4
	ebx = this->_4;			// via rsi;
	rax = _50;
	ecx = 0;
		// 755
	if ((bool)_50 == true) {		// via al
		OSAtomicOr32(0x1000000, (volatile uint32_t*)&this->_4);	// via rsi;
		ecx = 0x1000;
	} // 769
	eax = ebx;
	eax &= 0x3000;
		// 783
	if ((bool)_58 == true) {
		ecx |= 0x2000;
		OSAtomicOr32(0x800000, (volatile uint32_t*)&this->_4);	// via rsi;
	} // 798
	xmm1 = (double&)_38;
	rdx = r14;						// restore the 3rd argument, data, back to rdx.
		// 810
	goto _f824;	// to #13
				// end of non-inline #12

				/***
				* #13<<JmpBlock>>
				* 812 to 863
				* instrs: 16
				* inners: 1
				*
				*/
_f812:
_f812:	// from #0(112)
		// input: rsi = _68; and _68 is &this->_4;
		// input: ecx = 0
	ebx = this->_4;			// via rsi
	eax = this->_4 & 0x3000;		// via ebx
	r12d = 0;
_f824:	// from #12(810, EoJ)
		// input: ecx = 0 | ((bool)_50)?0x1000:0 | ((bool)_58)?0x2000:0;
		// input: eax = the old value of this->_4; this->_4 was configued accroding to _50 or _58;
		// input: rdx is data, the 3rd arg.
		// input: rdi = this;

	if ((ecx == eax			// 826					// rebuild-mode
		&& eax == 0)			// 830
		|| (ecx == eax		// 826
			&& eax != 0	// 830
			&& data->_8 == 0.f	// 844	 via rdx
			&& data->_c == 0)) {	// 850	
		// goto _f1147;
		// inline 1147 to 1151
		goto _f1151;
	} 
	
	if (ecx == eax) {			// 826
		if (eax != 0		// 830					// rebuild-mode
			&& (data->_8 != 0.f		// 844
				|| data->_c != 0)) {		// 850
			r13 = r12;
			r14 = this->_10;		// via rdi
		}
		// 863 jmp 900
	} else {	// 865
		r13 = r12;
		r14 = this->_10;							// via rdi
		eax = this->_4 & 0xffffcfff | 0x3000;		// via ebx
		rdx = rcx;				// save
		ecx &= eax;
		OSAtomicOr32(ecx, (volatile uint32_t*)&this->_4);	// via rsi
		rcx = rdx;				// restore
	}	// 900
	r15 = rdi;
	// 905
	if (ecx != 0) {				// ecx is still the input one.
		r12 = rcx;
		(double&)_38 = xmm1;
		al = [(id)r14 _scheduleAnimationTimer];
		rbx = _60;
		rdi = r15;
		// 944
		if (al == true) {
			rax = r12;			// the input ecx for this cover block
			// 956
			if (rax & (0x10<<8)) {
				r15 = rdi;
				r12 = rax;
				[(id)r14 setNeedsLayout];
				rax = r12;
				rdi = r15;
			} // 986
			// 989
			if (rax & (0x20<<8)) {
				r15 = rdi;
				// 997
				if (r13 != 0) {
					[(id)r14 performSelectorOnMainThread : @selector("removeAnimationForKey:") withObject:@"contents" waitUntilDone : 0];
				} // 1032
				[(id)r14 setNeedsDisplay];
				rdi = r15;
				rdi->_85 |= 0x20;
			} // 1058
			xmm0 = (double&)_38;
			(double&)_48 = xmm0;
			// 1068 jmp 1151
		} // 1151
	} else {	// 1070
		[(id)r14 _cancelAnimationTimer];
		// 1089
		if (ebx & (0x10<<8)) {
			[(id)r14 setNeedsLayout];
		} // 1107
		// 1110
		if ((ebx & (0x20<<8)) == 0) {
			rbx = _60;					// arg2
			rdi = r15;
			// 1119 jmp 1151
		} else { // 1121
			[(id)r14 setNeedsLayout];
			rdi = r15;
			rdi->_85 |= 0x20;
			rbx = _60;					// arg2
		} // 1151
	} // 1151
_f1151:		
	this->set_animations((CA::Layer::Animation*)_30);			// _30 is this->_98
	al = true;
_1162:
	*arg2 = (double&)_48;			// via rbx, xmm0
	// 1185
	return (bool)al;
}


/**
if ((!			// 826
&&)			// 830
|| (!		// 826
&& !	// 830
&& !	// 844
&& )) {	// 850
// goto _f1147;
// inline 1147 to 1151
goto _f1151;
}

if (!) {			// 826
if (!		// 830
&& (		// 844
|| !)) {		// 850
}
// 863 jmp 900
} else {	// 865

}	// 900

// 905
if (!) {
// 944
if (!) {
// 956
if (!) {

} // 986
// 989
if (!) {
// 997
if (!) {
} // 1032
} // 1058
// 1068 jmp 1151
} // 1151
}
else {	// 1070
// 1089
if (!) {
} // 1107
// 1110
if (!) {
// 1116 jmp 1151
} else { // 1121
} // 1151
} // 1151
_f1151:
// 1185
return;
*/