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

void CABackingStoreUpdate_(CABackingStore* content, unsigned int width, unsigned int height,
							unsigned int flag1, unsigned int flag2, 
							void(*backing_callback)(CGContext*, void*),
	CA::Layer* layer, CA::GenericContext* context)
{
	// 0x8(%rbp) is ret-rip, 0x10(%rbp) is 1st argument, 0x18(%rbp) is 2nd argument; 
	// _1c0 to _30 total 0x198 bytes, 41 quadwords for local variables;

	// CABackingStoreBuffer::_8 is CGColorSpace
	// CABackingStoreBuffer::_18 is region

	uint32_t _104;

	r14 = content;
	_d8 = width;
	r13 = height;
	_148 = backing_callback;
	r12d = flag1;
	r15 = (pthread_mutex_t*)&content->_10;

	// 50 call
	pthread_mutex_lock((pthread_mutex_t*)&content->_10);
	rbx = content->_168;
	// 65
	if (0 != content->_168) {
		// 67 call
		// 75
		if (pthread_self() == content->_168) {
			// goto _f2903;	inline
			// 2906 call
			pthread_mutex_unlock((pthread_mutex_t*)&content->_10);						// via r15, is _138, which is &content->_10
			return;
		}

		// 89
		if (0 != content->_168) {
			rbx = (pthread_cond_t*)&content->_50;
		_b95:
			// 101 call
			pthread_cond_wait((pthread_cond_t*)&content->_50, (pthread_mutex_t*)&content->_10);
			// 114
			if (0 != content->_168)
				goto _b95;
		} // 116
	} // 116
	cx = (short&)content->_174;
	_30 = 0;
	// 146
	if (!(width != content->_80)) {			// via _d8
		// 159
		if (!(height != content->_88)) {		// via r13
			_f8 = height;						// via r13;
			ebx = (flag1 >> 0xa) & 0x1;
			// 176
			if ((flag1 >> 0xa) & 0x1)
				goto _f311;
			eax = 0;
			// 192
			if ((short&)content->_174 & (2 << 8)) {				// via cx
				// goto _f3214; inline #1
				// 3216
				if (bl != 0)
					goto _b311;
				// 3225
				if (rax == 0) {
					// goto _b2903;	inline #2
					// 2906 call
					pthread_mutex_unlock((pthread_mutex_t*)&content->_10);						// via r15, is _138, which is &content->_10
					return;
				}
				// 3231
				goto _b311;
			}
			rdi = content->_150;
			eax = 0;
			// 215
			if (content->_150 == 0) {					// via rdi
				goto _f3214;
				// 3216
				if (bl != 0)
					goto _b311;
				// 3225
				if (rax == 0) {
					// goto _b2903;	inline #2
					// 2906 call
					pthread_mutex_unlock((pthread_mutex_t*)&content->_10);						// via r15, is _138, which is &content->_10
					return;
				}
				// 3231
				goto _b311;
			}
			// 225 call
			CGSBoundingShapeGetRegion(content->_150, (CGSRegionObject**)&_38);
			// 234
			if (flag1 & 0xff & 0x80) {					// via r12b
				// goto _f2929; inline
				/**
				* _70 is a transform { m11, m12, m21, m22, sx, sy }
				*/
				_70 = 0x3ff0000000000000;
				_60 = 0;
				_68 = 0;
				_58 = -0x4010000000000000;
				_50 = 0;
				rbx = _f8;
				xmm0 = (float&)height;					// via _f8;
				extern double rip_0x1432aa;
				extern double rip_0x1432b2[2];
				extern float rip_0x1432c1;
				xmm0 = (double)(float&)height - rip_0x1432b2[0] + rip_0x1432aa - rip_0x1432b2[1];
				(double&)_f0 = (double&)_e8 = (double)xmm0;
				(double&)_48 = (double)xmm0;
				// 3046 call
				CGSTransformRegion((CGSRegionObject*)_38, &_70, rip_0x1432c1, (CGSRegionObject**)&_40);
				// 3055 call
				CGSReleaseRegion((CGSRegionObject*)_38);
				xmm2._pd[0] = _f0;
				xmm2._pd[1] = _e8;
				_38 = (CGSRegionObject*)_40;
				// 3076 natural flow
			}
			else {
				rdi = (CGSRegionObject*)_38;									// a CGSRegionObject which just got, _38 is poision, _30 is size
				rbx = height;								// via _f8;
				xmm2 = (float&)rbx;
				extern double rip_0x143d5b;
				extern double rip_0x143d63[2];
				// <+256>:  punpckldq 0x143d5b(%rip), %xmm2
				//	<+264> : subpd  0x143d63(%rip), %xmm2
				//	<+272> : haddpd %xmm2, %xmm2
				(double&)xmm2 = (double)(float&)height - rip_0x143d63[0] + rip_0x143d5b - rip_0x143d63[1];
				// 276 goto _f3076; inline
			}
			// inline begin at
			// 3076
			_f8 = height;								// via rbx
			xmm0 = width;								// via _d8
			extern double rip_0x143248;
			extern double rip_0x143250[2];
			(double&)xmm0 = width - rip_0x143250[0] + rip_0x143248 - rip_0x143250[1];
			CGSRect& rect = *(CGSRect*)&_90;
			_90 = _88 = 0;
			(double&)_80 = (double)xmm0;				// transformed width
			(double&)_78 = (double)xmm2;				// transformed height

			// 3140 call
			;
			// 3149
			if (!((bl = (bool)CGSRectInRegion((CGSRegionObject*)_38, (CGSRect*)&_90)) == true)) {
				// 3166 call
				CGSIntersectRegionWithRect((CGSRegionObject*)_38, (CGSRect*)&_90, (CGSRegionObject**)&_30);
				// 3175 call
				;
				// 3182
				if (!(CGSRegionIsEmpty((CGSRegionObject*)_30) == false)) {
					// 3188 call
					CGSReleaseRegion((CGSRegionObject*)_30);
					_30 = 0;
				} // 3201
			} // 3201
			// 3205 call
			CGSReleaseRegion((CGSRegionObject*)_38);
			rax = _30;
			  // 3216
			if (bl == true)
				goto _b311;
			// 3225
			if (rax == 0) {
				// goto _b2903;		inline
				// 2906 call
				pthread_mutex_unlock((pthread_mutex_t*)&content->_10);						// via r15, is _138, which is &content->_10
				return;
			}
			// 3231
			goto _b311;
		} // 281
	} // 281

	content->_80 = width;				// via _d8
	content->_88 = height;				// via r13
	_f8 = height;						// via r13
	bl = true;
_b311:
_b311:
_f311:	// from 176
	_110 = rbx;							// ? (bool)
	_138 = (pthread_mutex_t*)&content->_10;		// via r15
	eax = (flag1 & 0x1) * 2 + 1;				// via r12d
	_104 = eax;

	r15 = (CABackingStoreBuffer**)&content->_138;
	rcx = (CABackingStoreBuffer*)content->_138;
	_130 = content;							// via r14
	rax = (CA::Render::Shmem**)&content->_138->_10;
	rdi = (CA::Render::Shmem*)content->_138->_10;

	// 373
	if (content->_138->_10 == 0) {
		// goto _f689; inline
		{
		_f689:
			_f0 = flag1;						// via r12d
			r13 = (CA::Render::Shmem**)&content->_138->_10;		// via rax
			_118 = (CA::Render::Shmem**)&content->_138->_10;	// via rax
			_100 = (CABackingStoreBuffer*)content->_138;								// via rcx
			rdx = (CABackingStoreBuffer*)content->_138;								// via rcx
			r12 = (CABackingStoreBuffer**)&content->_138;								// via r15
			r14b = al = _110;
			// 729
			goto _f842;
		}
	}

	r14d = flag1;						// via r12d
	r13 = (CA::Render::Shmem**)&content->_138->_10;			// via rax
	_118 = (CA::Render::Shmem**)&content->_138->_10;
	rbx = (CABackingStoreBuffer*)content->_138;				// via rcx
	_100 = (CABackingStoreBuffer*)content->_138;
	r12 = (CABackingStoreBuffer**)&content->_138;				// via r15;

	/***
	* this loop set all the shmem of buffer of content to volatile(0)
	*/
_b416:					// from 678
	// 420 call
	;
	// 427
	if (true == ((CA::Render::Shmem*)content->_138->_10)->set_volatile(false, int(0))) {
		// 440
		if ((rax = *(CA::Render::Shmem**)r13) == 0) {
			// goto _f763; inline #0
			// 763

			// 773
			// goto _f839; inline #1
			// 839
			goto _f842;
		}
		else if (
			// 459
			!((*(CA::Render::Shmem**)r13)->_18->_10 != ((flag1 & 0x1) * 2 + 1))			// via _104
			// 475
			&& !((*(CA::Render::Shmem**)r13)->_18->_14 != width)						// via _d8
			// 491
			&& !((*(CA::Render::Shmem**)r13)->_18->_18 != height)						// via _f8
			// 518
			&& !((*(CA::Render::Shmem**)r13)->_18->_1c > 0x1 != (!flag1))				// via r14d
			) {
			// 533
			rdx = (CABackingStoreBuffer*)rbx;						// content->_138 at first loop;		// as input @ _f645
			if (!(al = (*(CA::Render::Shmem**)r13)->_18->_0 != 0)) {		// as input @ _f645	
				// 539
				if (rdx->_0 != 0)
					goto _f645;
				rbx = rdx;
				edx = rdx->_20;
				++edx;

				// 568 call
				CABackingStoreSynchronize((CABackingStore*)content, (CA::GenericContext*)context, (unsigned int)(rdx->_20 + 1), int(0x1e));
				rcx = *(CA::Render::Shmem**)r13;
				al = true;
				// 582
				if (!(*(CA::Render::Shmem**)r13 == 0)) {
					al = (*(CA::Render::Shmem**)r13)->_18->_0 == 0;
				} // 594
				al ^= true;											// as input @ _f645
				rdx = (CABackingStoreBuffer*)rbx;					// as input @ _f645
				  // 599
				goto _f645;
			}
			else { // 601
				   // 608
				if (!((CABackingStoreBuffer*)rdx == (CABackingStoreBuffer*)content->_138)) {				// via _100
					// 614
					if (!(rdx == 0)) {
						rbx = rdx;
						edx = rbx->_20;
						// 635 call
						CABackingStoreSynchronize((CABackingStore*)content, (CA::GenericContext*)context, (unsigned int)rbx->_20, int(0));
						rdx = 0;				// as input @ _f645
						al = true;				// as input @ _f645
					} // 645
				} // 645
			} // 645
			/***
			* input: al = ?	(bool)
			* input: rdx = ? (CABackingStoreBuffer*)
			*/
		_f645:	// from 539
		_f645:	// from 599
			// 647
			if (!(al == false)) {
				// 655
				if ((rcx = ((CABackingStoreBuffer*)rdx)->_0) == 0) {
					// goto _f775; inline #0
					// inline
					// 775
					r14b = true;
					// 785
					if (!(rbx == _100)) {
						rax = _110;
						r14b = (bool&)rax;
					} // 797
					rbx = rdx;						// save rdx
					  // 803 call
					CABackingStoreDeleteBuffer((CABackingStoreBuffer*)rdx);
					// 808 call
					;
					// 816
					if (!((CAGetDebugFlags() & (0x20 << 8)) == 0)) {
						// 834 call
						// %rdi = "CoreAnimation: triple buffered backing store %p\n"
						x_log("CoreAnimation: triple buffered backing store %p\n", content);
					} // 839
					rdx = rbx;						// restore rdx
					// 842 natural flow
					goto _f842;
				}
				// 659
				if (al == false) {
					// goto _f719; inlilne
					{
						r14b = al = (bool&)_110;
						// 729
						goto _f842;
					}
				}
				r12 = rdx;
				r13 = &rdx->_0->_10;			// via 0x10(%rcx)
				rbx = rdx->_0;					// via rcx
				// 678
				if (((CABackingStoreBuffer*)rdx)->_0->_10 != (CA::Render::Shmem*)0)
					goto _b416;					// loop
				rdx = (CABackingStoreBuffer*)((CABackingStoreBuffer*)rdx)->_0;					// via rcx
																								// as input @ _f842
				// 687
				// goto _f719; inlilne
				{
					r14b = al = (bool&)_110;
					// 729
					goto _f842;
				}
			}
#if 0
			_f719:
				 // 729
				 goto _f842;
#endif
		}	// 731
		else {
			// inline begin at
			// 731
			r14b = true;
			// 741
			if (!(rbx == _100)) {
				r14b = al = (bool&)_110;
			} // 753
			  // 756 call
			CABackingStoreDeleteBuffer((CABackingStoreBuffer*)rbx);

			// 761 goto _f839; inline #1
			// 839
			rdx = (CABackingStoreBuffer*)rbx;
			goto _f842;
		}
	}
	else { // 731	
		   // inline begin at
		   // 731
		r14b = true;
		// 741
		if (!(rbx == _100)) {
			r14b = al = (bool&)_110;
		} // 753
		  // 756 call
		CABackingStoreDeleteBuffer((CABackingStoreBuffer*)rbx);
		// 761 goto _f839; inline #1
	  // 839
		rdx = (CABackingStoreBuffer*)rbx;
		goto _f842;
	}
#if 0
	_f719:
		 // 729
		 goto _f842;
	 _f731:
		 // 741
		 if (!) {
		 } // 753
		 // 761
		 goto _f839;
	 _f763:
		 // 773
		 goto _f839;
	 _f775:
		 // 785
		 if (!) {
		 } // 797
		 // 816
		 if (!) {

		 } // 839
	 _f839:
	 _f839:
#endif
_f842:
	/**
	* if loop from _b311, r15 is (CABackingStoreBuffer**)&content->_138
	*/
	/***
	* input: rdx = ? (CABackingStoreBuffer*)
	*/
	// 845
	if (!((CABackingStoreBuffer*)rdx == *(CABackingStoreBuffer**)r15)) {
		*(CABackingStoreBuffer**)r12 = (CABackingStoreBuffer*)((CABackingStoreBuffer*)rdx)->_0;
		((CABackingStoreBuffer*)rdx)->_0 = *(CABackingStoreBuffer**)r15;
		*(CABackingStoreBuffer**)r15 = (CABackingStoreBuffer*)rdx;
		r15 = (pthread_mutex_t*)&content->_10;			// via _138;
		r12 = (CABackingStore*)content;					// via _130;
		// 877
		goto _f902;
	} // 879
	r15 = (pthread_mutex_t*)&content->_10;			// via _138;
	r12 = (CABackingStore*)content;					// via _130;
	// 896
	if ((CABackingStoreBuffer*)rdx == 0) {
		// goto _f2903;	inline
		// 2906 call
		pthread_mutex_unlock((pthread_mutex_t*)&content->_10);						// via r15, is _138, which is &content->_10
		return;
	}


_f902:
	// 909
	if (!(*(CA::Render::Shmem**)r13 == 0)) {
		_110 = *(CA::Render::Shmem**)r13;			// ?
		// 918
		goto _f1083;
	} // 923
	al = r14b;
	r14b = true;
	// 936
	if (!((CABackingStoreBuffer*)rdx == _100)) {
		r14b = al;
	} // 941
	// 947 call
	CABackingStoreDeleteBuffer((CABackingStoreBuffer*)rdx);
	eax = _f0;										// _f0 is flag1 at the beginning, but the value changed in loop
	ecx = 0x1;
	// 965
	if (!((_f0 & 0x4) == 0)) {
		// 973 call
		rax = CA::Render::format_mipmap_min_size((unsigned int)((flag1 & 0x1) * 2 + 1));				// expression via _104
		rsi = height;								// via _f8;
		ecx = 0x1;
		// 992
		if (!(esi > eax)) {
			rdx = width;							// via _d8;
			if (edx <= eax)
				goto _f1028;
			// 1005
			goto _f1014;
		} // 1007
		rdx = width;							// via _d8;
	_f1014:
	_b1014:
	_b1014:
		++ecx;
		edx >>= 1;
		esi >>= 1;
		// 1022
		if (esi > eax)
			goto _b1014;
		// 1026
		if (edx > eax)
			goto _b1014;
	} // 1028
_f1028:
	/***
	* ecx is the counter of loop labeled _b1014;
	*/
	edi = (flag1 & 0x1) * 2 + 1;					// 	expression via _104
	rsi = width;									// via _d8
	rdx = height;									// via _f8;
	// 1048 call
	*(CA::Render::Shmem**)r13 =
		CA::Render::Shmem::new_bitmap((unsigned int)((flag1 & 0x1) * 2 + 1),
			(unsigned int)width, (unsigned int)height, (unsigned int)ecx);		// ecx is multipler
	rdx = (CABackingStoreBuffer*)rbx;
	// 1063
	if (*(CA::Render::Shmem**)r13 == 0) {
		// goto _f2903;	inline
		// 2906 call
		pthread_mutex_unlock((pthread_mutex_t*)&content->_10);						// via r15, is _138, which is &content->_10
		return;
	}
	_110 = *(CA::Render::Shmem**)r13;				// save r13
	_f0 = (int32_t)-0x3;
_f1083:
	r13b = r14b;
	// 1098
	if (!(((CABackingStoreBuffer*)rdx)->_8 == content->_90)) {			// via r12, is _130, which is content
		r14 = (CABackingStoreBuffer*)rdx;
		// 1103 call
		CGColorSpaceRelease(((CABackingStoreBuffer*)rdx)->_8);			// CABackingStoreBuffer::_8 is CGColorSpace
		// 1116 call
		((CABackingStoreBuffer*)rdx)->_8 = CGColorSpaceRetain(content->_90);

		// 1139
		if (!(_100->_8 == ((CABackingStoreBuffer*)rdx)->_8)) {
			// 1148
			if (!((rdi = ((CABackingStoreBuffer*)rdx)->_18) == 0)) {
				r14 = (CABackingStoreBuffer*)rdx;
				// 1153 call
				CGSReleaseRegion(((CABackingStoreBuffer*)rdx)->_18);
				rdx = (CABackingStoreBuffer*)r14;
				((CABackingStoreBuffer*)rdx)->_18 = 0;
			} // 1169
		} // 1169
	} // 1169
	r15 = (CABackingStoreBuffer*)content->_138;
	// 1187
	if (!((rdi = content->_150) == 0)) {								// via r12
		rbx = (CABackingStoreBuffer*)rdx;
		// 1192 call
		CGSBoundingShapeReset(content->_150);
	} // 1200
	(uint16_t&)content->_174 = (uint16_t)content->_174 & 0xf8ff | 0x200;
	_178 = (CGSRegionObject*)((CABackingStoreBuffer*)rdx)->_18;
	r12b = r13b;
	_120 = r13b;
	r12b |= 1;
	// 1264
	if (!((rbx = (CABackingStoreBuffer*)content->_138) == 0)) {						// via r12 is content
		r15 = &_98;																	// as output region
		/***
		* <<LOOP>> #_b1273
		* iterator: rbx as CABackingStoreBuffer*
		* iterator intialization: content->_138
		*
		* discustion:
		*  I guess that the 'LOOP #_419' use rbx as iterator too.
		*  rdx = rbx`, which is the iterator of outer loop, 'LOOP #_419'
		*
		* CABackingStoreBuffer* rbx = (CABackingStoreBuffer*)content->_138;
		* do { ... } while (rbx = rbx->next);
		*/
	_b1273:
		r13 = &((CABackingStoreBuffer*)rbx)->_18;
		// 1280
		if ((CABackingStoreBuffer*)rdx == (CABackingStoreBuffer*)rbx) {					// check if the outer-loop-iter equals the inner-loop-iter
			// inline begin at
			// 1336
			r14 = rdx;															// save rdx
			// 1342 call
			CGSNewEmptyRegion(&((CABackingStoreBuffer*)rbx)->_18);				// via r13
			// 1347 goto _f1365; inline #1
			// 1365
			rdx = r14;															// restore rdx
			// 1368	end
		}	// 1289
		else if (!((rax = ((CABackingStoreBuffer*)rbx)->_18) == 0)) {			// via (%r13)
			r14 = (CABackingStoreBuffer*)rdx;									// save rdx
			// 1297
			if (r12b != 0) {
				/**
				* input: rax = *&((CABackingStoreBuffer*)rbx)->_18
				*/
				// inline begin at
				// 1349
				// 1352 call
				CGSReleaseRegion(((CABackingStoreBuffer*)rbx)->_18);			// via rax
				*&((CABackingStoreBuffer*)rbx)->_18 = 0;						// via (%r13)
				rdx = r14;														// restore rdx
				// 1368	end 
			}
			else {
				// 1297 next

				// 1309 call
				CGSUnionRegion(_30, ((CABackingStoreBuffer*)rbx)->_18, &_98);	// via r15 = &_98; rsi = rax
				// 1318 call
				CGSReleaseRegion(((CABackingStoreBuffer*)rbx)->_18);			// via (%r13)

				// 1334 goto _f1365; inline #1
				// 1365
				rdx = r14;														// restore rdx
				// 1368 end
			}
		} // 1368
		rbx = ((CABackingStoreBuffer*)rbx)->_0;
		// 1374
		if (((CABackingStoreBuffer*)rbx)->_0 != 0)								// via rbx
			goto _b1273;
	} // 1376

	/***
	*
	*
	*
	*/
	_140 = rdx;
	_a0 = 0;
	rax = _f8;								// height;
	r13 = _178;
	// 1415
	if (!(_100 == (CABackingStoreBuffer*)rdx)) {
		// 1424
		if (!(r12b == true)) {
			// 1433
			if (!(r13 == 0)) {
				// 1449 call
				CGSDiffRegion(_178, _30, &_a0);
				// 1454
				goto _f1594;
			} // 1459
			else {
				/***
				* I guess there is a object, whose type is region, like struct CGSRegion { CGRect, double, double }
				*
				*/
				extern float rip_0x1438a0;
				extern double rip_0x1438a4[2];
				xmm0 = (float&)_d8;					// widith;
				xmm1 = (float)rip_0x1438a0;
				// <+1475>: punpckldq %xmm1, %xmm0; xmm0[0..31] = xmm0[0..31], xmm0[32..63] = xmm1[0..31]
				xmm2 = (float)rip_0x1438a4;
				xmm3 = _f8;							// via rax, height
				(float&)_b0 = (double)(float&)_d8 - rip_0x1438a4[0] + rip_0x1438a0 - rip_0x1438a4[1];
				(float&)_a8 = (double)(float&)_f8 - rip_0x1438a4[0] + rip_0x1438a0 - rip_0x1438a4[1];
				// <+1512>: pxor   %xmm1, %xmm1
				// <+1516> : movdqa %xmm1, -0xc0(%rbp)
				(CGRect&)_c0 = { {0.f,0.f},{0.f,0.f} };

				// 1554 call
				CGSNewRegionWithRect((void*)&_c0, (void**)&_c8);
				// 1577 call
				CGSDiffRegion((void*)_c8, (void*)_30, (void**)&_a0);
				// 1589 call
				CGSReleaseRegion((void*)_c8);
			}
		_f1594:
			// 1601 call
			;
			// 1608
			if (!(CGSRegionIsEmpty((void*)_a0) == false)) {
				// 1617 call
				CGSReleaseRegion((void*)_a0);
				_a0 = 0;
			} // 1633
		} // 1633
	} // 1633
	// 1643
	if ((rcx = (CA::Render::Shmem*)_110) == 0) {
		// inline begin at
		// 1713
		// 1747
		goto _f2774;
	} // 1645
	else {
		r15 = ((CA::Render::Shmem*)rcx)->_18;
		// 1659
		if (_a0 == 0) {
			// inline begin at
			// 1752
			r13b = _120;
			r12 = content;					// _130;
			// 1766 end
		} // 1661
		else {
			rax = *(CA::Render::Shmem**)_118;
			r13b = true;
			r12 = content;					// _130
			// 1684
			if (!(*(CA::Render::Shmem**)_118 == 0)) {
				// inline begin at
				// 1684 next
				// 1696 call
				rbx = rcx;								// save rcx
				CA::Render::ShmemBitmap::copy_pixels((CA::Render::ShmemBitmap const*)((CA::Render::Shmem*)_110)->_18,
					(CGSRegionObject*)(*(CA::Render::Shmem**)_118)->_18);
				rcx = rbx;								// restore rcx
				r13b = _120;
				// 1711
				goto _f1766;
			}
		}
	}
_f1766:
	/**
	* input: r13b = ?
	*
	*/
	r13b &= true;
	ebx = flag1;							// via _f0
	// 1779
	if (!((flag1 & 0x2) == 0)) {
		eax = 0;
		rdx = (!r13b) ? 0 : _30;
		r14 = rcx;							// save rcx
		((CA::Render::ShmemBitmap*)r15)->fill_pixels((unsigned int)0, (CGSRegionObject*)((!r13b) ? 0 : _30));
		rcx = r14;							// restore rcx
		ebx &= 0xfffffffd;
	} // 1813
	r14d = ebx;								// flag1 or flag1 & 0xfffffffd
	_149 = r13b;
	content->_158 = (r13b) ? 0 : _30;			// r12 is _130; via 0x158(%r12)
	/**
	* rcx = (CA::Render::Shmem*)_110; see to 1463;
	*
	* from now on
	* _110 will be used as unsigned int flag.
	*/
	_100 = (CA::Render::ShmemBitmap*) ((CA::Render::Shmem*)_110)->_18;				// via rcx = _110;
	_110 = ((CA::Render::ShmemBitmap*)_100)->_1c;
	// 1867
	if (!(((CA::Render::ShmemBitmap*)_100)->_1c == 0)) {
		extern float rip_0x143702;
		extern double rip_0x143706[2];
		xmm2 = (double&)_d8;
		_160 = (double&)_d8 - rip_0x143706[0] + (float)rip_0x143702 - rip_0x143706[1];
		_170 = (double&)_f8 - rip_0x143706[0] + (float)rip_0x143702 - rip_0x143706[1];

	_b1945:
		rbx = (CA::Render::ShmemBitmap*)_100;
		// 1958 call
		_d8 = ((CA::Render::ShmemBitmap*)_100)->lod_width((unsigned int)r15d);
		// 1975 call
		r12d = ((CA::Render::ShmemBitmap*)_100)->lod_height((unsigned int)r15d);
		// 1989 call
		_f8 = ((CA::Render::ShmemBitmap*)_100)->lod_data((unsigned int)r15d);
		// 2007 call
		int rowbytes = rbx = ((CA::Render::ShmemBitmap*)_100)->lod_rowbytes((unsigned int)r15d);

		// 2018
		if (!(r15d == 0)) {
			// 2028
			if (!(r14b & 0x28)) {
				rowbytes = (_d8 > r12d) ? _d8 : r12d;
			} // 2054
			// 2048
			if (!(rowbytes > 0x7)) {
				_f0 = r14d;				// see to 1813
				r14d = r15 + 1;
				r13 = _100;
				_118 = -rbx;
				_124 = r12d;
				r12d = ((CA::Render::ShmemBitmap*)_100)->lod_width((unsigned int)r14d);

				int lod_height = ebx = ((CA::Render::ShmemBitmap*)_100)->lod_height((unsigned int)r14d);

				_120 = ((CA::Render::ShmemBitmap*)_100)->lod_data((unsigned int)r14d);

				int rowbytes = rbx = ((CA::Render::ShmemBitmap*)_100)->lod_rowbytes((unsigned int)r14d);

				CA::downsample_image((unsigned int)_104, (void const*)_120,
					(unsigned long)rowbytes, (unsigned long)r12d,
					(unsigned long)lod_height, (void*)_f8,
					(unsigned long)_118, 0., 0., (double)_d8, (double)_124, (unsigned int)0);
				// 2225
				goto _f2715;
			} // 2230
		} // 2230

		// 2234
		if (r14b & 0x20) {
			// goto _f3236; inline
			abort();
		}
			

		/**
		* _f8 is lod_data retrieved from CA::Render::ShmemBitmap
		* _d8 is lod_width retrieved from CA::Render::ShmemBitmap
		* r12d is lod_height retrieved from CA::Render::ShmemBitmap
		* rbx is lod_rowbytes retreived from CA::Render::ShmemBitmap
		* _104 is associated to flag1.
		*
		* discussion:
		* levels of details?
		*/
		// 2276 call
		r13 = (CGBitmapContext*)CAGetCachedCGBitmapContext(_f8, _d8, r12d, _104, rbx, (CGColorSpaceRef)_140->_8);			//  to be used at 2473, till 2703
		// 2287 
		if (r13 == 0) {
			// inline begin at
			// 2495
			_f0 = r14d;
			// 2502 
			goto _f2715;
		}
		else {
			// inline begin at
			// 2287 next
			extern double rip_0x143553;
			xmm0 = rip_0x143553;
			xmm1 = xmm0;
			// 2308
			if (!(r15d == 0)) {
				xmm0 = (double)_d8 / (double&)_160;
				xmm1 = (double)r12d / (double&)_170;
			} // 2351

			// 2359
			if ((char)_149 != 0) {
				goto _f2559;
			} // 2368
			else if (r15d == 0) {
				/***
				* input r13 = ?
				*/
				// inline begin at 
				// 2507
				_f0 = (double)xmm1;							// svae xmm1
				_d8 = (double)xmm0;							// svae xmm0
				// 2530 call
				CGContextReplacePathWithShapePath((CGBitmapContext*)r13, (CGSRegionObject*)_30);
				// 2538 call
				CGContextClip((CGBitmapContext*)r13);
				xmm0 = (double&)_d8;						// restore xmm0
				xmm1 = (double&)_f0;						// restore xmm1
				// 2559 end
			}
			else {
				// inline begin at 
				// 2368 next
				(double&)_70 = xmm0;
				(double&)_d8 = xmm0;						// svae xmm0
				(double&)_58 = xmm1;
				(double&)_f0 = xmm1;						// save xmm1
				// ? &_68 is a local location object
				_68 = 0;
				_60 = 0;
				// ? &_50 is a local location object
				_50 = 0;
				_48 = 0;

				// _70 - _48 may be a local CGSregionObject.

				extern float rip_0x14350d;
				xmm0 = rip_0x14350d;
				// 2461 call
				CGSTransformRegion((CGSRegionObject*)_30, (CGSRegionObject*)&_70, (CGSRegionObject**)&_d0);;
				// 2476 call
				CGContextReplacePathWithShapePath((CGSRegionObject*)_30, (CGSRegionObject*)_d0);
				// 2488 call
				CGSReleaseRegion((CGSRegionObject*)_d0);
				// 2493 goto _f2535; inline #1
				// 2535
				// 2538 call
				CGContextClip((CGBitmapContext*)r13);
				xmm0 = (double&)_d8;						// restore xmm0
				xmm1 = (double&)_f0;						// restore xmm1
				// 2559 end
			}
		}
	_f2559:
		// 2562
		if (!(r15d == 0)) {
			// 2567 call
			CGContextScaleCTM((CGBitmapContext*)r13, (double)xmm0, (double)xmm1);
		} // 2572
		// 2576
		if (!((r14b & 0x2) == 0)) {
			extern CGRect CGRectInfinite;
			CGRect& rect = *(CGRect*)rsp;
			rect = CGRectInfinite;
			// 2625 call
			CGContextClearRect((CGBitmapContext*)r13, rect);
			r14d &= 0xfffffff9;
		} // 2634
		_f0 = r14d;										// flag, initalized with flag1 at the most beginning.
		r14 = content;									// via _130, is content
		// 2641 call
		content->_168 = (pthread_t)pthread_self();
		rbx = &content->_10;							// via _138
		// 2670 call
		pthread_mutex_unlock((pthread_mutex_t*)&content->_10);
		rsi = layer;									// via 0x10(%rbp) which is the 1st stack-based argument.
		// 2682 call
		backing_callback((CGBitmapContext*)r13, layer);								// via *-0x148(%rbp);
		// 2691 call
		pthread_mutex_lock((pthread_mutex_t*)&content->_10);		// via rbx = _138;
		content->_168 = 0;								// via r14, is content
		// 2710 call
		CAReleaseCachedCGContext((CGBitmapContext*)r13);
	_f2715:				// from 2225
	_f2715:				// from 2502
		++r15d;
		r14d = _f0;
		// 2732
		if (r15d < _110)
			goto _b1945;
	} // 2738
	rbx = content;										// via _130, is content
	rax = (CGSRegionObject**)&content->_158;
	rcx = (CA::Render::ShmemBitmap*)_100;
	OSAtomicIncrement32((volatile int32_t*)((CA::Render::ShmemBitmap*)_100)->_4);
	rdi = _30;
	r13 = _178;
_f2774:			// from 1747 (so many incoming points, i think the code here till ? should be inline)
	/**
	* input: rax = ?; maybe &((CGBackingStore*)rbx)->_158 or &content->_158;
	* input: rdi = ?; maybe ? or _30;
	* input: r13 = ?; maybe ? or _178;
	* input: rbx = ?; maybe iterator of what
	*/
	*(CGSRegionObject**)rax = 0;
	r15 = _138;				// (pthread_mutex_t*)&content->_10
	// 2791
	if (!(rdi == 0)) {
		// 2793 call
		CGSReleaseRegion(rdi);		// maybe ? or _30;
	} // 2798
	// 2801
	if (!(r13 == 0)) {
		// 2806 call
		CGSReleaseRegion(r13);		// maybe ? or _178;
	} // 2811
	// 2821
	if (!(_a0 == 0)) {
		// 2823 call
		CGSReleaseRegion((CGSRegionObject*)_a0);
	} // 2828
	// 2831 call
	CABackingStoreReleaseImages((CABackingStore*)rbx);
	eax = 0;
	// 2845
	if (!(context == 0)) {			// via 0x18(%rbp), is the 2nd argument of this function.
		// 2850 call virtual method
		eax = (int)((cpp_virtbl*)context->_0)->virmethod[0x48 >> 3]();
	} // 2855
	++eax;
	((CABackingStoreBuffer*)_140)->_20 = eax;
	((CABackingStoreBuffer*)_140)->_28 = 0;
	content->_160 = 0;									// via rbx, is content;
	(char&)content->_174 = 0x6;
	// 2898 call
	pthread_cond_broadcast((pthread_cond_t*)&content->_50);				// via rbx
#if 0
			/** inline piece */
		 _b2903:
			   // 2906 call
			   pthread_mutex_unlock((pthread_mutex_t*)&content->_10);						// via r15, is _138, which is &content->_10
			   return;
#endif
_f2929:
	// 3046 call
	CGSTransformRegion;
	// 3055 call
	CGSReleaseRegion;
_f3076:
	// 3140 call
	CGSRectInRegion;
	// 3149
	if (!) {
		// 3166 call
		CGSIntersectRegionWithRect;
		// 3175 call
		CGSRegionIsEmpty;
		// 3182
		if (!) {
			// 3188 call
			CGSReleaseRegion;
		} // 3201
	} // 3201
_f3214:
_f3214:
	// 3216
	if ()
		goto _b311;
	// 3225
	if () {
		// goto _b2903;		inline
		// 2906 call
		pthread_mutex_unlock((pthread_mutex_t*)&content->_10);						// via r15, is _138, which is &content->_10
		return;
	}
	// 3231
	goto _b311;
	// 3236 call
	abort;
_f3236:
}

void foo()
{
	// 65
	if (!) {
		// 75
		if ()
			goto _f2903;
		// 89
		if (!) {
		_b95:
			// 114
			if ()
				goto _b95;
		} // 116
	} // 116

	  // 146
	if (!) {
		// 159
		if (!) {
			// 176
			if ()
				goto _f311;
			// 192
			if ()
				goto _f3214;
			// 215
			if ()
				goto _f3214;
			// 234
			if ()
				goto _f2929;
			// 276
			goto _f3076;
		} // 281
	} // 281

_b311:
_b311:
_f311:


	// 373
	if ()
		goto _f689;
_b416:
	// 427
	if (!) {
		// 440
		if () {
			// goto _f763; inline #0
			// 763

			// 773
			// goto _f839; inline #1
			// 839
			goto _f842;
		}
		else if (
			// 459
			(!)
			// 475
			&& (!)
			// 491
			&& (!)
			// 518
			&& (!)
			) {
			// 533
			if (!) {
				// 539
				if ()
					goto _f645;
				// 582
				if (!) {
				} // 594
				  // 599
				goto _f645;
			}
			else { // 601
				   // 608
				if (!) {
					// 614
					if (!) {
					} // 645
				} // 645
			} // 645
		_f645:
			// 647
			if (!) {
				// 655
				if () {
					// goto _f775; inline #0
					// inline
					// 775

					// 785
					if (!) {
					} // 797
					  // 816
					if (!) {

					} // 839
					  // goto _f839; inline #1
					  // 839
					goto _f842;
				}
				// 659
				if () {
					goto _f719;
				}
				// 678
				if ()
					goto _b416;
				// 687
				goto _f719;
			}
			else {
			_f698:

			}// 719
		_f719:
			// 729
			goto _f842;
		}	// 731
		else {
			// inline
		_f731:
			// 741
			if (!) {
			} // 753
			  // 761
			  // goto _f839; inline #1
			  // 839
			goto _f842;
		}
	}
	else { // 731	
		   // inline
	_f731:
		// 741
		if (!) {
		} // 753
		  // 761
		  // goto _f839; inline #1
		  // 839
		goto _f842;
	}
#if 0
	_f719:
		 // 729
		 goto _f842;
	 _f731:
		 // 741
		 if (!) {
		 } // 753
		   // 761
		 goto _f839;
	 _f763:
		 // 773
		 goto _f839;
	 _f775:
		 // 785
		 if (!) {
		 } // 797
		   // 816
		 if (!) {

		 } // 839
	 _f839:
	 _f839:
#endif
	 _f842:
		 // 845
		 if (!) {
			 // 877
			 goto _f902;
		 } // 879
		   // 896
		 if (!) {
		 _f902:
			 // 909
			 if (!) {
				 // 918
				 goto _f1083;
			 } // 923
			   // 936
			 if (!) {
			 } // 941
			   // 965
			 if (!) {
				 // 992
				 if (!) {
					 // 1005
					 goto _f1014;
				 } // 1007
			 _f1014:
			 _b1014:
			 _b1014:
				 // 1022
				 if ()
					 goto _b1014;
				 // 1026
				 if ()
					 goto _b1014;
			 } // 1028
			   // 1063
			 if (!) {
			 _f1083:
				 // 1098
				 if (!) {
					 // 1139
					 if (!) {
						 // 1148
						 if (!) {
						 } // 1169
					 } // 1169
				 } // 1169
				   // 1187
				 if (!) {
				 } // 1200
				   // 1264
				 if (!) {
				 _b1273:
					 // 1280
					 if () {
						 // inline
						 // 1336

						 // 1347
						 // goto _f1365; inline #1
						 // 1365

						 // 1368	end
					 }	// 1289
					 else if (!) {
						 // 1297
						 if () {
							 // inline
							 // 1349
							 // 1368	end 
						 }
						 else {
							 // 1297 next

							 // 1334
							 // goto _f1365; inline #1
							 // 1365

							 // 1368 end
						 }
					 } // 1368

					   // 1374
					 if ()
						 goto _b1273;
				 } // 1376
				   // 1415
				 if (!) {
					 // 1424
					 if (!) {
						 // 1433
						 if (!) {
							 // 1454
							 goto _f1594;
						 } // 1459
					 _f1594:
						 // 1608
						 if (!) {
						 } // 1633
					 } // 1633
				 } // 1633
				   // 1643
				 if () {
					 // inline
					 // 1713
					 // 1747
					 goto _f2774;
				 } // 1659
				 else if () {
					 // inline
					 // 1752
					 // 1766 end
				 } // 1684
				 else if (!) {
					 // inline
					 // 1684 next
					 // 1711
					 goto _f1766;
				 }
			 _f1766:
				 // 1779
				 if (!) {
				 } // 1813
				   // 1867
				 if (!) {
				 _b1945:
					 // 2018
					 if (!) {
						 // 2028
						 if (!) {
						 } // 2054
						   // 2048
						 if (!) {
							 // 2225
							 goto _f2715;
						 } // 2230
					 } // 2230
					   // 2234
					 if ()
						 goto _f3236;
					 // 2287
					 if (!) {
						 // 2308
						 if (!) {
						 } // 2351
						   // 2493
						 goto _f2535;
					 } // 2495
					   // 2359
					 if (!) {
						 // 2368
						 if (!) {
							 // 2502
							 goto _f2715;
						 } // 2507
					 _f2535:
					 } // 2559
					   // 2562
					 if (!) {
					 } // 2572
					   // 2576
					 if (!) {
					 } // 2634
				 _f2715:
				 _f2715:
					 // 2732
					 if ()
						 goto _b1945;
				 } // 2738
			 _f2774:
				 // 2791
				 if (!) {
				 } // 2798
				   // 2801
				 if (!) {
				 } // 2811
				   // 2821
				 if (!) {
				 } // 2828
				   // 2845
				 if (!) {
				 } // 2855
			 } // 2903
		 } // 2903
	 _b2903:

	 _f2929:
	 _f3076:
		 // 3149
		 if (!) {
			 // 3182
			 if (!) {
			 } // 3201
		 } // 3201
	 _f3214:
	 _f3214:
		 // 3216
		 if ()
			 goto _b311;
		 // 3225
		 if ()
			 goto _b2903;
		 // 3231
		 goto _b311;
	 _f3236:
	  
		
	
			 
		 
		  
		
}

void foo2()
{
	pthread_mutex_lock;
	// 65
	if (!) {
		// 67 call
		pthread_self;
		// 75
		if ()
			goto _f2903;
		// 89
		if (!) {
		_b95:
			// 101 call
			pthread_cond_wait;
			// 114
			if ()
				goto _b95;
		} // 116
	} // 116

	  // 146
	if (!) {
		// 159
		if (!) {
			// 176
			if ()
				goto _f311;
			// 192
			if ()
				goto _f3214;
			// 215
			if ()
				goto _f3214;
			// 225 call
			CGSBoundingShapeGetRegion;
			// 234
			if ()
				goto _f2929;
			// 276
			goto _f3076;
		} // 281
	} // 281

_b311:
_b311:
_f311:


	// 373
	if ()
		goto _f689;

_b416:
	// 420 call
	CA::Render::Shmem::set_volatile(bool, int);
	// 427
	if (!) {
		// 440
		if () {
			// goto _f763; inline #0
			// 763

			// 773
			// goto _f839; inline #1
			// 839
			goto _f842;
		}
		else if (
			// 459
			(!)
			// 475
			&& (!)
			// 491
			&& (!)
			// 518
			&& (!)
			) {
			// 533
			if (!) {
				// 539
				if ()
					goto _f645;
				// 568 call
				CABackingStoreSynchronize(CABackingStore*, CA::GenericContext*, unsigned int, int);

				// 582
				if (!) {
				} // 594
				  // 599
				goto _f645;
			}
			else { // 601
				   // 608
				if (!) {
					// 614
					if (!) {
						// 635 call
						CABackingStoreSynchronize(CABackingStore*, CA::GenericContext*, unsigned int, int);

					} // 645
				} // 645
			} // 645
		_f645:
			// 647
			if (!) {
				// 655
				if () {
					// goto _f775; inline #0
					// inline
					// 775

					// 785
					if (!) {
					} // 797
					  // 803 call
					CABackingStoreDeleteBuffer(CABackingStoreBuffer*);
					// 808 call
					CAGetDebugFlags;
					// 816
					if (!) {
						// 834 call
						// %rdi = "CoreAnimation: triple buffered backing store %p\n"
						x_log;
					} // 839
					  // goto _f839; inline #1
					  // 839
					goto _f842;
				}
				// 659
				if () {
					goto _f719;
				}
				// 678
				if ()
					goto _b416;
				// 687
				goto _f719;
			}
			else {
			_f698:

			}// 719
		_f719:
			// 729
			goto _f842;
		}	// 731
		else {
			// inline
		_f731:
			// 741
			if (!) {
			} // 753
			  // 756 call
			CABackingStoreDeleteBuffer(CABackingStoreBuffer*);

			// 761 goto _f839; inline #1
			// 839
			goto _f842;
		}
	}
	else { // 731	
		   // inline
	_f731:
		// 741
		if (!) {
		} // 753
		  // 756 call
		CABackingStoreDeleteBuffer(CABackingStoreBuffer*);
		// 761 goto _f839; inline #1
		// 839
		goto _f842;
	}
#if 0
	_f719:
		 // 729
		 goto _f842;
	 _f731:
		 // 741
		 if (!) {
		 } // 753
		   // 761
		 goto _f839;
	 _f763:
		 // 773
		 goto _f839;
	 _f775:
		 // 785
		 if (!) {
		 } // 797
		   // 816
		 if (!) {

		 } // 839
	 _f839:
	 _f839:
#endif
	 _f842:
		 // 845
		 if (!) {
			 // 877
			 goto _f902;
		 } // 879
		   // 896
		 if (!) {
		 _f902:
			 // 909
			 if (!) {
				 // 918
				 goto _f1083;
			 } // 923
			   // 936
			 if (!) {
			 } // 941
			   // 947 call
			 CABackingStoreDeleteBuffer(CABackingStoreBuffer*);
			 // 965
			 if (!) {
				 // 973 call
				 CA::Render::format_mipmap_min_size(unsigned int);
				 // 992
				 if (!) {
					 // 1005
					 goto _f1014;
				 } // 1007
			 _f1014:
			 _b1014:
			 _b1014:
				 // 1022
				 if ()
					 goto _b1014;
				 // 1026
				 if ()
					 goto _b1014;
			 } // 1028
			   // 1048 call
			 CA::Render::Shmem::new_bitmap(unsigned int, unsigned int, unsigned int, unsigned int);

			 // 1063
			 if (!) {
			 _f1083:
				 // 1098
				 if (!) {
					 // 1103 call
					 CGColorSpaceRelease;
					 // 1116 call
					 CGColorSpaceRetain;
					 // 1139
					 if (!) {
						 // 1148
						 if (!) {
							 // 1153 call
							 CGSReleaseRegion;
						 } // 1169
					 } // 1169
				 } // 1169
				   // 1187
				 if (!) {
					 // 1192 call
					 CGSBoundingShapeReset;
				 } // 1200
				   // 1264
				 if (!) {
				 _b1273:
					 // 1280
					 if () {
						 // inline begin at
						 // 1336
						 // 1342 call
						 CGSNewEmptyRegion;
						 // 1347 goto _f1365; inline #1
						 // 1365

						 // 1368	end
					 }	// 1289
					 else if (!) {
						 // 1297
						 if () {
							 // inline begin at
							 // 1349
							 // 1352 call
							 CGSReleaseRegion;
							 // 1368	end 
						 }
						 else {
							 // 1297 next
							 // 1309 call
							 CGSUnionRegion;
							 // 1318 call
							 CGSReleaseRegion;

							 // 1334 goto _f1365; inline #1
							 // 1365

							 // 1368 end
						 }
					 } // 1368

					   // 1374
					 if ()
						 goto _b1273;
				 } // 1376
				   // 1415
				 if (!) {
					 // 1424
					 if (!) {
						 // 1433
						 if (!) {
							 // 1449 call
							 CGSDiffRegion;
							 // 1454
							 goto _f1594;
						 } // 1459
						 else {
							 // 1554 call
							 CGSNewRegionWithRect;
							 // 1577 call
							 CGSDiffRegion;
							 // 1589 call
							 CGSReleaseRegion;
						 }
					 _f1594:
						 // 1601 call
						 CGSRegionIsEmpty;
						 // 1608
						 if (!) {
							 // 1617 call
							 CGSReleaseRegion;
						 } // 1633
					 } // 1633
				 } // 1633
				   // 1643
				 if () {
					 // inline begin at
					 // 1713
					 // 1747
					 goto _f2774;
				 } // 1659
				 else if () {
					 // inline begin at
					 // 1752
					 // 1766 end
				 } // 1684
				 else if (!) {
					 // inline begin at
					 // 1684 next
					 // 1696 call
					 CA::Render::ShmemBitmap::copy_pixels(CA::Render::ShmemBitmap const*, CGSRegionObject*);

					 // 1711
					 goto _f1766;
				 }
			 _f1766:
				 // 1779
				 if (!) {
				 } // 1813
				   // 1867
				 if (!) {
				 _b1945:
					 // 1958 call
					 CA::Render::ShmemBitmap::lod_width(unsigned int) const;
					 // 1975 call
					 CA::Render::ShmemBitmap::lod_height(unsigned int) const;
					 // 1989 call
					 CA::Render::ShmemBitmap::lod_data(unsigned int);
					 // 2007 call
					 CA::Render::ShmemBitmap::lod_rowbytes(unsigned int) const;

					 // 2018
					 if (!) {
						 // 2028
						 if (!) {
						 } // 2054
						   // 2048
						 if (!) {
							 // 2225
							 goto _f2715;
						 } // 2230
					 } // 2230
					   // 2234
					 if ()
						 goto _f3236;
					 // 2276 call
					 CAGetCachedCGBitmapContext;
					 // 2287 
					 if () {
						 // inline begin at
						 // 2495

						 // 2502 
						 goto _f2715;
					 }
					 else {
						 // inline begin at
						 // 2287 next
						 // 2308
						 if (!) {
						 } // 2351
						   // 2359
						 if () {
							 goto _f2559;
						 } // 2368
						 else if () {
							 // inline begin at 
							 // 2507
							 // 2530 call
							 CGContextReplacePathWithShapePath;
							 // 2559 end
						 }
						 else {
							 // inline begin at 
							 // 2368 next
							 // 2461 call
							 CGSTransformRegion;
							 // 2476 call
							 CGContextReplacePathWithShapePath;
							 // 2488 call
							 CGSReleaseRegion;
							 // 2493 goto _f2535; inline #1
							 // 2535
							 // 2559 end
						 }
					 }
				 _f2559:
					 // 2562
					 if (!) {
						 // 2567 call
						 CGContextScaleCTM;
					 } // 2572
					   // 2576
					 if (!) {
						 // 2625 call
						 CGContextClearRect;
					 } // 2634
					   // 2641 call
					 pthread_self;
					 // 2670 call
					 pthread_mutex_unlock;
					 // 2682 call
					 *-0x148(%rbp);
					 // 2691 call
					 pthread_mutex_lock;
					 // 2710 call
					 CAReleaseCachedCGContext;
				 _f2715:
				 _f2715:
					 // 2732
					 if ()
						 goto _b1945;
				 } // 2738
			 _f2774:
				 // 2791
				 if (!) {
					 // 2793 call
					 CGSReleaseRegion;
				 } // 2798
				   // 2801
				 if (!) {
					 // 2806 call
					 CGSReleaseRegion;
				 } // 2811
				   // 2821
				 if (!) {
					 // 2823 call
					 CGSReleaseRegion;
				 } // 2828
				   // 2831 call
				 CABackingStoreReleaseImages(CABackingStore*);
				 // 2845
				 if (!) {
					 // 2850 call
					 *0x48(%rax);
				 } // 2855
				   // 2898 call
				 pthread_cond_broadcast;
			 } // 2903
		 } // 2903
	 _b2903:
		 // 2906 call
		 pthread_mutex_unlock;
	 _f2929:
		 // 3046 call
		 CGSTransformRegion;
		 // 3055 call
		 CGSReleaseRegion;
	 _f3076:
		 // 3140 call
		 CGSRectInRegion;
		 // 3149
		 if (!) {
			 // 3166 call
			 CGSIntersectRegionWithRect;
			 // 3175 call
			 CGSRegionIsEmpty;
			 // 3182
			 if (!) {
				 // 3188 call
				 CGSReleaseRegion;
			 } // 3201
		 } // 3201
	 _f3214:
	 _f3214:
		 // 3216
		 if ()
			 goto _b311;
		 // 3225
		 if ()
			 goto _b2903;
		 // 3231
		 goto _b311;
		 // 3236 call
		 abort;
	 _f3236:
}