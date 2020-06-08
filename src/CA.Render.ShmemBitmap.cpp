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

void CA::Render::ShmemBitmap::copy_pixels(CA::Render::ShmemBitmap const* other, CGSRegionObject* region)
{
	_60 = region;
	_68 = other;
	_70 = this;
	// 32
	if (!(0 == region)) { // 29 (0 == rdx)
			 // 42 call
		// 49
		if (!(false != CGSRegionIsEmpty((CGSRegionObject*)region))) { // 47 (0 != al)
				 int32_t& format_bpp = r15d;
				 // 64 call
				 r15d = CA::Render::format_Bpp((unsigned int)this->_10);
			// 79
			if (!(this->_10 != (int32_t&)other->_10)) { // 76 (ebx != (int32_t&)rax->_10)
					 ecx = this->_1c;
					 _74 = this->_1c;
					 // 102
				if (!(this->_1c != (int32_t&)other->_1c)) { // 99 (ecx != (int32_t&)rax->_1c)
						 // 112
					if (!((int32_t&)this->_1c == 0x0)) { // 108 ((int32_t&)_74 == 0x0)
						int32_t& scale = r12d;
						scale = 0;

						do {
						_b121:	// from 518
							void*& this_lod_data = _48;
							void*& other_lod_data = _50;
							int32_t& this_format_rowbytes = _58;
							int32_t& other_format_rowbytes = r14;
							r13 = this;
							// 131 call
							_48 = ((CA::Render::ShmemBitmap*)this)->lod_data((unsigned int)scale);
							// 165 call
							_58 = CA::Render::format_rowbytes((unsigned int)this->_10, (unsigned int)((0 == (this->_14 >> scale)) ? 0x1 : this->_14));
							rbx = other;
							// 184 call
							_50 = ((CA::Render::ShmemBitmap*)other)->lod_data((unsigned int)scale);
							// 210 call
							r14 = CA::Render::format_rowbytes((unsigned int)other->_10, (unsigned int)((0 == (other->_14 >> scale)) ? 0x1 : other->_14));
							edx = 0x0;
							_30 = (0 == (this->_18 >> scale)) ? 0x0 : ((this->_18 >> scale) - 1);
							cl = scale;
							_38 = (0 == ((other->_18) >> scale)) ? 0x0 : (((other->_18) >> scale) - 1);
							rdi = _60;
							// 270 call
							_40 = CGSRegionEnumerator((CGSRegionObject*)region);
							CGSRect*& cgsRect = rax;
							// 282 call
							cgsRect = CGSNextRect((CGSRegionEnumeratorObject*)_40);
							// 290
							if (!(0 == cgsRect)) { // 287 (0 == rax)
								r13 = _58;		// format_rowbytes
								rdx = _30;		// height of this
								_30 = rdx;
								r13 = -r13;
								rcx = _38;		// height of other
								_38 = _38 * r14;		// format_rowbytes of other
								r14 = -r14;
								_58 = (0x1 << r12b) - 1;

								int32_t& left = ebx;
								int32_t& top = edx;
								int32_t& right = edi;
								int32_t& bottom = eax;
								do {
								_b345:	// from 496
									left = (int32_t)(double&)cgsRect->_0;
									top = (int32_t)(double&)cgsRect->_8;
									right = (int32_t)((double)(int32_t)(double&)cgsRect->_0 + (double&)cgsRect->_10);
									bottom = (int32_t)((double)(int32_t)(double&)cgsRect->_8 + (double&)cgsRect->_18);
									// 386
									if (!(0 == scale)) {
										left = left >> scale;
										top = top >> scale;
										esi = _58;
										right = (right + this_format_rowbytes) >> scale;
										bottom = (bottom + this_format_rowbytes) >> scale;
									} // 415
									edi = (right - left) * format_bpp;
									rsi = (int64_t)(int32_t&)(bottom - top);
									rax = (int64_t)(int32_t&)top;
									rcx = top * r14;
									/*
									*                                     ____
									* 000000000000000000000000000000000000
									* 000000000000000000000000000000000000    top * format_rowbytes
									* 00000000000000000 __________        ----
									*                  |xxxxxxxxxx|
									*                  |yyyyyyyyyy|
									*                   ----------
									* |<- left * bpp ->|
									*     + ?
									*/
									rdx = left * format_bpp + _38 + top * other_format_rowbytes + (uintptr_t)other_lod_data;
									rbx = left * format_bpp + _30 + top * this_format_rowbytes + (uintptr_t)this_lod_data;
									rcx = left * format_bpp + _30 + top * this_format_rowbytes + (uintptr_t)this_lod_data;
									r8 = r14;
									r9 = r13;
									// 479 call
									CA::copy_bytes((long)rdi, (long)rsi, (void const*)rdx, (void*)rbx, (long)r14, (long)r13);
									// 488 call
									// 496
								} while (0 != CGSNextRect((CGSRegionEnumeratorObject*)_40)); // 493 (0 != rax) goto _b345;

							} // 502
							  // 506 call
							CGSReleaseRegionEnumerator((CGSRegionEnumeratorObject*)_40));
							++scale;
							// 518
						} while (scale != (int32_t&)this->_1c); // 514 (r12d != (int32_t&)_74) goto _b121;
							
					} // 524
				} // 524
			} // 524
		} // 524
	} // 524
	return;
}