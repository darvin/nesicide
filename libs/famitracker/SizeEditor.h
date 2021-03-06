/*
** FamiTracker - NES/Famicom sound tracker
** Copyright (C) 2005-2012  Jonathan Liss
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful, 
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
** Library General Public License for more details.  To obtain a 
** copy of the GNU Library General Public License, write to the Free 
** Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
** Any permitted reproduction of these routines, in whole or in part,
** must bear this legend.
*/

#pragma once

#include "cqtmfc.h"

// Size editor
class CSizeEditor : public CWnd
{
   // Qt stuff
protected:
   void paintEvent(QPaintEvent *) { OnPaint(); }
   void mouseMoveEvent(QMouseEvent *event);
   void mousePressEvent(QMouseEvent *event);
   void mouseReleaseEvent(QMouseEvent *event);
   void mouseDoubleClickEvent(QMouseEvent *event);
   void timerEvent(QTimerEvent *event);
   
	DECLARE_DYNAMIC(CSizeEditor)
public:
	CSizeEditor(CWnd *pParent);
	virtual ~CSizeEditor();
private:
	int m_iValue;
	int m_iButtonPressed;
	CWnd *m_pParentWnd;
	bool m_bSizeCursor;
private:
	void MouseAction(UINT nFlags, CPoint point);
	void IncreaseValue();
	void DecreaseValue();
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

	void SetValue(int Value);
	int GetValue() const;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
