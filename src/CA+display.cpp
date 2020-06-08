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

bool CA::Layer::display_if_needed(CA::Transaction* transaction)
{
	rbx = this;
	r13 = transaction;
	extern void** __stack_chk_guard;
	_30 = *__stack_chk_guard;
	uint32_t*& thread_flags = _1078;
	bool& isOK = _1084;
	// 47
	if (!((int32_t)transaction->_8 > 0)) {
		// 58
		if (!(this->_a8[(int32_t)transaction->_8] == 0)) {
			_1078 = (uint32_t*) &this->_a8[(int32_t)transaction->_8];
			// 75
			goto _f97;
		} // 77
	} // 77
	  // 83 call
	_1078 = (uint32_t*) this->thread_flags_(transaction);;
_f97:	 // from 75
		 // 100
	if (!(0 == (*thread_flags & (0x3<<8)))) {
		_1080 = this;							// save rbx,this?
		rbx = "display";
		isOK = false;							// via _1084

		/**
		* <<LOOP>>
		*
		*/
	_b130:	 // from 336
			 // 147 call
		void*& heapBuffer = r12;
		r12 = x_heap_new_with_ptr((uint32_t)0x400, &_1030, (uint32_t)0x1000);

		// 158 call
		transaction->lock();;

		CA::Layer::CollectLayersData& collectLayerData = *(CA::Layer::CollectLayersData*)&_1070;
		_1070 = 0;
		_1068 = 0;
		_1060 = 0;
		_1058 = transaction;
		_1050 = heapBuffer;
		_1048 = 0x100;
		_1044 = 0x200;
		_1040 = 0;

		// 242 call
		this->collect_layers_((CA::Layer::CollectLayersData*)&collectLayerData);;
		r14 = collectLayerData._0;					// via _1070
		r15 = collectLayerData._10;					// via _1060
		struct slist { CA::Layer* val; slist* next; } *& collectLayers = r14;

		// 264 call
		transaction->unlock();;
#if 0
		// 273
		if (!(0 != collectLayerData._10)) {			// via r15;
			// 275
			goto _f317;
		_b277:	 // from 307
				 // 287 call
			objc_msgSend((CALayer*)collectLayers->val->_10, "display");
			collectLayers->val = 0;
			collectLayers = collectLayers->next;
		} // 304
		  // 307
		if (collectLayers != 0)
			goto _b277;
		// 309
		isOK = true;					// via _1084, al
#else 
		// 273
		if (0 != collectLayerData._10) {			// via r15;
			while (collectLayers != 0) {
				objc_msgSend((CALayer*)collectLayers->val->_10, "display");
				collectLayers->val = 0;
				collectLayers = collectLayers->next;
			}
			// 309
			isOK = true;					// via _1084, al
		} // 317;
#endif
	_f317:	 // from 275
			 // 320 call
		x_heap_free(heapBuffer);
		// 336
		if (*thread_flags & (0x3<<8))
			goto _b130;

		// 342
		goto _f354;
	} // 344
	isOK = false;						// via _1084;

_f354:	 // from 342
		 // 368
	if (_30 != *__stack_chk_guard)
		goto _f396;

	return isOK;						// via _1084

#if unwind_exception
_f396:	 // from 368
	// 396 call
	__stack_chk_fail;;
#endif
}


void CA::Layer::display()
{
	rbx = this;
	// 20
	if (!((0x60000 & this->_4) == 0)) {
		return;
	} // 33
		 // 40
	if (!((0x1<<8) & this->_88)) {
		return objc_msgSend((CALayer*)this->_10, "_display");
	} // 69
	  // 69 call
	CA::Transaction*& transaction = r15;
	r15 = CA::Transaction::ensure();
	// 80 call
	transaction->lock();
	id& delegate = r14;
	r14d = 0;
	// 95
	if (!(0 == ((0x1 << 8) & this->_88))) {
		// 101 call
		r14 = objc_retain(this->_60);
	} // 109
	transaction->unlock();
	objc_msgSend(delegate, "displayLayer:", (CALayer*)this->_10);
	objc_msgSend(delegate, "release");
}

void ___ZN2CA5Layer8display_Ev_block_invoke(_NSConcreteBlock* Block)
{
	extern void backing_callback(CGContext*, void*);
	CABackingStoreUpdate_((CGImage*)Block->_28, 
							(unsigned int)Block->_38,					// scaled width
							(unsigned int)Block->_3c,					// scaled height
							(unsigned int)Block->_40,					// CA::Layer::_4
							(unsigned int)Block->_44,					// CA::Layer::_84
							(void(*)(CGContext*, void*))&backing_callback,
							(CA::Layer*)Block->_20,
							(void**)Block->_30);						// &CA::Transaction::_50::_b8
}

void CA::Layer::display_()
{
	// 
	// _f0 to _30 total 0xc8 bytes, 25 quadwords for local variables.
	// rbx is this;
	// r14 is (CALayer*)this->_10;
	rbx = this;
	double scale;
	bool cond_401;
	bool cond_491;
	// 30
	if ((this->_4 & 0x60000) == 0) {
		/***
		* xmm0 is this->_50, width;
		* xmm1 is this->_58, height;
		* xmm2 is scale.
		*/
		r14 = this->_10;
		xmm1 = 0.;
		xmm0 = (double&)this->_50;
		// 53
		if (!(0. == this->_50)) {
			// 64
			if (!(0. == this->_58)) {
				// 73
				if ((this->_88 & (1 << 8)) == 0) {
					extern double unknown;
					xmm2 = unknown;
					// 83
					goto _f110;
				} // 85
				  // 95 call
				objc_msgSend((CALayer*)this->_10, "contentsScale");
				xmm2 = (double&)this->_50;		// via xmm0;
				xmm0 = (double&)this->_50;
			_f110:
				xmm3 = 0.;
				xmm1 = (double&)this->_58;
				// 122
				if (!((double&)this->_50 < 0.)) {		// via xmm0, xmm3
					// 128
					if (!(this->_58 < 0.)) {			// via xmm1, xmm3
						xmm3 = xmm2 * xmm2 * this->_50 * this->_58;			// scaled_width * scaled_height
						// 154
						extern double def_prop_atoms_off_38;
						if (xmm3 <= def_prop_atoms_off_38)					// defines_property(unsigned int)::atoms + 38
							goto _f225;
					} // 156
				} // 156

				  // 185 call
				  // %rdi = @"-[%@ display]: Ignoring bogus layer size (%f, %f), contentsScale %f, backing store size (%f, %f)"
				NSLog(@ "-[%@ display]: Ignoring bogus layer size(%f, %f), contentsScale %f, backing store size(%f, %f)", this->_10, this->_50, this->_58, xmm2, this->_50 * xmm2, this->_58 * xmm2);
			} // 190
		} // 190
	_b190:
	_b190:
		return objc_msgSend((CALayer*)this->_10, "setContents:", 0);
	_f225:
		/***
		* xmm0 is this->_50, width;
		* xmm1 is this->_58, height;
		* xmm2 is scale.
		*/
		scale = xmm2;
		extern double rip_0x38ecf;
		extern double rip_0x38e9d;
		(double&)_88 = xmm2;
		(double&)_90 = xmm1;
		// 253 call
		r15d = (int)floor(this->_50 * scale + rip_0x38ecf);				// width
		// 287 call
		r12d = (int)floor(this->_58 * scale + rip_0x38e9d);				// height
		// 295
		if (r15d <= 0)
			// goto _b190; inline
			return objc_msgSend((CALayer*)this->_10, "setContents:", 0);
		// 305
		if (r12d <= 0)
			// goto _b190; inline
			return objc_msgSend((CALayer*)this->_10, "setContents:", 0);
		rax = r12d * r15d;
		// 319
		if (!((r12d * r15d) > 0x3ff)) {				// via eax
			// 335 call
			// %rsi = "isOpaque"
			rax = (uint32_t) (bool)objc_msgSend((CALayer*)this->_10, "isOpaque");
			_90 = edi = (uint32_t)rax + (uint32_t)rax + 1;
			// 357 call
			_88 = CA::Render::format_rowbytes((unsigned int)((uint32_t)rax + (uint32_t)rax + 1), (unsigned int)r15d);
			r13d = r12d;
			// 378 call
			rax = CA::Render::image_data_size((unsigned long)_88, (unsigned int)r12d);
			// 390 call
			r12 = CA::Render::aligned_calloc((unsigned long)rax, (void**)&_30);
			// 401
			if (!(cond_401 = (0 == r12))) {
				// 412 call
				// 420 call
				_bc = r15d;
				r15 = (CGColorSpaceRef)CGColorSpaceRetain(CAGetColorSpace(0x4));
				_a0 = r15;
				_98 = r13d;
				// 472 call
				r13 = (CGBitmapContextRef)CAGetCachedCGBitmapContext((void*)r12, (unsigned int)r15d, (unsigned int)r13d, (unsigned int)_90, (unsigned int)_88, (CGColorSpaceRef)_a0);
				// 483 call
				CGColorSpaceRelease((CGColorSpaceRef)r15);
				// 491
				if (!(cond_491 = (0 == r13))) {
					// 513 call
					this->prepare_context_for_drawing((CGContext*)r13, true, true);;
					// 518 call
					CA::Transaction::ensure_compat();;
					// 534 call
					rax = this->layer_being_drawn((CA::Transaction*)CA::Transaction::ensure_compat(), (unsigned int)0x800000);;
					// 552 call
					// %rsi = "drawInContext:"
					objc_msgSend((CALayer*)rax, "drawInContext:", (CGContext*)r13);
					// 561 call
					CAReleaseCachedCGContext((CGContext*)r13);
					// 573 call
					CA::Render::aligned_protect((void const*)r12, (void*)_30);
					// 585 call
					r12 = (CGDataProvider*)CA::Render::aligned_copy_data_provider((void const*)r12, (void*)_30);
					_a8 = (int64_t)(int32_t&)_bc;
					_98 = (int64_t)(int32_t&)_98;
					r15d = _90;
					// 631 call
					_b0 = CA::Render::format_bpc((unsigned int)_90);
					// 648 call
					r13d = CA::Render::format_bpp((unsigned int)_90);
					// 659 call
					(uint32_t&)_f0 = CA::Render::format_bitmap_info(unsigned int);;
					_e8 = r12;				// 0x8(%rsp)
					_e0 = 0;
					(uint32_t&)_c8 = 1;
					(uint32_t&)_c0 = 0;		// 0x20(%rsp)
					// 735 call
					// CGImageCreate(scaled_width, scaled_heghit, bpc, bpp, rowbytes, colorspace);
					r15 = (CGImageRef)CGImageCreate(_a8, _98, _b0, r13, _88, _a0);
					// 746 call
					CGDataProviderRelease((CGDataProvider*)r12);
					// 764 call
					// %rsi = "setContents:"
					objc_msgSend((CALayer*)this->_10, "setContents:", (CGImageRef)r15);
					// 773 call
					CGImageRelease((CGImageRef)r15);
					eax = (int32_t)this->_84;
					// 784
					// goto _f1653; inline
					this->_84 = eax & 0xffffdfff;
					return;
				}
				else {
					// goto _f1490; inlilne
					// 1497 call
					CA::Render::aligned_free((void const*)r12, (void*)_30);;
					// 1502
					// goto _f1664; inline
					return;
				}
			} // 1664, splitted into (401, 784), (789, 1664)
			else {
				// goto _f1664; inline
				return;
			}
		} // 789
		 

#if 0
		// gen by hand.
		// split (401, 1664) into (401, 784), (789, 1664)
		// split (491, 1490) into (491, 784), (789, 1490)
		if (((_98 * _bc) > 0x3ff)	// 319
			|| !cond_401) {	// 401
			if (cond_491) {	// 491
#else
		else {
			/***
			* from 319
			* r15d is scaled width
			* r12d is scaled height
			*/
#endif
			/***
			* _90 is reused, for temporary to content;
			*/
				// 789 start.
				_98 = r12d;
				// 796 call
				_a0 = (CA::Transaction*)CA::Transaction::ensure_compat();
				// 811 call
				((CA::Transaction*)_a0)->lock();;
				// 826 call
				// %rsi = "contents"
				r13 = objc_msgSend((CALayer*)this->_10, "contents");
				// 838
				if (0 != r13) {
					// 843 call
					r12 = (CFTypeID)CFGetTypeID(r13);
					// 851 call
					;
					// 859
					if (CABackingStoreGetTypeID() == r12) {
						// 864 call
						_90 = CFRetain(r13);
						// 876
						goto _f971;
					} // 878
				} // 878
				else {
					// 878 call
					r12 = (id)CABackingStoreCreate();
					_90 = r12 & 0xffffffff00000000;
					// 898
					if (0 != r12) {
						// 905 call
						// 913 call
						_a8 = r13;
						r13 = (CGColorSpaceRef)CGColorSpaceRetain(CAGetColorSpace());
						// 934 call
						CABackingStoreSetColorSpace(r12, (CGColorSpaceRef)r13);
						// 949 call
						CGColorSpaceRelease((CGColorSpaceRef)r13);
						r13 = _a8;
						// 959 call
						CABackingStoreInvalidate((id)r12);
						_90 = r12;				// a content created by CABackingStoreCreate
					} // 971
				} // 971
			_f971:
				/****
				* r13 is [(CALayer*)this->_10 content];
				* _a0 is transaction;
				*/
				_a8 = r13;
				r12 = _a0;
				edi = 0;
				// 988 call
				// %rsi = "drawsAsynchronously"
				if ((bool)objc_msgSend((CALayer*)this->_10, "drawsAsynchronously") == true // 1003 to 1027
					|| !((bool)objc_msgSend((CALayer*)this->_10, "acceleratesDrawing") == false)) { // 1025
					// 1027 start.
					edi = 0x10;
				} // 1032
				  // 1032 call
				r13d = CABackingStoreSetDefaultAccelFlags(edi);
				_b0 = 0;
				  // 1054
				if (0x10 != r13d) {
					_b0 = this->_84 << 0x14 >> 0x1f;
					// 1090 call
					this->mark((CA::Transaction*)r12, (unsigned int)0x2, (unsigned int)0x4);;
				} // 1095
				  // 1098 call
				((CA::Transaction*)r12)->unlock();;				// couple with op in offset 811
				  // 1111 because the end of container should jmp and its'end is beyond.
				if (0 == _90)
					// goto _f1664; inline
					return;
				// 1127 call
				// %rsi = "isOpaque"
				// 1135
				if (!((bool)objc_msgSend((CALayer*)this->_10, "isOpaque") == false)) {
					r13d |= 1;
				} // 1143
				else {
					// 1153 call
					// %rsi = "clearsContext"
					r13d = ((bool)objc_msgSend((CALayer*)this->_10, "clearsContext"))
								? r13d | 0x2 : r13d;
				} // 1171;
				_b8 = &this->_28;
				  // 1187 call
				r12d = ((bool)_CFExecutableLinkedOnOrAfter((unsigned int)0x3e9)) 
							? r13d : r13d | 0x2;
				// 1215 call
				// %rsi = "minificationFilter"
				;
				// 1226 call
				eax = CAInternAtom(objc_msgSend((CALayer*)this->_10, "minificationFilter"), 0);
				  // 1236
				if (!(0 != eax)) {
					// 1248 call
					// %rsi = "drawsMipmapLevels"
					eax = (uint32_t) !(bool)objc_msgSend((CALayer*)this->_10, "drawsMipmapLevels");
					eax <<= 3;
					eax |= r12d | 0x4;
					r12d = eax;
					//x_blame_allocations;;
				} // 1274
				extern double defines_property_atoms_46;					// defines_property(unsigned int)::atoms + 46
				xmm0 = (double&)_88;			// rowbytes
				r13d = r12d | 0x40;
				r13d = ((double&)_88 <= defines_property_atoms_46)
						? r12d : r12d | 0x40;
				eax = ~(this->_4 << 0xf) & 0x80 | r13d;
				r12 = _a0;
				rdx = 0;
				if (((CA::Transaction*)r12)->_50 != 0)
					rdx = (CA::GenericContext*)&((CA::Transaction*)r12)->_50->_b8;
				/***
				* constructure of _NSConcreteStackBlock
				*/
				struct _NSConcreteStackBlock;
				extern void* __block_descriptor_tmp;
				extern objc_object* _NSConcreteStackBlock;
				extern void (*___ZN2CA5Layer8display_Ev_block_invoke)(struct _NSConcreteStackBlock*);
				_80 = rcx = (Class) _NSConcreteStackBlock;
				_78 = 0xc0000000;
				_74 = 0x0;
				_70 = ___ZN2CA5Layer8display_Ev_block_invoke;
				_68 = __block_descriptor_tmp;
				_60 = this;								// pravite stack
				_58 = _90;								// an object created by CABackingStoreCreate;
				_50 = rdx;								// CA::GenericContext*
				_48 = r15d;								// scaled width
				r15 = _90;								// CABackingStore*
				_44 = (uint32_t&)_98;					// scaled height
				_40 = eax;
				_3c = (uint32_t&)_b0;
				  // 1455 call
				  // %rdi = backing_blame_callback(char*, unsigned long, void*)
				x_blame_allocations((void(*)(char*, unsigned long, void*))&backing_blame_callback,
									_b8, (struct _NSConcreteStackBlock*)&_80);
				  // 1467
				if (_90 == _a8)
					/**
					* verify whether the content is a new CABackingStore or the content belongs to CALayer.
					*/
					goto _f1507;
				// 1482 call
				// %rsi = "setContents:"
				objc_msgSend((CALayer*)this->_10, "setContents:", _90);
				// 1488 end.
				// goto _f1615; inline
				// 1618 call
				CFRelease((id)_90);
				eax = this->_84;
				if ((r13d & 0xff & 0x4) == 0) {
					eax = 0xffffefff;
				}
				else {
					eax |= 0x1000;
				}
				this->_84 = eax;
				return;
			} // 1490
#if 0
			else {
#else 
		_f1490:		// from 401
			/***
			* this piece of codes, range between 1490 to 1507, should be inline into 401
			*
			*/
#endif
			/****
			* r12 is a buffer, CA::Render::aligned_alloc
			*
			*/
				// 1497 call
				CA::Render::aligned_free((void const*)r12, (void*)_30);;
				// 1502
				// goto _f1664; inline
				return;
			_f1507:		// from 1467
				/****
				* r12 is transaction
				*
				*/
				// 1510 call
				((CA::Transaction*)r12)->lock();;
				// 1530 call
				rax = this->begin_change((CA::Transaction*)r12, (unsigned int)0x63, (objc_object*&)_38);;
				// 1554
				if (!(rax < 0)
					&& !(this->_a8[rax] == 0)) {
					rax = &this->_a8[rax];
				} // 1566
				else {
					// 1572 call
					rax = (uint32_t*) this->thread_flags_((CA::Transaction*)r12);
				} // 1579
				*(uint32_t*)rax |= 0xfffffeff;
				// 1602 call
				this->end_change((CA::Transaction*)r12, (unsigned int)0x63, (objc_object*)_38);;
				// 1610 call
				((CA::Transaction*)r12)->unlock();;
#if 0
			} // 1615
#endif
		_f1615:
			// 1618 call
			CFRelease((id)r15);
			eax = this->_84;
			// 1633
			if ((r13d & 0xff & 0x4) == 0) {
				eax = 0xffffefff;
			} // 1642
			else {
				eax |= 0x1000;
			} // 1647
			this->_84 = eax;
			return;
#if 0
		} // 1664
#endif
	} // 1664
}


void foo()
{
	// 30
	if (!) {
		// 53
		if (!) {
			// 64
			if (!) {
				// 73
				if (!) {
					// 83
					goto _f110;
				} // 85
				  // 95 call
				  // %rsi = "contentsScale"
				objc_msgSend;;
			_f110:
				// 122
				if (!) {
					// 128
					if (!) {
					} // 156
				} // 156
				  // 185 call
				  // %rdi = @"-[%@ display]: Ignoring bogus layer size (%f, %f), contentsScale %f, backing store size (%f, %f)"
				NSLog;;
			_b190:
			_b190:
			} // 190
		} // 190
		  // 154
		if (!) {
			// 185 call
			// %rdi = @"-[%@ display]: Ignoring bogus layer size (%f, %f), contentsScale %f, backing store size (%f, %f)"
			NSLog;;
		} // 225
		  // 253 call
		floor;;
		// 287 call
		floor;;
		// 295
		if ()
			goto _b190;
		// 305
		if ()
			goto _b190;
		// 319
		if (!) {
			
			goto _f1653;
		} // 789
		  // 401
		if (!) {
			// 412 call
			CAGetColorSpace;;
			// 420 call
			CGColorSpaceRetain;;
			// 472 call
			CAGetCachedCGBitmapContext;;
			// 483 call
			CGColorSpaceRelease;;
			// 491
			if (!) {
				// 513 call
				CA::Layer::prepare_context_for_drawing(CGContext*, bool, bool);;
				// 518 call
				CA::Transaction::ensure_compat();;
				// 534 call
				CA::Layer::layer_being_drawn(CA::Transaction*, unsigned int);;
				// 552 call
				// %rsi = "drawInContext:"
				objc_msgSend;;
				// 561 call
				CAReleaseCachedCGContext;;
				// 573 call
				CA::Render::aligned_protect(void const*, void*);;
				// 585 call
				CA::Render::aligned_copy_data_provider(void const*, void*);;
				// 631 call
				CA::Render::format_bpc(unsigned int);;
				// 648 call
				CA::Render::format_bpp(unsigned int);;
				// 659 call
				CA::Render::format_bitmap_info(unsigned int);;
				// 735 call
				CGImageCreate;;
				// 746 call
				CGDataProviderRelease;;
				// 764 call
				// %rsi = "setContents:"
				objc_msgSend;;
				// 773 call
				CGImageRelease;;
				// 796 call
				CA::Transaction::ensure_compat();;
				// 811 call
				CA::Transaction::lock();;
				// 826 call
				// %rsi = "contents"
				objc_msgSend;;
				// 838
				if (!) {
					// 843 call
					CFGetTypeID;;
					// 851 call
					CABackingStoreGetTypeID;;
					// 859
					if (!) {
						// 864 call
						CFRetain;;
						// 876
						goto _f971;
						// 878 call
						CABackingStoreCreate;;
					} // 878
					  // 878 call
					CABackingStoreCreate;;
				} // 878
				  // 878 call
				CABackingStoreCreate;;
				// 898
				if (!) {
					// 905 call
					CAGetColorSpace;;
					// 913 call
					CGColorSpaceRetain;;
					// 934 call
					CABackingStoreSetColorSpace;;
					// 949 call
					CGColorSpaceRelease;;
					// 959 call
					CABackingStoreInvalidate;;
				_f971:
				} // 971
				  // 988 call
				  // %rsi = "drawsAsynchronously"
				objc_msgSend;;
				// 1003
				if (!) {
					// 1015 call
					// %rsi = "acceleratesDrawing"
					objc_msgSend;;
				} // 1027
				  // 1025
				if (!) {
					// 1032 call
					CABackingStoreSetDefaultAccelFlags;;
				} // 1032
				  // 1032 call
				CABackingStoreSetDefaultAccelFlags;;
				// 1054
				if (!) {
					// 1090 call
					CA::Layer::mark(CA::Transaction*, unsigned int, unsigned int);;
				} // 1095
				  // 1098 call
				CA::Transaction::unlock();;
				// 1127 call
				// %rsi = "isOpaque"
				objc_msgSend;;
				// 1141
				goto _f1171;
				// 1153 call
				// %rsi = "clearsContext"
				objc_msgSend;;
			_f1171:
				// 1187 call
				_CFExecutableLinkedOnOrAfter;;
				// 1215 call
				// %rsi = "minificationFilter"
				objc_msgSend;;
				// 1226 call
				CAInternAtom;;
				// 1248 call
				// %rsi = "drawsMipmapLevels"
				objc_msgSend;;
				// 1455 call
				// %rdi = backing_blame_callback(char*, unsigned long, void*)
				x_blame_allocations;;
				// 1482 call
				// %rsi = "setContents:"
				objc_msgSend;;
				// 1488
				goto _f1615;
			} // 1490
			  // 1111
			if (!) {
				// 1127 call
				// %rsi = "isOpaque"
				objc_msgSend;;
				// 1135
				if (!) {
				} // 1143
				  // 1153 call
				  // %rsi = "clearsContext"
				objc_msgSend;;
				// 1187 call
				_CFExecutableLinkedOnOrAfter;;
				// 1215 call
				// %rsi = "minificationFilter"
				objc_msgSend;;
				// 1226 call
				CAInternAtom;;
				// 1236
				if (!) {
					// 1248 call
					// %rsi = "drawsMipmapLevels"
					objc_msgSend;;
				} // 1274
				  // 1455 call
				  // %rdi = backing_blame_callback(char*, unsigned long, void*)
				x_blame_allocations;;
				// 1467
				if (!) {
					// 1482 call
					// %rsi = "setContents:"
					objc_msgSend;;
					// 1497 call
					CA::Render::aligned_free(void const*, void*);;
					// 1502
					goto _f1664;
				} // 1507
				  // 1510 call
				CA::Transaction::lock();;
				// 1530 call
				CA::Layer::begin_change(CA::Transaction*, unsigned int, objc_object*&);;
				// 1554
				if (!) {
					// 1564
					goto _f1579;
				} // 1566
				  // 1572 call
				CA::Layer::thread_flags_(CA::Transaction*);;
			_f1579:
				// 1602 call
				CA::Layer::end_change(CA::Transaction*, unsigned int, objc_object*);;
				// 1610 call
				CA::Transaction::unlock();;
			_f1615:
				// 1618 call
				CFRelease;;
				// 1633
				if (!) {
					// 1640
					goto _f1647;
				} // 1642
			_f1647:
			_f1653:
			_f1664:
			} // 1664
		} // 1664
	} // 1664
}