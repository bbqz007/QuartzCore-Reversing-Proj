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

#include "UIKit.UIView.h"

extern double LastFlush;

// +[UIView(Rendering) flush]
void UIView28_Rendering29_20_flush(id self, SEL sel)
{
	// 18 call
	objc_msgSend(CATransaction, "flush");
	// 24 call
	LastFlush = CACurrentMediaTime();
}

// +[UIView(Rendering) throttledFlush]
void UIView28_Rendering29_20_throttledFlush(id self, SEL sel)
{

}


// +[UIView(Internal) _transitionFromView:toView:duration:options:animations:completion:]
void UIView28_Internal29_20__transitionFromView3A_toView3A_duration3A_options3A_animations3A_completion3A_(
	id self, SEL sel, UIView* _transitionFromView, UIView* toView, double duration, uintptr_t options, block_pointer animations, block_pointer completion)
{
	r15 = animations;
	_d8 = options;
	(double&)_d0 = duration;
	rbx = toView;
	_e0 = self;
	r13 = completion;
	r14 = (void *)0x00000001070a1d00: objc_retain;
	// 62 call
	r12 = (objc_object*)objc_retain((objc_object*)_transitionFromView);
	// 71 call
	rbx = (objc_object*)objc_retain((objc_object*)toView);
	_e8 = toView;
	// 87 call
	_f0 = (objc_object*)objc_retain((objc_object*)animations);
	// 100 call
	_f8 = (objc_object*)objc_retain((objc_object*)completion);
	// 134 call
	// 143 call
	_100 = (objc_object*)objc_retainAutoreleasedReturnValue(
					(objc_object*)objc_msgSend(UIViewController, "viewControllerForView:", toView));
	UIViewController*& toViewController = _100;	// &=_100
	r15 = _transitionFromView;
	// 175 call
	// 180 call
	r12 = (objc_object*)objc_retainAutoreleasedReturnValue(
					(objc_object*)objc_msgSend(UIViewController, "viewControllerForView:", _transitionFromView));
	UIViewController*& fromViewController = r12;		// &=r12
	// 198 call
	// 203 call
	_108 = (objc_object*)objc_retainAutoreleasedReturnValue(
					(objc_object*)objc_msgSend(_transitionFromView, "superview"));
	UIView*& superview = _108;		// &=_108
	extern Class _NSConcreteStackBlock;
	/**
	* animaBlock = ^{
	*	fromViewController;
	*	toViewController;
	*	_transitionFromView;
	*	toView;
	*	animations;
	* }
	*/
	struct _NSConcreteStackBlock& animaBlock = *(struct _NSConcreteStackBlock*)&_80;
	animaBlock.isa = _NSConcreteStackBlock;
	animaBlock.flag = 0xc2000000;
	animaBlock.refcnt = 0x0;
	animaBlock.invoke = &__86 + [UIView(Internal) _transitionFromView:toView:duration:options:animations:completion:]_block_invoke;
	animaBlock.descriptor = &__block_descriptor_tmp2958;
	// 265 call
	r13 = (objc_object*)objc_retain((objc_object*)fromViewController);
	MACRO_NSStackBlock_SET_PRIVSTACK(animaBlock, 0, UIViewController*, fromViewController);
	_30 = (duration > 0.);
	// 302 call
	r12 = (objc_object*)objc_retain((objc_object*)toViewController);
	MACRO_NSStackBlock_SET_PRIVSTACK(animaBlock, 0x8, UIViewController*, toViewController);
	// 315 call
	r15 = (objc_object*)objc_retain((objc_object*)_transitionFromView);
	MACRO_NSStackBlock_SET_PRIVSTACK(animaBlock, 0x10, UIView*, _transitionFromView);
	MACRO_NSStackBlock_SET_PRIVSTACK(animaBlock, 0x18, UIView*, toView);-
	// 336 call
	_e8 = (objc_object*)objc_retain((objc_object*)toView);
	rdi = animations;
	_40 = animations;
	MACRO_NSStackBlock_SET_PRIVSTACK(animaBlock, 0x20, block_pointer, animations);
	rbx = options;
	_38 = options;

	struct _NSConcreteStackBlock& completionBlock = *(struct _NSConcreteStackBlock*)&_c8;
	completionBlock.isa = _NSConcreteStackBlock;
	_ccompletionBlock.flag = 0xc2000000;
	completionBlock.refcnt = 0x0;
	completionBlock.invoke = &__86 + [UIView(Internal) _transitionFromView:toView:duration:options:animations:completion:]_block_invoke2959;
	completionBlock.descriptor = &__block_descriptor_tmp2964;
	// 430 call
	_f0 = (objc_object*)objc_retain((objc_object*)animations);
	_a8 = r12;
	MACRO_NSStackBlock_SET_PRIVSTACK(completionBlock, 0x0, UIViewController*, toViewController);
	MACRO_NSStackBlock_SET_PRIVSTACK(completionBlock, 0x18, uintptr_t, options);
	_88 = options;
	// 457 call
	_100 = (objc_object*)objc_retain((objc_object*)toViewController);
	_a0 = _transitionFromView;
	MACRO_NSStackBlock_SET_PRIVSTACK(completionBlock, 0x8, UIView*, _transitionFromView);
	// 477 call
	_110 = (objc_object*)objc_retain((objc_object*)_transitionFromView);
	_98 = fromViewController;
	MACRO_NSStackBlock_SET_PRIVSTACK(completionBlock, 0x10, UIViewController*, fromViewController);
	// 497 call
	r13 = (objc_object*)objc_retain((objc_object*)fromViewController);
	_90 = completion;
	MACRO_NSStackBlock_SET_PRIVSTACK(completionBlock, 0x20, block_pointer, completion);
	// 524 call
	r15 = (objc_object*)objc_retain((objc_object*)completion);
	// 587 call
	objc_msgSend(self, "_setupAnimationWithDuration:delay:view:options:animations:start:completion:", duration, 0., superview, options, animaBlock, 0, completionBlock);
	// 603 call
	objc_release((objc_object*)superview);
	rdi = _90;
	// 613 call
	objc_release((objc_object*)completion);
	rdi = _98;
	// 623 call
	objc_release((objc_object*)fromViewController);
	rdi = _a0;
	// 633 call
	objc_release((objc_object*)_transitionFromView);
	rdi = _a8;
	// 643 call
	objc_release((objc_object*)toViewController);
	rdi = _40;
	// 650 call
	objc_release((objc_object*)animations);
	rdi = _48;
	// 657 call
	objc_release((objc_object*)toView);
	rdi = _50;
	// 664 call
	objc_release((objc_object*)_transitionFromView);
	rdi = _58;
	// 671 call
	objc_release((objc_object*)toViewController);
	rdi = _60;
	// 678 call
	objc_release((objc_object*)fromViewController);
	rdi = r15;
	// 684 call
	objc_release((objc_object*)completion);
	rdi = r13;
	// 690 call
	objc_release((objc_object*)fromViewController);
	rdi = _110;
	// 700 call
	objc_release((objc_object*)_transitionFromView);
	rdi = _100;
	// 710 call
	objc_release((objc_object*)toViewController);
	rdi = _f0;
	// 720 call
	objc_release((objc_object*)animations);
	rdi = _e8;
	// 730 call
	objc_release((objc_object*)toView);
}



// +[UIView(UIViewAnimationWithBlocks) _setupAnimationWithDuration:delay:view:options:factory:animations:start:animationStateGenerator:completion:]
void UIView28_UIViewAnimationWithBlocks29_20__setupAnimationWithDuration3A_delay3A_view3A_options3A_factory3A_animations3A_start3A_animationStateGenerator3A_completion3A_(
	id self, SEL sel, double _setupAnimationWithDuration, double delay, UIView* view, uintptr_t options, uintptr_t factory, block_pointer animations, uintptr_t start, UIViewAnimationState* animationStateGenerator, block_pointer completion)
{
	r14 = animations;
	rbx = factory;
	_30 = options; 
	(double&)_68 = delay;
	(double&)_70 = _setupAnimationWithDuration;
	_50 = self;
	_48 = completion;
	r12 = animationStateGenerator;
	r13 = start;
	r15 = (void *)0x00000001070a1d00: objc_retain;
	// 67 call
	_58 = (objc_object*)objc_retain((objc_object*)view);
	// 77 call
	_38 = (objc_object*)objc_retain((objc_object*)factory);
	// 87 call
	(objc_object*)objc_retain((objc_object*)animations);
	// 96 call
	_40 = (objc_object*)objc_retain((objc_object*)start);
	// 106 call
	r12 = (objc_object*)objc_retain((objc_object*)animationStateGenerator);
	// 116 call
	_48 = (objc_object*)objc_retain((objc_object*)completion);
	extern UIViewAnimationState* __currentViewAnimationState;
	// 130 call
	r15 = (objc_object*)objc_retain((objc_object*)__currentViewAnimationState);
	// 146
	if (!(0 == (0x400 & options))) { // 140 (0 == (0x4 & ah))
		// 173
		if (false == objc_msgSend(self, "_isAnimationTracking")) { // 168 (0 == al)
				 // inline jmp 184
			// 191 call
			// 200 call
			// 208 call
			objc_release(
					(objc_object*)objc_retainAutoreleasedReturnValue(
							(objc_object*)objc_msgSend(self, "_startAnimationTracking")));
			_5c = true;
		}
		rdi = self;
	}
	  _5c = 0x0;
	  // 182
	goto _f219;

_f219:	 // from 182
		 rbx = start;
		 // 225
	if (!(0x200 & start)) { // 222 (0x2 & bh)
			 // 252 call
		// 267 call
		// 271
		if (!(NO == objc_msgSend(__currentViewAnimationState, "isKindOfClass:",
								objc_msgSend(UIViewSpringAnimationState, "class")))) { // 269 (0 == al)
				 rbx = (void *)0x00000001064419a0: UIViewSpringAnimationState;
				 rdi = r15;
				 // 287 call
				 r13 = (objc_object*)objc_retain((objc_object*)__currentViewAnimationState);
			// 310 call
			objc_msgSend(UIViewSpringAnimationState, "pushViewAnimationState:context:", 0, 0);
			__currentViewAnimationState->_mass._0 = __currentViewAnimationState->_mass._0;
			__currentViewAnimationState->_stiffness._0 = __currentViewAnimationState->_stiffness._0;
			__currentViewAnimationState->_damping._0 = __currentViewAnimationState->_damping._0;
			__currentViewAnimationState->_velocity._0 = __currentViewAnimationState->_velocity._0;
			// 402 call
			objc_release((objc_object*)__currentViewAnimationState);
			r13 = view;
			// 412
			goto _f457;
		} // 414
	} // 414
	  r13 = view;
	  // 421
	if (!(0 == animationStateGenerator)) { // 414 (0 == r12)
			 // 426 call
			(* animationStateGenerator->_8)();
		// 431
		goto _f457;
	} // 433
	else {
		extern Class UIViewAnimationState;
		// 451 call
		objc_msgSend(UIViewAnimationState, "pushViewAnimationState:context:", 0, 0);
	}
_f457:	 // from 431
_f457:	 // from 412
		 // 467
	if (!(0 == __currentViewAnimationState)) { // 464 (0 == rdi)
			 // 521 call
		objc_msgSend(__currentViewAnimationState, "setupWithDuration:delay:view:options:factory:parentState:start:completion:", 
			view, options, factory, animationStateGenerator, start, completion);
		// 546
		if (!(__currentViewAnimationState->_transition == 0x0)) { // 541 (rax->rcx == 0x0)
				 bl = (0 == (0x4 & __currentViewAnimationState->_cacheTransition));
		} // 564
		else {
			ebx = 0;
		}
			 // 569
		if (!(0 == animations)) { // 566 (0 == r14)
				 // 573
			if (!(0 != bl)) { // 571 (0 != bl)
					 // 578 call
					 animations->invoke(animations);
			} // 582
		} // 582
		  // 596 call
		objc_msgSend(UIViewAnimationState, "popAnimationState");
		// 605
		if (!(0 == animations)) { // 602 (0 == r14)
				 bl = !(bool)bl;
				 // 610
			if (!(true == bl)) {
				// 679 call
				objc_msgSend(self, "_setupAnimationWithDuration:delay:view:options:factory:animations:start:animationStateGenerator:completion:", 
								_setupAnimationWithDuration, delay, 0, options & -0x700081, factory, animations, 0, 0, 0);
			} // 685
		} // 685
	} // 685
	  eax = _5c;
	  // 690
	if (!(0 == _5c)) { // 688 (0 == al)
		/**
		* should be couple with _startAnimationTracking.
		*/
			 // 703 call
		objc_msgSend(self, "_finishAnimationTracking");
	} // 709
	  rbx = (void *)0x00000001070a1d70: objc_release;
	  
	  rdi = r15;
	  // 719 call
	objc_release((objc_object*)__currentViewAnimationState);
	rdi = _48;
	// 725 call
	objc_release((objc_object*)completion);
	rdi = r12;
	// 730 call
	objc_release((objc_object*)animationStateGenerator);
	rdi = _40;
	// 736 call
	objc_release((objc_object*)start);
	rdi = r14;
	// 741 call
	objc_release((objc_object*)animations);
	rdi = _38;
	// 747 call
	objc_release((objc_object*)factory);
	rdi = r13;
	return objc_release(view);
}
