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

CA::Render::Encoder::~Encoder()
{

}


CA::Render::Encoder::Encoder(x_heap_struct* heap, unsigned int flag1, void* something, unsigned int flag2, double flt)
{
	(double&)_30 = flt;
	r14d = flag2;
	r13 = something;
	r15d = flag1;
	r12 = heap;
	rbx = this;
	this->_0 = heap;
	al = (0 == heap);
	eax = (uint32_t)(uint8_t&)al;
	ecx = (0xff000000 & this->_8) | (0 == heap);
	// 56 testq %r12, %r12
	this->_8 = (0xff000000 & this->_8) | (0 == heap);
	this->_38 = 0x0;
	this->_30 = 0x0;
	this->_28 = 0x0;
	this->_20 = 0x0;
	this->_18 = 0x0;
	this->_10 = 0x0;

	x_heap_struct*& realHeap = rdi;
	realHeap = heap;
	// 112
	if (!(0 != heap)) {
		// 119 call
		realHeap = x_heap_new(0x1000);
		this->_0 = realHeap;
	} // 130
	this->_40 = something;
	this->_48 = 0x0;
	this->_58 = 0x0;
	this->_60 = 0x0;
	flag1 = flag1 | 0x1;
	this->_38 = flag1;
	eax = 0xffffe000 + heap->_10;
	// 172 cmpl $0x200, %eax
	// 177 cltq
	r12 = (>= ) ? 0x200 : rax;
	rsi = (r12 + 7) & -0x8;
	rcx = realHeap->_10 - ((r12 + 7) & -0x8);

	void*& free_buffer_of_heap = rax;
	// 205
	if (!(realHeap->_10 >= ((r12 + 7) & -0x8))) {
		// 207 call
		free_buffer_of_heap = x_heap_malloc_small_((x_heap_struct*)realHeap, (int)((r12 + 7) & -0x8));
		r15d = this->_38;
	} // 218
	else {
		free_buffer_of_heap = realHeap->_8;
		realHeap->_10 = rcx;
		rsi = ((r12 + 7) & -0x8) + realHeap->_8;
		realHeap->_8 = ((r12 + 7) & -0x8) + realHeap->_8;
	}
	this->_10 = free_buffer_of_heap;
	this->_18 = free_buffer_of_heap;
	r12 = r12 + free_buffer_of_heap;
	this->_20 = r12;
	// 254 call
	((CA::Render::Encoder*)this)->encode_int32((unsigned int)r15d);
	// 265 call
	((CA::Render::Encoder*)this)->encode_int32((unsigned int)flag2);
	// 283 call
	((CA::Render::Encoder*)this)->encode_int64((unsigned long long&)flt);
	this->_50 = this->_18 - this->_10;
}

void CA::Render::Encoder::encode_port(unsigned int port1, unsigned int port2, bool bWhat)
{

	SomeWhat*& newWhat = rax;
	// 31 call
	newWhat = (SomeWhat*)x_heap_malloc((x_heap_struct*)this->_0, 0x30);
	newWhat->_8 = 0x2;
	newWhat->_10 = port1;
	newWhat->_14 = port2;
	newWhat->_18 = bWhat;
	newWhat->_0 = this->_28;
	this->_28 = newWhat;
	++this->_30;
	return;
}

void CA::Render::Encoder::encode_object_uncached(CA::Render::Object const* uncachedObject)
{
	r14 = uncachedObject;
	rbx = this;
	r15d = 0;
	// 22
	if (!(0 == uncachedObject)) { // 19 (0 == r14)
			 // 30 call
		r15d = ((cpp_virtbl*)uncachedObject->_0)->virmethod[3](); // * 0x18(%rax);
	} // 36
	rax = this->_18;
	rcx = this->_18 + 1;
	// 48
	if ((this->_18 + 1) <= this->_20) { // 44 (rcx <= rbx->_20)
			// inline jmp 71
		*(char*)this->_18 = r15b;
		this->_18 = this->_18 + 1;
	} // 65  // 58 call
	else if (!(false == ((CA::Render::Encoder*)this)->grow((unsigned long)0x1))) { // 63 (0 == al)
				 // 65 next
		*(char*)this->_18 = r15b;
		this->_18 = this->_18 + 1;
	} // 82

_f82:	 // from 65
		 // 85
	if (!(0 == r15d)) { // 82 (0 == r15d)
		return ((cpp_virtbl*)uncachedObject->_0)->virmethod[5](this);
	} // 112
	return;
}


void CA::Render::Encoder::encode_object(CA::Render::Object const* rndrObject)
{
	rbx = rndrObject;
	r14 = this;
	// 16
	if (!(0 == rndrObject)) { // 13 (0 == rbx)
		// 25
		if (!(0 == this->_48)) { // 22 (0 == rax)
				 // 33 call
			// 38
			if (!(false == ((cpp_virtbl*)rndrObject->_0)->virmethod[4]())) { // 36 (0 == al)
				return ((CA::Render::Encoder::ObjectCache*)this->_48)->encode((CA::Render::Encoder*)this, (CA::Render::Object const*))rndrObject);
			} // 59
		} // 59
	} // 59
	return ((CA::Render::Encoder*)this)->encode_object_uncached((CA::Render::Object const*))rndrObject);
}



void CA::Render::Encoder::encode_atom(unsigned int atom)
{
	r14d = atom;
	r15 = this;
	// 42
	if (!(atom > 0x1f5)) { // 35 (r14d > 0x1f5)
			 // 51
		if (atom > 0xfd) { // 44 (r14d > 0xfd)
			// inline goto _f276;
		_f276:	 // from 51
			rax = this->_18;
			rcx = (uintptr_t)this->_18 + 1;
			// 288
			if ((uintptr_t)this->_18 + 1 <= this->_20) { // 284 (rcx <= r15->_20)
				// gen jmp 311
				goto _f311;
				// 298 call
			} // 305
			else if (false == ((CA::Render::Encoder*)this)->grow((unsigned long)0x1)) { // 303 (0 == al)
																						// inline jmp 322
				return ((CA::Render::Encoder*)this)->encode_int16((unsigned short)atom);
			}
			else { // 305 next
				rax = this->_18;
			} // 311
		_f311:	 // from 288
			rcx = (uintptr_t)this->_18 + 1;
			*(char*)this->_18 = -0x2;
			this->_18 = (uintptr_t)this->_18 + 1;
		_f322:	 // from 305
			return ((CA::Render::Encoder*)this)->encode_int16((unsigned short)atom);
		}

		rax = this->_18;
		rcx = (uintptr_t)this->_18 + 1;
		// 69
		if ((uintptr_t)this->_18 + 1 <= this->_20) { // 65 (rcx <= r15->_20)
				// gen jmp 96
			goto _f96;
			// 79 call
		} // 86
		else if (false == ((CA::Render::Encoder*)this)->grow((unsigned long)0x1)) { // 84 (0 == al)
					 // inline jmp 255
			return;
		}
		else { // 86 next
			rax = this->_18;
		} // 96
	_f96:	 // from 69
		rcx = (uintptr_t)this->_18 + 1;
		*(char*)this->_18 = atom & 0xff;
		this->_18 = (uintptr_t)this->_18 + 1;
		// 107
		return;
	} // 112
	rax = this->_18;
	rcx = (uintptr_t)this->_18 + 1;
	// 124
	if (this->_18 + 1 <= this->_20) { // 120 (rcx <= r15->_20)
			// gen jmp 147
		goto _f147;
		// 134 call
	} // 141
	else if (false == ((CA::Render::Encoder*)this)->grow((unsigned long)0x1)) { // 139 (0 == al)
				 // gen jmp 158
		goto _f158;
	}
	else { // 141 next
		rax = this->_18;
	} // 147
_f147:	 // from 124
	rcx = (uintptr_t)this->_18 + 1;
	*(char*)this->_18 = -0x1;
	this->_18 = (uintptr_t)this->_18 + 1;
_f158:	 // from 141
	__CFString*& atomCFString = r14;
	char*& atomCString = rbx;
	// 161 call
	atomCFString = CAAtomGetString(atom);
	// 174 call
	atomCString = CFStringGetCStringPtr((__CFString*)atomCFString, 0);
	// 185
	if (!(0 != atomCString)) { // 182 (0 != rbx)

		ratomCStringbx = alloca(0x100);
		r12d = 0;
		// 216 call
		al = (bool)CFStringGetCString((__CFString*)atomCFString, (char*)atomCString, 0x100, 0);
		edx = 0x0;
		// 228
		if (0 == al) { // 221 (0 == al)
					// inline jmp 244
					// 250 call
			((CA::Render::Encoder*)this)->encode_data((void const*)atomCString, (unsigned long)0);
			return;
		}
	}
_f230:	 // from 185
  // 233 call
	r12 = atomCString;
_f244:	 // from 228
		 // 250 call
	((CA::Render::Encoder*)this)->encode_data((void const*)atomCString, (unsigned long)strlen(atomCString));
_f255:	 // from 107
_f255:	 // from 86 
	return;
}

void CA::Render::Encoder::encode_cfobject(void const* cfobject)
{
	r13 = cfobject;
	r14 = this;
	ebx = 0;
	// 46
	if (!(0 == cfobject)) { // 43 (0 == r13)
		// 66
		if (!(0 == CFGetTypeID(cfobject))) { // 63 (0 == r15)
			ebx = 0x1;
			// 77
			if (!(cfobject == 0x1)) { // 73 (r13 == 0x1)
				ebx = 0x2;
				// 92
				if (!(r15 == CFStringGetTypeID())) { // 89 (r15 == rax)
					ebx = 0x3;
					// 107
					if (!(r15 == CFNumberGetTypeID)) { // 104 (r15 == rax)
						ebx = 0x4;
						// 122
						if (!(r15 == CFBooleanGetTypeID())) { // 119 (r15 == rax)
							ebx = 0x5;
							// 137
							if (!(r15 == CFDataGetTypeID())) { // 134 (r15 == rax)
								ebx = 0x6;
								// 152
								if (!(r15 == CFArrayGetTypeID())) { // 149 (r15 == rax)
									ebx = 0x7;
									// 167
									if (!(r15 == CFDictionaryGetTypeID())) { // 164 (r15 == rax)
											 // 169 call
										ebx = (r15 == CGColorSpaceGetTypeID()) << 0x3;
									} // 186
								} // 186
							} // 186
						} // 186
					} // 186
				} // 186
			} // 186
		} // 186
	} // 186
	rax = this->_18;
	rcx = this->_18 + 1;
	// 198
	if ((this->_18 + 1) <= this->_20) { // 194 (rcx <= r14->_20)
			// inline jmp 221
	_f221:	 // from 198
		*(char*)this->_18 = bl;
		this->_18 = this->_18 + 1;
	} // 215
	else if (!(0 == ((CA::Render::Encoder*)this)->grow((unsigned long)0x1))) { // 213 (0 == al)
		 // 215 next
		*(char*)this->_18 = bl;
		this->_18 = this->_18 + 1;
	} // 231

_f231:	 // from 215
	ebx = ebx + -0x2;

	enum {
		CASE_CFSTRING = 0,
		CASE_CFNUMBER,
		CASE_CFBOOLEAN,
		CASE_CFDATA,
		CASE_CFARRAY,
		CASE_CFDICTIONARY
	};

	char*& cstring = (char*)&_1030;
	// 237
	switch (ebx) {
	case CASE_CFSTRING: {
		r15d = 0;
		// 267 call
		r12 = CFStringGetCStringPtr((__CFString*)cfobject, 0);
		// 278
		if (!(0 != r12)) { // 275 (0 != r12)
			bool& bOK = al;
			bOK = CFStringGetCString((__CFString*)cfobject, (char*)&_1030, 0x1000, 0x8000100);
			// 309 call
			r12 = (false != bOK) ? &_1030 : 0;
			// 323
			if (false == bOK) { // 317 (0 == al)
				// inline goto _f730;
					 // 738 call
				((CA::Render::Encoder*)this)->encode_int32((unsigned int)0xffffffff);
				// 743
				// inline goto _b363;
				break;
			}
		} // 329
		  // 335 call
		((CA::Render::Encoder*)this)->encode_int32((unsigned int)r15d);
		// 358 call
		((CA::Render::Encoder*)this)->encode_data((void const*)r12, (unsigned long)strlen(r12) + 1);
	}
						break;		// goto _f706
	case CASE_CFNUMBER: {
		// 394 call
		// 401
		if (false == CFNumberGetValue(cfobject, 0xd, &_1038)) { // 399 (0 == al)
				// inline jmp 685
			_1038 = 0x0;
			// 701 call
			((CA::Render::Encoder*)this)->encode_int64((unsigned long long)0);
			break;
		}
		else { // 401 next
			   // 414
			// inline goto _f698;
			((CA::Render::Encoder*)this)->encode_int64((unsigned long long&)_1038);
			break;
		}
	}
						break;
	case CASE_CFBOOLEAN: {
		// 422 call
		bl = CFBooleanGetValue(cfobject);
		rax = this->_18;
		rcx = this->_18 + 1;
		// 441
		if (!((this->_18 + 1) <= this->_20)) { // 437 (rcx <= r14->_20)
			// 451 call
			((CA::Render::Encoder*)this)->grow((unsigned long)0x1);
			// 456 testb %al, %al
		 // 458
			if (false == ((CA::Render::Encoder*)this)->grow((unsigned long)0x1)) { // 456 (0 == al)
						// inline jmp 706
				break;
			}
			else { // 458 next
				rax = this->_18;
			}
		} // 468
		*(char*)this->_18 = bl;
		this->_18 = this->_18 + 1;
	}
						 break;
	case CASE_CFDATA: {
		return ((CA::Render::Encoder*)this)->encode_data_async((void const*)CFDataGetBytePtr((__CFData*)cfobject),  // 486 call
			(unsigned long)CFDataGetLength((__CFData*)cfobject),	// 497 call
			(void(*)(void const*, void*))& CA::Render::release_cfdata,
			(void*)CFRetain(cfobject));								// 508 call
	}
					  break;
	case CASE_CFARRAY: {
		// 567 call
		r15 = CFArrayGetCount((__CFArray*)cfobject);
		// 581 call
		((CA::Render::Encoder*)this)->encode_int64((unsigned long long)r15);
		ebx = 0;
		// 591
		if (0 == r15) // 588 (0 == r15)
			  // inlin jmp 706
			break;

		do {
		_b593:	 // from 621
			// 599 call
			// 610 call
			((CA::Render::Encoder*)this)->encode_cfobject(CFArrayGetValueAtIndex((__CFArray*)cfobject, (int64_t)rbx));
			++rbx;
			// 621
		} while (r15 != rbx); // 618 (r15 != rbx) goto _b593;
	}
					   break;
	case CASE_CFDICTIONARY: {
		// 628 call
		// 639 call
		((CA::Render::Encoder*)this)->encode_int64((unsigned long long)CFDictionaryGetCount((__CFDictionary*)cfobject));
		return CFDictionaryApplyFunction((__CFDictionary*)cfobject, &CA::Render::encode_dictionary_item, (void*)this);
	}
							break;
	default: {
		_1038 = 0x0;
		// 701 call
		((CA::Render::Encoder*)this)->encode_int64((unsigned long long)0);
	}
			 break;
	}
	return;
}


void CA::Render::Encoder::encode_data_async(void const* dataObject, unsigned long dataLength, void(*release_cfdata)(void const*, void*), void* context)
{
	r14 = context;
	r12 = dataLength;
	r15 = dataObject;
	rbx = this;
	// 26 cmpq $0xfff, %r12
	// 33
	if (dataLength > 0xfff) { // 26 (r12 > 0xfff)
			// gen jmp 93
		goto _f93;
	}
	else {
		r13 = release_cfdata;
		// 44 call
		((CA::Render::Encoder*)this)->encode_int64((unsigned long long)dataLength);
		// 58 call
		((CA::Render::Encoder*)this)->encode_bytes((void const*)dataObject, (unsigned long)dataLength);
		rax = release_cfdata;
		// 69
		if (0 == release_cfdata) { // 66 (0 == rax)
				 // inline jmp 162
			return;
		}
		else { // 69 next
			return release_cfdata(dataObject, context);
		}
	} // 93
_f93:	 // from 33
	r13 = release_cfdata;
	// 106 call
	((CA::Render::Encoder*)this)->encode_int64((unsigned long long) - 0x1);

	SomeWhat*& newWhat = rax;
	// 119 call
	newWhat = (SomeWhat*)x_heap_malloc((x_heap_struct*)this->_0, 0x30);
	newWhat->_8 = 0x1;
	newWhat->_10 = dataObject;
	newWhat->_18 = dataLength;
	newWhat->_20 = release_cfdata;
	newWhat->_28 = context;
	newWhat->_0 = this->_28;
	this->_28 = newWhat;
	++this->_30;
	return;
}

void CA::Render::Encoder::receive_reply(unsigned int reply_port)
{
	// 54 call
	mach_msg((void*)&_70, 0x2, 0, 0x5c, (mach_port)reply_port, 0, (mach_port)0x0);
	return;
}

void CA::Render::Encoder::send_message(unsigned int send_port, unsigned int reply_port)
{
	r8d = reply_port;
	_94 = send_port;
	r9 = this;
	rax = this->_18;
	rcx = this->_18 + 1;
	// 55 cmpq 0x20(%r9), %rcx
	// 59
	if ((this->_18 + 1) <= this->_20) { // 55 (rcx <= r9->_20)
			// inline jmp 94
	_f94:	 // from 59
		*(char*)this->_18 = 0x0;
		this->_18 = this->_18 + 1;
	} // 88
	else if (false == ((CA::Render::Encoder*)this)->grow((unsigned long)0x1)) { // 86 (0 == al)
		r9 = r14;	// restore r9, set to this
		r8d = ebx;	// restore r8d, set to 
				 // gen jmp 105
		goto _f105;
	}
	else { // 88 next
		rax = this->_18;
		// 94
		*(char*)this->_18 = 0x0;
		this->_18 = this->_18 + 1;
	} // 94 105


_f105:	 // from 88
	r15 = this->_30;
	eax = 0;
	r14d = 0x0;
	r13d = 0x0;
	edi = 0x0;
	// 131
	if (!(0 == this->_30)) { // 111 (0 == r15)
		r14 = alloca((this->_30 * 8 + f) & -0x10);
		rcx = this->_28;		// iterator for traverssing this->_28
		r13d = 0;
		// 161 testq %rcx, %rcx
		// 164
		if (!(0 == this->_28)) { // 161 (0 == rcx)
			rdx = &((int64_t*)&r14->_0)[this->_30 - 1];	// (uintptr_t)r14 - 0x8 + r15 * 8
			edi = 0;			// counter for even
			r13d = 0;			// counter for non-even

			SomeWhat** bufferCollection = r14;
			SomeWhat**& itCollection = rdx;
			SomeWhat*& itLink = rcx;
			itCollection = &bufferCollection[this->_30 - 1];
			itLink = this->_28;
			do {
			_b176:	 // from 210
				*itCollection = itLink;
				esi = itLink->_8;
				// 185
				if (!(itLink->_8 != 0x2)) { // 182 (esi != 0x2)
					++rdi;
				} // 192
				  // 195
				else if (!(itLink->_8 != 0x1)) { // 192 (esi != 0x1)
					++r13;
				} // 200
			_f200:	 // from 190
				itLink = itLink->_0;
				itCollection = itCollection - 1;
				// 210
			} while (0 != itLink); // 207 (0 != rcx) goto _b176;

		} // 214
		else {
			edi = 0;
		}

	} // 216
_f216:	 // from 212
	/***
	* the results of last code block from 115 to 216
	*
	*/
	int32_t& count_of_type_0x2 = edi;
	int32_t& count_of_type_0x1 = r13d;
	r10 = this->_18 - this->_10;

	kern_return_t& mach_msg_return = rax;		// &=rax
	bool& is_reply_port_from_mig = _a0;		// &=_a0
	bool& is_message_size_gt_than_0x1000 = _a8;	// &=_a8
	CA::Render::Message*& the_end_of_message = _b0;		// &=_b0;
	CA::Render::Message*& message = rbx;	// &=rbx

	mach_msg_return = 0;
	// 224
	if (!(0 == r10)) {
		int32_t& algined_size_for_msgcontent_type1_and_type2 = r12d;		// &=r12d
		ecx = 0xfffffffc;
		r11 = count_of_type_0x2 * 0xc;			// size of type1 object, is 0xc
		r13 = count_of_type_0x1 * 0x10;			// size of type2 object, is 0x10
		rdx = count_of_type_0x1 * 0x10 + count_of_type_0x2 * 0xc + 0x1c + r10;
		rsi = ((0xfffffffc + 0x3) & rdx) + 0x3;
		r12 = 0x1fffffffc & rsi;					// align 4 bytes
		eax = 0;
		// 288
		if (!(r12 < 0x1000)) { // 281 (r12 < 0x1000)
			r12 = (count_of_type_0x1 * 0x10 + (count_of_type_0x2 * 0xc + 0x1c) + 0x10) & 0xfffffffc;
			eax = 0x1;
		} // 308
		else {
			eax = 0;
		}
		_a8 = rax;			// is_message_size_gt_than_0x1000
		_b0 = rsp;			// the end of message, message + 1
		_b8 = (r12 + 0xf) & -0x10;			// size_of_message
		message = (CA::Render::Message*) alloca((r12 + 0xf) & -0x10);
		ecx = 0;
		// 352
		if (!(0 != reply_port) // 349 (0 != r8d)
			// 360
			&& !(0 == this->_58)) { // 358 (0 == al)
			// 383 call
			reply_port = mig_get_reply_port();
			cl = 0x1;
		} // 414
		else {
			ecx = 0;
		}
		_a0 = ecx;			// is_reply_port_from_mig
		message->_0 = (0 == reply_port) ? 0x80001513 : 0x80000013;
		message->_4 = algined_size_for_msgcontent_type1_and_type2;
		message->_8 = send_port;
		message->_c = reply_port;
		message->_10 = 0x0;
		message->_14 = is_message_size_gt_than_0x1000 + 0x9c42;
		message->_18 = is_message_size_gt_than_0x1000 + r15;
		// 487
		if (!(0 == is_message_size_gt_than_0x1000)) { // 485 (0 == edi)
			/**
			* _1c to _24, quad
			* _24 to _28,
			* _28 to _30
			*/
			message->_1c = this->_10;
			message->_28 = r10d;
			message->_24 = 0x1000100;
			r12 = &message->_2c;
		} // 514
		else {
			rcx = -size_of_message;
			rax = the_end_of_message;
			r12 = (uintptr_t)(the_end_of_message - 1) + 0x1c
				r13 = r13 + r11;
			rdi = (uintptr_t)message + 0x1c + r13;
			rsi = this->_10;
			rdx = r10;
			r13d = reply_port;
			// 554 call
			memcpy((uintptr_t)message + 0x1c + r13, this->_10, r10);
			r8d = r13d;
		}
		// 562
		r13d = reply_port;
		// 568
		if (!(0 == this->_30)) { // 565 (0 == r15)
			eax = 0xff0000;
			SomeWhat** itCollection = r14;

			do {
			_b575:	 // from 662
				int32_t& type = edx;

				rcx = *itCollection;
				edx = (*itCollection)->_8;
				// 584
				if (!((*itCollection)->_8 != 0x2)) { // 581 (edx != 0x2)
					/**
					* type 0x2
					*/
					r12->_0 = (*itCollection)->_10;
					r12->_a = (uint16_t)(uint8_t&)(*itCollection)->_14;
					r12 = r12 + 0xc;		// size shift
				} // 609
				else {
					// 612
					if (!((*itCollection)->_8 != 0x1)) { // 609 (edx != 0x1)
					   /**
					   * type 0x1
					   */
						r12->_0 = (*itCollection)->_10;
						r12->_c = (*itCollection)->_18;
						r12->_8 = (r12->_8 & 0xff0000) | 0x1000100;
						r12 = r12 + 0x10;	// size shift
					}
				}// 655
				++itCollection;
				--r15;
				// 662
			} while (ecx |= 0x1000100); // 640 (ecx |= 0x1000100) goto _b575;

		} // 664
		  // 667 call
		mach_msg_return = ((CA::Render::Message*)message)->send_message();
		ecx = is_reply_port_from_mig;
		// 680
		if (0 == is_reply_port_from_mig) { // 678 (0 == cl)
				// inline jmp 776
				 // 787
			goto _f797;
		}
		else { // 680 next
			   // 695
			if (!(0 != mach_msg_return)) { // 682 (0 != eax)
				rsp = rsp - 0x10;
				rsp->_0 = 0x0;
				rdi = &_90;
				esi = 0x2;
				edx = 0;
				ecx = 0x5c;
				r9d = 0;
				r8d = r13d;
				// 733 call
				mach_msg_return = mach_msg((void*)&_90, 0x2, 0, 0x5c, (mach_port)reply_port, 0, (mach_port)0x0);
				rsp = rsp + 0x10;
			} // 742
			edx = mach_msg_return - 10000002;
			rbx = mach_msg_return;					// save rax (mach_msg_return)
			// 757
			if ((mach_msg_return - 10000002) > 0xe) { // 751 (edx > 0xe)
				  // inline jmp 789
				  // 789 call
				mig_dealloc_reply_port((mach_port)reply_port);
				rax = rbx;				// restore rax, set to mach_msg_return
				goto _f797;
			}
			else
				// 767
				if ((0x4003 & (1 << (mach_msg_return - 10000002))) >= 0) {
					// inline jmp 789
					// 789 call
					mig_dealloc_reply_port((mach_port)reply_port);
					rax = rbx;				// restore rax, set to mach_msg_return
					goto _f797;
				}
				else {
					// 769 call
					mig_put_reply_port((mach_port)reply_port);
					rax = rbx;				// restore rax, set to mach_msg_return
					goto _f797;
				}
		} // 776 unreachale
	} // 797
_f797:	 // from 787
	return mach_msg_return;
}
