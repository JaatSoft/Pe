/*	$Id$
	
	Copyright 1996, 1997, 1998, 2002
	        Hekkelman Programmatuur B.V.  All rights reserved.
	
	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:
	1. Redistributions of source code must retain the above copyright notice,
	   this list of conditions and the following disclaimer.
	2. Redistributions in binary form must reproduce the above copyright notice,
	   this list of conditions and the following disclaimer in the documentation
	   and/or other materials provided with the distribution.
	3. All advertising materials mentioning features or use of this software
	   must display the following acknowledgement:
	   
	    This product includes software developed by Hekkelman Programmatuur B.V.
	
	4. The name of Hekkelman Programmatuur B.V. may not be used to endorse or
	   promote products derived from this software without specific prior
	   written permission.
	
	THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
	INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
	FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
	AUTHORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
	EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
	PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
	OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
	WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
	OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
	ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 	

	Created: 10/02/97 21:26:20
*/

#include "pe.h"
#include "PText.h"
#include "PSplitter.h"
#include "HAppResFile.h"
#include "HError.h"
#include "HDefines.h"

const void *PSplitter::sfCursor = NULL;

PSplitter::PSplitter(BRect frame, PText *txt)
	: BView(frame, "splitter", B_FOLLOW_RIGHT, B_WILL_DRAW)
{
	if (sfCursor == NULL)
	{
		sfCursor = HResources::GetResource('CURS', 0);
		FailNilRes(sfCursor);
	}
	
	fText = txt;
} /* PSplitter::PSplitter */

PSplitter::~PSplitter()
{
} /* PSplitter::~PSplitter */

void PSplitter::AttachedToWindow()
{
	BPoint p = ConvertToParent(Bounds().LeftTop());
	fOrigin = p.y;
	fText->SetSplitter(this);
	
	SetViewColor(B_TRANSPARENT_32_BIT);
} /* PSplitter::AttachedToWindow */

void PSplitter::MouseDown(BPoint where)
{
	fText->TrackSplitter(ConvertToScreen(where));
} /* PSplitter::MouseDown */

void PSplitter::Draw(BRect update)
{
	BRect b(Bounds());
	
	SetHighColor(kDarkShadow);
	StrokeRect(b);
	b.InsetBy(1, 1);
	
	SetHighColor(kWhite);
	StrokeLine(b.LeftTop(), b.RightTop());	b.top += 1;
	SetHighColor(kViewColor);
	StrokeLine(b.LeftTop(), b.RightTop());	b.top += 1;
	SetHighColor(kShadow);
	StrokeLine(b.LeftTop(), b.RightTop());	b.top += 1;
	SetHighColor(kDarkShadow);
	StrokeLine(b.LeftTop(), b.RightTop());
} /* PSplitter::Draw */

void PSplitter::MouseMoved(BPoint where, uint32 code, const BMessage *a_message)
{
	if (a_message == NULL && Bounds().Contains(where))
		be_app->SetCursor(Cursor());
	else
		be_app->SetCursor(B_HAND_CURSOR);
} /* PSplitter::MouseMoved */