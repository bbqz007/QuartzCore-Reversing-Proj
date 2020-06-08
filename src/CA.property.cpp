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

void CA::Layer::property_did_change(CA::Transaction* transaction, unsigned int flag)
{
	r14d = flag;						// immutable till 1234
	rbx = transaction;					// mutable
	r15 = this;
	_40 = transaction;					// immutable
	CA::Layer::State*& state = r12;		// till 1216

										//
	extern ent_off__0x8c0;				// 68 	leaq 0x875(%rip), %rcx;	 <+2240>
										// 121 extern ent_off__0x898;	leaq 0x818(%rip), %rcx;	 <+2200>
										// 409 extern ent_off__0x840;	leaq 0x6a0(%rip), %rcx;	 <+2112>
										// 569 extern ent_off__0x7b8;	leaq 0x578(%rip), %rcx;	 <+1976>
										// 742 extern ent_off__0x81c;	leaq 0x52f(%rip), %rcx;	 <+2076>
										// 809 extern ent_off__0x790;	leaq 0x460(%rip), %rcx;	 <+1936>
										// 886 extern ent_off__0x830;	leaq 0x4b3(%rip), %rcx;	 <+2096>

										// 26 call
	state = this->writable_state(transaction);
	r13d = 0x8000;

	/**
	* 95 to 644 , flag > 0x28
	* 1208 flag < 0x17
	* 644 (0x18, 0x27)
	*/
	// 46
	if (flag > 0x28) { // 42 (r14d > 0x28)
					   // gen jmp 95
		goto _f95;
	}
	else {
		rbx = this;				// via r15
								// 62 
		if ((flag - 0x2) > 0x15) { // 56 (eax > 0x15)
								   // gen jmp 1208
			goto _f1208;
		}
		else { // 62 next
			switch (flag)
				// 90
				goto _f644;

		}
	}// 95
_f95:	 // from 46
		 // 99
	if () { // 95 (r14d > 0x38)
			// gen jmp 148
		goto _f148;
	} // 115
	else if () { // 109 (eax > 0x9)
				 // gen jmp 1208
		goto _f1208;
	}
	else { // 115 next
		   // 143
		goto _f1216;
	} // 148
_f148:	 // from 99
		 // 155
	if () { // 148 (r14d > 0x103)
			// gen jmp 216
		goto _f216;
	} // 164
	else if () { // 157 (r14d > 0xc4)
				 // gen jmp 263
		goto _f263;
	} // 174
	else if () { // 170 (r14d > 0x5e)
				 // gen jmp 380
		goto _f380;
	} // 190
	else if () { // 184 (eax < 0x2)
				 // gen jmp 1216
		goto _f1216;
	} // 200
	else if () { // 196 (r14d != 0x3f)
				 // gen jmp 855
		goto _f855;
	}
	else { // 200 next
		   // 211
		goto _f649;

	} // 216
_f216:	 // from 155
		 // 227
	if () { // 220 (r14d > 0x162)
			// gen jmp 307
		goto _f307;
	} // 239
	else if () { // 229 (r14d > 0x116)
				 // gen jmp 436
		goto _f436;
	} // 252
	else if () { // 245 (r14d != 0x104)
				 // gen jmp 1208
		goto _f1208;
	}
	else { // 252 next
		   // 258
		goto _f585;
	} // 258
_f263:	 // from 164
		 // 274
	if () { // 267 (r14d > 0xce)
			// gen jmp 506
		goto _f506;
	} // 290
	else if () { // 280 (r14d != 0xc5)
				 // gen jmp 631
		goto _f631;
	}
	else { // 290 next
		   // 302
		goto _f1216;
	} // 302
_f307:	 // from 227
		 // 317
	if () { // 307 (r14d > 0x187)
			// gen jmp 540
		goto _f540;
	} // 333
	else if () { // 330 (eax > 0x12)
				 // gen jmp 1208
		goto _f1208;
	} // 347
	else if () {
		// gen jmp 1216
		goto _f1216;
	} // 361
	else if () {
		// gen jmp 1068
		goto _f1068;
	} // 369
	else if () { // 367 (0 == eax)
				 // gen jmp 1170
		goto _f1170;
	}
	else { // 369 next
		   // 375
		goto _f1208;
	} // 375
_f380:	 // from 174
		 // 390
	if () { // 380 (r14d > 0x87)
			// gen jmp 660
		goto _f660;
	} // 403
	else if () { // 400 (eax > 0x15)
				 // gen jmp 1208
		goto _f1208;
	}
	else { // 403 next
		   // 431
		goto _f1216;
	} // 431
_f436:	 // from 239
		 // 443
	if () { // 436 (r14d > 0x130)
			// gen jmp 713
		goto _f713;
	} // 456
	else if () { // 449 (r14d > 0x129)
				 // gen jmp 870
		goto _f870;
	} // 469
	else if () { // 462 (r14d == 0x117)
				 // gen jmp 1113
		goto _f1113;
	} // 482
	else if () { // 475 (r14d == 0x122)
				 // gen jmp 1216
		goto _f1216;
	} // 495
	else if () { // 488 (r14d != 0x127)
				 // gen jmp 1208
		goto _f1208;
	}
	else { // 495 next
		   // 501
		goto _f1216;
	} // 501
_f506:	 // from 274
		 // 516
	if () { // 506 (r14d == 0xcf)
			// gen jmp 1170
		goto _f1170;
	} // 529
	else if () { // 522 (r14d != 0xd0)
				 // gen jmp 1208
		goto _f1208;
	}
	else { // 529 next
		   // 535
		goto _f1216;
	} // 535
_f540:	 // from 317
		 // 547
	if () { // 540 (r14d > 0x1b5)
			// gen jmp 780
		goto _f780;
	} // 563
	else if () { // 560 (eax > 0x18)
				 // gen jmp 1208
		goto _f1208;
	}
	else { // 563 next
	_f585:	 // from 258
			 // 591
		goto _f1216;
	} // 591
	  // 602
	goto _f644;
	// 613 call
	CA::Layer::mark_sublayers_should_fetch_geometry();;
	// 626
	goto _f1216;
_f631:	 // from 290
		 // 638
	if () { // 631 (r14d != 0xc8)
			// gen jmp 1208
		goto _f1208;
	}
	else { // 638 next
	_f644:	 // from 602
	_f644:	 // from 90
	_b649:	 // from 1894
	_f649:	 // from 211
			 // 655
		goto _f1216;
	} // 655
_f660:	 // from 390
		 // 667
	if () { // 660 (r14d > 0xb0)
			// gen jmp 913
		goto _f913;
	} // 680
	else if () { // 673 (r14d > 0x97)
				 // gen jmp 1059
		goto _f1059;
	} // 693
	else if () { // 686 (r14d == 0x88)
				 // gen jmp 769
		goto _f769;
	} // 702
	else if () { // 695 (r14d != 0x92)
				 // gen jmp 1208
		goto _f1208;
	}
	else { // 702 next
		   // 708
		goto _f1216;
	} // 708
_f713:	 // from 443
		 // 720
	if () { // 713 (r14d > 0x138)
			// gen jmp 950
		goto _f950;
	} // 736
	else if () { // 733 (eax > 0x4)
				 // gen jmp 1208
		goto _f1208;
	}
	else { // 736 next
		   // 764
		goto _f1216;
	} // 764
_f769:	 // from 693
		 // 775
	goto _f1216;
_f780:	 // from 547
		 // 787
	if () { // 780 (r14d > 0x1c6)
			// gen jmp 1006
		goto _f1006;
	} // 803
	else if () { // 800 (eax > 0x9)
				 // gen jmp 1208
		goto _f1208;
	}
	else { // 803 next
		   // 834 call
		CA::Layer::fetch_defaults();;
		// 850
		goto _f1216;
		// 834 call
		CA::Layer::fetch_defaults();;
	} // 850
_f855:	 // from 200
		 // 859
	if () { // 855 (r14d != 0x4b)
			// gen jmp 1208
		goto _f1208;
	}
	else { // 859 next
		   // 865
		goto _f1105;
	_f870:	 // from 456
			 // 880
		if () // 877 (eax > 0x3)
			  // gen jmp 1208
			goto _f1208;
		// 908
		goto _f1216;
	_f913:	 // from 667
			 // 920
		if () { // 913 (r14d == 0xb1)
				// gen jmp 1068
			goto _f1068;
		}
		else { // 920 next
			   // 933
			if () // 926 (r14d != 0xb4)
				  // gen jmp 1208
				goto _f1208;
			// 945
			goto _f1216;
		_f950:	 // from 720
				 // 957
			if () // 950 (r14d < 0x13a)
				  // gen jmp 1105
				goto _f1105;
			// 970
			if () // 963 (r14d > 0x14a)
				  // gen jmp 1127
				goto _f1127;
			// 983
			if () // 976 (r14d != 0x13a)
				  // gen jmp 1183
				goto _f1183;
			// 1001
			goto _f1216;
		_f1006:	 // from 787
				 // 1013
			if () // 1006 (r14d > 0x1df)
				  // gen jmp 1096
				goto _f1096;
			// 1022
			if () { // 1015 (r14d == 0x1c7)
					// gen jmp 1068
				goto _f1068;
			} // 1031
			else if () { // 1024 (r14d != 0x1d0)
						 // gen jmp 1208
				goto _f1208;
				// 1054
				goto _f1216;
			_f1059:	 // from 680
			} // 1066
			else if () { // 1059 (r14d != 0x98)
						 // gen jmp 1144
				goto _f1144;
			}
			else { // 1066 next
			_f1068:	 // from 1022
			_f1068:	 // from 920
			_f1068:	 // from 361
			} // 1068
		} // 1068
		  // 1078 call
		CAMediaTimingInvalidate;;
		// 1094
		goto _f1216;
	_f1096:	 // from 1013
			 // 1103
		if () // 1096 (r14d != 0x1e0)
			  // gen jmp 1155
			goto _f1155;
	_f1105:	 // from 957
	_f1105:	 // from 865
			 // 1111
		goto _f1216;
	} // 1111
_f1113:	 // from 469
		 // 1125
	goto _f1216;
_f1127:	 // from 970
		 // 1134
	if () { // 1127 (r14d != 0x14b)
			// gen jmp 1199
		goto _f1199;
		// 1142
		goto _f1170;
	_f1144:	 // from 1066
	} // 1151
	else if () { // 1144 (r14d != 0x99)
				 // gen jmp 1208
		goto _f1208;
		// 1153
		goto _f1216;
	_f1155:	 // from 1103
	} // 1162
	else if () { // 1155 (r14d != 0x1f4)
				 // gen jmp 1208
		goto _f1208;
	}
	else { // 1162 next
	_f1170:	 // from 1142
	_f1170:	 // from 516
	_f1170:	 // from 369
			 // 1181
		goto _f1216;
	} // 1181
_f1183:	 // from 983
		 // 1190
	if () { // 1183 (r14d != 0x140)
			// gen jmp 1208
		goto _f1208;
	}
	else { // 1190 next
		   // 1197
		goto _f1216;
	} // 1197
_f1199:	 // from 1134
		 // 1206
	if (!) { // 1199 (r14d == 0x14c)
	_f1208:	 // from 1162
	_f1208:	 // from 1151
	_f1208:	 // from 1031
	_f1208:	 // from 933
	_f1208:	 // from 880
	_f1208:	 // from 859
	_f1208:	 // from 803
	_f1208:	 // from 736
	_f1208:	 // from 702
	_f1208:	 // from 563
	_f1208:	 // from 529
	_f1208:	 // from 495
	_f1208:	 // from 403
	_f1208:	 // from 375
	_f1208:	 // from 333
	_f1208:	 // from 252
	_f1208:	 // from 115
	_f1208:	 // from 62
	_b1216:	 // from 1928
	_b1216:	 // from 1911
	_b1216:	 // from 1883
	_b1216:	 // from 1866
	_b1216:	 // from 1849
	_b1216:	 // from 1838
	_b1216:	 // from 1822
	_b1216:	 // from 1800
	_f1216:	 // from 1197
	_f1216:	 // from 1181
	_f1216:	 // from 1153
	_f1216:	 // from 1125
	_f1216:	 // from 1111
	_f1216:	 // from 1094
	_f1216:	 // from 1054
	_f1216:	 // from 1001
	_f1216:	 // from 945
	_f1216:	 // from 908
	_f1216:	 // from 850
	_f1216:	 // from 775
	_f1216:	 // from 764
	_f1216:	 // from 708
	_f1216:	 // from 655
	_f1216:	 // from 626
	_f1216:	 // from 591
	_f1216:	 // from 535
	_f1216:	 // from 501
	_f1216:	 // from 482
	_f1216:	 // from 431
	_f1216:	 // from 347
	_f1216:	 // from 302
	_f1216:	 // from 190
	_f1216:	 // from 143
	} // 1216
	  // 1237
	if (!) { // 1228 (0x10000 & edx)
			 // 1247
		if (!) {
			// 1260 call
			CAAtomGetString;;
			// 1286 call
			// %rdi = @"%@ - changing property %@ in transform-only layer, will have no effect"
			NSLog;;
		} // 1291
	} // 1291
	  // 1298
	if (!) { // 1291 (0x60000 & r12d)
			 // 1307
		if () { // 1304 (0 == r13d)
				// gen jmp 1363
			goto _f1363;
		} // 1320
		else if () { // 1309 (-0x80 & rbx->_80)
					 // gen jmp 1399
			goto _f1399;
		}
		else { // 1320 next
			   // 1356 call
			CA::Layer::mark(CA::Transaction*, unsigned int, unsigned int);;
			// 1361
			goto _f1436;
		_f1363:	 // from 1307
				 // 1356 call
			CA::Layer::mark(CA::Transaction*, unsigned int, unsigned int);;
		} // 1363
		  // 1374
		if () { // 1371 (0 > rax)
				// gen jmp 1386
			goto _f1386;
		} // 1384
		else if () {
			// gen jmp 1453
			goto _f1453;
		}
		else { // 1384 next
		_f1386:	 // from 1374
		} // 1386
		  // 1392 call
		CA::Layer::thread_flags_(CA::Transaction*);;
		// 1397
		goto _f1453;
	_f1399:	 // from 1320
			 // 1403 call
		CALayerPortalGetDestination;;
		// 1411
		if (!) { // 1408 (0 == rax)
				 // 1431 call
				 // %rcx = CALayer._attr
			CA::Layer::set_commit_needed(CA::Transaction*, unsigned int);;
		_f1436:	 // from 1361
		} // 1436
		  // 1440
		if (!) { // 1436 (0 == (0x2 & r13b))
				 // 1448 call
			CA::Layer::invalidate_sublayers(CA::Transaction*);;
		_f1453:	 // from 1397
		_f1453:	 // from 1384
		} // 1453
		  // 1457
		if (!) { // 1453 (0 == (0x40 & r14b))
				 // 1466
			if (!) { // 1463 (0 == r12)
					 // 1479 call
				CA::Layer::layout_is_active(CA::Transaction*, bool);;
				// 1486
				if (!) { // 1484 (0 != al)
						 // 1503 call
						 // %rsi = "needsLayoutOnGeometryChange"
					objc_msgSend;;
					// 1511
					if (!) { // 1509 (0 == al)
							 // 1523 call
							 // %rsi = "setNeedsLayout"
						objc_msgSend;;
					} // 1529
				} // 1529
			} // 1529
		} // 1529
		  // 1538
		if () { // 1533 (0 == (0x40 & r13->_60))
				// gen jmp 1573
			goto _f1573;
			// 1551 call
			// %rsi = "class"
			objc_msgSend;;
			// 1564 call
			CAObject_needsLayoutForKey;;
		} // 1571
		else if () { // 1569 (0 != al)
					 // gen jmp 1600
			goto _f1600;
		}
		else { // 1571 next
		_f1573:	 // from 1538
		} // 1573
		  // 1577
		if (!) { // 1573 (0 == (0x20 & r14b))
				 // 1590 call
				 // %rsi = "needsLayoutOnGeometryChange"
			objc_msgSend;;
			// 1598
			if (!) { // 1596 (0 == al)
			_f1600:	 // from 1571
					 // 1611 call
				CA::Layer::layout_is_active(CA::Transaction*, bool);;
				// 1618
				if (!) { // 1616 (0 != al)
						 // 1631 call
						 // %rsi = "setNeedsLayout"
					objc_msgSend;;
				} // 1637
			} // 1637
		} // 1637
		  // 1646
		if () { // 1637 (0 == (0x20 & r13->_60))
				// gen jmp 1680
			goto _f1680;
			// 1659 call
			// %rsi = "class"
			objc_msgSend;;
			// 1671 call
			CAObject_needsDisplayForKey;;
		} // 1678
		else if () { // 1676 (0 != al)
					 // gen jmp 1707
			goto _f1707;
		}
		else { // 1678 next
		_f1680:	 // from 1646
		} // 1680
		  // 1684
		if (!) { // 1680 (r14d != 0x3f)
				 // 1697 call
				 // %rsi = "needsDisplayOnBoundsChange"
			objc_msgSend;;
			// 1705
			if (!) { // 1703 (0 == al)
			_f1707:	 // from 1678
			} // 1741
		} // 1741
	} // 1741
	  // 1755 ret
	return;
	// 1767 call
	// %rsi = "minificationFilter"
	objc_msgSend;;
	// 1778 call
	CAInternAtom;;
	// 1788
	if (!) { // 1783 (eax != 0x10b)
			 // 1793 call
		CA::Layer::ensure_mipmaps();;
	} // 1798
	  // 1800
	goto _b1216;
	// 1822
	goto _b1216;
	// 1838
	goto _b1216;
	// 1849
	goto _b1216;
	// 1866
	goto _b1216;
	// 1883
	goto _b1216;
	// 1894
	goto _b649;
	// 1911
	goto _b1216;
	// 1928
	goto _b1216;


	/*****
	* global variables
	*
	*/

	// 68 extern ent_off__0x8c0;	leaq 0x875(%rip), %rcx;	 <+2240>
	// 121 extern ent_off__0x898;	leaq 0x818(%rip), %rcx;	 <+2200>
	// 409 extern ent_off__0x840;	leaq 0x6a0(%rip), %rcx;	 <+2112>
	// 569 extern ent_off__0x7b8;	leaq 0x578(%rip), %rcx;	 <+1976>
	// 742 extern ent_off__0x81c;	leaq 0x52f(%rip), %rcx;	 <+2076>
	// 809 extern ent_off__0x790;	leaq 0x460(%rip), %rcx;	 <+1936>
	// 886 extern ent_off__0x830;	leaq 0x4b3(%rip), %rcx;	 <+2096>
	// 1268 extern ent_off__0x80a18;	leaq 0x8051d(%rip), %rdi;	 @"%@ - changing property %@ in transform-only layer, will have no effect"
	// 1413 extern ent_off__0x706a0;	movq 0x70114(%rip), %rcx;	 CALayer._attr
	// 1493 extern ent_off__0x6f2e8;	movq 0x6ed0c(%rip), %rsi;	 "needsLayoutOnGeometryChange"
	// 1513 extern ent_off__0x6f2f0;	movq 0x6ed00(%rip), %rsi;	 "setNeedsLayout"
	// 1544 extern ent_off__0x6e828;	movq 0x6e219(%rip), %rsi;	 "class"
	// 1583 extern ent_off__0x6f2e8;	movq 0x6ecb2(%rip), %rsi;	 "needsLayoutOnGeometryChange"
	// 1624 extern ent_off__0x6f2f0;	movq 0x6ec91(%rip), %rsi;	 "setNeedsLayout"
	// 1652 extern ent_off__0x6e828;	movq 0x6e1ad(%rip), %rsi;	 "class"
	// 1690 extern ent_off__0x6f330;	movq 0x6ec8f(%rip), %rsi;	 "needsDisplayOnBoundsChange"
	// 1714 extern ent_off__0x6f308;	movq 0x6ec4f(%rip), %rsi;	 "setNeedsDisplay"
	// 1760 extern ent_off__0x6f1b0;	movq 0x6eac9(%rip), %rsi;	 "minificationFilter"


}