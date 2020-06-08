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

void CA::Context::commit_root(CA::Layer* layer, void* unknownCTX)
{
#define transaction ((CA::Transaction*) ((uintptr_t)unknownCTX + 0x0))
#define context ((CA::Context*) ((uintptr_t)unknownCTX + 0x8))							// ? is that right
	// 20
	if (!(layer->_a4 != context->_5c)) {
		return layer->commit_if_needed(transaction, (void(*)(CA::Layer*, unsigned int, unsigned int, void*))&CA::Context::commit_layer, (void*)unknownCTX);
	} // 41
	return;
}

double CA::Context::commit_layer_time(CA::Layer* layer, double givenTime, void* unknownCTX)
{
#define renderEncoder ((CA::Render::Encoder*) ((uintptr_t)unknownCTX + 0x20))
#define renderContext ((CA::Render::Context*) ((uintptr_t)unknownCTX + 0x28))
#define transaction ((CA::Transaction*) ((uintptr_t)unknownCTX + 0x0))
#define layerTime (*(double*) ((uintptr_t)unknownCTX + 0x30))							// ?
#define unknownTime (*(double*) ((uintptr_t)unknownCTX + 0x10))							// ?

	// 13
	if (0. != givenTime) {
		// gen jmp 43
		goto _f43;
	} // 24
	else if (0. <= layerTime) {
		// gen jmp 74
		goto _f74;
	}
	else { // 24 next
		layerTime = unknownTime;
		   // 41
		// goto _f64; inline #0
		// 69 call
		CALayerConvertTime(&layerTime, 0, (CALayer*)layer->_10, transaction);
		return layerTime;
	} // 43
_f43:	// from 13
	unknownTime += givenTime;
_f64:	// from 41
		// 69 call
	CALayerConvertTime(&unknownTime, 0, (CALayer*)layer->_10, transaction);
_f74:	// from 24
	return unknownTime;
}

void CA::Context::commit_layer(CA::Layer* layer, unsigned int flag1, unsigned int flag2, void* unknownCTX)
{
#define renderEncoder ((CA::Render::Encoder*) ((uintptr_t)unknownCTX + 0x20))
#define renderContext ((CA::Render::Context*) ((uintptr_t)unknownCTX + 0x28))
#define transaction ((CA::Transaction*) ((uintptr_t)unknownCTX + 0x0))
#define layerTime (*(double*) ((uintptr_t)unknownCTX + 0x30))							// ?
#define SET_UNKNOWNCTX_FLAG_AND_RETURN	\
		*(char*)((uintptr_t)unknownCTX + 0x38) = 0x1;			\
		return;

	  // 34
	if (!(0x200000 == flag1)) {
		layerTime = 2.;
		// 80 call
		// %r8 = CA::Context::remove_animation(CA::Layer*, __CFString const*, void*)
		// %rcx = CA::Context::commit_animation(CA::Layer*, CA::Render::Animation*, void*)
		// %rdx = CA::Context::commit_layer_time(CA::Layer*, double, void*)
		layer->commit_animations(transaction, 
								(double(*)(CA::Layer*, double, void*))&CA::Context::commit_layer_time,
								(void(*)(CA::Layer*, CA::Render::Animation*, void*))&CA::Context::commit_animation, 
								(void(*)(CA::Layer*, __CFString const*, void*))&CA::Context::remove_animation,
								(void*)unknownCTX);
	} // 85

	CA::Render::Layer*& renderLayer = r12;								// &=r12
	  // 98 call
	renderLayer = layer->copy_render_layer(transaction, flag1, (unsigned int*)&_24);
	// 109
	if (!(0 == renderLayer)) {
		// 118
		if (!(0 == renderEncoder)) {
			// 133 call
			CA::Render::encode_set_object(renderEncoder, (unsigned long)layer, flag1, (CA::Render::Object*)renderLayer, (unsigned int)_24);
		} // 138
		  // 145
		if (!(0 == renderContext)) {
			// 160 call
			renderContext->set_object((unsigned long)layer, flag1, (CA::Render::Object*)renderLayer, (unsigned int)_24);
			// 165
			// goto _f175; inline #0
			layer->did_commit(transaction);
			SET_UNKNOWNCTX_FLAG_AND_RETURN
		} // 167
		  // 170 call
		((CA::Render::Object*)renderLayer)->unref();
	} // 175
_f175:	// from 165
	// 181 call
	layer->did_commit(transaction);
	SET_UNKNOWNCTX_FLAG_AND_RETURN
}

void CA::Context::commit_deleted(unsigned long hkey, unsigned int id, void* unknownCTX)
{
#define renderEncoder ((CA::Render::Encoder*) ((uintptr_t)unknownCTX + 0x20))
#define renderContext ((CA::Render::Context*) ((uintptr_t)unknownCTX + 0x28))

	// 26
	if (!(0 == renderContext)) {
		// 34 call
		renderContext->delete_object((unsigned long)hkey, (unsigned int)id);
	} // 39
	  // 46
	if (!(0 == renderEncoder)) {
		return CA::Render::encode_delete_object(renderEncoder, (unsigned long)hkey, (unsigned int)id);
	} // 69
	return;
}

void CA::Context::commit_animation(CA::Layer* layer, CA::Render::Animation* anima, void* unknownCTX)
{
#define renderEncoder ((CA::Render::Encoder*) ((uintptr_t)unknownCTX + 0x20))
#define renderContext ((CA::Render::Context*) ((uintptr_t)unknownCTX + 0x28))
#define SET_UNKNOWNCTX_FLAG_AND_RETURN	\
		*(char*)((uintptr_t)unknownCTX + 0x38) = 0x1;			\
		return;

	// 26
	if (!(0 == renderContext)) {
		// 34 call
		renderContext->add_animation(unsigned long)layer, (CA::Render::Animation*)anima);
	} // 39
	  // 46
	if (!(0 == renderEncoder)) {
		// 54 call
		CA::Render::encode_add_animation(renderEncoder, (unsigned long)layer, (CA::Render::Animation*)anima);
	} // 59
	SET_UNKNOWNCTX_FLAG_AND_RETURN
}

void CA::Context::commit_command(Command command, unsigned long cmd_arg, void const* unknownCTX)
{
	ebx = command._0;								// via edi, validate till 355
	r14 = command._8;								// via rsi
	r13 = cmd_arg;										// validate till 800
	r15 = unknownCTX;

#define renderEncoder ((CA::Render::Encoder*) ((uintptr_t)unknownCTX + 0x20))
#define renderContext ((CA::Render::Context*) ((uintptr_t)unknownCTX + 0x28))
#define transaction ((CA::Transaction*) ((uintptr_t)unknownCTX + 0x0))
#define SET_UNKNOWNCTX_FLAG_AND_RETURN	\
		*(char*)((uintptr_t)unknownCTX + 0x38) = 0x1;			\
		return;

	// 37
	if ((command._0 - 0x2) > 0x12) {
		SET_UNKNOWNCTX_FLAG_AND_RETURN
	} 

#if 1
	// 43 to 57
	switch (command._0) {
#endif

	case 0:
		// 66
		if (!(0 == renderEncoder)) {
			al = (command._0 == 0x7);
			// 80 call
			CA::Render::encode_order_relative(renderEncoder, (command._0 == 0x7), (unsigned int)command._8);
		} // 85
		// 92
		if (0 == renderContext) {
			SET_UNKNOWNCTX_FLAG_AND_RETURN
		}
		// 110 call
		renderContext->order_relative((command._0 == 0x7), (unsigned int)command._8);
		// 115
		// goto _f1761; inline #0
		SET_UNKNOWNCTX_FLAG_AND_RETURN
	case 1:
			// 127
		if (!(0 == renderEncoder)) {
			// 132 call
			CA::Render::encode_update_layer(renderEncoder, (unsigned long)command._8);
		} // 137
		  // 144
		if (0 == renderContext) {
			SET_UNKNOWNCTX_FLAG_AND_RETURN
		} 
		// 153 call
		renderContext->update_layer((unsigned long)command._8);
		// 158
		// goto _f1761; inline #0
		SET_UNKNOWNCTX_FLAG_AND_RETURN
	case 2:
		// 170
		if (!(0 == renderEncoder)) {
			// 175 call
			CA::Render::encode_remove_all_animations(renderEncoder, (unsigned long)command._8);
		} // 180
		  // 187
		if (0 == renderContext) {
			SET_UNKNOWNCTX_FLAG_AND_RETURN
		}
		// 196 call
		renderContext->remove_all_animations((unsigned long)command._8);
		// 201
		// goto _f1761; inline #0
		SET_UNKNOWNCTX_FLAG_AND_RETURN
	case 3:
		// 213
		if (!(0 == renderEncoder)) {
			// 221 call
			CA::Render::encode_remove_animation(renderEncoder, (unsigned long)command._8, (__CFString const*)cmd_arg);
		} // 226
		  // 233
		if (0 == renderContext) {
			SET_UNKNOWNCTX_FLAG_AND_RETURN
		}
		// 245 call
		renderContext->remove_animation((unsigned long)command._8, (__CFString const*)cmd_arg);
		// 250
		// goto _f1761; inline #0
		SET_UNKNOWNCTX_FLAG_AND_RETURN
	case 4:
		// 262
		if (!(0 == renderEncoder)) {
			// 267 call
			CA::Render::encode_set_layer_id(renderEncoder, (unsigned long)command._8);
		} // 272
		  // 279
		if (0 == renderContext) {
			SET_UNKNOWNCTX_FLAG_AND_RETURN
		}
		// 288 call
		renderContext->set_layer_id((unsigned long)command._8);
		// 293
		// goto _f1761; inline #0
		SET_UNKNOWNCTX_FLAG_AND_RETURN
	case 5:
		float& level = xmm0.ss;
		// 301 call
		level = CA_CFFloatValue(cmd_arg);
		// 313
		if (!(0 == renderEncoder)) {
			// 325 call
			CA::Render::encode_order_level(renderEncoder, (float)level);
		} // 335
		  // 342
		if (0 == renderContext) {
			SET_UNKNOWNCTX_FLAG_AND_RETURN
		}
		// 348 call
		CA::Render::Context::order_level((float)level);
		// 353
		// goto _f1761; inline #0
		SET_UNKNOWNCTX_FLAG_AND_RETURN
	case 6:
		CA::Render::Object*& slotValue = rbx;
		// 361 call
		slotValue = CA::Render::copy_render_value((void const*)cmd_arg);
		// 376
		if (!(0 == renderEncoder)) {
			// 384 call
			CA::Render::encode_set_slot(renderEncoder, (unsigned int)command._8, (CA::Render::Object*)slotValue);
		} // 389
		  // 396
		if (0 == renderContext) {
			// gen jmp 1519
			// goto _f1519; inline #0
			// 1522
			if (0 == slotValue) {
				SET_UNKNOWNCTX_FLAG_AND_RETURN
			}
			// 1531 call
			CA::Render::Object::unref() const;;
			// 1536
			// goto _f1761; inline #1
			SET_UNKNOWNCTX_FLAG_AND_RETURN
		}
		else { // 396 next
			   // 408 call
			renderContext->set_slot((unsigned int)command._8, (CA::Render::Object*)slotValue);
			// 413
			// goto _f1519; inline #0
			// 1522
			if (0 == slotValue) {
				SET_UNKNOWNCTX_FLAG_AND_RETURN
			}
			// 1531 call
			CA::Render::Object::unref() const;;
			// 1536
			// goto _f1761; inline #1
			SET_UNKNOWNCTX_FLAG_AND_RETURN
		}
	case 7:
		// 425
		if (!(0 == renderEncoder)) {
			// 430 call
			CA::Render::encode_delete_slot(renderEncoder, (unsigned int)command._8);
		} // 435
		  // 442
		if (0 == renderContext) {
			SET_UNKNOWNCTX_FLAG_AND_RETURN
		}
		// 451 call
		renderContext->delete_slot((unsigned int)command._8);
		// 456
		// goto _f1761; inline #0
		SET_UNKNOWNCTX_FLAG_AND_RETURN
	case 8:
		// 468
		if (!(0 == renderEncoder)) {
			// 473 call
			CA::Render::encode_flush_image_queue(renderEncoder, (unsigned int)command._8);
		} // 478
		  // 485
		if (0 == renderContext) {
			SET_UNKNOWNCTX_FLAG_AND_RETURN
		}
		// 494 call
		renderContext->flush_image_queue((unsigned int)command._8);
		// 499
		// goto _f1761; inline #0
		SET_UNKNOWNCTX_FLAG_AND_RETURN
	case 9:						
		CGColor*& cvtColor = rbx;						// &=rbx
		cvtColor = 0;
		// 511 call
		;
		// 519 call
		_68 = CA_CFIntValue(CFArrayGetValueAtIndex((__CFArray*)cmd_arg, 0));
		// 535 call
		;
		// 543 call
		_64 = CA_CFIntValue(CFArrayGetValueAtIndex((__CFArray*)cmd_arg, 1));
		// 559 call
		;
		// 567 call
		_4c = CA_CFIntValue(CFArrayGetValueAtIndex((__CFArray*)cmd_arg, 2));
		// 583 call
		;
		// 591 call
		_50 = CA_CFIntValue(CFArrayGetValueAtIndex((__CFArray*)cmd_arg, 3));
		// 607 call
		;
		// 615 call
		_54 = CA_CFIntValue(CFArrayGetValueAtIndex((__CFArray*)cmd_arg, 4));
		// 631 call
		;
		// 639 call
		_6c = CA_CFIntValue(CFArrayGetValueAtIndex((__CFArray*)cmd_arg, 5));
		// 655 call
		;
		// 663 call
		_58 = CA_CFIntValue(CFArrayGetValueAtIndex((__CFArray*)cmd_arg, 6));
		// 679 call
		;
		// 687 call
		_5c = CA_CFIntValue(CFArrayGetValueAtIndex((__CFArray*)cmd_arg, 7));
		// 703 call
		;
		// 711 call
		_60 = CA_CFIntValue(CFArrayGetValueAtIndex((__CFArray*)cmd_arg, 8));
		// 745 call
		;
		// 753 call
		r12d = CA_CFIntValue(CFArrayGetValueAtIndex((__CFArray*)cmd_arg, 9));
		extern void* kCFNull;
		// 769 call
		rbx = ((rax = CFArrayGetValueAtIndex((__CFArray*)cmd_arg, 10)) != kCFNull) ? rax : rbx;
		// 791 call
		// %rcx = (void *)0x0000000103d23de0: kCFNull
		;
		// 817 call
		CA::Render::convert_cgcolor((CGColor*)cvtColor,
			(CGColorSpace*)CA::Context::current_colorspace(transaction),
			(unsigned int&)_2c, (CA::Render::Pattern**)&_38);
		ebx = _6c;
		r13d = _68;
		// 829
		if (!(0 == renderEncoder)) {
			// 905 call
			CA::Render::encode_image_provider_create(renderEncoder,
				(unsigned long)command._8,
				(unsigned int)_68,				// via r13d		#0
				(unsigned int)_64,				//				#1
				(unsigned int)_4c,				//				#2
				(unsigned int)_50,				//				#3
				(unsigned int)_54,				// (%rsp)		#4
				(unsigned int)_6c,				// via ebx		#5
				(unsigned int)_58,				//				#6
				(bool)(_5c != 0),				//				#7
				(float)(float&)_60,				//				#8
				(int)r12d,						//				#9
				(unsigned int)_2c,
				(CA::Render::Pattern*)_38);
		} // 910
		  // 939
		if (0 == renderContext) {
			SET_UNKNOWNCTX_FLAG_AND_RETURN
		}
		// 1000 call
		CA::Render::ImageProvider::create(renderContext,
			(unsigned long)command._8,
			(unsigned int)cmd_arg,
			(unsigned int)_64,				//				#1
			(unsigned int)_4c,				//				#2
			(unsigned int)_50,				//				#3
			(unsigned int)_54,				// (%rsp)		#4
			(unsigned int)_6c,				// via ebx		#5
			(unsigned int)_58,				//				#6
			(bool)(_5c != 0),				//				#7
			(float)(float&)_60,				//				#8
			(int)r12d,						//				#9
			(unsigned int)_2c,
			(CA::Render::Pattern*)_38);
		// 1005
		// goto _f1761; inline #0
		SET_UNKNOWNCTX_FLAG_AND_RETURN
	case 10:
		// 1015 call
		;
		// 1023 call
		r12d = CA_CFIntValue(CFArrayGetValueAtIndex((__CFArray*)cmd_arg, 0));
		// 1039 call
		;
		// 1047 call
		ebx = CA_CFIntValue(CFArrayGetValueAtIndex((__CFArray*)cmd_arg, 1));
		// 1061
		if (!(0 == renderEncoder)) {
			// 1071 call
			CA::Render::encode_image_provider_set_image_size(renderEncoder, (unsigned long)command._8, (unsigned int)r12d, (unsigned int)ebx);
		} // 1076
		  // 1083
		if (0 == renderContext) {
			SET_UNKNOWNCTX_FLAG_AND_RETURN
		}
		// 1097 call
		CA::Render::ImageProvider::set_image_size(renderContext, (unsigned long)command._8, (unsigned int)r12d, (unsigned int)ebx);
		// 1102
		// goto _f1761; inline #0
		SET_UNKNOWNCTX_FLAG_AND_RETURN
	case 11:
		{
			CGColor*& cvtColor = rbx;						// &=rbx
			cvtColor = 0;
			extern void* kCFNull;
			// 1114 call
			cvtColor = ((rax = CFArrayGetValueAtIndex((__CFArray*)cmd_arg, 0)) != kCFNull) ? rax : cvtColor;
			// 1136 call
			// %rcx = (void *)0x0000000103d23de0: kCFNull
			;
			// 1155 call
			CA::Render::convert_cgcolor((CGColor*)cvtColor,
				(CGColorSpace*)CA::Context::current_colorspace(transaction),
				(unsigned int&)_3c,
				(CA::Render::Pattern**)&_48);
			// 1167
			if (!(0 == renderEncoder)) {
				// 1179 call
				CA::Render::encode_image_provider_set_fill_color(renderEncoder, (unsigned long)command._8, (unsigned int)_3c, (CA::Render::Pattern*)_48);
			} // 1184
			  // 1191
			if (0 == renderContext) {
				SET_UNKNOWNCTX_FLAG_AND_RETURN
			}
			// 1207 call
			CA::Render::ImageProvider::set_fill_color(renderContext, (unsigned long)command._8, (unsigned int)_3c, (CA::Render::Pattern*)_48);
			// 1212
			// goto _f1761; inline #0
			SET_UNKNOWNCTX_FLAG_AND_RETURN
		}
	case 12:
		{
			// 1222 call
			;
			// 1230 call
			ebx = CA_CFIntValue(CFArrayGetValueAtIndex((__CFArray*)cmd_arg, 0));
			// 1244
			if (!(0 == renderEncoder)) {
				// 1251 call
				CA::Render::encode_image_provider_set_max_tile_scale(renderEncoder, (unsigned long)command._8, (int)ebx);
			} // 1256
			  // 1263
			if (0 == renderContext) {
				SET_UNKNOWNCTX_FLAG_AND_RETURN
			}
			// 1274 call
			CA::Render::ImageProvider::set_max_tile_scale(renderContext, (unsigned long)command._8, (int)ebx);
			// 1279
			// goto _f1761; inline #0
			SET_UNKNOWNCTX_FLAG_AND_RETURN
		}
	case 13:
		{
			rbx = 0;
			// 1291 call
			;
			// 1299 call
			_54 = CA_CFIntValue(CFArrayGetValueAtIndex((__CFArray*)cmd_arg, 0));
			// 1315 call
			;
			// 1323 call
			_4c = CA_CFIntValue(CFArrayGetValueAtIndex((__CFArray*)cmd_arg, 1));
			// 1339 call
			;
			// 1347 call
			_50 = CA_CFIntValue(CFArrayGetValueAtIndex((__CFArray*)cmd_arg, 2));
			// 1363 call
			rbx = ((rax = CFArrayGetValueAtIndex((__CFArray*)cmd_arg, 3)) != kCFNull) ? rax : rbx;
			// 1390 call
			// %rcx = (void *)0x0000000103d23de0: kCFNull
			;
			// 1398 call
			r12 = CA_CFIntValue(CFArrayGetValueAtIndex((__CFArray*)cmd_arg, 4));
			// 1414 call
			;
			// 1422 call
			r13 = CA_CFIntValue(CFArrayGetValueAtIndex((__CFArray*)cmd_arg, 5));
			// 1433 call
			rbx = CA::Render::copy_render_value((void const*)rbx);
			// 1448
			if (!(0 == renderEncoder)) {
				// 1475 call
				CA::Render::encode_image_provider_set_subimage(renderEncoder, 
																(unsigned long)command._8, 
																(unsigned int)_54,						// #0
																(unsigned int)_4c,						// #1
																(unsigned int)_50,						// #2
																(CA::Render::Texture*)rbx, 						// #3
																(unsigned int)r12,						// #4 
																(unsigned int)r13);						// #5
			} // 1480
			  // 1494
			if (!(0 == renderContext)) {
				// 1514 call
				CA::Render::ImageProvider::set_subimage(renderContext,
																(unsigned long)command._8,
																(unsigned int)_54,						// #0
																(unsigned int)_4c,						// #1
																(unsigned int)_50,						// #2
																(CA::Render::Texture*)rbx, 						// #3
																(unsigned int)r12,						// #4 
																(unsigned int)r13);						// #5

			} // 1519
		} // 1519
	_f1519:	// from 396
	_f1519:	// from 413
		if (0 == slotValue) {
			SET_UNKNOWNCTX_FLAG_AND_RETURN
		}
		// 1531 call
		((CA::Render::Object*)rbx)->unref();
		// 1536
		// goto _f1761; inline #1
		SET_UNKNOWNCTX_FLAG_AND_RETURN}
	case 14:
		{
			// 1546 call
			;
			// 1554 call
			rbx = CA_CFIntValue(CFArrayGetValueAtIndex((__CFArray*)cmd_arg, 0));
			// 1569 call
			;
			// 1577 call
			_4c = CA_CFIntValue(CFArrayGetValueAtIndex((__CFArray*)cmd_arg, 1));
			// 1593 call
			;
			// 1601 call
			_50 = CA_CFIntValue(CFArrayGetValueAtIndex((__CFArray*)cmd_arg, 2));
			// 1617 call
			;
			// 1625 call
			_54 = CA_CFIntValue(CFArrayGetValueAtIndex((__CFArray*)cmd_arg, 3));
			// 1641 call
			;
			// 1649 call
			r12 = CA_CFIntValue(CFArrayGetValueAtIndex((__CFArray*)cmd_arg, 4));
			// 1668 call
			;
			// 1676 call
			r13 = rbx;
			rbx = CA_CFIntValue(CFArrayGetValueAtIndex((__CFArray*)cmd_arg, 5));
			// 1690
			if (!(0 == renderEncoder)) {
				// 1717 call
				CA::Render::encode_image_provider_invalidate(renderEncoder, 
																(unsigned long)command._8,
																(int)r13,						// #0
																(int)_4c,						// #1
																(int)_50,						// #2
																(int)_54, 						// #3
																(unsigned int)r12,						// #4 
																(unsigned int)rbx);						// #5
			} // 1722
			  // 1740
			if (!(0 == renderContext)) {
				// 1756 call
				CA::Render::ImageProvider::invalidate(renderContext, 
														(unsigned long)command._8,
														(int)r13,						// #0
														(int)_4c,						// #1
														(int)_50,						// #2
														(int)_54, 						// #3
														(unsigned int)r12,						// #4 
														(unsigned int)rbx);						// #5

			} // 1761
		} // 1761
		SET_UNKNOWNCTX_FLAG_AND_RETURN
#if 1
	}
#endif
	SET_UNKNOWNCTX_FLAG_AND_RETURN
}