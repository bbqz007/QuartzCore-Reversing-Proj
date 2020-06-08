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

//+ [UIView(Animation) beginAnimations:context:]
void UIView28_Animation29_20_beginAnimations3A_context3A_(id self, SEL sel, id animations, id context)
{
	return objc_msgSend(UIViewAnimationState, "pushViewAnimationState:context:", animations, context);
}

// +[UIViewAnimationState pushViewAnimationState:context:]
void UIViewAnimationState20_pushViewAnimationState3A_context3A_(id self, SEL sel, id animationState, id context)
{
	UIViewAnimationState*& newAnimationState = r13;
	r15 = context;
	rbx = self;
	// 23 call
	r14 = (objc_object*)objc_retain((objc_object*)animationState);
	// 49 call
	// 62 call
	newAnimationState = objc_msgSend(objc_msgSend(UIViewAnimationState, "alloc"), "init");
	// 71
	if (!(0 == newAnimationState)) { // 68 (0 == r13)
			 // 87 call
		newAnimationState->_animationID._0 = objc_msgSend(r14, "copy");
		// 110 call
		objc_release((objc_object*)r13->_animationID._0);
		newAnimationState->_context._0 = context;
		newAnimationState->_duration._0 = 0x3fc999999999999a;
		r15 = & __currentViewAnimationState;
		// 174 call
		objc_storeStrong(&newAnimationState->_nextState, __currentViewAnimationState);
		// 185 call
		objc_storeStrong(&__currentViewAnimationState, newAnimationState);

		extern ent_off__0xc4fde2;	// cmpb $0x0, 0xc4fd1d(%rip);	 __KeyWindowStackEnabled + 975
		// 197
		if (!((int8_t&)ent_off__0xc4fde2 == 0x0)) { // 190 ((int8_t&)rip->_c4fd1d == 0x0)
				 // 206 call
				 r15 = (objc_object*)objc_retain((objc_object*)animationState);
				 extern __CFString* UICalloutBarAnimationFade;
			// 235 call
			// 243
			if (!(false == objc_msgSend(r15, "isEqualToString:", UICalloutBarAnimationFade))) { // 241 (0 == al)
					 // 248 call
				objc_release((objc_object*)r15);
			} // 256
			else {
				extern __CFString* UITextSelectionViewAnimation;
				// 276 call
				r12b = (bool)objc_msgSend(r15, "isEqualToString:", UITextSelectionViewAnimation);
				// 288 call
				objc_release((objc_object*)r15);
				// 297
				if (!(false != r12b)) { // 294 (0 != r12b)
					extern id __alongsideAnimationStateBlock;
					// 309
					if (!(0 == __alongsideAnimationStateBlock)) { // 306 (0 == rdx)
							 // 321 call
						objc_msgSend(newAnimationState, "_setAlongsideAnimations:", __alongsideAnimationStateBlock);
						extern (__trackedAnimationMapping + 4);
						__trackedAnimationMapping + 4 = 0x0;
						// 345 call
						objc_release((objc_object*)__alongsideAnimationStateBlock);
					} // 351
					extern id __currentlyTrackedAnimation;
					// 361
					if (!(0 == __currentlyTrackedAnimation)) { // 358 (0 == rdx)
							 // 373 call
						objc_msgSend(newAnimationState, "_addAnimationStateForTracking:", __currentlyTrackedAnimation);
					} // 379
				}
			} // 379
		} // 379
	} // 379
_f379:	 // from 254
	  // 389 call
	objc_release((objc_object*)r13);
	return objc_release(r14);
}


// +[UIView(UIViewAnimationWithBlocks) animateWithDuration:animations:completion:]
UIView28_UIViewAnimationWithBlocks29_20_animateWithDuration3A_animations3A_completion3A_(id self, SEL sel, double dura, block_pointer animations, block_pointer completion)
{
	r15 = completion;
	(double&)_20 = dura;
	r14 = self;
	// 27 call
	rbx = (objc_object*)objc_retain((objc_object*)animations);
	// 86 call
	objc_msgSend(self, "_setupAnimationWithDuration:delay:view:options:factory:animations:start:animationStateGenerator:completion:", 
		dura, 0., 0, 0, 0, animations, 0, 0, completion);
	return objc_release((objc_object*)animations);
}

// +[UIView(UIViewAnimationWithBlocks) _setupAnimationWithDuration:delay:view:options:animations:start:completion:]
UIView28_UIViewAnimationWithBlocks29_20__setupAnimationWithDuration3A_delay3A_view3A_options3A_animations3A_start3A_completion3A_(id self, SEL sel, double dura, double delay, id view, int options, block_pointer animations, int start, block_pointer completion)
{
	r15 = start;
	rbx = animations;
	_30 = options;
	(double&)_38 = delay;
	(double&)_40 = dura;
	_48 = self;
	_50 = completion;
	// 59 call
	r12 = (objc_object*)objc_retain((objc_object*)view);
	// 68 call
	r14 = (objc_object*)objc_retain((objc_object*)animations);
	// 77 call
	rbx = (objc_object*)objc_retain((objc_object*)start);
	// 139 call
	objc_msgSend(self, "_setupAnimationWithDuration:delay:view:options:factory:animations:start:animationStateGenerator:completion:",
				dura, delay, view, options, 0, animations, start, 0, completion);
	// 155 call
	objc_release((objc_object*)start);
	// 161 call
	objc_release((objc_object*)animations);
	objc_release((objc_object*)view);
}
