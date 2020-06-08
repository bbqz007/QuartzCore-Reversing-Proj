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

void CA::Layer::update_sublayers(CA::Transaction* transaction, CALayerArray* oldSublayers, CALayerArray* newSublayers)
{
	r15 = oldSublayers;
	_48 = transaction;
	_50 = this;
	int64_t& countOfOldSublayers = r13;
	int64_t& countOfNewSublayers = r12;
	CALayer*& collectOldSublayers = r14;				// &=r14, since 119 before 440
	CALayer*& collectNewSublayers = rbx;				// &=rbx, since 282 before 440

	/**
	* beginning, to do some preparations.
	* alloc the buffers for collections both of the old oc layers and the new oc layers
	* qsort the two collections by sorter of pointer.
	*/
	// 45
	if (!(oldSublayers == newSublayers)) { // 42 (r15 == rcx)
		_38 = 0x0;
		countOfOldSublayers = 0;
		// 65
		if (!(0 == oldSublayers)) { // 62 (0 == r15)
			countOfOldSublayers = oldSublayers->_ivars._8;
		} // 82
		countOfNewSublayers = 0;
		// 88
		if (!(0 == newSublayers)) { // 85 (0 == rcx)
			countOfNewSublayers = newSublayers->_ivars._8;
		} // 105
		_40 = newSublayers;
		rbx = &_38;
		r14 = &_38;				// via rbx
		// 119
		if (!(countOfOldSublayers <= 0)) {
			rbx = countOfOldSublayers * 8;
			rdi = 8 + countOfOldSublayers * 8;
			// 144
			if (!((8 + countOfOldSublayers * 8) > 0x1000)) { // 137 (rdi > 0x1000)
				collectOldSublayers = (CALayer**)alloca(((8 + countOfOldSublayers * 8) + 0xf) & -0x10);
			} // 165
			else {
				// 165 call
				collectOldSublayers = (CALayer**)malloc(8 + countOfOldSublayers * 8);
			}
				 // 193 call
			memcpy(collectOldSublayers, oldSublayers->_ivars._0, countOfOldSublayers * 8);
			// 216 call
			qsort(collectOldSublayers, countOfOldSublayers, 0x8, (int(*)(void const*, void const*))&compare_pointer);
			((CALayer**)collectOldSublayers)[r13] = 0x0;
			rbx = &_38;
		} // 233
		  // 236
		if (!(countOfNewSublayers <= 0)) {
			r15 = countOfNewSublayers * 8;
			rdi = 8 + countOfNewSublayers * 8;
			// 261
			if (!((8 + countOfNewSublayers * 8) > 0x1000)) { // 254 (rdi > 0x1000)
				collectOldSublayers = (CALayer**)alloca(((8 + countOfNewSublayers * 8) + 0xf) & -0x10)
			} // 282
			else {
				// 282 call
				collectOldSublayers = (CALayer**)malloc(8 + countOfNewSublayers * 8);
			}
				 // 314 call
			memcpy(collectOldSublayers, newSublayers->_ivars._0, countOfNewSublayers * 8);
			// 337 call
			qsort(collectOldSublayers, countOfNewSublayers, 0x8, (int(*)(void const*, void const*))&compare_pointer);
			((CALayer**)collectOldSublayers)[countOfNewSublayers] = 0x0;
		} // 350

		_70 = countOfNewSublayers;
		_68 = countOfOldSublayers;
		CA::Layer*& tailLayer = rax;
		CA::Layer*& itLayer = rcx;
		itLayer = this;					// via _50

		do {
		_b362:	 // from 372
			tailLayer = itLayer;
			itLayer = tailLayer->_8;
			// 372
#if 0
			if (itLayer) // 369 (0 != rcx)
				goto _b362;
#else
		} while (itLayer);
#endif
		// _40 re-used
		ecx = tailLayer->_a4;
		_40 = tailLayer->_a4;				// via ecx
		rax = collectOldSublayers;
		_60 = collectOldSublayers;							// via rax
		r12 = collectOldSublayers + 1;
		r14 = *collectOldSublayers;
		_78 = collectNewSublayers;
		r15 = collectNewSublayers + 1;
		r13 = *collectNewSublayers;
		_54 = 0x0;

		CALayer*& currentOldOcLayer = r14;
		CALayer*& currentNewOcLayer = r13;
		CALayer**& nextItCollectOldOcLayer = r12;
		CALayer**& nextItCollectNewOcLayer = r15;

		// 418
		if (!(0 == countOfOldSublayers) // 415 (0 == r13)
				 // 427
			&& !(0 == currentOldOcLayer)) { // 424 (0 == r14)
			_54 = 0x0;
		_b440:	 // from 644
			rax = r12;
		_b443:	 // from 533
			r12 = rax;
		_b446:	 // from 502
		_b446:	 // from 449 #0, 533 #2
		_b446:	 // from 451 #0, 644 #2
			// 449
			if (currentOldOcLayer == currentNewOcLayer) { // 446 (r14 == r13)
				// inline jmp 509
				currentOldOcLayer = *nextItCollectOldOcLayer;
				currentNewOcLayer = *nextItCollectNewOcLayer;
				nextItCollectNewOcLayer = nextItCollectNewOcLayer + 1;
				// 523
				if (0 == currentNewOcLayer) { // 520 (0 == r13)
					/**
					* reach the end of collection of new oc layers
					* break;
					*/
					// inline jmp 652, #1
					nextItCollectOldOcLayer = nextItCollectOldOcLayer + 1;
					goto _f656;
				}
				else { // 523 next
					rax = nextItCollectOldOcLayer + 1;
					// 533
					if (0 != currentOldOcLayer) { // 530 (0 != r14)
						// goto _b443; inline #2
						nextItCollectOldOcLayer = nextItCollectOldOcLayer + 1;
						// natural flow to _b446
						goto _b446;
					}
					/**
					* reach the end of collection of old oc layers
					* break;
					*/
					// 535
					// goto _f652; inline #2
					nextItCollectOldOcLayer = nextItCollectOldOcLayer + 1;
					goto _f656;
				}
			} // 451
			else if (currentOldOcLayer >= currentNewOcLayer) {
				/**
				* in this case,, there are new ones in the hole between two old ones, 
				* that mean the ones which the old collection doesn't own.
				* we should call update_added_sublayer to update it and its visibleFlags with this tail layer's visibleFlags..
				* and union their thread flags.
				*/
				// inline jmp 537
					 // 540 call
				CFRetain(currentNewOcLayer);
				// 571 call
				((CA::Layer*)currentNewOcLayer->_attr._8)->update_added_sublayer(transaction, (CA::Layer*)this, (unsigned int)tailLayer->_a4);
				rdi = currentNewOcLayer->_attr._8;
				uint32_t& thread_flags = eax;
				thread_flags = (int64_t)(int32_t&)transaction->_8;
				// 595
				if ((0 > transaction->_8)  // 592 (0 > rax)
					|| !(0 != (eax = ((int32_t*)&currentNewOcLayer->_attr._8->_a8)[transaction->_8]))) { // 604 (0 != eax)
						 // 612 call
					thread_flags = *(uint32_t*)((CA::Layer*)currentNewOcLayer->_attr._8)->thread_flags_(transaction);
				}
				_54 |= thread_flags;
				currentNewOcLayer = *nextItCollectNewOcLayer;
				nextItCollectNewOcLayer = nextItCollectNewOcLayer + 1;
				// 632
				if (0 == currentNewOcLayer) { // 629 (0 == r13)
					/**
					* reach the end of collection of new oc layers
					* break;
					*/
					// gen jmp 656
					goto _f656;
				}
				rax = _60;	// collectOldSublayers;
				ecx = _40;	// tailLayer->_a4;
				// 644
				if (0 != currentOldOcLayer) { // 634 (0 != r14)
					// goto _b440; inline #2
					nextItCollectOldOcLayer = nextItCollectOldOcLayer;
					// natural flow to _b446
					goto _b446;
				}
				/**
				* reach the end of collection of old oc layers
				* break;
				*/
				// 650
				goto _f663;
				// 652 unreachable
			}
			else { // 451 next
				/**
				* in this case, there are old ones in the hole between two new ones
				* so, these old ones have been remove from new ones.
				* we should release them.
				*/
				rbx = _48;
				// 475 call
				((CA::Layer*)currentOldOcLayer->_attr._8)->update_removed_sublayer(transaction, (unsigned int)tailLayer->_a4);
				// 486 call
				transaction->release_object((void const*)currentOldOcLayer);
				currentOldOcLayer = *nextItCollectOldOcLayer;
				nextItCollectOldOcLayer = nextItCollectOldOcLayer + 1;
				// 502
				if (0 != currentOldOcLayer) // 499 (0 != r14)
					goto _b446;
				/**
				* reach the end of collection of old oc layers
				* break;
				*/
				// 504
				goto _f731;
			} // 509 unreachable

		_f652:	 // from 523
		_f652:	 // from 535
			nextItCollectOldOcLayer = nextItCollectOldOcLayer + 1;
		_f656:	 // from 632
			rax = _60;	// collectOldSublayers;
			ecx = _40;	// tailLayer->_a4;
		} // 663
	_f663:	 // from 650
		/**
		* deal with the odds of collection of old oc layers.
		* call update_removed_sublayer
		* and release it.
		*/
		_60 = rax;
		// 670
		if (!(0 == currentOldOcLayer)) { // 667 (0 == r14)
			rbx = transaction; // via _48;
			_40 = ecx;
			do {
			_b679:	 // from 724
					 // 697 call
				((CA::Layer*)currentOldOcLayer->_attr._8)->update_removed_sublayer(transaction, (unsigned int)tailLayer->_a4);
				// 708 call
				transaction->release_object((void const*)currentOldOcLayer);
				currentOldOcLayer = *nextItCollectOldOcLayer;
				nextItCollectOldOcLayer = nextItCollectOldOcLayer + 1;
#if 0
				// 724
				if (0 != currentOldOcLayer) // 721 (0 != r14)
					goto _b679;
#else
			} while (currentOldOcLayer);
#endif
			// 726
			goto _f731;
		} // 728
		_40 = ecx;
	_f731:	 // from 726
	_f731:	 // from 504
		r12d = _54;
		// 735 testq %r13, %r13
		rbx = transaction; // via _48;
		r14 = this; // via _50;
		// 746
		if (!(0 == currentNewOcLayer)) { // 735 (0 == r13)
			/**
			* deal with the odds of collection of new oc layers.
			* call update_added_sublayer
			* and union their thread flags.
			*/
			do {
			_b748:	 // from 837
					 // 751 call
				CFRetain(currentNewOcLayer);
				// 777 call
				((CA::Layer*)currentNewOcLayer->_attr._8)->update_added_sublayer(transaction, (CA::Layer*)this, (unsigned int)tailLayer->_a4);
				rdi = currentNewOcLayer->_attr._8;
				uint32_t& thread_flags = eax;		// &=rax;
				thread_flags = (int64_t)(int32_t&)transaction->_8;
				// 801
				if ((0 > transaction->_8)  // 798 (0 > rax)
					|| !(0 != (thread_flags = ((int32_t*)&currentNewOcLayer->_attr._8->_a8)[transaction->_8]))) { // 810 (0 != eax)
						 // 817 call
					thread_flags = *(uint32_t*)((CA::Layer*)currentNewOcLayer->_attr._8)->thread_flags_(transaction);
				}
				r12d = r12d | eax;
				currentNewOcLayer = *nextItCollectNewOcLayer;
				nextItCollectNewOcLayer = nextItCollectNewOcLayer + 1;
				// 837
#if 0
				if (0 != currentNewOcLayer) // 834 (0 != r13)
					goto _b748;
#else
			} while (currentNewOcLayer);
#endif
		} // 839

		/**
		* finally, 
		* call update_for_changed_sublayers, to update the thread flags of sublayers
		* with the union of thread flags.
		*
		*/
		  // 848 call
		this->update_for_changed_sublayers(transaction, (unsigned int)r12d);
		rax = countOfOldSublayers * 8 + 8;

		/**
		* finalize,
		* free the buffer of collections both of old oc layers and new oc layers.
		* 
		*/
		// 871
		if (!((countOfOldSublayers * 8 + 8) < 0x1001)) { // 865 (rax < 0x1001)
				 // 877 call
			free(collectOldSublayers);
		} // 882
		rax = countOfNewSublayers * 8 + 8;
		// 910
		if (!((countOfNewSublayers * 8 + 8) < 0x1001)) { // 894 (rax < 0x1001)
				 // 916 call
			free(collectNewSublayers);
		} // 921
	} // 921
	return;
}


void CA::Layer::update_removed_sublayer(CA::Transaction* transaction, unsigned int visibleFlags)
{
	r14 = transaction;
	rbx = this;
	this->_8 = 0x0;
	this->_a4 = visibleFlags;
	edx = 0;
	// 29 call
	// %edx = 0
	this->mark_visible(transaction, false);
	// 40 call
	transaction->add_root((CA::Layer*)this);
	// 45 lock
	OSAtomicAnd32(0xffefffff, (volatile int32_t*)&this->_4);
	OSAtomicAnd32(0xffffbfff, (volatile int32_t*)&this->_84);
	// 77
	if (0x400000 & (((this->_80) << 0x3) ^ this->_4)) { // 72 (0x400000 & eax)
		// goto _f84; inline #0
		return this->toggle_flipped(transaction);
	}
	return;
}


void CA::Layer::update_for_changed_sublayers(CA::Transaction* transaction, unsigned int visibleFlags)
{
	r14 = transaction;
	rbx = this;
	// 18
	if (!(0 == visibleFlags)) { // 16 (0 == edx)
		al = (0 != (visibleFlags & 0xff & 0x6));
		eax = (0 == (0x18 & visibleFlags)) ? ((uint32_t)(uint8_t&)al * 4) : ((uint32_t)(uint8_t&)al * 4 + 10);
		ecx = (0 == (0x60 & visibleFlags)) ? eax : (eax | 0x40);
		r15d = (0 == (0x300 & visibleFlags)) ? ecx : (ecx | 0x200);

		CA::Layer*& itLayer = rbx;				// &=rbx, begin at this
		itLayer = this;						// fake
		// 84
		if (!(0 == itLayer)) { // 81 (0 == rbx)
			r15d = r15d | (visibleFlags & 0x800);

			do {
			_b95:	 // from 160
				uint32_t*& thread_flags_place = rax;				// &=rax, after 113
				uint32_t& thread_flags = rcx;						// &=rcx
				rax = (int64_t)(int32_t&)transaction->_8;
				// 102
				if (!(0 > transaction->_8)) { // 99 (0 > rax)
					thread_flags = ((int32_t*)&itLayer->_a8)[transaction->_8];
					// 113
					if (!(0 == thread_flags)) { // 111 (0 == ecx)
						thread_flags_place = (uint32_t*)&((int32_t*)&rbx->_a8)[transaction->_8];
						// 123
						goto _f138;
					} // 125
				} // 125
				  // 131 call
				this->thread_flags_(transaction);
				thread_flags = *thread_flags_place;
			_f138:	 // from 123
					 // 146
				if (!((ecx & r15d) == r15d)) { // 143 (edx == r15d)
					*thread_flags_place = thread_flags | r15d;
					itLayer = itLayer->_8;
					// 160
#if 0
					if (0 != itLayer) // 157 (0 != rbx)
						goto _b95;
				} // 162
#else
			}
				} while (0 != itLayer);
#endif
			} // 162
		} // 162
	return;
	// 173 nop
	}


void CA::Layer::update_added_sublayer(CA::Transaction* transaction, CA::Layer* sublayer, unsigned int visibleFlags)
{
	r12d = visibleFlags;
	r15 = sublayer;
	r14 = transaction;
	rbx = this;
	r13d = this->_a4;
	this->_8 = sublayer;
	this->_a4 = 0x0;
	edx = (sublayer->_84 & 0x800) >> 0xb;
	// 63 call
	this->mark_visible(transaction, (bool)((sublayer->_84 & 0x800) >> 0xb));
	// 74 call
	transaction->remove_root((CA::Layer*)this);
	// 82
	if (!(0 == this->_a4)) { // 79 (0 == r13d)
		// 87
		if (!(this->_a4 == visibleFlags)) { // 84 (r13d == r12d)
			// 95 call
			this->mark_context_changed(transaction);
		} // 100
	} // 100
	ecx = (0 == (0x80000 & this->_80)) ? ((sublayer->_4) & 0x400000) : (((sublayer->_4) & 0x400000) ^ 0x400000);
	eax = 0x400000 & this->_4;
	// 140
	if (!(eax == ecx)) { // 138 (eax == ecx)
		// 148 call
		this->toggle_flipped(transaction);
	} // 153
	  // 161
	if (!(0 == (0x8 & sublayer->_88))) { // 153 (0 == (0x8 & r15->_88))
		// 167 lock
		OSAtomicOr32(0x100000, (volatile int32_t*)&this->_4);
		rbx->_84 |= 0x40 << 8;
	} // 181
	// 193 (false == $(186 call))
	if (!(false == _CFExecutableLinkedOnOrAfter(0x3f7))) { // 191 (0 == al)
		return this->ensure_transaction_recursively(transaction);
	} // 220

	return;
	// 235 nop
}


void CA::Layer::toggle_flipped(CA::Transaction* transaction)
{
	r15 = transaction;
	r12 = this;
	r13 = __cfs("contentsAreFlipped");
	// 27
	goto _f41;

	CA::Layer*& itLayer = r12;					// &=r12, begin at this
	itLayer = this;								// fake
#if 0
	_b29:	 // from 224
			 r12 = itLayer->_20->_attr._8;
#else 
	for (;;) {
#endif
	_f41:	 // from 27
		r14 = itLayer->_10;
		// 59 call
		// [itLayer->_10 willChangeValueForKey:@"contentsAreFlipped"];
		objc_msgSend(itLayer->_10, "willChangeValueForKey:", __cfs("contentsAreFlipped"));
		// 65 lock
		OSAtomicXor32(0x400000, (volatile int32_t*)&itLayer->_4);
		// 86 call
		// 93
		if (!(false != ((CA::Layer*)itLayer)->layout_is_active(transaction, true))) { // 91 (0 != al)
			// 113 (false == $(105 call))
			// [itLayer->_10 needsLayoutOnGeometryChange]
			if (!(false == objc_msgSend(itLayer->_10, "needsLayoutOnGeometryChange"))) { // 111 (0 == al)
					 // 125 call
				// [itLayer->_10 setNeedsLayout];
				objc_msgSend(itLayer->_10, "setNeedsLayout");
			} // 131
		} // 131
		  // 144 call 
		// [itLayer->_10 didChangeValueForKey:@"contentsAreFlipped"];
		objc_msgSend(itLayer->_10, "didChangeValueForKey:", __cfs("contentsAreFlipped"));
		CALayerArray*& sublayers = rax;				// &=rax, temporary
		sublayers = (CALayerArray*)itLayer->_18;
		// 158
		if (!(0 == sublayers)) { // 155 (0 == rax)
			int64_t& count = r14;					// &=r14
			count = sublayers->_ivars._8;
			// 178
			if (!(0 == count)) { // 175 (0 == r14)
				CALayer**& itOcSublayer = rbx;		// &=rbx
				itOcSublayer = sublayers->_ivars._0;
				do {
				_b184:	 // from 214
					// 202 call
					((CA::Layer*)(*itOcSublayer)->_attr._8)->toggle_flipped(transaction);
					itOcSublayer = itOcSublayer + 1;
					--count;
					// 214
#if 0
					if (count != 0)
						goto _b184;
#else
				} while (count != 0);
#endif
				} // 216
			} // 216
#if 0
		rax = itLayer->_20;
		// 224
		if (0 != itLayer->_20) { // 221 (0 != rax)
			// goto _b29; inline #0
			itLayer = itLayer->_20->_attr._8;
			// natural flow to 41
			goto _f41;
		}
#else
		if (0 == itLayer->_20)
			break;
		/***
		* pick the underlying layer of oc mask layer of current iterated underlying layer.
		*/
		itLayer = itLayer->_20->_attr._8;
		} // end for
#endif
	return;
}


CALayer* CA::Layer::superlayer()
{
	CA::Transaction*& transaction = r14;				// &=r14
	rbx = this;
	r15d = 0x60000 & this->_4;
	// 23
	if (0 == (0x60000 & this->_4)) {
#if 0
		/**
		// inline jmp 115
		rcx = this->_8;
		eax = 0;
		// 124
		if (!(0 == this->_8)) { // 121 (0 == rcx)
			rax = this->_8->_10;
		} // 130
		// goto _f130; inline #1
		*/
#else
		return (this->_8) ? (CALayer*)this->_8->_10 : 0;
#endif
	}
	// 25 call
	transaction = CA::Transaction::ensure_compat();
	CA::Layer*& modelLayer = rcx;						// &=rcx, temporary
	// 39 call
	modelLayer = this->model_layer(transaction);
	eax = 0;
	// 52
	if (0 == modelLayer) { // 49 (0 == rcx)
		  // inline jmp 130
		return 0;
	}
	rdi = modelLayer->_8;

	CALayer*& presentationLayer = rcx;					// &=rcx, temporary
	// 65
	if ((0x60000 & this->_4) != 0x20000		// 58 (r15d != 0x20000)
											// 70
		|| 0 == modelLayer->_8) { // 67 (0 == rdi)
#if 0
		/**
			// inline jmp 102
		eax = 0;
		// 107
		if (0 == modelLayer->_8) { // 104 (0 == rdi)
			// inline jmp 130, #1
			return 0;
		}
		rax = rdi->_10;
		// 113
		// goto _f130; inline #2
		return modelLayer->_8->_10;
		*/
#else
		return (0 == modelLayer->_8) ? 0 : (CALayer*)modelLayer->_8->_10;
#endif
	} // 102

	if (0 == (presentationLayer = rax = ((CA::Layer*)modelLayer->_8)->presentation_layer(transaction))) { // 85 (0 == rcx)
				 // inline jmp 130
		return 0;
	}
	else { // 88 next
		rdi = presentationLayer->_attr._8;
	} // 102
#if 0
	/**
	eax = 0;
	// 107
	if (0 == presentationLayer->_attr._8) // 104 (0 == rdi)
		  // gen jmp 130
		goto _f130;
	rax = presentationLayer->_attr._8->_10;
	// 113
	goto _f130;



_f130:	 // from 113
_f130:	 // from 107
_f130:	 // from 88
_f130:	 // from 52
	return;
	*/
#else
	return (0 == presentationLayer->_attr._8) ? 0 : presentationLayer->_attr._8->_10;
#endif
	// 141 nop
}


CALayerArray* CA::Layer::sublayers()
{
_b0:	// from 245
	CALayer**& newSublayers = _48;						// &=_48
	CA::Transaction*& transaction = _38;					// &=_38
	int64_t& count = r12;									// &=r12
	r13 = this;
	rbx = (void *)0x00000001066f9070: __stack_chk_guard;
	rbx = rbx->_0;
	_30 = rbx;
	eax = 0x60000 & this->_4;
	// 48
	if ((0x60000 & this->_4) != 0x20000) { // 43 (eax != 0x20000)
		// inline jmp 175
		// 177
		if (!(0 != (0x60000 & this->_4))) { // 175 (0 != eax)
			r13 = r13 + 0x18;
			// 183
			// goto _f442; inline #1
			return this->_18;
		} // 188
		CA::Layer*& modelLayer = rcx;					// &=rcx, temporary
		  // 188 call
		// 199 call
		modelLayer = this->model_layer(CA::Transaction::ensure_compat());
		eax = 0;
		// 212
		if (!(0 == modelLayer)) { // 209 (0 == rcx)
			// goto _f446; inline #0
			return 0;
		}
		// 245 goto _b0;
		return modelLayer->sublayers();
	} // 57
	else if (0 != (rax = this->_18)) { // 54 (0 != rax)
		// inline jmp 446
		return this->_18;
	}
	else {
		CA::Layer*& modelLayer = rcx;					// &=rcx, temporary
		// 63 call
		_38 = CA::Transaction::ensure_compat();
		// 78 call
		modelLayer = this->model_layer(transaction);
		eax = 0;
		// 91
		if (0 == modelLayer) { // 88 (0 == rcx)
			// inline jmp 446
			return 0;
		}
		CALayerArray*& sublayersOfModelLayer = rcx;		// &=rcx, since dst, temporary
		sublayersOfModelLayer = modelLayer->_18;		// via rcx = rcx->_18;
		eax = 0;
		// 106
		if (0 == sublayersOfModelLayer) { // 103 (0 == rcx)
			// inline jmp 446
			return 0;
		}
	} // 112 splitted by hand

	CALayerArray**& retSublayersArrayPlace = r13;				// &=r13, since dst operand
	r13 = (CALayerArray**)&this->_18;
	count = sublayersOfModelLayer->_ivars._8;
	_40 = sublayersOfModelLayer;					// save rcx (sublayersOfModelLayer)
	r14 = count + count * 8;
	// 150
	if ((count + count * 8) > 0x1000) { // 143 (r14 > 0x1000)
		// inline jmp 250
		// 253 call
		newSublayers = (CALayer**)malloc(count + count * 8);
		// 265
		if (0 == newSublayers) { // 262 (0 == rax)
			// goto _f442; inline #1
			rax = *retSublayersArrayPlace;
			return this->_18;
		}
		goto _f271;
	}
	else { // 150 next
		newSublayers = (CALayer**)alloca((count + count * 8 + 0xf) & -0x10);
		// 173
		goto _f271;
	}
	// 175 unreachable

_f271:	// from 173
	int64_t& sizeOfBufferOfCFArrray = _50;		// &=_50
	sizeOfBufferOfCFArrray = count + count * 8;					// via r14
	ebx = 0;
	int32_t& indexOfSublayers = ebx;
	int32_t& countOfSublayers = ebx;
	// 280
	if (!(0 == count)) { // 277 (0 == r12)
		int32_t& addedCount = r14d;

		r14d = 0;
		// 285
		goto _f297;
	_b287:	// from 352
	_f297:	// from 285
		CALayerArray*& sublayersOfModelLayer = _40;
		CALayer*& ocSublayer = rax;
		ocSublayer = sublayersOfModelLayer->_ivars._0[indexOfSublayers];
		CALayer*& presentationLayer = rax;
		// 325 call
		presentationLayer = ((CA::Layer*)ocSublayer->_attr._8)->presentation_layer(transaction);
		// 333
		if (!(0 == presentationLayer)) { // 330 (0 == rax)
			rcx = newSublayers;
			newSublayers[addedCount] = presentationLayer;
			++addedCount;
		} // 346
		++indexOfSublayers;
		// 352
		if (count != rbx) // 349 (r12 != rbx)
			goto _b287;

		countOfSublayers = addedCount;
	} // 357
	extern Class CALayerArray;
	r14 = &objc_msgSend;
	// 378 call
	r15 = newSublayers;
	// 407 call
	*(struct CALayerArray**)r13 = objc_msgSend(objc_msgSend(CALayerArray, "alloc"), "initWithLayers:count:retain:", newSublayers, countOfSublayers, 0x1);// *%r14;
  // 422
	if (!(sizeOfBufferOfCFArrray < 0x1001)) { // 414 (_50 < 0x1001)
		// 427 call
		free(newSublayers);
	} // 432
_f442:	// from 183
	rax = *(struct CALayerArray**)r13;


_f446:	// from 106
_f446:	// from 91
_f446:	// from 57
	return *(struct CALayerArray**)r13;
}

bool CA::Layer::style_value(unsigned int hkey, objc_object** value)
{
	r14 = value;
	r15d = hkey;
	rbx = this;
	// 31
	if (0 == (0x1 & this->_88)) { // 24 (0 == (0x1 & rbx->_88))
		return false;
	}
	// 44
	if ((0 == (CA::AttrList*)this->_78)  // 41 (0 == rdi)
		|| !(false != ((CA::AttrList*)this->_78)->get(0x1b6, (_CAValueType)0x1, (void*)&_28))) { // 65 (0 != al)
		// 69
		// 80 call
		// %rsi = "class"
		// 103 call
		CAObject_defaultValueForAtom(objc_msgSend((CALayer*)this->_10, "class"), 0x1b6, 0x1, &_28);
	} // 108
	// 113
	if (_28 == 0x0) { // 108 (_28 == 0x0)
		return false;
	}
	__CFString*& atomKeyString = r15;					// &=r15, validate after 118
	// 118 call
	atomKeyString = CAAtomGetString(hkey);
	rax = _28;
	// 133
	if (!(0 == _28)) { // 130 (0 == rax)
		rbx = "objectForKey:";
		r12 = __cfs("style");

		do {
		_b149:	// from 192
			objc_object*& objectForKey = rax;			// &=rax, temporary
		   // 158 call
			objectForKey = objc_msgSend((objc_object*)_28, "objectForKey:", atomKeyString);
			// 167
			if (0 != objectForKey) { // 164 (0 != rax)
				// goto _f209; inlilne #0
				extern objc_object* kCFNull;
				*value = (objectForKey != kCFNull) ? objectForKey : 0;
				al = true;
				// 230
				// goto _b196; inline #1
				return true;
			}
			// 179 call
			_28 = objc_msgSend((objc_object*)_28, "objectForKey:", __cfs("style"));
			// 192
#if 0
			if (0 != _28) // 189 (0 != rax)
				goto _b149;
#else 
		} while (_28);
#endif
		} // 194
	eax = 0;
_b196:	// from 230
	return false;
	}

void CA::Layer::replace_sublayer(CA::Transaction* transaction, CALayer* removeLayer, CALayer* replaceWithLayer)
{
	rbx = replaceWithLayer;
	r12 = removeLayer;
	r15 = transaction;
	r14 = this;
	extern Class NSException;
	// 32
	if (removeLayer == replaceWithLayer) { // 29 (r12 == rbx)
		// inline goto 142
		return;
	}
	// 37 call
	transaction->lock();
	// 45
	if (0 == replaceWithLayer) { // 42 (0 == rbx)
		// inline jmp _f157
		// 166 call
		this->remove_sublayer(transaction, (CALayer*)removeLayer);
		// 177 call
		transaction->release_object((void const*)removeLayer);
		// 182
		// goto _f449; inline #1
		return transaction->unlock();
	}

	CA::Layer*& replaceCxxLayer = rcx;						// &=rcx
	replaceCxxLayer = replaceWithLayer->_attr._8;
	// 59 testl $0x60000, 0x4(%rcx)
	// 66
	if (!(0x60000 & replaceCxxLayer->_4))) { // 59 (0 == (0x60000 & rcx->_4))
	eax = 0;
	// 102 call
	objc_msgSend(NSException, "raise:format:", __cfs("CALayerInvalidTree"), __cfs("expecting model layer not copy: %@"), replaceCxxLayer->_10);
	rax = CALayer._attr;
	} // 115
	rdi = replaceWithLayer->_attr._8;
	// 127
	if (0 == replaceWithLayer->_attr._8) { // 124 (0 == rdi)
		// inline goto _f187;
		// 190 call
		CFRetain(replaceWithLayer);
		// 207 call
		((CA::Layer*)replaceWithLayer->_attr._8)->remove_from_context();
		// natural flow to 212
		goto _f212;
	}
	else {
		// 135 call
		((CA::Layer*)replaceWithLayer->_attr._8)->remove_sublayer(transaction, (CALayer*)replaceWithLayer);
		// 140
		goto _f212;
	}



_f212:	// from 140
		// 212 cmpq %r12, 0x20(%r14)
		// 216
	if (!(this->_20 == removeLayer)) { // 212 (r14->_20 == r12)
			 // 237 call
		this->begin_change(transaction, (unsigned int)0x1b8, (objc_object*&)*(objc_object**)&_30);

		CA::Layer*& tail = rax;
		rcx = this;
		do {
		_b245:	// from 255
			tail = rcx;
			rcx = tail->_8;
			// 252 testq %rcx, %rcx
			// 255
#if 0
			if (rcx) // 252 (0 != rcx)
				goto _b245;
#else 
		} while (rcx);
#endif

		edx = tail->_a4;
		_34 = edx;
		// 281 call
		((CA::Layer*)removeLayer->_attr._8)->update_removed_sublayer(transaction, (unsigned int)tail->_a4);
		// 292 call
		transaction->release_object((void const*)removeLayer);

		CALayerArray*& sublayers = r13;
		sublayers = this->_18;
		// 321 call (r13, $(307 call), rbx)
		CALayerArraySetValue(sublayers, CALayerArrayGetIndexOfValue(sublayers, removeLayer), replaceWithLayer);
		ecx = _34;
		// 347 call
		((CA::Layer*)replaceWithLayer->_attr._8)->update_added_sublayer(transaction, (CA::Layer*)this, (unsigned int)tail->_a4);


		uint32_t& thread_flags = edx;
		rdi = replaceWithLayer->_attr._8;
		rax = (int64_t)(int32_t&)transaction->_8;
		// 371
		if (0 > transaction->_8) { // 368 (0 > rax)
				// inline jmp 384
			rsi = r15;
			// 387 call
			// %rsi = r15
			thread_flags = *(uint32_t*)((CA::Layer*)replaceWithLayer->_attr._8)->thread_flags_(transaction);
			goto _f394;
		} // 382
		else if (0 != (thread_flags = ((int32_t*)&rdi->_a8)[transaction->_8])) { // 380 (0 != edx)
					 // gen jmp 394
			goto _f394;
		}

	_f394:	// from 382
		// 400 call
		this->update_for_changed_sublayers(transaction, (unsigned int)thread_flags);
		// 420 call
		this->end_change(transaction, (unsigned int)0x1b8, (objc_object*)_30);
		// 425
		goto _f449;
		} // 427
	else {
		// 433 call
		this->set_mask((CALayer*)replaceWithLayer);
		// 444 call
		transaction->release_object((void const*)replaceWithLayer);
	}

_f449:	// from 425
_f449:	// from 182
	return transaction->unlock();
	}

X::Ref<CA::Render::Timing> CA::Layer::render_timing(CA::Transaction* transaction)
{
	X::Ref<CA::Render::Timing>& retObject = *(X::Ref<CA::Render::Timing>*)rdi;
	r14 = transaction;
	rbx = this;
	r15 = &retObject;
	// 27
	if (!((int32_t&)this->_84 < 0x0)) { // 20 ((int32_t&)rbx->_84 < 0x0)
		retObject._Ptr = 0x0;
		// 36
		// goto _f73; inline #0
		rax = &retObject;
		return retObject;
	}

	// 38
	CA::Render::Timing*& copyedTiming = r12;					// &=r12
	  // 42 call
	copyedTiming = CAMediaTimingCopyRenderTiming(this->_10);
	// 53
	if (!(0 != copyedTiming)) { // 50 (0 != r12)
		CA::Layer::State*& state = rax;							// &=rax
		// 61 call
		state = this->writable_state(transaction);
		state->_5c &= 0x7fffffff;
	} // 70
	retObject._Ptr = copyedTiming;
_f73:	// from 36
	rax = &retObject;
	return retObject;
}

void CA::Layer::remove_sublayer(CA::Transaction* transaction, CALayer* sublayer)
{
	r12 = sublayer;
	r14 = transaction;
	r13 = this;
	rbx = this->_20;
	// 33
	if (this->_20 == sublayer) { // 30 (rbx == r12)
			// inline jmp 148
		// 163 call
		this->begin_change(transaction, (unsigned int)0x12a, (objc_object*&)*(objc_object**)&_30);

		rdi = this->_20->_attr._8;
		CA::Layer*& tailLayer = rax;
		CA::Layer*& itLayer = rcx;
		itLayer = this;
		do {
		_b183:	// from 193
			tailLayer = itLayer;
			itLayer = tailLayer->_8;
			// 193
#if 0
			if (0 != itLayer) // 190 (0 != rcx)
				goto _b183;
#else
		} while (itLayer);
#endif

		// 204 call
		((CA::Layer*)this->_20->_attr._8)->update_removed_sublayer(transaction, (unsigned int)tailLayer->_a4);
		this->_20 = 0;
		// 226
		 // goto _f273; inline #1
		return this->end_change(transaction, (unsigned int)0x12a, (objc_object*)_30);
		}

	CALayerArray*& sublayers = r15;						// &=r15
	sublayers = this->_18;
	// 42
	if (0 == r15) { // 39 (0 == r15)
				 // inline jmp 228
		return;
	}
	// 42 next
		  // 63 call
	this->begin_change(transaction, (unsigned int)0x1b8, (objc_object*&)*(objc_object**)&_38);
	rdi = sublayer->_attr._8;

	CA::Layer*& tailLayer = rax;
	CA::Layer*& itLayer = rcx;
	itLayer = this;
	do {
	_b83:	// from 93
		tailLayer = itLayer;
		itLayer = tailLayer->_8;
		// 93
#if 0
		if (0 != itLayer) // 90 (0 != rcx)
			goto _b83;
#else
	} while (itLayer);
#endif

	// 104 call
	((CA::Layer*)sublayer->_attr._8)->update_removed_sublayer(transaction, (unsigned int)tailLayer->_a4);
	// 125
	if (sublayers->_ivars._8 != 0x1) { // 119 (rax->r15._8 != 0x1)
		// inline goto _f243;
		// 259 call (, $(249 call))
		CALayerArrayRemoveValue(sublayers, CALayerArrayGetIndexOfValue(sublayers, sublayer));
		// natural flow to 264
		goto _f264;
	}
	else {
		// 133 call
		transaction->release_object((void const*)sublayers);
		this->_18 = 0;
		// 146
		goto _f264;
	}

_f264:	// from 146
	return this->end_change(transaction, (unsigned int)0x1b8, (objc_object*)_38);

	}

void CA::Layer::remove_from_superlayer()
{
	rbx = this;
	CA::Transaction*& transaction = r14;				// &=r14
	extern Class NSException;
	// 13 call
	transaction = CA::Transaction::ensure_compat();
	// 21 testl $0x60000, 0x4(%rbx)
	// 28
	if (!(0 == (0x60000 & this->_4))) { // 21 (0 == (0x60000 & rbx->_4))
		eax = 0;
		// 64 call
		objc_msgSend(NSException, "raise:format:", __cfs("CALayerInvalidTree"), __cfs("expecting model layer not copy: %@"), this->_10);
	} // 70
	CALayer*& ocLayer = r15;		// &=r15
	ocLayer = this->_10;
	// 77 call
	transaction->lock();
	rdi = this->_8;
	// 89
	if (!(0 == this->_8)) { // 86 (0 == rdi)
			 // 97 call
		((CA::Layer*)this->_8)->remove_sublayer(transaction, (CALayer*)ocLayer);
		// 105 call
		transaction->unlock();
		return transaction->release_object((void const*)ocLayer);
	} // 131
	return transaction->unlock();
}

void CA::Layer::remove_from_context()
{
	rbx = this;
	// 17
	if (!(0 == ((0x8 << 8) & rbx->_84))) { // 10 (0 == ((0x8<<8) & rbx->_84))
		CA::Context*& context = r14;
		// 22 call
		context = this->retain_context();
		// 33
		if (!(0 == context)) { // 30 (0 == r14)
			rax = context->_68;
			// 43
			if (!(context->_68 != (CALayer*)this->_10)) { // 39 (rax != rbx->_10)
				// 50 call
				context->set_layer((void const*)0);
			} // 55
			return context->:unref(false);
		} // 69
	} // 69
	return;
}

bool CA::Layer::needs_layout()
{
	CA::Transaction*& transaction = rax;			// &=rax
	uint32_t& thread_flags = ecx;
	rbx = this;
	// 9 call
	transaction = CA::Transaction::ensure_compat();
	rcx = (int64_t)(int32_t&)transaction->_8;
	// 21
	if (0 > transaction->_8) { // 18 (0 > rcx)
		// gen jmp 34
		goto _f34;
	} // 32
	else if (0 != (thread_flags = ((int32_t*)&rbx->_a8)[transaction->_8])) { // 30 (0 != ecx)
		// gen jmp 47
		goto _f47;
	} // 34
_f34:	// from 21
	// 40 call
	thread_flags = *(uint32_t*) this->thread_flags_(transaction);
_f47:	// from 32
	return (bool)(((thread_flags & 0x20) >> 0x5) & 0xff);
}

bool CA::Layer::needs_display()
{
	CA::Transaction*& transaction = rax;			// &=rax
	uint32_t& thread_flags = ecx;
	rbx = this;
	// 9 call
	transaction = CA::Transaction::ensure_compat();
	rcx = (int64_t)(int32_t&)transaction->_8;
	// 21
	if (0 > transaction->_8) { // 18 (0 > rcx)
			// gen jmp 34
		goto _f34;
	} // 32
	else if (0 != (thread_flags = ((int32_t*)&rbx->_a8)[transaction->_8])) { // 30 (0 != ecx)
				 // gen jmp 47
		goto _f47;
	} // 34
_f34:	// from 21
	  // 40 call
	thread_flags = *(uint32_t*) this->thread_flags_(transaction);
_f47:	// from 32
	return (bool)(((thread_flags & 0x100) >> 0x8) & 0xff);
}

CALayer* CA::Layer::mask()
{
	rbx = this;
	r15d = 0x60000 & this->_4;
	// 23
	if (0 == r15d) {
		// inline jmp 102
		return this->_20;
	}

	CA::Transaction*& transaction = r14;			// &=r14
	CA::Layer*& modelLayer = rcx;					// &=rcx
	CALayer*& maskLayer = rax;						// &=rax
		// 25 call
	transaction = CA::Transaction::ensure_compat();
	// 39 call
	modelLayer = this->model_layer(transaction);
	eax = 0;
	// 49 testq %rcx, %rcx
 // 52
	if (0 == modelLayer) { // 49 (0 == rcx)
		// inline jmp 106 
		return 0;
	}
	maskLayer = modelLayer->_20;
	// 58 cmpl $0x20000, %r15d
	// 65
	if ((0x60000 & this->_4) != 0x20000) { // 58 (r15d != 0x20000)
				 // inline jmp 106
		return maskLayer;
	}
	// 70
	if (0 == maskLayer) { // 67 (0 == rax)
				 // inline jmp 106
		return 0;
	}
	else { // 70 next
		return maskLayer->_attr._8->presentation_layer(transaction);
	} // 102
}

void CA::Layer::mark_visible(CA::Transaction* transaction, bool bWhat)
{
	ebx = bWhat;
	r13 = transaction;
	r15 = this;
	eax = this->_84;
	cl = (((this->_84 & 0x800) >> 0xb) & 0xff) ^ bWhat;
	ecx = (uint32_t)(uint8_t&)cl;
	// 48 cmpl $0x1, %ecx
	// 51
	if (!(ecx != 0x1)) { // 48 (ecx != 0x1)
		this->_84 = (false == bWhat) ? (this->_84 | 0x800) : (this->_84 & 0xfffff7ff);
		// 90
		if (!(this->_98 == 0x0)) { // 82 (r15->_98 == 0x0)
			// 101 call
			this->animation_visibility_changed(transaction, bWhat);
		} // 106
		CALayer*& ocLayer = r14;
		ocLayer = this->_10;

		// 128 $(120 call)
		if (!(false == objc_msgSend(ocLayer, "_defersDidBecomeVisiblePostCommit"))) { // 126 (0 == al)
			_38 = ocLayer;					// save r14 
			_2c = bWhat;					// save ebx
			// 143 call
			transaction->add_deferred_visibility_layer((CA::Layer*)this);
		} // 150
		else {
			_2c = bWhat;					// save ebx
			_38 = ocLayer;					// save r14 
			// 170 call
			objc_msgSend(ocLayer, "layerDidBecomeVisible:", bWhat);
		} // 176

		CALayerArray*& sublayers = rax;
		sublayers = this->_18;
		// 180 testq %rax, %rax
		// 183
		if (!(0 == sublayers)) { // 180 (0 == rax)
			CALayer**& itCALayer = r14;			// &=r14
			int64_t& count = r12;				// &=r12
			count = sublayers->_ivars._8;
			// 200 testq %r12, %r12
			// 203
			if (!(0 == count)) { // 200 (0 == r12)
				itCALayer = sublayers->_ivars._0;
				ebx = (uint32_t)(uint8_t&)bWhat;			// via _2c
			_b215:	// from 247
				// 235 call
				(*itCALayer)->_attr._8->mark_visible(transaction, bWhat);
				itCALayer = itCALayer + 1;
				// 247
				if (--count != 0)
					goto _b215;
			} // 249
		} // 249

		rax = this->_20;
		// 253 testq %rax, %rax
		r14d = bWhat;		// via _2c
		// 260
		if (!(0 == this->_20)) { // 253 (0 == rax)
				 // 281 call
			this->_20->_attr._8->mark_visible(transaction, bWhat);
		} // 286
		  // 296 call
		this->contents_visibility_changed(transaction, bWhat);
		r14 = _38;					// restore r14, set to ocLayer
		CAAction*& action = rax;					// &=rax
		__CFString*& actionKey = rbx;
		actionKey = (bWhat) ? __cfs("onOrderOut") : __cfs("onOrderIn");
		// 339 call
		action = objc_msgSend(ocLayer, "actionForKey:", actionKey);
		// 348
		if (!(0 == action)) { // 345 (0 == rax)
			objc_msgSend(action, "runActionForKey:object:arguments:", actionKey, ocLayer, nil);
			return;
		} // 389
	} // 389
	return;

}

void CA::Layer::mark_sublayers_should_fetch_geometry()
{
	rcx = this->_18;
	// 11
	if (!(0 == this->_18)) { // 8 (0 == rcx)
		int64_t& count = rax;
		count = ((CALayerArray*)this->_18)->_ivars._8;
		// 31
		if (!(0 == count)) { // 28 (0 == rax)
			CALayer**& itCALayer = rcx;						// &=rcx
			itCALayer = ((CALayerArray*)this->_18)->_ivars._0;
		_b37:	// from 74
			CA::Layer*& cxxLayer = rdx;						// &=rdx
			cxxLayer = (*itCALayer)->_attr._8;
			// 52 lock
			cxxLayer->_4 |= 0x100000;
			cxxLayer->_84 |= 0x40 << 8;
			itCALayer = itCALayer + 1;
			// 74
			if (--rax) // 60 (--rax)
				goto _b37;
		} // 76
	} // 76
	return;
}

void CA::Layer::mark_context_changed(CA::Transaction* transaction)
{
	r15 = transaction;
	r14 = this;
	// 17 lock
	OSAtomicOr32(0x2000000, (volatile int32_t*)&this->_4);
	this->_2c |= 0x1fffff;
	edx = this->_a0;
	// 43
	if (!(0 == this->_a0)) { // 41 (0 == edx)
		// 51 call
		transaction->add_deleted_id((unsigned long)this, (unsigned int)this->_a0);
		this->_a0 = 0x0;
	} // 67
	rax = this->_18;
	// 74
	if (!(0 == this->_18)) { // 71 (0 == rax)
		int64_t& count = r12;
		count = ((CALayerArray*)this->_18)->_ivars._8;
		// 94
		if (!(0 == count)) { // 91 (0 == r12)
			CALayer**& itCALayer = rbx;
			itCALayer = ((CALayerArray*)this->_18)->_ivars._0;
		_b100:	// from 130
				// 118 call
			((CA::Layer*)(*itCALayer)->_attr._8)->mark_context_changed(transaction);
			itCALayer = itCALayer + 1;
			// 130
			if (--r12 != 0) // (--r12 != 0)
				goto _b100;
		} // 132
	} // 132
	rax = this->_20;
	// 139
	if (!(0 == this->_20)) { // 136 (0 == rax)
		// 156 call
		((CA::Layer*)this->_20->_attr._8)->mark_context_changed(transaction);
	} // 161

	CA::Layer::Animation*& itAnima = rax;
	itAnima = this->_98;
	// 168
	goto _f180;
_b170:	// from 183
	itAnima->_2c = 0;
	itAnima = itAnima->_0;
_f180:	// from 168
		// 183
	if (0 != itAnima) // 180 (0 != rax)
		goto _b170;

	return;
}

void CA::Layer::mark_animations(CA::Transaction* transaction, bool bWhat)
{
	rbx = transaction;
	eax = (uint32_t)(uint8_t&)bWhat;
	edx = rax + rax + 0x200808;
	ecx = rax + rax * 4 + 0x810;
	// 26 call
	this->mark(transaction, (uint32_t)(uint8_t&)bWhat * 2 + 0x200808, (uint32_t)(uint8_t&)bWhat * 5 + 0x810);
	rax = transaction->_0;
	// 34 cmpl $0x0, 0x10(%rax)
	// 38
	if (transaction->_0->_10 == 0x0) { // 34 (rax->_10 == 0x0)
		// inline goto _f47;
		return transaction->ensure_implicit();
	}
	return;
}


void CA::Layer::mark(CA::Transaction* transaction, unsigned int flag1, unsigned int flag2)
{
	r12d = flag2;
	r15d = flag1;
	r14 = transaction;
	rbx = this;
	rax = (int64_t)(int32_t&)transaction->_8;
	uint32_t*& thread_flags_place = rax;
	uint32_t& thread_flags = ecx;
	// 30
	if (!(0 > transaction->_8)) { // 27 (0 > rax)
		ecx = ((int32_t*)&rbx->_a8)[transaction->_8];
		// 41
		if (!(0 == this->_a8[transaction->_8])) { // 39 (0 == ecx)
			thread_flags_place = (uint32_t*)&this->_a8[transaction->_8];
			// 51
			goto _f66;
		} // 53
	} // 53
	else {
		// 59 call
		thread_flag_place = (uint32_t*) this->thread_flags_(transaction);
		thread_flags = *(uint32_t*)thread_flags_place;
		edx = thread_flags;
	}
_f66:	 // from 51
	edx = edx & flag1;
	// 74
	if (!((thread_flags & flag1) == flag1)) { // 71 (edx == r15d)
		thread_flags = thread_flags | flag1;
		// 83
		goto _f88;

		CA::Layer*& itLayer = rbx;					// &=rbx, begin at this
		CA::Layer*& targetLayer = rbx;
	_b85:	 // from 209
		thread_flags = thread_flags | flag2;
	_f88:	 // from 83
		*thread_flag_place = thread_flags;
		rax = itLayer->_8;
		// 97
		if (0 == itLayer->_8) { // 94 (0 == rax)
			// inline jmp 213
			targetLayer = itLayer;			// fake
											// 217
			if (!(0 == (0x8 & flag1 & 0xff))) { // 213 (0 == (0x8 & r15b))
												// 226
				if (!(targetLayer->_a4 == 0x0)) { // 219 (rbx->_a4 == 0x0)
					return transaction->add_root(targetLayer);
				} // 247
			} // 247
			return;
		}
		itLayer = itLayer->_8;
		// 109
		if (!(0 == (-0x80 & itLayer->_80))) { // 102 (0 == (-0x80 & rbx->_80))
			CALayer*& dstLayer = rax;
			// 123 $(115 call)
			if (!(0 == (dstLayer = CALayerPortalGetDestination(itLayer->_10)))) { // 120 (0 == rax)
				// 146 call
				dstLayer->_attr._8->mark(transaction, flag1, flag2);
			} // 151
		} // 151
		  // 151 prefetcht0 0xa8(%rbx)
		rax = (int64_t)(int32_t&)transaction->_8;
		// 165
		if (!(0 > transaction->_8)) { // 162 (0 > rax)
			thread_flags = ((int32_t*)&rbx->_a8)[transaction->_8];
			// 176
			if (!(0 == itLayer->_a8[transaction->_8])) { // 174 (0 == ecx)
				thread_flags_place = (uint32_t*)&itLayer->_a8[transaction->_8];
				// 186
				goto _f201;
			} // 188
		} // 188
		  // 194 call
		itLayer->thread_flags_(transaction);
		thread_flags = *thread_flags_place;
	_f201:	 // from 186
		// 209
		if ((thread_flags & flag2) != flag2) // 206 (edx != r12d)
			goto _b85;
		// 211
		// goto _f247; inline #0
		return;
	} // 247
_f247:	 // from 211
	  // 255 ret
	return;
}

typedef void(*applyVec2r_func)(void*, CA::Mat4<double> const&);
typedef void(*unapplyVec2r_func)(void*, CA::Mat4<double> const&);
static void CA::Layer::map_geometry(CALayer* fromLayer, CALayer* toLayer, applyVec2r_func applyVec2r, unapplyVec2r_func unapplyVec2r, void* _cvtPoint /**CGPoint{0x8(%rsp) 0x10(%rsp)}*/)
{
	// cvtPoint /**CGPoint{0x8(%rsp) 0x10(%rsp)}*/
	CGPoint*& cvtPoint = _cvtPoint;
	_238 = cvtPoint;
	_248 = unapplyVec2r;
	_240 = applyVec2r;
	r13 = toLayer;
	r15 = fromLayer;

	CA::Transaction*& transaction = _250;					// &=_250;
	// 47 call
	transaction = CA::Transaction::ensure_compat();;
	// 62 call
	transaction->lock();
	// 80 call
	_230 = objc_msgSend(fromLayer, "ancestorSharedWithLayer:", toLayer);
	// 100
	if (_230 == fromLayer) { // 93 (_230 == r15)
			// gen jmp 396
		goto _f396;
	}
	else { // 100 next
		_258 = r13;					// save r13 (toLayer)
		CA::Mat4<double>*& mat4 = r12;						// &=r12;
		rsi = CA::Mat4Impl::mat4_identity_double;
		mat4 = (CA::Mat4<double>*)&_a8;
		// 130 call
		CA::Mat4Impl::mat4_assign((double*)mat4, (double const*)&CA::Mat4Impl::mat4_identity_double);

		CALayer*& itFromLayer = r15;						// &=r15, begin at fromLayer
		r13d = 0;
		r14d = 0;
		for (;;) {
		_b141:	 // from 353
			// 148
			if (_230 == itFromLayer)
				// gen jmp 363
				goto _f363;				// break;
			// 177 call
			((CA::Layer*)itFromLayer->_attr._8)->get_frame_transform(*(CA::Mat4<double>*)&_128, false, (CA::Mat4<double> const*)0);
			ebx = itFromLayer->_attr._8->_4 & 0x10000;
			// 208
			if (!(0x1 & r14b)) { // 204 (0x1 & r14b)
				r14b = 0x1;
				// 223 call
				CA::Mat4Impl::mat4_assign((double*)mat4, (double const*)&_128);
				// 228
				goto _f328;
			} // 230
			r13d = r13d | ebx;
			// 233
			if (0x1 & r14b) {
				// inline jmp 251
				r14b = 0x1;
				// 267 call
				CA::Mat4Impl::mat4_concat((double*)mat4, (double const*)mat4, (double const*)&_128);
				// 272
				goto _f328;
			} // 249
			else if (false == CA::Mat4Impl::mat4_is_affine((double const*)&_128)) { // 247 (0 == al)
				// inline jmp 274
				// 284 call
				applyVec2r(cvtPoint, *mat4); // *-0x240(%rbp);;
				// 304 call
				applyVec2r(cvtPoint, *(CA::Mat4<double>*)&_128); // * -0x240(%rbp);;
				// 320 call
				// %rsi = CA::Mat4Impl::mat4_identity_double
				// %rdi = r12
				CA::Mat4Impl::mat4_assign((double*)mat4, (double const*));
				goto _f328;
			} // 251

		_f328:	 // from 272
		_f328:	 // from 228
			ebx = ebx >> 0x10;
			// 341 call
			itFromLayer = objc_msgSend(itFromLayer, "superlayer");
			r13d = ebx;
			// 353
			goto _b141;
		}
	}

_f363:	 // from 148
	r13 = _258;					// restore r13, set to toLayer;
		 // 374
	if (!(0 == (0x1 & r14b))) { // 363 (0 == (0x1 & r14b))
			 // 390 call
		applyVec2r(cvtPoint, &_a8); // * -0x240(%rbp);;
	} // 396
_f396:	 // from 100
	  // 403
	if (_230 == toLayer) { // 396 (_230 == r13)
			// gen jmp 795
		goto _f795;
	}
	else {
		r14 = "superlayer";
		x_list*& head = r12;
		CALayer*& itOcLayer = r13;		// &=r13, begin at toLayer
		head = 0;

	_b419:	 // from 464
		// 426
		if (_230 == itOcLayer) {
			// gen jmp 471
			goto _f471; // break;
		}

		x_list*& list = rbx;
		list = (x_list*)alloca(0x10);
		list->_0 = itOcLayer;
		list->_8 = head;
		// 452 call
		itOcLayer = objc_msgSend(r13, "superlayer");
		head = list;
		// 464
		goto _b419;
	}
_f471:	 // from 426
	x_list*& head = r12;				// &=r12, use the result of loop _b419
		 // 485 call
	// %rsi = CA::Mat4Impl::mat4_identity_double
	CA::Mat4Impl::mat4_assign((double*)&_1a8, (double const*)CA::Mat4Impl::mat4_identity_double);
	// 493
	if (!(0 == head)) { // 490 (0 == r12)
		r14d = 0;
		r13d = 0;
	_b505:	 // from 749
		CALayer*& itOcLayer = rbx;
		r13d = 0;
		itOcLayer = (CALayer*)head->_0;
		// 532 call
		((CA::Layer*)itOcLayer->_attr._8)->get_frame_transform(*(CA::Mat4<double>*)&_228, false, (CA::Mat4<double> const*)0);

		r15d = itOcLayer->_attr._8->_4 & 0x10000;
		// 565
		if (!(0x1 & r13b)) { // 561 (0x1 & r13b)
			r13b = 0x1;
			// 584 call
			CA::Mat4Impl::mat4_assign((double*)&_1a8, (double const*)&_228);
			// 589
			goto _f734;
		} // 594
		r14d = r14d | r15d;
		// 597
		if (0x1 & r13b) {
			// inline jmp 615
			r13b = 0x1;
			// 635 call
			CA::Mat4Impl::mat4_concat((double*)&_1a8, (double const*)&_228, (double const*)&_1a8);
			// 640
			goto _f734;
		} // 613
		else if (false == CA::Mat4Impl::mat4_is_affine((double const*)&_228)) { // 611 (0 == al)
			// inline jmp 642
			// 652 call
			CA::Mat4Impl::mat4_invert((double*)&_1a8, (double const*)&_1a8);
			// 671 call
			unapplyVec2r(cvtPoint, &_1a8);	// *-0x248(%rbp);;
			// 687 call
			CA::Mat4Impl::mat4_invert((double*)&_228, (double const*)&_228);
			// 706 call
			unapplyVec2r(cvtPoint, &_228); // * -0x248(%rbp);;
			// 726 call
			CA::Mat4Impl::mat4_assign((double*)&_1a8, (double const*)CA::Mat4Impl::mat4_identity_double);
			// natural flow 
			goto _f374;
		}


	_f734:	 // from 640
	_f734:	 // from 589
		r15d = r15d >> 0x10;
		head = head->_8;
		r14d = r15d;
		// 749
		if (head) // 743 (0 != r12)
			goto _b505;

		// 758
		if (!(0 == r13b)) { // 755 (0 == r13b)
				 // 770 call
				 // %rsi = rdi
			CA::Mat4Impl::mat4_invert((double*)&_1a8, (double const*)&_1a8);
			// 789 call
			unapplyVec2r(cvtPoint, &_1a8) // * -0x248(%rbp);;

		} // 795
	} // 795
_f795:	 // from 403
	transaction->unlock();
	// 821 ret
	return;
}

void* CA::Layer::fetch_defaults()
{
	CA::Transaction*& transaction = rbx;
	r14 = rdi;
	transaction = CA::Transaction::ensure();
	CA::Layer::State*& state = rax;
	state = this->writable_state(transaction);
	extern void* defaultValueForAtom(void*, unsigned int, _CAValueType, void*);
	return CA::Layer::State::fetch_defaults(state, transaction, &defaultValueForAtom, (void*)this);
}

void CA::Layer::add_animation(CAAnimation* anima, __CFString const* keyPath)
{
	static counter = 0;
	r12 = keyPath;
	_50 = keyPath;				// via r12
	rbx = anima;
	_40 = anima;				// via rbx
	r14 = this;
	CA::Transaction*& transaction = _48;		// &=_48
	__CFSet*& keyPathSet = _30;
	// 34 call
	transaction = r15 = CA::Transaction::ensure();
	// 59 call
	CAAnimationSetFlags(anima, 0x1, 0xffffffff);
	// 71 call
	CA::Render::key_path_set((void**)&keyPathSet, (__CFString const*)keyPath);
	// 79 call
	transaction->lock();

	/**
	* # Step 1
	* traverse the animations in this cxx layer, and find out the one whose key path equals to the will-add.
	* if the found one has no continuation, dequeue it and stop its callback and free it.
	* listAnimation will point to the next of one if found, otherwise point to null;
	*/

	CA::Layer::Animation*& itAnima = r15;		// &=r15, till ?
	CA::Layer::Animation*& listAnima = _38;			// _38, till 174
	itAnima = this->_98;
	rbx = this;
	_38 = itAnima;
	// 101
	if (!(0 == itAnima)) { // 98 (0 == r15)
		CA::Layer::Animation**& prev = r13;			// &=r13
		prev = &listAnima;
		r12d = 0;
		r14 = &keyPathSet;
	_b114:	// from 174
		do {
			// 130 (123 call)
			if (!(false == CA::Render::key_path_equal((void* const*)&keyPathSet, (void* const*)&itAnima->_10, false))) { // 128 (0 == al)
				eax = (uint32_t)(uint16_t&)itAnima->_38;
				// 141
				if (!(0x602 & itAnima->_38)) { // 137 (0x602 & ax)
						 // 148
					if (itAnima->_30 == 0x0) { // 143 (r15->_30 == 0x0)
						// goto _f810; inline #0
					_f810:	// from 148
						*prev = itAnima->_0;
						r14 = transaction;					// via _48
							// 824 call
							// %rdi = r15
						schedule_stop_callback((CA::Layer::Animation*)itAnima);
						r13 = this;							// via rbx
						r12b = 0x1;
						// 840 call
						// %rdi = r15
						CA::Layer::free_animation((CA::Layer::Animation*)itAnima, false);
						/**
						* we have found the target animation
						*/
						// 845
						goto _b201;				// break;
					}
				} // 154
				itAnima->_38 |= 0x8;
				r12b = 0x1;
			} // 165
			prev = &itAnima->_0;
			itAnima = itAnima->_0;
			// 174
#if 0
			if (itAnima) // 171 (0 != r15)
				goto _b114;
#else
		} while (itAnima);
#endif
		} // 178
	else {
		r12d = 0;
	} // 181

	/**
	* # Step 2
	* new a cxx animation for a will-add oc animation,
	* initialize the cxx animation.
	*/

	CA::Layer::Animation*& cxxAnima = r15;					// &=r15
		// 186 call
		// %edi = 0x3
	cxxAnima = x_mem_alloc_bucket(0x3);
	r14 = transaction;					// via _48
	r13 = this;							// via rbx

_b201:	// from 845 (inlined before)
	/**
	* this is not a loop, 845 has been inline in the place before 201
	*
	*/
	// 205 call
	cxxAnima->_8 = CFRetain(anima);
	cxxAnima->_10 = _30;
	eax = 0;
	// 231
	if (!(0 == keyPath)) { // 228 (0 == rdi)
			 // 233 call
		cxxAnima->_18 = CFRetain(keyPath);
	} // 238
	else {
		cxxAnima->_18 = 0;
	}
	cxxAnima->_20 = 0x0;
	cxxAnima->_28 = 1 + OSAtomicAdd32(0x1, (volatile int32_t*)&counter);
	// 280 call
	al = (bool)objc_msgSend(anima, "isRemovedOnCompletion");

	eax = (uint32_t)(uint8_t&)al;
	r12b = r12b & 0x1;
	cxxAnima->_38 = (((uint32_t)(uint8_t&)r12b << 0x4) | eax) | ((uint32_t)(uint16_t&)cxxAnima->_38 & 0xffe0);

	// 335 call
	eax = objc_msgSend(cxxAnima->_8, "_propertyFlagsForLayer:", this->_10);

	esi = (eax << 0x6) & 0x40;
	edx = (uint32_t)(uint16_t&)r15->_38 & 0xfe1f;
	ebx = (eax << 0x5) & 0x80;
	edi = (eax << 0x5) & 0x100;
	ecx = (eax << 0x4) & 0x20;
	ecx |= esi | ebx | edi | edx;

	cxxAnima->_38 = cx;
	eax = eax & 0x6;

	// 406
	if (!(eax != 0x6)) { // 403 (eax != 0x6)
		OSAtomicOr32(0x1000000, (volatile int32_t*)&this->_4);
		ecx = (uint32_t)(uint16_t&)r15->_38;
	} // 422
	  // 434
	if (!((ecx & 0x120) != 0x120)) { // 428 (ecx != 0x120)
		OSAtomicOr32(0x800000, (volatile int32_t*)&this->_4);
	} // 445
	  // 456 call
	  // %rsi = "delegate"
	objc_msgSend(anima, "delegate");
	// 465
	if (!(0 == (rax = objc_msgSend(anima, "delegate")))) { // 462 (0 == rax)
		objc_object*& delegate = rax;
		// 473 call
		eax = lookup_delegate_methods(transaction, (objc_object*)delegate);
		eax = ((eax & 0x60) << 0x4) | ((uint32_t)(uint16_t&)cxxAnima->_38 & 0xf9ff);
	} // 499
	else {
		eax = (uint32_t)(uint16_t&)cxxAnima->_38 & 0xf9ff;
	} // 509
	cxxAnima->_38 = ax;

	// 525
	if (!(0 == transaction->current_continuation())) { // 522 (0 == rax)
			 // 530 call
		cxxAnima->_30 = (CA::Transaction::Continuation*)transaction->current_continuation()->ref();
	} // 549
	else {
		cxxAnima->_30 = 0;
	} // 557


	/**
	* # Step 3
	* traverse the listAnimation,
	* insert the new one in a right position according to the media timing.
	* if listAnimation is not null, we do it inline.
	* otherwise, we should do it by calling set_animations.
	*/

	CA::Layer::Animation*& itAnima2 = rbx;
	itAnima2 = listAnima;						// via _38
	CA::Render::Timing*& addTiming = r12;							// &=r12;
	CA::Layer::Animation**& prevAnima = r14;						// &=r14, invalidate until 598
		// 564
	if (0 == itAnima2) { // 561 (0 == rbx)
			// inline jmp 703
		_38 = cxxAnima;
		cxxAnima->_0 = 0x0;
		// 714
	// goto _f759; inline #1
		this->set_animations(cxxAnima);
		this->mark_animations(transaction, true);
		transaction->:unlock();
		return;
	}
	else { // 564 next

		   // 574 call
		addTiming = CAMediaTimingCopyRenderTiming(anima);
		_40 = r12;					// save r12
		_50 = r13;					// save r13 (this)
		_48 = r14;					// save r14 (transaction)
		prevAnima = (CA::Layer::Animation**) &_38;

	_b598:	// from 699
		CA::Render::Timing*& itTiming = rax;
		// 602 call
		itTiming = CAMediaTimingCopyRenderTiming(itAnima2->_8);
		xmm0 = 0.;
		xmm1 = 0.;
		// 618
		if (!(0 == copyAnima)) { // 607 (0 == r12)
			xmm1.sd = (double&)addTiming->_20;
		} // 627
		  // 630
		if (!(0 == itTiming)) { // 627 (0 == rax)
			xmm0.sd = (double&)itTiming->_20;
		} // 637

		  // 641
		if (xmm1.sd < xmm0.sd) { // 637 (xmm1.sd < xmm0.sd)
			  // inline jmp 716
				// 719
			if (!(0 == itTiming)) { // 716 (0 == rax)
					 // 724 call
				((CA::Render::Object*)itTiming)->unref();
			} // 729
			goto _f729;
		}
		// 643
		if (xmm1.sd <= xmm0.sd) {
			// inline jmp 660
			r13d = cxxAnima->_28;
			r12d = itAnima2->_28;
			// 671
			if (!(0 == itTiming)) { // 660 (0 == rax)
				// 676 call
				((CA::Render::Object*)itTiming)->unref();
			} // 681
			r12 = _40;				// restore r12, set to addTiming
			  // 688
			if (cxxAnima->_28 < itAnima2->_28) // 681 (r13d < r12d)
				  // gen jmp 729
				/**
				* we found it
				*/
				goto _f729;
		} // 648
		else if (0 == itTiming) { // 645 (0 == rax)
					 // gen jmp 690
			goto _f690;
		}
		else { // 648 next
			   // 653 call
			   // %rdi = rax
			((CA::Render::Object*)itTiming)->unref();
			// 658
			goto _f690;
		} // 660

	_f690:	// from 658
	_f690:	// from 648
		prevAnima = &itAnima2->_0;
		itAnima2 = itAnima2->_0;
		// 699
		if (0 != itAnima2) // 696 (0 != rbx)
			goto _b598;

		// 701
		goto _f729;
	} // 703

_f729:	// from 701		we can't found the one, so insert to tail
_f729:	// from 688		we found it, insert front of it
	cxxAnima->_0 = *prevAnima;
	*prevAnima = cxxAnima;
	r14 = _48;					// restore r14, set to transaction
	r13 = _50;					// restore r13, set to this
	  // 749
	if (!(0 == addTiming)) { // 738 (0 == r12)
			 // 754 call
		((CA::Render::Object*)addTiming)->unref();
	} // 759
_f759:	// from 714

	this->set_animations((CA::Layer::Animation*)listAnima);
	this->mark_animations(transaction, true);
	transaction->:unlock();
	return;
	}

void CA::Layer::prepare_commit(CA::Transaction* transaction)
{
	// _1080 to _30
	r15 = transaction;
	_1078 = transaction;						// save r15
	r14 = this;
	void*& newHeap = *(void**)&_1080;

	// 64 call
	rbx = x_heap_new_with_ptr(0x400, &_1030, 0x1000);
	newHeap = rbx;								// save rbx;
	// 82 call
	transaction->lock();
	CA::Layer::CollectLayersData& collectLayerData = *(CA::Layer::CollectLayersData*)&_1070;
	collectLayerData._0 = 0;
	collectLayerData._8 = 0;
	collectLayerData._10 = 0;
	collectLayerData._18 = transaction;
	collectLayerData._20 = newHeap;
	collectLayerData._28 = 0x2;
	collectLayerData._2c = 0x4;
	collectLayerData._30 = 0;
	// 162 call
	this->collect_layers_(&collectLayerData);
	x_list*& collect_list = rbx;
	collect_list = (x_list*)&_1070->_0;
	// 177 call
	transaction->unlock();;
	// 182
	goto _f188;
_b184:	// from 403
_b184:	// from 386
	collect_list = collect_list->_8;
_f188:	// from 182
		// 191
	if (!(0 == collect_list)) { // 188 (0 == rbx)
		CA::Layer*& layer = r12;
		CALayer*& oclayer = r14;
		layer = (CA::Layer*) collect_list->_0;
		oclayer = layer->_10;
		// 208
		if (!(0 == oclayer)) { // 205 (0 == r14)
			CGImage*& cgImage = r13;
			// 217 call
			transaction->lock();
			// 232 call
			// %rsi = "contents"
			cgImage = objc_msgSend(oclayer, "contents");
			// 244
			if (0 == cgImage) { // 241 (0 == r13)
					// gen jmp 336
				goto _f336;

			}
			else {
				// 249 call
				CFRetain(cgImage);
				// 257 call
				transaction->unlock();

				// 281 $(265 call) != $(273 call)
				if (CFGetTypeID(cgImage) != CGImageGetTypeID()) { // 278 (r15 != rax)
					// inline jmp 346
					// 356 call
					// %rsi = "CA_prepareRenderValue"
					objc_msgSend(cgImage, "CA_prepareRenderValue");
					// 372 call
					CFRelease(cgImage);
					// natural flow to 377
					goto _f377;
				}
				else { // 281 next
					   // 293 call
					   // %rsi = "_renderImageCopyFlags"
					r14d = objc_msgSend(oclayer, "_renderImageCopyFlags");
					// 312 call
					;			// via _1078
					// 329 call
					CA::Render::prepare_image(cgImage, (CGColorSpace*)CA::Context::current_colorspace(transaction), (unsigned int)r14d, 0.);
					// 334
					// goto _f369; inline #0
					CFRelease(cgImage);
					// natural flow to 377
					goto _f377;
				}
			}// 336
		_f336:	// from 244
			  // 339 call
			transaction->unlock();
			// 344
			goto _f377;
		} // 377
	_f377:	// from 344
		  // 386
		if (0 == (CA::Layer::Animation*)layer->_98)
			goto _b184;

		// 398 call
		layer->prepare_animations(transaction);
		// 403
		goto _b184;
	} // 408
	x_heap_free(newHeap);
	// 453 ret
	return;
}

void CA::Layer::prepare_animations(CA::Transaction* transaction)
{
	r14 = transaction;
	rbx = this;
	CA::Layer::Animation*& anima = rbx;					// &=rbx

	// 19 call
	transaction->lock();
	anima = this->_98;
	// 34
	if (!(0 == anima)) { // 31 (0 == rbx)
	_b43:	// from 68
			// 47
		if (!(0x1e & anima->_38)) { // 43 (0x1e & rbx->_38)
				 // 56 call
			objc_msgSend(anima->_8, "CA_prepareRenderValue");
		} // 62
		anima = anima->_0;
		// 68
		if (anima) // 65 (0 != rbx)
			goto _b43;
	} // 70
	  // 83 ret
	return transaction->unlock();	// jmp 0x1041cc6ee; CA::Transaction::unlock()
}

void CA::Layer::run_animation_callbacks(void*)
{
	x_list*& didStartAnimations = _38;				// &=_38
	x_list*& didStopAnimations = _30;				// &=_30
	CA::Layer::Animation* needToFreeAnimation = r14;// &=r14
	CA::Transaction*& transaction = r12;			// &=r12
	// 17 call
	transaction = CA::Transaction::ensure_compat();
	// 28 call
	transaction->lock();
	extern CA::Layer::Animation* ent_off__0x6d8dc;
	extern x_list* ent_off__0x6d8cc;
	extern x_list* ent_off__0x6d8d4;
	r14 = ent_off__0x6d8dc;
	ent_off__0x6d8dc = 0;
	didStopAnimations = rbx = ent_off__0x6d8cc;
	ent_off__0x6d8cc = 0;
	r15 = ent_off__0x6d8d4;
	ent_off__0x6d8d4 = 0;
	// 94 call
	transaction->unlock();
	// 102
	if (0 != rbx)						// didStopAnimations
		goto _f129;
	// 107
	if (0 != r14)						// needToFreeAnimation
		goto _f129;
	// 112
	if (0 != r15)						// didStartAnimations
		goto _f129;
	return;
_f129:	 // from 112
_f129:	 // from 107
_f129:	 // from 102
		 // 132
	if (!(0 == needToFreeAnimation)) {
		CA::Layer::Animation*& nextAnimation = rbx;
	_b134:	 // from 156
		nextAnimation = ((CA::Layer::Animation*)r14)->_0;
		// 145 call
		CA::Layer::free_animation((CA::Layer::Animation*)needToFreeAnimation, true);
		needToFreeAnimation = nextAnimation;
		// 156
		if (nextAnimation) {
			goto _b134;
		}
	} // 158

	didStartAnimations = r15;
	// 165
	if (!(0 == didStartAnimations)) {
		x_list*& it = rbx;				// &=rbx
		CAAnimation*& animation = r15;	// &=r15
	_b192:	 // from 231
		r12 = "delegate";
		r13 = "animationDidStart:";
		r14 = &objc_msgSend;
		it = didStartAnimations;
		animation = (CAAnimation*)it->_0;
		// 213 call ($(201 call))
		objc_msgSend(objc_msgSend(animation, "delegate"), "animationDidStart:", animation); // *%r14;
		// 219 call
		CFRelease(animation);
		it = it->_8;
		// 231
		if (it)
			goto _b192;
	} // 233

	  // 238
	if (!(0 == didStopAnimations)) {
		x_list*& it = r12;				// &=r12
		CAAnimation*& animation = rbx;	// &=rbx

		r13 = "animationDidStop:finished:";
		r15 = &objc_msgSend;
		it = didStopAnimations;
	_b258:	 // from 324
		animation = (CAAnimation*)it->_0;
		// 305 call($(290 call), $(265 call)
		objc_msgSend(objc_msgSend(animation, "delegate"), "animationDidStop:finished:",
			animation, CAAnimationGetFlags(animation)); //  *%r15;;
// 311 call
		CFRelease(animation);
		it = it->_8;
		// 324
		if (it)
			goto _b258;
	} // 326
	x_list_free(didStartAnimations);
	return x_list_free(didStopAnimations);
}

void CA::Layer::run_animation_callbacks_compat(double timing, void* objc_obj)
{
	// 15 call ($(7 call))
	try {
		CA::Layer::run_animation_callbacks((void*)objc_autoreleasePoolPush(objc_obj));
		return objc_autoreleasePoolPop(objc_obj);
	}
	catch (void* e) {
		NSLog(__cfs("CoreAnimation: ignoring exception: %@"), e);
		return objc_autoreleasePoolPop(objc_obj);
	}
	catch (...) {
		__raise;
	}
}

CA::Context* CA::Layer::retain_context()
{
	// 11
	if (!(0 == (this->_84 & 0x800))) {
		CA::Layer*& current = rax;
		CA::Layer*& next = rdi;
		next = this;
	_b13:	 // from 23
		current = next;
		next = current->_8;
		// 23
		if (next)
			goto _b13;

		// 33
		if (!(0 == current->_a4)) {
			return CA::Context::retain_context_with_id((unsigned int)current->_a4);
		} // 41
	} // 41
	return 0;
}

CA::Layer::State* CA::Layer::writable_state(CA::Transaction* transaction)
{
	CA::Layer::State*& newState = r15;							// &=r15
	rbx = this;
	r14 = transaction;
	// 24
	if (!(0 != (CA::Layer::State*)this->_90)) {
		// 37
		if (!(0 == (0x4000 & this->_84))) {
			// 45 call
			this->fetch_geometry(transaction);
		} // 50
		  // 55 call
		newState = new (x_mem_alloc_bucket(0x6)) CA::Layer::State();
		{
			newState->_0 = 0x1;
			newState->_4 = this->_28._4;
			newState->_8.vec[0] = this->_28._8.vec[0];		// tx, ty
			newState->_8.vec[1] = this->_28._8.vec[1];
			newState->_18 = this->_28._18;					// x, y, w, h
			newState->_20 = this->_28._20;
			newState->_28 = this->_28._28;
			newState->_30 = this->_28._30;
			newState->_38 = 0;
			newState->_38 = this->_28._38;
		}
		eax = 0;
		// 136
		if (!(0 == this->_28._40)) {
			// 138 call
			newState->_40 = CFRetain(this->_28._40);
		} // 143
		else {
			newState->_40 = 0;
		}
		eax = 0;
		// 156
		if (!(0 == this->_28._48)) {
			// 158 call
			newState->_48 = CFRetain(this->_28._48);
		} // 163
		else {
			newState->_48 = 0;
		}
		newState->_50 = 0;
		// 180
		if (!(0 == (CA::AttrList*)this->_28._50)) {
			// 185 call
			transaction->lock();
			eax = 0;
			// 199
			if (!(0 == (CA::AttrList*)this->_28._50)) {
				// 201 call
				newState->_50 = ((CA::AttrList*)this->_28._50)->copy();
			} // 206
			  // 213 call
			transaction->unlock();
		} // 218

		eax = 0;
	_b220:	// from 239
		(&newState->_58)[eax] = (&this->_28._58)[eax];
		// 239
		if (++eax != 4)
			goto _b220;

		newState->_58 &= 0xffffefff;
		this->_90 = newState;
	} // 253

	return &this->_28;
}

CA::Layer::~Layer()
{
	CA::Transaction*& transaction = r14;					// &=r14
	r12 = this;
	// 14 call
	transaction = CA::Transaction::ensure_compat();

	// 25 call
	transaction->lock();
	// 39
	if ((0 == (0x60000 & this->_4))) {
		// gen jmp 66
		// goto _f66; inline #0
	_f66:	// from 39
			// 74
		if (!(0 == (CALayerArray*)this->_18)) {
			// 84 call
			this->update_sublayers(transaction, (CALayerArray*)0, (CALayerArray*)this->_18);
		} // 89
		  // 97
		if (!(0 == (CALayer*)this->_20)) {
			CA::Layer*& itLayer = rcx;						// &=rcx
			CA::Layer*& tailLayer = rax;					// &=rax
			itLayer = this;

			// do {
		_b114:	// from 124
			tailLayer = itLayer;
			itLayer = itLayer->_8;
			// 124
			if (itLayer)
				goto _b114;
			// } while (itLayer = itLayer->_8);

			// 135 call
			((CA::Layer*)this->_20->_attr._8)->update_removed_sublayer(transaction, (unsigned int)tailLayer->_a4);
		} // 140
		  // 143 call
		this->invalidate_animations(transaction);
		// 158
		if (!(0 == this->_a0)) {
			// 166 call
			transaction->add_deleted_id((unsigned long)this, (unsigned int)this->_a0);
		} // 171 natural flow
		goto _f171;
	} // 54
	else if (0 == transaction->_0->_80) {
		// gen jmp 171
		goto _f171;
	}
	else { // 54 next
		   // 59 call
		x_hash_table_remove(transaction->_0->_80, this);
		// 64
		goto _f171;
	} // 66 has been inlined to 39

_f171:	// from 64
_f171:	// from 54
	  // 182
	if (!(0 == (CA::Layer::State*)this->_90)) {
		// 184 call
		((CA::Layer::State*)this->_90)->unref(transaction);
	} // 189
	this->_90 = (CA::Layer::State*)0;
	// 204 call
	transaction->unlock();

	// 217
	if (!(0 == (CALayerArray*)this->_18)) {
		// 222 call
		transaction->release_object((void const*)(CALayerArray*)this->_18);
		this->_18 = (CALayerArray*)nil;
	} // 236

	  // 244
	if (!(0 == (CALayer*)this->_20)) {
		// 249 call
		transaction->release_object((void const*)(CALayer*)this->_20);
		this->_20 = (CALayer*)nil;
	} // 263

	  // 274
	if (!(0 == this->_b8)) {
		// 282
		if (!(0 == (CA::Render::Shmem*)this->_b8->_Ptr)) {
			// 284 call
			((CA::Render::Object*)this->_b8->_Ptr)->unref();
		} // 289
		  // 294 call
		x_mem_dealloc_bucket(0, (CA::Render::ShmemPtr<CA::Render::LayerShmem>*)this->_b8);
		this->_b8 = 0;
	} // 311

	CA::Transaction*& ensuredTrans = r15;					// &=r15		
	  // 311 call
	ensuredTrans = CA::Transaction::ensure();
	// 327
	if (!(0 == this->_68)) {
		// 332 call
		ensuredTrans->release_object((void const*)this->_68);
		this->_68 = 0;
	} // 346

	  // 354
	if (!(0 == this->_70)) {
		// 359 call
		ensuredTrans->release_object((void const*)this->_70);
		this->_70 = 0;
	} // 373

	  // 379
	if (!(0 == (CA::AttrList*)this->_78)) {
		// 384 call
		ensuredTrans->lock();
		// 397
		if (!(0 == (CA::AttrList*)this->_78)) {
			// 399 call
			((CA::AttrList*)this->_78)->free();
			this->_78 = (CA::AttrList*)0;
		} // 404
		ensuredTrans->unlock();
	} // 429
	return;
}

CA::Layer* CA::Layer::model_layer(CA::Transaction* transaction)
{
	rbx = this;
	r14 = transaction;
	CA::Layer*& retLayer = rax;							// &=rax, validate after 75
	eax = 0;
	// 20
	if (!(0 == this->_10)) {
		// 29
		if (!(0 == (0x60000 & this->_4))) {
			// 34 call
			transaction->lock();
			// 52
			if (!(0 == transaction->_0->_80)) {
				// 59 call
				rbx = x_hash_table_lookup(transaction->_0->_80, this, 0);
			} // 67
			  // 70 call
			transaction->unlock();;
		} // 75
		retLayer = rbx;
	} // 78
	return retLayer;
}

CALayer* CA::Layer::presentation_layer(CA::Transaction* transaction)
{
	// _50 to _30 total 0x28 bytes
	r14 = transaction;
	r15 = this;

	CALayer*& retLayer = r12;							// &r12, except range between 188 and 271
	CA::Layer*& modelLayer = rax;						// &=rax till 58
		// 23 call
	modelLayer = this->model_layer(transaction);
	// 31
	if (!(this == modelLayer)) {
		// 36
		if (!(0 == modelLayer)) {
			// 58
			return modelLayer->presentation_layer(transaction);
		} // 60
	} // 60
	retLayer = 0;
	// 70
	if (!(0 == (this->_4 & 0x4000))) {
		CA::Transaction::Shared*& shared = r13;			// &=r13
		shared = transaction->_0;
		// 82 call
		transaction->lock();
		rdi = shared->_78;
		// 94
		if (!(0 == shared->_78)) {
			// 101 call
			retLayer = x_hash_table_lookup(shared->_78, this, 0);
			// 112
			if (retLayer) {
				// gen jmp 521
				// goto _f521; inline
				return retLayer;
			}
		} // 118

		  // 126
		if (!(0 == (this->_84 & 0x4000))) {
			// 134 call
			this->fetch_geometry(transaction);
		} // 139
		_38 = this->_10;
		// 154 call %rsi = "class", 
	  // 170 call %rsi = "alloc"
		CALayer*& newOCLayer = rax;						// &=rax, till 214, then &=_40, till 290
		retLayer = 0;
		newOCLayer = objc_msgSend((Class)objc_msgSend((CALayer*)this->_10, "class"), "alloc");
		// 182
		if (nil == newOCLayer) {
			// gen jmp 521
			// goto _f521; inline
			return 0;
		}

		CA::Layer*& newUnderlyingLayer = _50;			// &=_50
		CA::Layer::State*& state = r12;					// &=r12, till 271
		state = &this->_28;
		_48 = r13;										// save r13
		unsigned int& constructFlags = r13d;			// &=r13d
		r13d = this->_4 & 0xffedffff | 0x20000;
		state = (this->_90) ? this->_90 : state;
		// 237 call
		newUnderlyingLayer = new (x_mem_alloc_bucket(0xb))
			// 271 call
			CA::Layer::Layer(newOCLayer,
				(CA::Layer::State const&)*state, (CA::Layer::State const*)0,
				transaction, constructFlags);
		r13 = _48;										// restore r13, set to shared
		// 285 call
		newUnderlyingLayer->set_model_layer(transaction, this);
		// 305 call
		// %rsi = "initWithLayer:"
		retLayer = objc_msgSend(newOCLayer, "initWithLayer:", (CALayer*)this->_10);
		// 317
		if (nil == retLayer) {
			// gen jmp 521
			// goto _f521; inline
			return 0;
		}
		CA::Layer::Animation*& cxxAnima = rbx;			// &=rbx
		cxxAnima = this->_98;
		// 333
		if (!(0 == this->_98)) {
			double& sharedTime = _30;					// &=_30
			// 338 call
			sharedTime = xmm0.sd = ((CA::Transaction::Shared*)transaction->_0)->time();
			// 361 call
			;
			// 368
			if (!(false == CA::Layer::convert_time(transaction, (double&)sharedTime, (CALayer*)0, (CALayer*)this->_10))) {
				//: do {
			_b377:	// from 414
					// 381
				if (!(0 == (cxxAnima->_38 & 0x2))) {
					// 402 call
					objc_msgSend((CAAnimation*)cxxAnima->_8, "applyForTime:presentationObject:modelObject:", sharedTime, retLayer, this->_10);
				} // 408
				cxxAnima = cxxAnima->_0;
				// 414
				if (cxxAnima)
					goto _b377;
				//: } while (cxxAnima = cxxAnima->_0);

				r13 = _48;								// restore r13, set to shared
				// 432
				goto _f446;
			} // 434
			OSAtomicOr32(0x8000, (volatile uint32_t*)newUnderlyingLayer->_4);
		} // 446
	_f446:	// from 432
		  // 453
		if (!(0 != (transaction->_0->_10))) {
			// 458 call
			transaction->ensure_implicit();
		} // 463
		  // 470
		if (!(0 != shared->_78)) {
			rbx = shared->_50;
			// 498 call (..., 479 call)
			shared->_78 = x_hash_table_new_(0, 0, 0, 0, shared->_50, shared->hash_pool());
		} // 510
		  // 516 call
		x_hash_table_insert(shared->_78, this, retLayer);
		// 524 call
		transaction->unlock();;
	} // 529
	return retLayer;
}


CALayer* CA::Layer::layer_being_drawn(CA::Transaction* transaction, unsigned int flag)
{
	rbx = this;
	r14 = transaction;
	CALayer*& oclayer = r15;						// &=r15
	oclayer = this->_10;
	// 23
	if (!(flag == this->_4)) {
		// 38
		if (!(0x40000 == (0x60000 & this->_4))) {
			// 48
			if (!(0 == (CA::Layer::Animation*)this->_98)) {
				// 53 call
				transaction->lock();
				CA::Transaction::Shared*& shared = rdi;						// &=rdi, till 82
				shared = (CA::Transaction::Shared*)transaction->_0;
				double& atTime = xmm0.sd;									// &=xmm0.sd
				atTime = shared->_88;
				// 76
				if (!(atTime == 0.)) {
					// 80
					goto _f97;
				} // 82
				extern double rip_0x49d77;
				// 82 call
				atTime = shared->time() + rip_0x49d77;
			_f97:	// from 80
					// 111 call
				oclayer = this->layer_at_time(transaction, atTime, true, true);
				// 122 call
				transaction->unlock();;
			} // 127
		} // 127
	} // 127
	return oclayer;
}

CALayer* CA::Layer::layer_at_time(CA::Transaction* transaction, double atTime, bool flag1, bool flag2)
{
	// _80 to _30 total 0x68 bytes;
	r13d = flag2;						// till 173
	_4c = flag1;						// till 490
	rbx = this;							// till 131, then saved to _60
	r14 = transaction;					// till 647, then saved to _68, and restore at 882
	(double&)_30 = atTime;

	CALayer*& oclayer = _48;					// &=_48
	oclayer = this->_10;
	CALayer*& presentationLayer = r15;			// &=r15

	// 50
	if (!(0 == (CA::Layer::Animation*)this->_98)) {
		// 59 call
		transaction->lock();

		CA::Layer::Animation*& itAnima = r12;	// &=r12
		itAnima = this->_98;
		// 74
		if (!(0 == itAnima)) {
			extern __CFString* kCAAnimationNonZero;
			extern __CFString* kCAAnimationAbsolute;
			_70 = kCAAnimationNonZero;								// immutable
			_58 = kCAAnimationAbsolute;								// immutable
			_74 = (flag2 == true) ? 0x40000 : 0x60000;				// immutable
			_80 = (CA::Layer::State*)this->_28;						// immutable
			_60 = this;												// immutable
			presentationLayer = nil;								// via r15d = 0;

		_b142:	// from 860
			eax = (uint32_t)(int16_t)itAnima->_38;
			// 150
			if (itAnima->_38 & 0xc) {
				// gen jmp 853
				goto _f853;
			}
			else { // 150 next
				   // 162
				if (0x2 != (itAnima->_38 & 0x22)) {
					// gen jmp 173
					goto _f173;
				} // 167
				else if (r13b == true) {
					// gen jmp 853
					goto _f853;
				}
			_f173:	// from 162
				ebx = r13d;												// save r13d

				X::Ref<CA::Render::Timing>& renderTimingRef = _38;			// &=_38
				renderTimingRef._Ptr = 0;
				// 193 call
				(&renderTimingRef)->operator=((CA::Render::Timing*)itAnima->_20);
				// 204
				if (!(itAnima->_38 & 0x2)) {
					extern double rip_0x3bd08;
					// 236
					if (!(rip_0x3bd08 != objc_msgSend((CAAnimation*)itAnima->_8, "beginTime"))) {			// != [222 call]
						// 254 call
						// %rsi = "beginTimeMode"
						;
						// 274 call
						// %rsi = "isEqualToString:"
						bool& isEqual = al = objc_msgSend((__CFString*)objc_msgSend((CAAnimation*)itAnima->_8, "beginTimeMode"), "isEqualToString:", kCAAnimationNonZero);
						// 282
						if (!(NO == isEqual)) {
							double& sharedTime = (double&)_40;				// &=_40
							// 287 call
							sharedTime = ((CA::Transaction::Shared*)transaction->_0)->time();
							// 314 call
							CA::Layer::convert_time(transaction, (double&)sharedTime, (CALayer*)0, (CALayer*)this->_10);
							// 331 call
							CAAnimationSetFlags((CAAnimation*)itAnima->_8, 0x1, 0);
							// 353 call
							// %rsi = "setBeginTime:"
							objc_msgSend((CAAnimation*)itAnima->_8, "setBeginTime:", sharedTime);
							// 375 call
							// %rsi = "setBeginTimeMode:"
							objc_msgSend((CAAnimation*)itAnima->_8, "setBeginTimeMode:", kCAAnimationAbsolute);
							// 396 call
							CAAnimationSetFlags((CAAnimation*)itAnima->_8, 0x5, 0xffffffff);
						} // 401
					} // 401
					  // 413 call
					  // %rsi = "beginTimeMode"
					;
					// 433 call
					// %rsi = "isEqualToString:"
					bool& isEqual = al = objc_msgSend((__CFString*)objc_msgSend((CAAnimation*)itAnima->_8, "beginTimeMode"), "isEqualToString:", kCAAnimationAbsolute);
					// 441
					if (!(false == isEqual)) {
						// 448 call
						CA::Render::Timing*& oldRenderTiming = rdi;
						oldRenderTiming = renderTimingRef._Ptr;
						renderTimingRef._Ptr = CAMediaTimingCopyRenderTiming((CAAnimation*)itAnima->_8);
						// 464
						if (0 == oldRenderTiming) {
							// gen jmp 475
							goto _f475;
						}
						else { // 464 next
							   // 466 call
							((CA::Render::Object*)oldRenderTiming)->unref();
						}
					}// 471
				} // 471
			_f471:	// from 441
				rax = renderTimingRef._Ptr;
			_f475:	// from 464
				r13d = 0x4;
				// 484
				if (!(0 == renderTimingRef._Ptr)) {
					ecx = _4c;
					// 496
					if (!(0 == (ecx & true))) {
						// 515 call
						bool& isSuccess = al = CA::Layer::convert_time(transaction, (double&)atTime, (CALayer*)0, (CALayer*)rcx = this->_10);
						// 522
						if (false == isSuccess) {
							// gen jmp 814
							// goto _f814; inline #0
							r13d = 0x1;
							// 820
							goto _f826;
						}
						else { // 522 next
							rax = renderTimingRef._Ptr;
							_4c = 0;
						}
					}// 539
				_f539:	// from 496
					xmm0.sd = atTime;
					// 549
					if (atTime >= renderTimingRef._Ptr->_20) {
						// gen jmp 564
						goto _f564;
					} // 558
					else if (0 == (renderTimingRef._Ptr & 0x40000)) {
						// gen jmp 826
						goto _f826;
					}
				_f564:	// from 549
					(double&)_68 = atTime;							// via xmm0.sd; validate till 605
					// 586
					if (((CA::Render::Timing*)renderTimingRef._Ptr)->end_time() == (double&)_68) {			// [572 call] == _68
						// gen jmp 605
						goto _f605;
					} // 599
					else if (0 == (renderTimingRef._Ptr->_8 & 0x20000)) {
						// gen jmp 826
						goto _f826;
					}
				_f605:	// from 586
					  // 608
					if (presentationLayer) {
						// gen jmp 779
						goto _f779;
					}
					else {
						// 625 call
						// %rsi = "class"
						;
						// 641 call
						// %rsi = "alloc"
						presentationLayer = objc_msgSend((Class)objc_msgSend(oclayer, "class"), "alloc");
						_68 = transaction;							// save r14
						r13d = 0x1;
						// 663
						if (nil == presentationLayer) {
							// gen jmp 822
							goto _f822;
						}
						else {
							r14d = this->_4 & 0xffebffff | _74;
							CA::Layer*& newUnderlyingLayer = _88;					// &=_88
							// 693 call
							newUnderlyingLayer = new (x_mem_alloc_bucket(0xb))
								// 727 call
								CA::Layer::Layer((CALayer*)presentationLayer,
									(CA::Layer::State const&)this->_28, (CA::Layer::State const*)0,
									transaction, (unsigned int)r14d);
							// 746 call
							newUnderlyingLayer->set_model_layer(transaction, (CA::Layer*)this);
							// 765 call
							// %rsi = "initWithLayer:"
							presentationLayer = objc_msgSend((CALayer*)r15, "initWithLayer:");
							// 777
							if (nil == r15) {
								// gen jmp 826
								goto _f826;
							}
						}
					}// 779
				_f779:	// from 608
					r13d = 0;
					// 806 call
					// %rsi = "applyForTime:presentationObject:modelObject:"
					objc_msgSend((CAAnimation*)itAnima, "applyForTime:presentationObject:modelObject:", atTime, presentationLayer, oclayer);
					// 812
					goto _f826;
				} // 826

				/**
				* input: r13d
				*/
			_f822:	// from 663
				r14 = _68;								// restore r14, set to transaction
			_f826:	// from 820
			_f826:	// from 812
			_f826:	// from 777
			_f826:	// from 599
			_f826:	// from 558
				  // 833
				if (!(0 == renderTimingRef._Ptr)) {
					// 835 call
					((CA::Render::Object*)renderTimingRef._Ptr)->unref();
				} // 840
				  // 851
				if (0x4 != (r13d | 0x4)) {
					r13d = ebx;
					// gen jmp 911
					// goto _f911; inline #0
					transaction->unlock();
					return oclayer;
				}
				r13d = ebx;
			} // 853
		_f853:	// from 150
		_f853:	// from 167
			itAnima = itAnima->_0;
			// 860
			if (itAnima)
				goto _b142;								// loop back to _b142 if itAnima is not null


			/***
			* already walk through all the animations
			*
			*/
			// 869
			if (!(0 == presentationLayer)) {
				OSAtomicOr32(0x8000, (volatile uint32_t*)&presentationLayer->_attr._8->_4);
				// 901 call
				// %rsi = "autorelease"
				oclayer = objc_msgSend(presentationLayer, "autorelease");
			} // 911
		} // 911
	_f911:	// from 851
		  // 914 call
		transaction->unlock();
	} // 919
	return oclayer;
}

CA::Layer::Layer(CALayer* oclayer, State const& inState, State const* outState, CA::Transaction* transaction, unsigned int flag)
{
	rbx = this;
	r14 = oclayer;
	r13 = inState;
	r12 = outState;
	r15 = transaction;

	this->_8 = (CA::Layer*)0;
	this->_10 = oclayer;
	this->_18 = (CALayerArray*)0;
	this->_20 = (CALayer*)0;

	/***
	* constucture of CA::Layer::State
	*
	*/
	this->_28._0 = 1;						// 0x28(%rbx)
	this->_28._4 = inState._4;				// 0x2c(%rbx)
	this->_28._8.vec[0] = inState._8.vec[0];			// 0x30(%rbx)
	this->_28._8.vec[1] = inState._8.vec[1];			// 0x38(%rbx)
	this->_28._18 = inState._18;			// movups 0x18(%r13), %xmm0; movups %xmm0, 0x40(%rbx)
	this->_28._20 = inState._20;
	this->_28._28 = inState._28;
	this->_28._30 = inState._30;
	this->_28._38 = 0;

	eax = 0;
	// 134
	if (!(0 == inState._40)) {
		// 136 call
		this->_28._40 = CFRetain(inState._40);
	} // 141
	else {
		this->_28._40 = 0;
	}
	eax = 0;
	// 154
	if (!(0 == inState._48)) {
		// 156 call
		this->_28._48 = CFRetain(inState._48);
	} // 161
	else {
		this->_28._48 = 0;
	}
	// 165
	this->_28._50 = (CA::AttrList*)0;		// 0x78(%rbx)

	  // 178
	if (!(0 == inState._50)) {
		// 183 call
		transaction->lock();
		eax = 0;
		// 197
		if (!(0 == inState._50)) {
			// 199 call
			this->_28._50 = ((CA::AttrList*)inState._50)->copy();
		} // 204
		else {
			this->_28._50 = 0;
		}
		// 211 call
		transaction->unlock();;
	} // 216

	eax = 0;
_b218:	// from 237
	((unsigned int*)&this->_28._58)[eax] = ((unsigned int*)&inState._58)[eax];
	++eax;
	// 237
	if (eax != 4)
		goto _b218;

	this->_28._58 &= 0xffffefff;			// andb   $-0x11, 0x81(%rbx)
	eax = 0;
	// 251
	if (!(0 == outState)) {
		// 259
		if (!(outState->_58 & 0x1000)) {
			++outState->_0;
		} // 265
		this->_28._68 = outState;
	} // 268
	else {
		this->_28._68 = (CA::Layer::State*)0;
	}

	this->_a8[(0xb4 - 0xa8) >> 2] = 0;
	this->_b8 = 0;
	this->_a0 = 0;
	this->_98 = 0;

	this->_0 = 1;
	this->_4 = flag;
	this->_a8[(0xb0 - 0xa8) >> 2] = 0;
	this->_28._58 &= 0xffffefff;

	oclayer->_attr._8 = this;
}

void CA::Layer::latch_thread_flags(CA::Transaction* transaction, unsigned int* thread_flags)
{
	r14 = transaction;
	int32_t*& someflags_ref = rsi;						// &=rsi
	someflags_ref = &this->_4;
	// 25
	if (this->_84 & 0x4) {
		// gen jmp 192
		// goto _f192; inline #0
		*thread_flags = *someflags_ref & 0xffdff480 | 0x1;
		return;
	}

_b31:	 // from 51
	ebx = *someflags_ref;
	ecx = ebx & 0xfbfffed7;
	// 43
	if (!(ebx == ecx)) {
		eax = ebx;
		// 51
		if (false == OSAtomicCompareAndSwap32(ebx, ecx, (volatile int32_t*)someflags_ref))
			goto _b31;
	} // 53

	*thread_flags = ebx | 0x1;

	al = (ebx & 0x6) != 0;
	eax = (int32_t)(bool)al;
	eax = ((ebx & 0x18) == 0) ? (eax + eax * 4 + 0x10) : (eax + eax * 4);
	ecx = ((ebx & 0x60) == 0) ? eax : (eax | 0x40);
	r15d = ((ebx & 0x300) == 0) ? ecx : (ecx | 0x200);
	/**
		rbx = this->_8;
		  // 121
		goto _f132;

	_b123:	 // from 188
	_f132:	 // from 121
	*/
	CA::Layer*& itLayer = rbx;					// &=rbx, 
	uint32_t& each_thread_flags = ecx;				// &=ecx, validate from 157 to 188
	for (itLayer = this->_8						// 117 then goto _f132
		; itLayer								// 135, ok then 137, otherwise 204
		; itLayer = itLayer->_8) {		// _b123 from 188, indeed 180
		// 144
		if (!(transaction->_8 < 0)) {
			// 155
			if (!(0 == (each_thread_flags = itLayer->_a8[transaction->_8]))) {
				// 165
				goto _f180;
			} // 167
		} // 167
		  // 173 call
		each_thread_flags = *(uint32_t*)itLayer->thread_flags_(transaction);
	_f180:	 // from 165
			 // 188
		if (!(r15d != (each_thread_flags & r15d)))
			break;
	} // 204
_f204:	 // from 190
_f204:	 // from 135
	return;
}

bool CA::Layer::is_visible()
{
	return (this->_84 & 0x800) != 0;
}

void CA::Layer::invalidate_sublayers(CA::Transaction* transaction)
{
	rbx = transaction;
	// 23
	if (!(0 == transaction->_0->_78)) {
		CALayer*& oclayer = rax;					// &=rax;
		// 30 call
		oclayer = x_hash_table_lookup((x_hash_table*)transaction->_0->_78, this, 0);
		// 38
		if (!(nil == oclayer)) {
			CA::Layer*& underlyingLayer = r14;		// &=r14;
			CALayerArray*& sublayers = rsi;			// &=rsi;
			underlyingLayer = oclayer->_attr._8;
			sublayers = underlyingLayer->_18;
			// 59
			if (!(nil == sublayers)) {
				// 64 call
				transaction->release_object((void const*)sublayers);
				underlyingLayer->_18 = nil;
			} // 77
		} // 77
	} // 77
}

void CA::Layer::invalidate_layout()
{
	rbx = this;
	// 16
	if (!(0 == this->_78)) {
		// 37
		if (!(false == ((CA::AttrList*)this->_78)->get((unsigned int)0x194, (_CAValueType)0x1, (void*)0))) {		// false == [30 call]
			extern CGSize CGSizeZero;
			return objc_msgSend((CALayer*)this->_10, "setSizeRequisition:", CGSizeZero);
		} // 78
	} // 78
	return;
}

void CA::Layer::invalidate_contents()
{
	CA::Transaction*& transaction = r14;			// &=r14
	rbx = this;
	// 21
	if (this->_4 & 0x60000)
		return;

	// 32 call
	transaction = CA::Transaction::ensure_compat();
	// 43 call
	transaction->lock();

	CABackingStore*& content = r15;						// &=r15, validate till 102
	uint32_t*& someflags = r15d;							// &=r15d, invalidate until 107
	// 59 call
	// %rsi = "contents"
	content = objc_msgSend((CALayer*)this->_10, "contents");
	// 71
	if (!(0 == content)) {
		// 92
		if (CFGetTypeID(content) == CABackingStoreGetTypeID()) {				// [76 call] == [84 call]
			// gen jmp 146
			// goto _f146; inline #0
			// 159 call
			// %rsi = "setContents:"
			objc_msgSend((CALayer*)this->_10, "setContents:", 0);
			someflags = &this->_84;
			// natural flow to 172
		}
		else {
			// 102 call
			CABackingStoreSetVolatile(content, 0x1);
			someflags = &this->_84;
			// 121
			if (this->_84 & (0x80 << 8)) {								// unlikely
				// gen jmp 244
				// goto _f244; inline #0
			_f244:	 // from 121
					 // 248 call
				CA::Layer*& destLayer = rax;							// &=rax;
				destLayer = CALayerPortalGetDestination((CALayer*)this->_10);
				// 256
				if (0 == destLayer)
					goto _b172;
				// 278 call
				// %rcx = CALayer._attr
				destLayer->set_commit_needed(transaction, (unsigned int)0x1);
				// 283
				goto _b172;
			}
			else { // 121 next
				   // 139 call
				this->mark(transaction, (unsigned int)0x408, (unsigned int)0x10);;
				// 144
				goto _f172;
			}
		}// 146
	} // 146
	else {
	_f146:	 // from 92
		  // 159 call
		  // %rsi = "setContents:"
		objc_msgSend((CALayer*)this->_10, "setContents:", 0);
		someflags = &this->_84;
	} // 172

_b172:	 // from 283
_b172:	 // from 256
_f172:	 // from 144
	*someflags &= 0xffffdfff;
	uint32_t*& thread_flags = rax;						// &=rax;
		 // 184
	if (!(transaction->_8 < 0)
		&& !(0 == this->_a8[transaction->_8])) {
		thread_flags = &this->_a8[transaction->_8];
		// 205
		goto _f220;
	} // 207
	else {
		thread_flags = (uint32_t*) this->thread_flags_(transaction);
	}
_f220:	 // from 205
	*thread_flags &= 0xfffffeff;
	transaction->unlock();
	return;
}

void CA::Layer::invalidate_animations(CA::Transaction*)
{
	CA::Layer::Animation*& anima = rbx;				// &=rbx
	r14 = this;
	anima = this->_98;
	// 23
	if (!(0 == anima)) {
		// 33
		if (!(this->_84 & (0x8 << 8))) {
			extern  __CFSet* non_visible_animating_layers;
			// 45
			if (!(0 == non_visible_animating_layers)) {
				// 50 call
				CFSetRemoveValue(non_visible_animating_layers, this);
			} // 55
		} // 55

	_b55:	 // from 85
		  // 61 call
		schedule_stop_callback((CA::Layer::Animation*)anima);
		// 74 call
		CA::Layer::free_animation((CA::Layer::Animation*)anima, true);
		anima = anima->_0;									// via r15
		// 85
		if (anima)
			goto _b55;
		return this->set_animations((CA::Layer::Animation*)0);
	} // 107
	return;
}

void CA::Layer::insert_sublayer(CA::Transaction* transaction, CALayer* sublayer, unsigned long index)
{
	// _40 to _30 total 0x18 bytes;
	r12 = index;
	rbx = sublayer;
	r14 = transaction;
	r15 = this;
	objc_object*& token = *(objc_object**)&_38;			// &=&_38
	// 32
	if (!(nil == sublayer)) {
		CALayerArray*& sublayers = r13;					// &=r13, validate till 274, then from 304 to the end
		int64_t& count = rax;							// &=rax, validate between 59 and 67
		r13 = (CALayerArray*)this->_18;
		eax = 0;
		// 47
		if (!(nil == sublayers)) {
			count = sublayers->_ivars._8;
		} // 64
		index = (count < index) ? count : index;

		// 90
		if (this == sublayer->_attr._8->_8) {
			// gen jmp 110
			// goto _f110; inline #0
			// 114
			if (!(this->_20 == sublayer)) {
				// 130
				if (index == (rax = CALayerArrayGetIndexOfValue(sublayers, sublayer))) {			// index == [122 call]
					// gen jmp 462
					// goto _f462; inline #0
					return;
				}
				int64_t& rmIndex = _40;								// &=_40, validate till 186
				rmIndex = rax;
				// 155 call
				this->begin_change(transaction, (unsigned int)0x1b8, (objc_object*&)token);
				rsi = rmIndex;
				// 168
				if (!(-1 == rmIndex)) {
					// 173 call
					CALayerArrayRemoveValue(sublayers, rmIndex);
					index -= (rmIndex < index) ? 1 : 0;
				} // 186
				_40 = this;
				// 193
				goto _f265;
			} // 224
			// goto _f224; inline #1
			else {
			_f224:	 // from 114
				// 233 call
				this->remove_sublayer(transaction, sublayer);
				rax = this;
				// natural flow to 241;
				goto _f241;
			}
		} // 95
		else if (nil == sublayer->_attr._8->_8) {
			// gen jmp 195
			// goto _f195; inline #0
			// 198 call
			CFRetain(sublayer);
			// 215 call
			((CA::Layer*)sublayer->_attr._8)->remove_from_context();
			eax = 0;
			// 222
			goto _f241;
		}
		else { // 95 next
			   // 103 call
			((CA::Layer*)sublayer->_attr._8->_8)->remove_sublayer(transaction, sublayer);
			// 108
			// goto _f220; inline #0
			// 222
			eax = 0;
			goto _f241;
		} // 110

	_f241:	 // from 222
		_40 = rax;
		// 260 call
		this->begin_change(transaction, (unsigned int)0x1b8, (objc_object*&)token);
	_f265:	 // from 193
			 // 268
		if (!sublayers) {
			r13 = objc_msgSend;
			extern Class CALayerArray;
			// 291 call
			// %rsi = "alloc"
			// %rdi = (void *)0x000000010421cf40: CALayerArray
			;
			// 304 call
			// %rsi = "init"
			sublayers = objc_msgSend(objc_msgSend(CALayerArray, "alloc"), "init");
			this->_18 = sublayers;
		} // 314
		_30 = sublayer;
		// 333 call
		CALayerArrayInsertValues(sublayers, index, (CALayer*&)_30, 0x1);
		// 343
		if (!(0 != _40)) {
			rax = OFFSET_OF(CALayer, _attr);
			rdi = sublayer->_attr._8;
			rcx = this;

			CA::Layer*& underlyingLayer = rdi;		// &=rdi;
			CA::Layer*& target = rax;				// &=rax, validate till 384
			CA::Layer*& it = rcx;					// &=rcx, validate till 370
		_b360:	 // from 370
			target = it;
			it = it->_8;
			// 370
			if (it)
				goto _b360;

			// 384 call
			((CA::Layer*)underlyingLayer)->update_added_sublayer(transaction, (CA::Layer*)this, (unsigned int)target->_a4);
			underlyingLayer = sublayer->_attr._8;
			uint32_t& thread_flags = edx;					// &=edx
			// 408
			if (transaction->_8 < 0) {
				// gen jmp 421
				goto _f421;
			} // 419
			else if ((thread_flags = underlyingLayer->_a8[transaction->_8])) {
				// gen jmp 431
				goto _f431;
			}
		_f421:	 // from 408
			  // 424 call
			thread_flags = *(uint32_t*)underlyingLayer->thread_flags_(transaction);
		_f431:	 // from 419
				 // 437 call
			this->update_for_changed_sublayers(transaction, (unsigned int)thread_flags);
		} // 442
		  // 457 call
		this->end_change(transaction, (unsigned int)0x1b8, (objc_object*)token);;
	} // 462
_f462:	 // from 130
	return;
}

void CA::Layer::getter(unsigned int hkey, _CAValueType valueType, void* value)
{
	rbx = this;
	r12d = heky;
	r15d = valueType;
	r14 = value;
	CA::Transaction*& transaction = r13;
	// 26 call
	transaction = CA::Transaction::ensure_compat();;
	// 37 call
	transaction->lock();;
	// 49
	if (nil == (CA::AttrList*)this->_78
		|| !(true == ((CA::AttrList*)this->_78)->get(heky, (_CAValueType)valueType, (void*)value))) {
		// 69
		// 81 call
		this->default_value(hkey, (_CAValueType)valueType, (void*)value);
	} // 86
	transaction->unlock();
	return;
}

void CA::Layer::get_frame_transform(CGAffineTransform& transform, bool flag)
{
	// _350 to _30 total 0x328 bytes;
	rbx = transform;
	r15 = this;
	r13d = flag;
	r12 = (CALayer*)this->_10;
	CA::Transaction*& transaction = _2d8;
	// 33 call
	transaction = CA::Transaction::ensure_compat();
	// 48 call
	transaction->lock();

	ecx = this->_84;
	// 63
	if (!(0 == (this->_84 & (0x40 << 8)))) {
		// 75 call
		this->fetch_geometry(transaction);
		ecx = this->_84;
	} // 87
	  // 93
	if (!(ecx & 0x8000000)) {
		extern double memset_pattern_318[2];
		xmm0._pd[0] = memset_pattern_318[0];
		xmm0._pd[1] = memset_pattern_318[1];
	} // 105
	else {
		// 115 call
		// %rsi = "anchorPoint"
		objc_msgSend((CALayer*)this->_10, "anchorPoint");					// via r12;
		ecx = this->_84;
		xmm0._pd[0] = xmm0._pd[0];											// unpcklpd %xmm1,%xmm0
		xmm0._pd[1] = xmm1._pd[0];
	}
_f132:	 // from 103
#if 0
	xmm1._pd[0] = this->_50;
	xmm1._pd[1] = this->_58;
	xmm1._pd[0] *= xmm0._pd[0];
	xmm1._pd[1] *= xmm0._pd[1];
#else 
	xmm1._pd[0] = this->_50 * xmm0._pd[0];
	xmm1._pd[1] = this->_58 * xmm0._pd[1];
#endif

	// 148
	if (!(ecx & 0x100000)) {
		double& tx = xmm0._pd[0];
		double& ty = xmm0._pd[1];
		tx = this->_30.vec[0] - xmm1._pd[0];
		ty = this->_30.vec[1] - xmm1._pd[1];
		transform = CGAffineTransformMakeTranslation(tx, ty);
		// 198
		goto _f507;
	} // 203
	(double&)_2f0 = xmm1._pd[0];
	(double&)_2e8 = xmm1._pd[1];
	// 214
	CATransform3D& retTempTransform = *(CATransform3D*)&_160;								// total 16(0x10) quadwords, 0x80 bytes.
	r14 = &retTempTransform;
	if (!(nil == this->_10)) {
		// 236 call
		// %rdx = "transform"
		objc_msgSend_stret(&retTempTransform, (CALayer*)this->_10, "transform");			// layerTransform = [(CALayer*)this->_10 transform]
		// 241
		goto _f318;
	} // 243
	memset(&retTempTransform, 0, sizeof(CATransform3D));
_f318:	 // from 241
	CATransform3D& layerTransform = *(CATransform3D*)&_d8;
	memcpy(&layerTransform, &retTempTransform, sizeof(CATransform3D));
	// 342 call
	;
	// 349
	if (!(false == CATransform3DIsAffine_(layerTransform))) {
		// 361 call
		transform = CATransform3DGetAffineTransform_(layerTransform);
	} // 368
	else {
		extern CGAffineTransform& CGAffineTransformIdentity;
		transform = CGAffineTransfor; mIdentity
	}
_f421:	 // from 366
	extern double gc_standard_params_48;
	xmm0.sd = gc_standard_params_48;
	xmm2._pd[0] = (double&)_2f0;
	xmm2._pd[1] = (double&)_2e8;
	xmm1 = xmm2;
	xmm1._pd[0] ^= xmm0._pd[0];
	xmm1._pd[1] ^= xmm0._pd[1];
	xmm2._pd[0] = xmm2._pd[1];			// shufpd $0x1, %xmm2, %xmm2; xmm2._ps[1] = xmm2._ps[2] = xmm2._ps[3] = xmm2._ps[0], if shufps $0x0, %xmm2; xmm2
	xmm2._pd[0] ^= xmm0._pd[0];
	xmm2._pd[1] ^= xmm0._pd[1];

	xmm0._pd[0] = transform.a;
	xmm0._pd[1] = transform.b;
	xmm1._pd[1] = xmm1._pd[0];
	xmm1._pd[0] *= xmm0._pd[0];
	xmm1._pd[1] *= xmm0._pd[1];

	xmm0._pd[0] = transform.c;
	xmm0._pd[1] = transform.d;
	xmm2._pd[0] = xmm2._pd[1];
	xmm2._pd[0] *= xmm0._pd[0];
	xmm2._pd[1] *= xmm0._pd[1];
	xmm2._pd[0] += xmm1._pd[0];
	xmm2._pd[1] += xmm1._pd[1];

	xmm0._pd[0] = this->_30.vec[0];
	xmm0._pd[1] = this->_30.vec[1];
	xmm0._pd[0] += xmm2._pd[0];
	xmm0._pd[1] += xmm2._pd[1];
	xmm1._pd[0] = transform.tx;
	xmm1._pd[1] = transform.ty;
	xmm1._pd[0] += xmm0._pd[0];
	xmm1._pd[1] += xmm0._pd[1];

	transform.tx = xmm1._pd[0];
	transform.ty = xmm1._pd[1];

_f507:	 // from 198
		 // 510
	if (!flag) {
		// 526 call
		// %rsi = "superlayer"
		r12 = objc_msgSend((CALayer*)this->_10, "superlayer");
		CALayer*& superlayer = r12;
		// 538
		if (!(nil == superlayer)) {
			// 549 call
			;
			// 556
			if (!(false == _CFExecutableLinkedOnOrAfter(0x3f2))) {
				CA::Layer*& underlyingLayer = r14;
				rax = OFFSET_OF(CALayer, _attr);
				r14 = superlayer->_attr._8;							// underlyingLayer
				eax = underlyingLayer->_84;
				// 586
				if (!(0 == (underlyingLayer->_84 & 0x200000))) {
					// 597
					if (!(0x8000000 & underlyingLayer->_84)) {
						extern double memset_pattern_318[2];
						xmm0._pd[0] = memset_pattern_318[0];
						xmm0._pd[1] = memset_pattern_318[1];
						// 607
						goto _f629;
					} // 609
					CGPoint& anchorPoint = xmm0;
					// 619 call
					// %rsi = "anchorPoint"
					anchorPoint = objc_msgSend(superlayer, "anchorPoint");					// xmm0._pd[1] = xmm1._pd[0];
				_f629:	 // from 607
					CATransform3D& sublayerTransform = *(CATransform3D*)&_d8;
					CATransform3D& retTempTransform = *(CATransform3D*)&_1e0;
					anchorPoint.x = anchorPoint.x * underlyingLayer->_50 + underlyingLayer->_40;
					anchorPoint.y = anchorPoint.y * underlyingLayer->_58 + underlyingLayer->_48;
					(double&)_2f0 = anchorPoint.x;
					(double&)_2e8 = anchorPoint.y;
					transform.tx -= anchorPoint.x;
					transform.ty -= anchorPoint.y;
					// 688 call
					// %rdx = "sublayerTransform"
					objc_msgSend_stret(&retTempTransform, superlayer, "sublayerTransform");			// sublayerTransform = [superlayer sublayerTransform];

					memcpy(&sublayerTransform, &retTempTransform, sizeof(CATransform3D));
					// 721 call
					;
					// 728
					if (!(false == CATransform3DIsAffine_(sublayerTransform))) {
						CGAffineTransform& sublayerAffineTransform = *(CGAffineTransform*)&_58;
						// 745 call
						sublayerAffineTransform = CATransform3DGetAffineTransform_(sublayerTransform);

						CGAffineTransform& retTempAffineTransform = *(CGAffineTransform*)&_210;
						CGAffineTransform& argAffineTransform2 = *(CGAffineTransform*)((uintptr_t)rsp + 0x30);
						CGAffineTransform& argAffineTransform1 = *(CGAffineTransform*)((uintptr_t)rsp);
						memcpy(&argAffineTransform2, &sublayerAffineTransform, sizeof(CGAffineTransform));
						memcpy(&argAffineTransform1, &transform, sizeof(CGAffineTransform));
						// 863 call
						retTempAffineTransform = CGAffineTransformConcat(transform, sublayerAffineTransform);
						memset(&transform, &retTempAffineTransform, sizeof(CGAffineTransform));
					} // 933
					transform.tx += (double&)_2f0;
					transform.ty += (double&)_2e8;
				} // 951
			} // 951
		} // 951
	} // 951
	  // 959
	if (!(0 == (this->_80 & (0x8 << 16)))) {
		CGAffineTransform& retTempAffineTransform = *(CGAffineTransform*)&_240;
		CGAffineTransform& affineTransform = *(CGAffineTransform*)&_270;
		CGAffineTransform& arg2AffineTransform = *(CGAffineTransform*)((uintptr_t)rsp + 0x30);
		CGAffineTransform& arg1AffineTransform = *(CGAffineTransform*)((uintptr_t)rsp);

		affineTransform = CGAffineTransformMake(1., 0., 0., 2., 0., this->_58);
		arg2AffineTransform = transform;
		arg1AffineTransform = affineTransform;
		// 1174 call
		retTempAffineTransform = CGAffineTransformConcat(affineTransform, transform);
		transform = retTempAffineTransform;
	} // 1244
	  // 1252
	if (!(0 == (this->_84 & (0x4 << 16)))) {
		// 1429 call
		CGAffineTransformTranslate;;
	} // 1499
	transaction->unlock();
	return;
}

void CA::Layer::free_transaction(CA::Transaction* transaction)
{
	extern void release_presentation_layer(CA::Layer*, CALayer*, void*);
	r15 = transaction;
	r14 = &release_presentation_layer;
	// 24
	// goto _f208; inline #0
	CA::Transaction::Shared*& shared = rbx;
	shared = transaction->_0;
	shared->_80 = 0;
	// 229
	if (!(0 == shared->_78)) {			// mistaken @20160429
		// 236 call
		x_hash_table_foreach(shared->_78, &release_presentation_layer, 0);
		transaction->_78 = 0;
	} // 249
	r13 = shared->_70;
	// 256
	if (!shared->_70)
		return;
	// end inline
	// then goto _b29

	do {
	_b29:	// from 256
		shared->_70 = 0;
		// 40 call
		transaction->lock();

		struct slist { void* val; slist* next; };
		slist*& sl_head = r13;
		slist*& sl_cur = rbx;
		sl_head = shared->_70;			// fake
		sl_cur = sl_head;
		do {
		_b48:	// from 163
			CA::Layer*& layer = r12;		// &=r12;
			uint32_t& thread_flags = eax;	// &=eax
			layer = (CA::Layer*) sl_cur->val;			// r12 = rbx->_0;
				// 62
			if (!(0 == layer->_90)) {
				// 64 call
				((CA::Layer::State*)layer->_90)->unref(transaction);					// fix up @ 20160501, rsi has not been changed yet since beginning.
				layer->_90 = 0;
			} // 81
			  // 88
			if (!(transaction->_8 < 0)) {
				eax = layer->_a8[transaction->_8];										// thread_flags
				layer->_a8[transaction->_8] = 0;
			} // 112
			else {
				// 121 call
				eax = *(uint32_t*)x_hash_table_lookup(transaction->_10, layer, 0);		// thread_flags
			} // 128
				// 131
			if (!(0 == (thread_flags & (0x4 << 8)))) {
				layer->_2c |= 0x1;
			} // 139
			  // 144
			if (!(thread_flags & 0x60000)) {
				// 151 call
				layer->commit_thread_flags(thread_flags);;
			} // 156
			sl_cur = sl_cur->next;			// via rbx = rbx->_8;
			  // 163
		} while (sl_cur);		// goto _b48;


		// 168 call
		transaction->unlock();;

		/***
		* <<LOOP>>
		* traverse the slist of transaction->_70
		* and clean it.
		*/
		do {
		_b173:	// from 206
			CA::Layer*& layerToBeClean = rax;
			rax = (CA::Layer*)sl_head->val;				// via rax = r13->_0;
			rdi = layerToBeClean->_10;
			// 184
			if (!(0 == rdi)) {
				// 186 call
				CALayerRelease((CALayer*)layerToBeClean->_10);
			} // 191
			sl_head->val = nil;							// via r13->_0 = 0;
			sl_head = sl_head->next;					// via r13 = r13->_8;
			  // 206
		} while (sl_head);	// goto _b173;


	_f208:	// from 24
		shared = transaction->_0;
		shared->_80 = 0;
		// 229
		if (!(0 == shared->_78)) {
			// 236 call
			x_hash_table_foreach(shared->_78, &release_presentation_layer, 0);
			shared->_78 = 0;
		} // 249
		r13 = shared->_70;
		// 256
	} while (shared->_70);		// goto _b29;
		
	return;
}

void CA::Layer::free_animation(Animation* anima, bool dispose)
{
	r14d = dispose;
	rbx = anima;
	// 18
	if (!(0 == (CAAnimation*)anima->_8)) {
		// 20 call
		;;
		// 32 call
		CA::Transaction::ensure()->release_object((void const*)this->_8);;
	} // 37
	  // 44
	if (!(0 == (CA::Render::Timing*)anima->_20)) {
		// 46 call
		((CA::Render::Object*)anima->_20)->unref();
	} // 51
	  // 55 call
	CA::Render::key_path_free((void**)&anima->_10);
	// 67
	if (!(0 == (__CFString*)anima->_18)) {
		// 69 call
		CFRelease((__CFString*)anima->_18);
	} // 74
	  // 77
	if (!(false == dispose)) {
		return x_mem_dealloc_bucket(0x3, anima);
	} // 96
}

void CA::Layer::fetch_geometry(CA::Transaction* transaction)
{
	// _130 to _28 total 0x110 bytes
	r14 = transaction;
	rbx = this;
	// 31
	if (!(0x60000 & this->_4)) {
		// 40
		if (!transaction) {
			// 42 call
			transaction = CA::Transaction::ensure_compat();;
		} // 50
		uint32_t*& thread_flags = rax;
		// 57
		if (!(transaction->_8 < 0)) {
			// 68
			if (!(0 == this->_a8[transaction->_8])) {
				rax = (uint32_t*)&this->_a8[transaction->_8];
				// 78
				goto _f93;
			} // 80
		} // 80
		  // 86 call
		rax = (uint32_t*) this->thread_flags_(transaction);;
	_f93:	 // from 78
			 // 99
		if (!(0 == (*thread_flags & 0x100000))) {
			*thread_flags &= 0xffefffff;
			// 116 call
			transaction->lock();;
			// 131
			if (0 == (rax = this->_b8)) {
				CA::Context*& context = r15;				// validate till 229
				   // 140 call
				r15 = this->retain_context();;
				// 151
				if (!(nil == context)) {
					// 160 call
					transaction->unlock();;
					CA::Render::ShmemPtr<CA::Render::LayerShmem>& shmemPtr = *(CA::Render::ShmemPtr<CA::Render::LayerShmem>*)&_30;
					CA::Render::ShmemPtr<CA::Render::LayerShmem>*& shmemPtrInHeap = r15;
					_30 = 0;
					_28 = 0;								// via xorps  %xmm0, %xmm0; movaps %xmm0, -0x30(%rbp)
					// 182 call
					context->get_layer_shmem((unsigned long)this, shmemPtr);;
					// 192 call
					context->unref(false);;

					// 200 call
					transaction->lock();;
					// 213
					if (!(0 != this->_b8)) {
						// 222
						if (!(0 == shmemPtr._Ptr)) {
							r12d = 0;
							// 229 call
							r15 = x_mem_alloc_bucket(0);			// shmemPtrInHeap
							rdi = shmemPtr._Ptr;
							// 244
							if (!(0 == shmemPtr._Ptr)) {
								// 246 call
								r12 = ((CA::Render::Object*)shmemPtr._Ptr)->ref();
							} // 254
							shmemPtrInHeap->_Ptr = r12;
							shmemPtrInHeap->_8 = shmemPtr._8;
							this->_b8 = shmemPtrInHeap;
						} // 272
					} // 272
					rdi = shmemPtr._Ptr;
					// 279
					if (!(0 == shmemPtr._Ptr)) {
						// 281 call
						((CA::Render::Object*)shmemPtr._Ptr)->unref();
					} // 286
				} // 286
				rax = this->_b8;
				// 296
				if (0 == this->_b8) {
					// gen jmp 525
					// goto _f525; inline #0
					transaction->unlock();
					return;
				}
			} // 302

			CA::Render::ShmemPtr<CA::Render::LayerShmem>*& shmemPtrInLayer = this->_b8;			// via rax;
			rcx = shmemPtrInLayer->_Ptr;
			rax = shmemPtrInLayer->_8;
			rdi = shmemPtrInLayer->_Ptr->_18;				// ? CA::Render::Object::_18, i guess it may be CA::Render::Shmem
			  // 322
			if (!(ecx == this->_b4)) {
				rdi = (uintptr_t)shmemPtrInLayer->_Ptr->_18 + (uintptr_t)shmemPtrInLayer->_8;
				CA::Mat4<double>& mat4 = *(CA::Mat4<double>*)&_b0;
				// 345 call
				this->_a8[(0xb4 - 0xa8) >> 2] = ((CA::Render::LayerShmem*)rdi)->get_geometry((unsigned long)this, (CA::Vec2<double>&)this->_30, (CA::Mat4<double>&)mat4);;
				// 358
				if (!(0 == this->_a8[(0xb4 - 0xa8) >> 2])) {
					// 367
					if (!(this->_84 & (0x10 << 16))) {
						// 383 call
						// %rsi = CA::Mat4Impl::mat4_identity_double
						;;
						// 390
						if (true == CA::Mat4Impl::mat4_is_equal((double const*)&mat4, (double const*)&CA::Mat4Impl::mat4_identity_double)) {
							// gen jmp 525
							// goto _f525; inline #0
							transaction->unlock();
							return;
						}
					} // 396

					CA::Mat4<double>& newMat4 = *(CA::Mat4<double>*)&_130;
					// 410 call
					CA::Mat4Impl::mat4_assign((double*)&newMat4, (double const*)mat4);;
					// 422
					if (!(CA::AttrList*)this->_78) {
						// 426 call
						this->_78 = (CA::AttrList*) x_mem_alloc0_bucket(0);;
					} // 434
					  // 451 call
					((CA::AttrList*)this->_78)->set((unsigned int)0x1d0, (_CAValueType)0x16, (void const*)&newMat4);;
					// 467
					// goto _f525; inline #0
					transaction->unlock();
					return;
				} // 469

				r15 = this->_b8;						// shmemPtrInLayer
				  // 479
				if (!(0 == shmemPtrInLayer)) {				// shmemPtrInLayer
					// 487
					if (!(0 == shmemPtrInLayer->_Ptr)) {
						// 489 call
						((CA::Render::Object*)shmemPtrInLayer->_Ptr)->unref();
					} // 494
					  // 499 call
					x_mem_dealloc_bucket(0, shmemPtrInLayer);
				} // 504
				this->_b8 = 0;
				this->_a8[(0xb4 - 0xa8) >> 2] = 0;
			} // 525
		_f525:	 // from 467
		_f525:	 // from 390
		_f525:	 // from 296
			  // 528 call
			transaction->unlock();;
		} // 533
	} // 533
	return;
#if unwind_exception
	_b552 :	 // from 587
			 // 559
			 if (!) {
				 // 561 call
				 CA::Render::Object::unref() const;;
			 } // 566
			   // 587
			 goto _b552;
#endif
}

int CA::Layer::fetch_defaults()
{
	extern void defaultValueForAtom(void*, unsigned int, _CAValueType, void*);
	r14 = this;
	CA::Transaction*& transaction = rbx;
	CA::Layer::State*& state = rax;
	rbx = CA::Transaction::ensure();
	rax = this->writable_state(transaction);
	return state->fetch_defaults(transaction, (void(*)(void*, unsigned int, _CAValueType, void*))&defaultValueForAtom, (void*)this);
}

void CA::Layer::ensure_transaction_recursively(CA::Transaction* transaction)
{
	r15 = transaction;
	r14 = this;
	// 24
	if (transaction->_8 < 0) {
		// gen jmp 37
		goto _f37;
	} // 35
	else if (0 != this->_a8[transaction->_8]) {
		// gen jmp 48
		goto _f48;
	}
_f37:	 // from 24
	  // 43 call
	this->thread_flags_(transaction);;
_f48:	 // from 35
	eax = this->_84;
	// 60
	if (!(0 == (this->_84 & 0x20000))) {
		extern Class NSException;
		eax = 0;
		// 96 call
		// %rcx = @"layer %@ is a part of cycle in its layer tree"
		// %rdx = @"CALayerInvalid"
		// %rsi = "raise:format:"
		// %rdi = (void *)0x0000000103d130d0: NSException
		objc_msgSend(NSException, "raise:format:", __cfs("CALayerInvalid"), __cfs("layer %@ is a part of cycle in its layer tree"));
		eax = this->_84;
	} // 109
	eax |= 0x20000;
	this->_84 = eax;

	CALayerArray*& sublayers = rax;
	rax = (CALayerArray*)this->_18;
	// 128
	if (!(nil == sublayers)) {
		rcx = OFFSET_OF(CALayerArray, _ivars);
		int64_t& count = r12;
		r12 = sublayers->_ivars._8;
		// 148
		if (!(0 == count)) {
			CALayer*& layer = rbx;
			rbx = sublayers->_ivars._0;
			/**
			* << LOOP >>
			* do { ... ++layer; } while(0 != --count);
			*/
		_b154:	 // from 184
			rcx = OFFSET_OF(CALayer, _attr);
			// 172 call
			// %rcx = CALayer._attr
			((CA::Layer*)layer->_attr._8)->ensure_transaction_recursively(transaction);
			++layer;
			// 184
			if (0 != --count)
				goto _b154;
		} // 186
	} // 186

	CALayer*& superlayer = rax;
	rax = (CALayer*)this->_20;
	// 193
	if (!(nil == superlayer)) {
		rcx = OFFSET_OF(CALayer, _attr);
		// 210 call
		// %rcx = CALayer._attr
		((CA::Layer*)superlayer->_attr._8)->ensure_transaction_recursively(transaction);
	} // 215
	this->_84 &= 0xfffdffff;				// via  andb   $-0x3, 0x86(%r14)

}

void CA::Layer::ensure_mipmaps()
{
	rbx = this;
	// 17
	if (!((0x10 << 8) & this->_84)) {
		id& contents = rax;				// for one shot
		// 30 call
		// %rsi = "contents"
		rax = objc_msgSend((CALayer*)this->_10, "contents");
		// 39
		if (!(contents == nil)) {
			Class& contentClass = r14;
			r14 = CFGetTypeID(content);
			// 60
			if (!(contentClass != CABackingStoreGetTypeID())) {				// [44 call] != [52 call]
				// 73
				// goto _f96; inline #0
				// 96
				return objc_msgSend((CALayer*)this->_10, "setNeedsDisplay");
			} // 75
			// 83
			if (!(contentClass != CGImageGetTypeID()) {			// contentClass != [75 call]
				return objc_msgSend((CALayer*)this->_10, "setContentsChanged");
			} // 106
		} // 106
	} // 106
}

void CA::Layer::end_change(CA::Transaction* transaction, unsigned int atom, objc_object* voucher)
{
	r15 = voucher;
	r12d = atom;
	r13 = transaction;
	rbx = this;
	__CFString*& atomString = r14;
	// 29 call
	r14 = CAAtomGetString(atom);
	// 44
	if (!(0x60000 != this->_4)) {
		// 60 call
		// %rsi = "didChangeValueForKey:"
		objc_msgSend((CALayer*)this->_10, "didChangeValueForKey:", atomString);
	} // 66
	  // 75 call
	this->property_did_change(transaction, (unsigned int)atom);;
	// 83
	if (!(voucher == 0)) {
		return objc_msgSend(voucher, "runActionForKey:object:arguments:", atomString, (CALayer*)this->_10, (uint32_t)0);
	} // 125
}

void CA::Layer::did_commit(CA::Transaction* transaction)
{
	objc_msgSend((CALayer*)this->_10, "_didCommitLayer:", transaction);
}

void CA::Layer::default_value(unsigned int hkey, _CAValueType valueType, void* value)
{
	rbx = this;
	r12d = hkey;
	r15d = valueType;
	r14 = value;
	// 34
	if (!(0x1b6 == hkey)) {
		// 43
		if (!((0x1 & this->_88) == 0)) {
			// 55 call
			;;
			// 62
			if (!(false == this->style_value((unsigned int)hkey, (objc_object**)&_28))) {
				return CAValueObjCUnbox((objc_object*)_28, valueType, value);
			} // 91
		} // 91
	} // 91
	CAObject_defaultValueForAtom((Class)objc_msgSend((CALayer*)this->_10, "class"),
		(unsigned int)hkey,
		(_CAValueType)valueType,
		(void*)value);
}

CA::Render::Layer* CA::Layer::copy_render_layer(CA::Transaction* transaction, unsigned int layerFlags, unsigned int* commitFlags)
{
	// 21
	if (!(this->_84 & (0x80 << 8))) {
		return objc_msgSend((CALayer*)this->_10, "_copyRenderLayer:layerFlags:commitFlags:", transaction, layerFlags, commitFlags);
	} // 49
	*commitFlags |= 0x1fffff;
	return new (x_mem_alloc_bucket((unsigned int)0x8)) CA::Render::Layer();
}

bool CA::Layer::convert_time(CA::Transaction* transaction, double& want_to_convert_time, CALayer* from, CALayer* to)
{
	// _50 to _30 total 0x28 bytes;
	CALayer*& fromLayer = rbx;
	CALayer*& toLayer = r13;
	r13 = to;										// validate till 212, then will select another layer as the "to"
	rbx = from;									// validate till 157, then will select anthoer layer as the "from"
	_48 = want_to_convert_time;
	r14 = transaction;
	_40 = transaction;									// validate till 333
	bool& isOK = r15b;
	// 36
	if (fromLayer == toLayer) {
		// gen jmp 341
		// goto _f341; inline #0
		return true;
	}

	CALayer*& sharedLayer = r12;

	// 55 call
	// %rsi = "ancestorSharedWithLayer:"
	r12 = objc_msgSend(fromLayer, "ancestorSharedWithLayer:", toLayer);
	// 71 call
	transaction->lock();;
	r15 = &_30;

	/**
	* <<LOOP>>
	* traverse all supers of fromLayer,
	* and inverse_map_time if it has render_timing;
	*
	*/
_b80:	 // from 160				for ( ; ; )
		 // 83
	if (r12 == fromLayer)
		// gen jmp 167
		goto _f167;					// break; 
	rax = OFFSET_OF(CALayer, _attr);
	rdi = r15;									// &_30 for return constructure.
	rsi = fromLayer->_attr._8;
	rdx = _40;
	struct ret_Obj { CA::Render::Timing* _0; };
	// 104 call 
	// there is a object return function, rdi is the location for the return object.
	_30 = (X::Ref<CA::Render::Timing>&)((CA::Layer*)fromLayer->_attr._8)->render_timing(transaction);;
	r14 = (CA::Render::Timing*)((X::Ref<CA::Render::Timing>&)_30)._Ptr;				// via movq   -0x30(%rbp), %r14
	// 116
	if (!(r14 == 0)) {
		xmm0 = 0.;
		// 128 call
		((X::Ref<CA::Render::Timing>&)_30)._Ptr->inverse_map_time((double&)want_to_convert_time, (double)0.);;
		// 136 call
		((X::Ref<CA::Render::Timing>&)_30)._Ptr->unref();;
	} // 141
	  // 151 call
	  // %rsi = "superlayer"
	fromLayer = objc_msgSend(fromLayer, "superlayer");
	// 160
	goto _b80;
#if unwind_exception
	// 162
	goto _f371;
#endif

_f167:	 // from 83
	r15 = "superlayer";
	r14d = 0;
	struct slist { CALayer* val; slist* next; };
	slist*& head = r14;

	/**
	* <<LOOP>>
	* use slist to pick up all the supers of toLayer;
	*
	*/
_b177:	 // from 218
		 // 180
	if (!(sharedLayer == toLayer)) {
		// expand the stack with 0x10 bytes;
		slist*& list = rbx;
		rbx = (slist*)alloca(sizeof(slist));
		list->next = r14;
		list->val = toLayer;
		// 206 call
		toLayer = objc_msgSend(toLayer, "superlayer");
		head = list;
		// 218
		goto _b177;
#if unwind_exception
		// 220
		goto _f371;
#endif
	} // 225
	isOK = true;
	// 231
	if (!(head == 0)) {
		r12 = &_38;
		rbx = transaction;

		/**
		* <<LOOP>>
		* traverse all supers of toLayer,
		* and map_time if it has render_timing;
		*
		*/
	_b241:	 // from 317
		rcx = OFFSET_OF(CALayer, _attr);
		// 262 call			rdi is the location for the constructure of returned object
		// %rcx = CALayer._attr
		_38 = (ret_Obj)((CA::Layer*)head->val->_attr._8)->render_timing(transaction);;
		// 274
		if ((((ret_Obj&)_38)._0) == 0) {
			// gen jmp 310
			goto _f310;
		}
		else {
			// 285 call
			isOK = (bool)((CA::Render::Timing*)(((ret_Obj&)_38)._0)->map_time((double&)want_to_convert_time, (unsigned int*)0);
			// 296 call
			((CA::Render::Object*)(((ret_Obj&)_38)._0)->unref();

			// 308
			if (isOK == false) {
				// gen jmp 330
				// goto _f330; inline %0
				transaction->unlock();
				return false;
			}
		}// 310
	_f310:	 // from 274
		head = head->next;
		// 317
		if (head)
			goto _b241;							// loop back to _b241;
		// 322
		goto _f333;
	} // 324
	rbx = transaction;							// via _40;
	  // 328
	goto _f333;
_f333:	 // from 328
_f333:	 // from 322
		 // 336 call
	transaction->unlock();;
_f341:	 // from 36
	return isOK;
#if unwind_exception
	// 365
	goto _f382;
_f371:	 // from 220
_f371:	 // from 162
		 // 374
	goto _f387;
	// 382 call
	CA::Render::Object::unref() const;;
_f382:	 // from 365
_f387:	 // from 374
		 // 391 call
	CA::Transaction::unlock();;
	// 399 call
	_Unwind_Resume;;
#endif
}

void CA::Layer::contents_visibility_changed(CA::Transaction* transaction, bool isChagned)
{
	CALayer*& layer = r13;
	r12d = isChagned;					// for whole scope of function
	_30 = transaction;					// for whole scope of function
	r15 = this;							// for whole scope of function
	r13 = this->_10;					// for whole scope of function
	// 31
	if (!(layer == 0)) {
		void*& content = rbx;
		// 47 call
		// %rsi = "contents"
		rbx = objc_msgSend(layer, "contents");
		// 59
		if (!(content == 0)) {
			// 84
			if (!(CFGetTypeID(content) != CABackingStoreGetTypeID())) {				// [68 call], [76 call]
				bool& isVolatile = r14b;
				// 93 call
				r14b = CABackingStoreIsVolatile(content);
				r12b = isChagned ^ true;											// xor with 1, mean to reverse the value, like !value.
				// 112 call
				;
				// 119
				if (!(true == CABackingStoreSetVolatile(content, isChagned ^ true))) {
					// 124
					if (!(true == (isChagned ^ true))) {
						return objc_msgSend(layer, "setNeedsDisplay");
					} // 156
				} // 156
				isVolatile |= isChagned ^ true;
				eax = (uint32_t)(bool)isVolatile;
				// 166
				if (!(1 != eax)) {
					// 176
					if (!(this->_84 & (0x80 << 8))) {
						return this->mark(transaction, (unsigned int)0x408, (unsigned int)0x10);
					} // 214
					CALayer*& destLayer = rax;
					// 218 call
					rax = CALayerPortalGetDestination((CALayer*)this->_10);
					// 226
					if (!(0 == destLayer)) {
						rcx = OFFSET_OF(CALayer, _attr);
						return ((CA::Layer*)destLayer->_attr._8)->set_commit_needed(transaction, (unsigned int)0x1);
					} // 268
				} // 268
			} // 268
		} // 268
	} // 268
	return;
}

void CA::Layer::commit_thread_flags(unsigned int thread_flags)
{
	ecx = eax = thread_flags;
	ecx &= 0x204b7e;
	// 14
	if (!(ecx == 0)) {
		OSAtomicOr32(ecx, (volatile int32_t*)&this->_4);
		cl = (eax & 0x6) != 0;
		ecx = (uint32_t)(bool)cl;
		edx = rcx + rcx * 4;						// via  leal   (,%rcx,4), %edx
		ecx = rcx + 0x10 + rcx * 4;
		edx = ((eax & 0x18) == 0) ? edx : ecx;
		edx |= 0x40;
		ecx = ((eax & 0x60) == 0) ? ecx : edx;
		ecx |= 0x200;
		ecx = ((eax & (0x3 << 8)) == 0) ? edx : ecx;
		/**
			// there is a pattern of for loop.
				CA::Layer*& layer = rax;
				rax = (CA::Layer*) this->_8;
				// 75
				goto _f88;
			_b77:	 // from 100
				rdx = &layer->_4;
				OSAtomicOr32(ecx, (volatile int32_t*)&layer->_4);
				layer = layer->_8;
			_f88:	 // from 75
					 // 91
				if (!(layer == 0)) {
					// 100
					if (ecx != (layer->_4 & ecx))
						goto _b77;
				} // 102
		*/
		for (CA::Layer* layer = this->_8; layer && ecx != (layer->_4 & ecx); layer = layer->_8)
		{
			OSAtomicOr32(ecx, (volatile int32_t*)&layer->_4);
		}
	} // 102
}

/**
* called by CA::Context::commit_transaction
*
*/
bool CA::Layer::commit_if_needed(CA::Transaction* transaction,
	void(*commit_layer)(CA::Layer*, unsigned int, unsigned int, void*),
	void* token)
{
	// _50 to _30 total 0x28 bytes, 5 quadwords

	r14 = transaction;					// validate till 290
	rbx = this;
	_30 = commit_layer;
	_38 = token;
	_40 = this;							// via rbx, 136 or 237 for saving rbx
	bool& isOK = r13b;					// for return;
	uint32_t*& thread_flags = _48;
	// 38
	if (!((rax = transaction->_8) < 0)) {
		// 48
		if (!this->_a8[transaction->_8] == 0) {
			rax = (uint32_t*)&this->_a8[transaction->_8];
			// 58
			goto _f71;
		} // 60
	} // 60
	  // 66 call
	rax = (uint32_t*)this->thread_flags_(transaction);;
_f71:	 // from 58
	rcx = (uint32_t*)&this->_4;
	// 82
	if (!(0x2000000 == this->_4)) {
		*(uint32_t*)rax |= 0x200018;
	} // 90
	  // 96
	if (!(0x2200418 == this->_4)) {				// via (%rcx)
		OSAtomicAnd32(0xfddffbe7, (volatile int32_t*)&this->_4);
	} // 105
	  // 108
	if (!(*(uint32_t*)rax & 0x18)) {
		// 117
		if (!(this->_a0 == 0)) {
			r13d = 0;
			// 122
			// goto _f391; inline #0
			return false;
		} // 127
	} // 127
	CALayerArray*& sublayers = rbx;				// validate till 189
	rdx = (CALayerArray*)this->_18;
	// 134
	if (sublayers == 0) {
		// gen jmp 226
		// goto _f226; inline #0 (226, 237)
		// 226
		_40 = rbx;
		_48 = rax;
		r13d = 0;
		// natural flow to 237
		goto _f237;			// by hand;
	}
	else { // 134 next
		_40 = rbx;								// save rbx; rbx is this right now.
		_48 = rax;
		rcx = OFFSET_OF(CALayerArray, _ivars);
		int64_t& count = r15;
		r15 = sublayers->_ivars._8;				// via 8(%rdx, %rcx)
		ebx = 0;
		// 164
		if (sublayers->_ivars._8 == 0) {
			// gen jmp 234
			// goto _f234; inline #0 
			r13d = 0;
			// natural flow to 237
			goto _f237;							// by hand;
		}

		CALayer**& itlayer = r12;
		r12 = (CALayer**)sublayers->_ivars._0;				// via (%rdx, %rcx)
	_b170:	 // from 222									// a loop: if(count != 0) { do { ... } while (--count != 0); }
		CALayer*& layer = rax;
		rax = *itlayer;
		rcx = OFFSET_OF(CALayer, _attr);
		// 197 call
		// %rcx = CALayer._attr
		al = (bool)((CA::Layer*)layer->_attr._8)->commit_if_needed(transaction, commit_layer, token);
		isOK = true;
		// 207
		if (!(true == (bool)al)) {
			isOK = (bool)bl;
		} // 212
		itlayer++;											// via r12
		count--;											// via r15
		bl = r13b;
		// 222
		if (count != 0)
			goto _b170;										// loop back to _b170.
		// 224
		goto _f237;
	} // 226
_f226:	 // from 134
	_40 = rbx;
	_48 = rax;
_f234:	 // from 164
	r13d = 0;
_f237:	 // from 224, 134(inline), 164(inline)
	rbx = _40;												// restore rbx, set to this.
	rax = this->_20;
	// 248
	if (!((CALayer*)this->_20 == 0)) {
		rcx = OFFSET_OF(CALayer, _attr);
		// 273 call
		// %rcx = CALayer._attr
		isOK = (((CA::Layer*)this->_20->_attr._8)->commit_if_needed(transaction, commit_layer, token)) ? true : isOK;
	} // 290
	r14 = (uint32_t*)_48;								// uint32_t*
	  // 302
	if (!((edx = this->_a0) != 0)) {
		// 304 call
		this->_a0 = edx = CA::Render::next_sequence();;
	} // 317
	  // 327 call
	commit_layer(this, *(uint32_t*)r14, this->_a0, token); // *-0x30(%rbp);;
	eax = *(uint32_t*)r14;
	// 337
	if (!((((CA::Layer::State&)this->_28)._4 & (0x10 << 8)) == 0)) {				// this->_28 is an inline State, this->_2c is the member which is State::_4
		*(uint32_t*)r14 |= 0x80000;
		isOK = true;
	} // 350
	  // 352
	if (!((*(uint32_t*)r14 & 0x8) == 0)) {
		this->_28._4 = 0;
		eax = *(uint32_t*)r14;
	} // 364
	eax &= 0xfddfbbe7;
	isOK &= true;
	ecx = (uint32_t)(bool)isOK;
	ecx <<= 0xb;
	ecx |= eax;
	ecx |= 0x4000;																// set the thread_flags to which is pointed by r14 now.
	*(uint32_t*)r14 = ecx;
	return isOK;
}

void CA::Layer::commit_animations(CA::Transaction* transaction,
	double(*commit_layer)(CA::Layer*, double, void*),
	void(*commit_animation)(CA::Layer*, CA::Render::Animation*, void*),
	void(*remove_animation)(CA::Layer*, __CFString const*, void*),
	void*)
{
	/**
	* discussion:
	* the caller may be CA::Context::commit_layer
	* func1 may be static CA::Context::commit_layer_time
	* func2 may be static CA::Context::commit_animation
	* func3 may be static CA::Context::remove_animation
	*
	* the caller is CA::Context::commit_transaction --> CA::Layer::commit_if_needed
	* func1 is CA::Context::commit_layer
	*/
	// _a0 to _30 tcontextotal 0x78 bytes;
	_48 = (void(*)(CA::Layer*, __CFString const*, void*))remove_animation;				// via r8
	_78 = (void(*)(CA::Layer*, CA::Render::Animation*, void*))commit_animation;		// via rcx
	_68 = (double(*)(CA::Layer*, double, void*))commit_layer;						// via rdx
	_58 = (void*)context;					// 57 via r9
	_80 = r12 = this;						// for whole function scope.
	CA::Layer::Animation*& animaListHead = _30;
	CA::Layer::Animation*& itAnima = r15;			// for the loop named _b127, till 774
	r15 = (CA::Layer::Animation*) this->_98;
	_30 = r15;

	// 51
	if (this->_98 == 0) {
		return;
	}

	_90 = (CA::Layer::Animation*) this->_98;		// via r15;
	_3c = (int)transaction->_50->_5c;				// ?
	extern __CFString* kCAAnimationNonZero;
	extern __CFString* kCAAnimationRelative;
	extern __CFString* kCAAnimationAbsolute;
	_70 = kCAAnimationNonZero;
	_88 = kCAAnimationRelative;
	_60 = kCAAnimationAbsolute;
	r14 = (CA::Layer::Animation**)&_30;										// ? unused until 805

_b127:	 // from 774
	eax = (uint32_t)itAnima->_38;
	// 134
	if ((short)itAnima->_38 & 0x8) {
		// gen jmp 470
		goto _f470;
	}
	else { // 134 next
		   // 142
		if (!((short)itAnima->_38 & 0x2)) {
			itAnima->_2c = _3c;
			xmm0.sd = 0.;
			// 159 call
			;
			// 170
			if (!(CAAnimationGetFlags((CAAnimation*)itAnima->_8) & 0x4)) {
				CAAnimation*& anima = r13;						// for scope of this closure, till 351
				r13 = (CAAnimation*)itAnima->_8;
				// 190 call
				// %rsi = "beginTimeMode"
				__CFString*& cfsBeginTimeMode = r13;			// for short scope of this closure, till 254
				rbx = objc_msgSend(anima, "beginTimeMode");
				// 203
				if (kCAAnimationNonZero != cfsBeginTimeMode) {
					// gen jmp 235
					goto _f235;
				}
				else {

					// 215 call
					// %rsi = "beginTime"
					// 233
					if ((double)objc_msgSend(anima, "beginTime") == 0.) {
						// gen jmp 351
						goto _f351;
					}
				}// 235
			_f235:

				// 242
				if (kCAAnimationRelative == cfsBeginTimeMode) {
					// gen jmp 335
					goto _f335;
				}
				else { // 242 next
					   // 248
					if (kCAAnimationAbsolute == cfsBeginTimeMode)
						// gen jmp 446
						goto _f446;
					// 268 call
					// %rsi = "isEqualToString:"
					;
					// 276
					if (objc_msgSend(cfsBeginTimeMode, "isEqualToString:", kCAAnimationNonZero) == NO) {
						// gen jmp 308
						goto _f308;
					}
					else {
						// 288 call
						// %rsi = "beginTime"
						;
						// 306
						if ((double)objc_msgSend(anima, "beginTime") == 0.) {
							// gen jmp 351
							goto _f351;
						}
					}// 308
				_f308:	 // from 276
					  // 325 call
					  // %rsi = "isEqualToString:"
					;
					// 333
					if (objc_msgSend(cfsBeginTimeMode, "isEqualToString:", kCAAnimationRelative) == NO)
						// gen jmp 446
						goto _f446;
				} // 335
			_f335:	 // from 242
					 // 345 call
					 // %rsi = "beginTime"
				xmm0.sd = (anima, "beginTime");
			_f351:	 // from 306
			_f351:	 // from 233
			} // 351
			/**
			* input: xmm0 = [anima beginTime];
			*
			*/
			// 358 call
			commit_layer(this, (double)xmm0, (void*)_58);		// via *-0x68(%rbp);;
			// 377 call
			CAAnimationSetFlags((CAAnimation*)itAnima->_8, (int)0x5, 0);
			rbx = &objc_msgSend;
			// 408 call
			// %rsi = "setBeginTime:"
			objc_msgSend((CAAnimation*)itAnima->_8, "setBeginTime:", (double&)_50);// *%rbx;;
			// 425 call
			// %rsi = "setBeginTimeMode:"
			objc_msgSend((CAAnimation*)itAnima->_8, "setBeginTimeMode:", kCAAnimationAbsolute); //  *%rbx;;
			// 441 call
			CAAnimationSetFlags((CAAnimation*)itAnima->_8, (int)0x1, (int)0xffffffff);
		_f446:	 // from 333
		_f446:	 // from 248
			itAnima->_38 |= 0x2;
			// 459
			goto _f546;
		} // 461
		/**
		* input: eax = (uint32_t)itAnima->_38;
		*
		*/
		ecx = _3c;
		// 468
		if (itAnima->_2c != _3c) {
			// gen jmp 512
			// goto _f512; inline #0
		_f512:	 // from 468
			itAnima->_2c = _3c;
			// 526
			if (!((CA::Render::Timing*)itAnima->_20 == 0)) {
				// 528 call
				((CA::Render::Object*)itAnima->_20)->unref();
				eax = (uint32_t)itAnima->_38;
			} // 538
			itAnima->_20 = 0;
		_f546:	 // from 459
				 // 548
			if (!((eax & 0x40) == 0)) {
				CA::Render::Animation*& renderAnima = r13;					// for scope of this closure, till 768
				// 570 call
				// %rsi = "_copyRenderAnimationForLayer:"
				r13 = objc_msgSend((CAAnimation*)itAnima->_8, "_copyRenderAnimationForLayer:", (CALayer*)this->_10);
				// 582
				if (!(renderAnima == 0)) {
					// 595 call
					renderAnima->set_identifier((__CFString const*)itAnima->_18);
					renderAnima->_30 = itAnima->_28;
					rbx = (CAAnimation*)itAnima->_8;
					r12 = &objc_msgSend;
					// 633 call
					// %rsi = "class"
					// %rdi = (void *)0x000000010421c658: CAPropertyAnimation
					extern Class CAPropertyAnimation;
					; // *%r12;;
					// 649 call
					// %rsi = "isKindOfClass:"
					;// *%r12;;
					// 654
					if (!(objc_msgSend((CAAnimation*)itAnima->_8, "isKindOfClass:", (Class)objc_msgSend(CAPropertyAnimation, "class")) == NO)) {
						// 663 call
						;;
						// 671
						if (!(CA::Render::key_path_count((void* const*)renderAnima->_40) != 0)) {
							void*& key_path = rbx;
							rbx = &_38;
							// 684 call
							CA::Render::key_path_copy((void**)&key_path, (void* const*)itAnima->_10);;
							// 695 call
							((CA::Render::PropertyAnimation*)renderAnima)->set_property((void* const*)key_path);;
						} // 700
					} // 700
					r12 = this;							// via _80, restore r12 to this.
					  // 714 call
					commit_animation(this, renderAnima, (void*)_58); // *-0x78(%rbp);;
					eax = 0;
					// 729
					if (!(renderAnima->_10 == 0)) {
						// 731 call
						rax = ((CA::Render::Object*)renderAnima->_10)->ref();
					} // 736
					itAnima->_20 = (CA::Render::Timing*)rax;
					// 743 call
					((CA::Render::Object*)renderAnima)->unref();
				} // 748
			} // 748
			  // 753
			if (!(itAnima->_20 != 0)) {
				// 759 call
				itAnima->_20 = (CA::Render::Timing*) CAMediaTimingCopyRenderTiming((CAAnimation*)itAnima->_8);
			} // 768
			// natual flow to 768
			goto _f768;					// by hand
		}

	} // 470
_f470:	 // from 134
		 // 479
	if (!(this->_84 & (0x8 << 8))) {
		// 493
		if (!((itAnima->_38 & 0x1) == 0)) {
			itAnima->_38 |= 0x4;
			// 507
			goto _f768;

		} // 768
	} // 768
_f768:	 // from 507
	itAnima = itAnima->_0;
	// 774
	if (itAnima != 0)
		goto _b127;							// loop back

	// 780
	r15 = _58;
	rax = (CA::Layer::Animation*)this->_98;				// via _90
	CA::Layer::Animation*& itAnima2 = rbx;				// for scope of loop named _b791, till 890
_b791:	 // from 890
	rbx = rax;
_b794:	 // from 864
		 // 800
	if (!(((eax = itAnima2->_38) & 0xc) == 0)) {
		/**
		* r14 is a position where to begin removing anima.
		* the removed current anima, will link to animation_state_2 by front inserting.
		* the iterator will point to the next of current.
		*/
		*(CA::Layer::Animation**)r14 = itAnima2->_0;			// r14 is &_30;
		// 818
		if (!(0x44 != (itAnima2->_38 & 0x4c))) {
			// 830 call
			remove_animation(this, itAnima2->_18, (void*)r15); // *-0x48(%rbp);;
		} // 833
		  // 836 call
		schedule_stop_callback((CA::Layer::Animation*)itAnima2);;
		extern CA::Layer::Animation* animation_state_2;
		itAnima2->_0 = animation_state_2;
		animation_state_2 = itAnima2;
		itAnima2 = *(CA::Layer::Animation**)r14;
		// 864
		if (itAnima2)
			goto _b794;									// loop back
	} // 868
	else {
		// 870
		if (!((itAnima2->_38 & 0x10) == 0)) {			// via al
			itAnima2->_38 &= 0xffef;
		} // 881
		rax = itAnima2->_0;
		r14 = (CA::Layer::Animation**)&itAnima2->_0;
		// 890
		if (itAnima2->_0) {
			// goto _b791;		inline #0							// loop back
			itAnima2 = itAnima2->_0;					// via rbx = rax;
			// natural flow to 794
			goto _b794;									// by hand
		}

	}
_f892:	 // from 866
		 // 899 call
	this->set_animations((CA::Layer::Animation*)_30);;
}

uintptr_t CA::Layer::animation_heart_beat(CAAnimation*, __CFString const*)
{
	// 4 call
	CA::Transaction*& transaction = rax;
	transaction = CA::Transaction::ensure();;
	// 16
	if (transaction->_0->_10 != 0) {
		return transaction;
	} // 20
	return transaction->ensure_implicit();
}

void CA::Layer::animation_visibility_changed(CA::Transaction* transaction, bool visibility)
{
	rbx = this;
	// 21
	if ((CA::Layer::Animation*)this->_98 == 0) {
		return;
	}
	extern void* non_visible_animating_layers;
	// 25
	if (visibility == false) {
		// 57 call
		add_non_visible_animating_layer((CA::Layer*)this);;
	} // 37
	else if (non_visible_animating_layers == 0) {
		return this->mark_animations(transaction, false);
	}
	else { // 37 next
		   // 42 call
		CFSetRemoveValue(non_visible_animating_layers, this);;
		return this->mark_animations(transaction, false);
	}
}

void CA::Layer::begin_change(CA::Transaction* transaction, unsigned int atom, objc_object*& voucher)
{
	r15 = &voucher;
	r12 = transaction;
	rbx = this;
	r14d = atom;
	rax = transaction->_0;
	// 31
	if (!(transaction->_0->_10 != 0)) {
		// 36 call
		transaction->ensure_implicit();
		eax = this->_4;
	} // 41
	  // 47
	if (!((eax & (0x80 << 8)) == 0)) {
		extern Class NSException;
		// 83 call
		objc_msgSend(NSException, "raise:format:", @ "CALayerReadOnly", @ "attempting to modify read - only layer %@", (CA::Layer*)this->_10);
	} // 89
	  // 96
	if (!((this->_4 & 0x60000) == 0)) {
		voucher = 0;
		return;
	} // 114

	voucher = (objc_object*)actionForKey(this, transaction, (NSString*)CAAtomGetString(atom));
	return objc_msgSend(this, "willChangeValueForKey:", (NSString*)CAAtomGetString(atom));
}

void CA::Layer::call_did_become_visible()
{
	objc_msgSend((CA::Layer*)this->_10, "layerDidBecomeVisible:", (boolean)(0x800 & this->_84) >> 0xb);
}

int CA::Layer::changed_flags_for_class(objc_class* cls)
{
	// _50 to _30
	rbx = cls;				// via rdi
	_30 = cls;				// via rbx;
	extern Class CALayer;
	static void** changed_flags[];		// int, char*, int, char*....
	// 38 call
	objc_class*& clsget = rcx;
	int64_t& flag = (int64_t&)_50;
	_38 = rcx = objc_msgSend(CALayer, "class");
	_50 = 0;
	// 60
	if (!(clsget == 0)) {
		_50 = 0;				// via rax, eax = 0;
		r15 = "instanceMethodForSelector:";
		r12 = &objc_msgSend;
		eax = 0;
	_b88:	// from 225
		(int&)_40 = eax;
		(int&)_48 = eax << 0x4;		// eax * 16, size of 2 quadwords
		rbx = (char*)changed_flags[_40 + 1];
		// 118
		if (!(*(char*)rbx == 0)) {
		_b120:	// from 188
				// 123 call
			r13 = (SEL)sel_registerName((char*)rbx);;				// @selector(rbx);
			// 134
			if (r13 == 0) {
				// gen jmp 170
				// goto _f170; inline #0
				// 170
					// 173 call
				strlen((char*)rbx);
				// 188
				if (*(char*)(rbx = (char*)rbx + strlen((char*)rbx) + 1) != 0)				// "char\0\0" next is null-term
					goto _b120;
				// 190
				// goto _f214; inline #0
			}
			else {

				// 146 call
				r14 = (Method)objc_msgSend((objc_class*)_38, "instanceMethodForSelector:", (SEL)r13);
				// 162 call
				rax = (Method)objc_msgSend(cls, "instanceMethodForSelector:", (SEL)r13);		// via _30;
				// 168
				if ((Method)r14 == (Method)rax) {
					// 170
					// 173 call
					strlen((char*)rbx);
					// 188
					if (*(char*)(rbx = (char*)rbx + strlen((char*)rbx) + 1) != 0)				// "char\0\0" next is null-term
						goto _b120;
					// 190
					// goto _f214; inline #0
				}
				else {
					// gen jmp 192
					// goto _f192; inline #0
					// 192
					(int&)_50 |= (int)changed_flags[_40];
					// natural flow to 214
					goto _f214;
				}
			}
		} // 214
	_f214:
		rax = (int&)_40;
		// 225
		if (++rax != 0x10)
			goto _b88;
	} // 231
	;
	return ((bool)objc_msgSend(cls, "_hasRenderLayerSubclass")) ? (int&)_50 | 0x10000 : (int&)_50;				// 1<<0x10
}


CA::Layer::State* CA::Layer::class_state(objc_class* cls)
{
	r15 = cls;
	CA::Layer::State*& state = rbx;
	// 17 call
	state = (CA::Layer::State*)CAObject_classInfo(cls);
	// 28
	if (state != 0) {
		// 452 inline
		return state;
	}
	r13d = 0x4920a8;
	r14 = (void*(*)(void*, unsigned int, _CAValueType, void*)) &fetchDefault;
_b47:	 // from 446
		 // 52 call
	rbx = x_mem_alloc_bucket(0x6);
	memset(state, 0, sizeof(*state))
		state->_0 = 0x1;
	state->_58 = 0xffffe007;
	state->_5c = 0x7fffffff;

	extern unsigned int bool_bits[];
	unsigned int*& it_bool_bits = rax;
	rax = bool_bits;
	edx = 0;
_b192:	 // from 227			a loop for(edx = 0; edx < 0x1d; ++edx)
		 // 196
	if (!(((1 << edx) & 0x4920a8) == 0)) {					// via r13
		ecx = *it_bool_bits;
		esi = ecx >> 0x5;
		*(&state->_58 + rsi) |= 1 << (ecx & 0xff);
	} // 216
	++edx;
	it_bool_bits += (0x20 >> 2);
	// 227
	if (edx != 0x1d)
		goto _b192;


	// 232 call
	;
	// 239
	if (!((bool)CAObject_hasNeedsDisplayForKey(cls) == false)) {
		state->_60 |= 0x20;			// set bit
	} // 245
	  // 248 call
	;
	// 255
	if (!((bool)CAObject_hasNeedsLayoutForKey(cls) == false)) {
		state->_60 |= 0x40;			// set bit
	} // 261
	// 278 call
	state->_4 |= state->fetch_defaults((CA::Transaction*)CA::Transaction::ensure(),				// 261 call
		(void(*)(void*, unsigned int, _CAValueType, void*))fetchDefault, (void*)cls);
	// 289 call
	state->_4 |= CA::Layer::changed_flags_for_class((objc_class*)cls);
	// 303 call
	;
	// 310
	if (!((bool)CAObject_setClassInfo(cls, state) == true)) {
		/**
		* this closure means the failure of setClassInfo,
		* we should release the objects of state, and release the state,
		* and then loop back to _b47;
		*/
		CA::Transaction*& transaction = r12;
		// 316 call
		transaction = CA::Transaction::ensure();;
		// 331
		if (!(state->_40 == 0)) {
			// 336 call
			transaction->release_object((void const*)state->_40);;
			state->_40 = 0;
		} // 349
		  // 356
		if (!(state->_48 == 0)) {
			// 361 call
			transaction->release_object((void const*)state->_48);;
			state->_48 = 0;
		} // 374
		  // 379
		if (!(state->_50 == 0)) {
			// 384 call
			transaction->lock();;
			// 396
			if (!(state->_50 == 0)) {
				// 398 call
				((CA::AttrList*)state->_50)->free();;
			} // 403
			state->_50 = 0;
			// 414 call
			transaction->unlock();;
		} // 419
		  // 427 call
		x_mem_dealloc_bucket(0x6, state);

		/***
		* maybe somewhere else a classInfo has been set to.
		*
		*/
		// 435 call
		state = (CA::Layer::State*)CAObject_classInfo(cls);
		// 446
		if (state == 0)
			goto _b47;
	} // 452
	return state;
	/***
	_b473:	 // from 492
			 // 476 call
		_Unwind_Resume;;
		// 487 call
		CA::Transaction::unlock();;
		// 492
		goto _b473;
		*/

}

void CA::Layer::collect_layers_(CollectLayersData* data)
{
	/***
	* collect the layers from CA::Layer::layers, which meet the condiction.
	* and link them into CA::Layer::_0 through a single link list. (slist).
	*
	*/
	r14 = this;			// for whole function scope
	r13 = (CA::Layer::CollectLayersData*)data;			// for whole function scope
	rsi = (CA::Transaction*)data->_18;
	rax = (int64_t)((CA::Transaction*)rsi)->_8;
	// 31
	if (!(rax < 0)) {
		r12d = this->_a8[rax];
		// 44
		if (!(r12d == 0)) {
			rbx = (unsigned int*)&this->_a8[rax];
			// 54
			goto _f70;
		} // 56
	} // 56
	  // 59 call
	rbx = (unsigned int*)this->thread_flags_((CA::Transaction*)data->_18);;
	r12d = *(unsigned int*)rbx;
_f70:	 // from 54
	struct slist { CA::Layer* val; slist* next; };
	ecx = ~(data->_2c | data->_28 & r12d);
	OSAtomicAnd32(ecx, (volatile int32_t*)&this->_4);
	eax &= r12d;
	// 93
	if (!(eax == 0)) {
		eax = data->_30;
		// 105
		if (!(eax == 0)) {
			*(unsigned int*) |= eax;
			rdi = data->_20;
			// 121
			if (!((rcx = data->_20->_10) >= 0x10)) {
				// 128 call
				rax = x_heap_malloc_small_(data->_20, (uint32_t)0x10);
			} // 135
			else {
				rax = data->_20->_8;
				data->_20->_10 -= 0x10;				// via rcx
				data->_20->_8 = (slist*)data->_20->_8 + 1;
			} // 155
			rax->_0 = this;
			rax->_8 = data->_8;
			data->_8 = rax;
		} // 170
		  // 177
		if (!((data->_2c & r12d) == 0)) {
			*(unsigned int*)rbx &= ~data->_2c;
			_30 = (unsigned int*)rbx;										// save rbx
			rax = (struct CALayerArray*)this->_18;
			// 194
			if (!(this->_18 == 0)) {			// via rax
				int64_t& count = rbx;
				rcx = OFFSET_OF(CALayerArray, _ivars);
				rbx = ((CALayerArray*)this->_18)->_ivars._8;				// count of CALayer**
				// 214
				if (!(count == 0)) {
					CALayer**& itCALayer = r15;
					r15 = (CALayer**)((CALayerArray*)this->_18)->_ivars._0;
				_b220:	 // from 257
					rax = (CALayer*)*itCALayer;
					rcx = OFFSET_OF(CALayer, _attr);
					// 245 call
					// %rcx = CALayer._attr
					((CA::Layer*)((*itCALayer)->_attr._8))->collect_layers_(data);
					++itCALayer;
					// 257
					if (--count != 0)
						goto _b220;
				} // 259
			} // 259
			rax = (CALayer*)this->_20;
			rbx = (unsigned int*)_30;														// restore rbx
			  // 270
			if (!((CALayer*)this->_20 == 0)) {
				rcx = OFFSET_OF(CALayer, _attr);
				// 294 call
				// %rcx = CALayer._attr
				((CA::Layer*)(((CALayer*)this->_20)->_attr._8))->collect_layers_(data);
			} // 299
		} // 299
		eax = data->_28;
		// 306
		if (!(r12d == data->_28)) {
			*(unsigned int*)rbx &= ~data->_28;
			rdi = data->_20;
			rcx = data->_20->_10;					// via rdi
			// 324
			if (!(data->_20->_10 >= 0x10)) {		// via rcx
				/***
				* the inline buffer of CollectLayersData for slist node has run out.
				* so we should use heap to allocate slist node.
				*/
				// 331 call
				rax = (slist*)x_heap_malloc_small_(data->_20, (unsigned int)0x10);
			} // 338
			else {
				/***
				* there is still free space of buffer of CollectLayersData for slist node.
				* so we can allocate slist node under these buffers.
				*/
				rax = (slist*)data->_20->_8;				// via 0x8(%rdi)		slist[]
				data->_20->_10 -= 0x10;						// sizeof(slist)
				data->_20->_8 = (slist*)data->_20->_8 + 1;	// via rax;			skip sizeof(slist)
			} // 358
			rcx = (slist*)data->_0;							// front insert.
			((slist*)rax)->val = this;
			((slist*)rax)->next = (slist*)rcx;
			data->_0 = (slist*)rax;
			++data->_10;
		} // 377
	} // 377
	return;
}


CA::Layer::collect_non_visible_animations(CA::Transaction* transaction)
{
	// _1030 to _20 total 0x1018 bytes
	r15 = transaction;
	extern void** __stack_chk_guard;
	_20 = r14 = *__stack_chk_guard;
	// 33 call
	transaction->lock();
	extern int animation_state_7;
	// 46
	if (!(animation_state_7 == 0)) {
		extern __CFSet* non_visible_animating_layers;
		struct slist { void* val; slist* next; };
		slist*& head = _28;
		slist*& itSlist = rbx;

		/***
		* new a heap as buffer for slist node.
		* from _1028 to _28
		*/
		// 66 call
		_1030 = (void*)x_heap_new_with_ptr(0x1000, &_1028, 0);
		/**
		* _1030 is type of struct { char* ptr; char buffer[0x1000]; slist* head; }
		* _1028 to _28 is buffer for slist
		* _28 is the slist head
		*/
		head = 0;
		// 107 call
		// %rsi = CA::Layer::collect_non_visible_callback(void const*, void*)
		// %rdi = non_visible_animating_layers
		CFSetApplyFunction(non_visible_animating_layers, (void(*)(void const*, void*))&CA::Layer::collect_non_visible_callback, (void*)&_1030);
		rbx = (slist*)head;
		// 116
		goto _f122;

		/**
		* there is a loop
		*
		*/

	_b118:	 // from 142			// small loop
		itSlist = itSlist->next;
	_f122:	 // from 116
			 // 132
		if (itSlist == 0)
			goto _f175;				// break; and enter another loop named _b144;
		// 137 call
		rax = CFSetRemoveValue(non_visible_animating_layers, (void*)itSlist->val);
		// 142
		goto _b118;

		/***
		* there is a try-catch block
		*
		*/
		/*** exception block
	_b144:	 // from 248
		r14 = rax;
			 // 154 call
		x_heap_free((void*)_1030);				// &_1028
	_b159:	 // from 258

			 // 162 call
		transaction->unlock();;
		// 170 call
		_Unwind_Resume(r14);
		// 175 call
		CFSetGetCount;;
		*/
	_f175:
		// 175 call
		;
		// 183
		if (!(CFSetGetCount(non_visible_animating_layers) != 0)) {
			// 192 call
			// %rdi = non_visible_animating_layers
			CFRelease(non_visible_animating_layers);
			extern int animation_state_4;
			animation_state_4 = 0;
		} // 208
		  // 215 call
		x_heap_free((void*)_1030);
	} // 220
	// 223
	transaction->unlock();
	// 232
	if (_20 != r14)					// stack check before return;
		goto _f250;
	return;
	/** exception block
	// 248
	goto _b144;
	// 250 call
	r14 = rax = __stack_chk_fail();
_f250:	 // from 232
		 // 258
	goto _b159;
	*/

}

void CA::Layer::collect_non_visible_callback(void const* elem, void* context)
{
	/**
	* every element of array will apply this callback function.
	*
	*/
	// _30 to _28 total 0x10 bytes
	// context is type of struct { char* ptr; char buffer[0x1000]; slist* head; }, this structure is referent to the caller CA::Layer::collect_non_visible_animations.
	r15 = elem;
	r14 = context;

	_28 = rax = (CA::Layer::Animation*) ((CA::Layer*)elme)->_98;				// via r15
	// 35
	if (!(((CA::Layer*)elem)->_98 == 0)) {										// via r15
		r12 = (CA::Layer::Animation**) &_28;
	_b41:	 // from 117
		CA::Layer::Animation**& prev = r12;
		CA::Layer::Animation*& it = rbx;
		rbx = rax;
	_b44:	 // from 97
			 // 47 call
		schedule_stop_callback((CA::Layer::Animation*)rbx);;
		eax = (unsigned int)((CA::Layer::Animation*)rbx)->_38;
		// 64
		if (!((eax & 0x5) != 1)) {
			// 68
			if (!((eax & 0xff & 0x12) != 0)) {
				/***
				* if the current CA::Layer::Animation is which we want to free.
				* 1.delink the rbx: *prev = it->next;
				* 2.free the it
				* 3.it = *prev;
				*/
				rax = ((CA::Layer::Animation*)rbx)->_0;
				*prev = (CA::Layer::Animation*) rax;				//  *(CA::Layer::Animation**)r12 = (CA::Layer::Animation*) rax;
				// 85 call
				CA::Layer::free_animation((CA::Layer::Animation*)rbx, true);;
				rbx = *(CA::Layer::Animation**)r12;
				// 97
				if (rbx != 0)
					goto _b44;										// loop back
				// 99
				goto _f119;											// break;
			} // 101
			eax |= 0x4;
			((CA::Layer::Animation*)rbx)->_38 = ax;
		} // 108
		/**
		* 1.skip it to next.
		* 2.prev forwards one step.
		*/
		rax = ((CA::Layer::Animation*)rbx)->_0;							// tmp = it->next;
		r12 = (CA::Layer::Animation**)&rbx->_0;							// rbx is &rbx->_0; prev = &it->next;
		  // 117
		if (rax != 0) {
			// goto _b41; inline #0
			rbx = rax;													// it = *prev;
			// natural flow to 44
			goto _b44;												// loop back
		}

	_f119:	 // from 99
		rax = (CA::Layer::Animation*)_28;			// *(CA::Layer::Animation**)r12
	} // 123
	((CA::Layer*)elem)->_98 = (CA::Layer::Animation*)rax;				// r15 is elem
	  // 133
	if (!(rax != 0)) {
		struct slist { CA::Layer* val; slist* next; };
		struct context { char* zone; char buffer[0x1000]; slist* head; };
		struct context*& ctx = r14 = context;
		slist*& newlist = rax;
		slist*& lasthead = rcx;
		// 143 call
		rax = (slist*)x_heap_malloc(ctx->zone, 0x10);					// 0x10 is sizeof(slist).
		rcx = (slist*)ctx->head;
		((slist*)newlist)->val = elem;								// via r15
		((slist*)newlist)->next = lasthead;
		ctx->head = (slist*)newlist;									// context->head = rax;
	} // 169

}