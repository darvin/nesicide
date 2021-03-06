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
** Any permitted reproduction of these routin, in whole or in part,
** must bear this legend.
*/

#include "stdafx.h"
#include "FamiTracker.h"
#include "FamiTrackerDoc.h"
#include "FamiTrackerView.h"
#include "MainFrm.h"
#include "CustomControls.h"

/*

 Contains some custom GUI controls.

 * CInstrumentList
   - The instrument list, extended to contain a context menu
 
 * CBannerEdit
   - An edit box that displays a banner when no text is present
 
 * CLockedEdit
   - An edit box that is locked for editing, unlocked with double-click

*/

///
/// CInstrumentList
///

// This class takes care of the context menu message

IMPLEMENT_DYNAMIC(CInstrumentList, CListCtrl)

//BEGIN_MESSAGE_MAP(CInstrumentList, CListCtrl)
//	ON_WM_CONTEXTMENU()
//END_MESSAGE_MAP()

// TODO: expand this class

//bool CInstrumentList::eventFilter(QObject *object, QEvent *event)
//{
//   if ( event->type() == QEvent::Show )
//   {
//      showEvent(dynamic_cast<QShowEvent*>(event));
//      return true;
//   }
//   if ( event->type() == QEvent::ShowToParent )
//   {
//      showEvent(dynamic_cast<QShowEvent*>(event));
//      return true;
//   }
//   if ( event->type() == QEvent::Hide )
//   {
//      hideEvent(dynamic_cast<QHideEvent*>(event));
//      return true;
//   }
//   if ( event->type() == QEvent::Move )
//   {
//      moveEvent(dynamic_cast<QMoveEvent*>(event));
//      return true;
//   }
//   if ( event->type() == QEvent::Paint )
//   {
//      paintEvent(dynamic_cast<QPaintEvent*>(event));
//      return true;
//   }
//   if ( event->type() == QEvent::FocusIn )
//   {
//      focusInEvent(dynamic_cast<QFocusEvent*>(event));
//      return true;
//   }
//   if ( event->type() == QEvent::FocusOut )
//   {
//      focusOutEvent(dynamic_cast<QFocusEvent*>(event));
//      return true;
//   }
//   if ( event->type() == QEvent::MouseButtonPress )
//   {
//      mousePressEvent(dynamic_cast<QMouseEvent*>(event));
//      return true;
//   }
//   if ( event->type() == QEvent::MouseButtonRelease )
//   {
//      mouseReleaseEvent(dynamic_cast<QMouseEvent*>(event));
//      return true;
//   }
//   if ( event->type() == QEvent::MouseButtonDblClick )
//   {
//      mouseDoubleClickEvent(dynamic_cast<QMouseEvent*>(event));
//      return true;
//   }
//   if ( event->type() == QEvent::MouseMove )
//   {
//      mouseMoveEvent(dynamic_cast<QMouseEvent*>(event));
//      return true;
//   }
//   if ( event->type() == QEvent::Wheel )
//   {
//      wheelEvent(dynamic_cast<QWheelEvent*>(event));
//      return true;
//   }
//   if ( event->type() == QEvent::Resize )
//   {
//      resizeEvent(dynamic_cast<QResizeEvent*>(event));
//      return true;
//   }
//   if ( event->type() == QEvent::KeyPress )
//   {
//      keyPressEvent(dynamic_cast<QKeyEvent*>(event));
//      return true;
//   }
//   if ( event->type() == QEvent::KeyRelease )
//   {
//      keyReleaseEvent(dynamic_cast<QKeyEvent*>(event));
//      return true;
//   }
////   qDebug("eventFilter: unhandled %d object %s", event->type(), object->objectName().toAscii().constData());
//   return false;
//}

CInstrumentList::CInstrumentList(CMainFrame *pMainFrame) : m_pMainFrame(pMainFrame)
{
//   _qt->installEventFilter(this);
   InsertColumn(0,_T(""));
}

void CInstrumentList::OnContextMenu(CWnd* pWnd, CPoint point)
{
	int Instrument(0);
	TCHAR Text[256];

	if (GetSelectionMark() != -1) {
		// Select the instrument
		GetItemText(GetSelectionMark(), 0, Text, 256);
		_stscanf(Text, _T("%X"), &Instrument);
		CFamiTrackerDoc::GetDoc()->GetInstrumentName(Instrument, Text);
		CFamiTrackerView::GetView()->SetInstrument(Instrument);
		// TODO: fix??
		//m_wndDialogBar.GetDlgItem(IDC_INSTNAME)->SetWindowText(Text);
	}

	// Display the popup menu
	CMenu *pPopupMenu, PopupMenuBar;
	PopupMenuBar.LoadMenu(IDR_INSTRUMENT_POPUP);
	pPopupMenu = PopupMenuBar.GetSubMenu(0);
	// Route the menu messages to mainframe
	pPopupMenu->TrackPopupMenu(TPM_LEFTBUTTON, point.x, point.y, m_pMainFrame);

	// Return focus to pattern editor
	m_pMainFrame->GetActiveView()->SetFocus();
}

///
/// CBannerEdit
///

const TCHAR CBannerEdit::BANNER_FONT[]	 = _T("Tahoma");
const COLORREF CBannerEdit::BANNER_COLOR = 0x808080;

// Used to display a banner in edit boxes

IMPLEMENT_DYNAMIC(CBannerEdit, CEdit)

//BEGIN_MESSAGE_MAP(CBannerEdit, CEdit)
//	ON_WM_PAINT()
//	ON_WM_SETFOCUS()
//	ON_WM_KILLFOCUS()
//END_MESSAGE_MAP()

bool CBannerEdit::eventFilter(QObject *object, QEvent *event)
{
   if ( event->type() == QEvent::Show )
   {
      showEvent(dynamic_cast<QShowEvent*>(event));
      return true;
   }
   if ( event->type() == QEvent::ShowToParent )
   {
      showEvent(dynamic_cast<QShowEvent*>(event));
      return true;
   }
   if ( event->type() == QEvent::Hide )
   {
      hideEvent(dynamic_cast<QHideEvent*>(event));
      return true;
   }
   if ( event->type() == QEvent::Move )
   {
      moveEvent(dynamic_cast<QMoveEvent*>(event));
      return true;
   }
   if ( event->type() == QEvent::Paint )
   {
      paintEvent(dynamic_cast<QPaintEvent*>(event));
      return true;
   }
   if ( event->type() == QEvent::FocusIn )
   {
      focusInEvent(dynamic_cast<QFocusEvent*>(event));
      return true;
   }
   if ( event->type() == QEvent::FocusOut )
   {
      focusOutEvent(dynamic_cast<QFocusEvent*>(event));
      return true;
   }
   if ( event->type() == QEvent::MouseButtonPress )
   {
      mousePressEvent(dynamic_cast<QMouseEvent*>(event));
      return true;
   }
   if ( event->type() == QEvent::MouseButtonRelease )
   {
      mouseReleaseEvent(dynamic_cast<QMouseEvent*>(event));
      return true;
   }
   if ( event->type() == QEvent::MouseButtonDblClick )
   {
      mouseDoubleClickEvent(dynamic_cast<QMouseEvent*>(event));
      return true;
   }
   if ( event->type() == QEvent::MouseMove )
   {
      mouseMoveEvent(dynamic_cast<QMouseEvent*>(event));
      return true;
   }
   if ( event->type() == QEvent::Wheel )
   {
      wheelEvent(dynamic_cast<QWheelEvent*>(event));
      return true;
   }
   if ( event->type() == QEvent::Resize )
   {
      resizeEvent(dynamic_cast<QResizeEvent*>(event));
      return true;
   }
   if ( event->type() == QEvent::KeyPress )
   {
      keyPressEvent(dynamic_cast<QKeyEvent*>(event));
      return true;
   }
   if ( event->type() == QEvent::KeyRelease )
   {
      keyReleaseEvent(dynamic_cast<QKeyEvent*>(event));
      return true;
   }
//   qDebug("eventFilter: unhandled %d object %s", event->type(), object->objectName().toAscii().constData());
   return false;
}

void CBannerEdit::paintEvent(QPaintEvent *event)
{
   OnPaint();
}

void CBannerEdit::focusInEvent(QFocusEvent *)
{
   OnSetFocus(GetFocus());
}

void CBannerEdit::focusOutEvent(QFocusEvent *)
{
   OnKillFocus(NULL);
}

void CBannerEdit::OnSetFocus(CWnd* pOldWnd)
{
	CEdit::OnSetFocus(pOldWnd);
	Invalidate();
	RedrawWindow(NULL, NULL, RDW_ERASE);
}

void CBannerEdit::OnPaint()
{
	CEdit::OnPaint();

	// Overlay some text
	CString str;
	GetWindowText(str);

	// only if empty and not in focus
	if (str.GetLength() > 0 || GetFocus() == this)
		return;

	CDC *dc(GetDC());
	CFont font;

	font.CreateFont(12, 0, 0, 0, 0, TRUE, FALSE, FALSE, 0, 0, 0, 0, 0, BANNER_FONT);
	CFont *pOldFont = dc->SelectObject(&font);

	dc->SetTextColor(BANNER_COLOR);
	dc->TextOut(2, 1, m_strText);
	dc->SelectObject(pOldFont);

	ReleaseDC(dc);
}


void CBannerEdit::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);
	// Limit string size to 31 chars
	CString text;
	GetWindowText(text);
	if (text.GetLength() > 31)
		text = text.Left(31);
	SetWindowText(text);
}

///
/// CLockedEdit
///

// This class takes care of locking/unlocking edit boxes by double clicking

IMPLEMENT_DYNAMIC(CLockedEdit, CEdit)

//BEGIN_MESSAGE_MAP(CLockedEdit, CEdit)
//	ON_WM_LBUTTONDBLCLK()
//	ON_WM_SETFOCUS()
//	ON_WM_KILLFOCUS()
//END_MESSAGE_MAP()

bool CLockedEdit::eventFilter(QObject *object, QEvent *event)
{
   if ( event->type() == QEvent::Show )
   {
      showEvent(dynamic_cast<QShowEvent*>(event));
      return true;
   }
   if ( event->type() == QEvent::ShowToParent )
   {
      showEvent(dynamic_cast<QShowEvent*>(event));
      return true;
   }
   if ( event->type() == QEvent::Hide )
   {
      hideEvent(dynamic_cast<QHideEvent*>(event));
      return true;
   }
   if ( event->type() == QEvent::Move )
   {
      moveEvent(dynamic_cast<QMoveEvent*>(event));
      return true;
   }
   if ( event->type() == QEvent::Paint )
   {
      paintEvent(dynamic_cast<QPaintEvent*>(event));
      return true;
   }
   if ( event->type() == QEvent::FocusIn )
   {
      focusInEvent(dynamic_cast<QFocusEvent*>(event));
      return true;
   }
   if ( event->type() == QEvent::FocusOut )
   {
      focusOutEvent(dynamic_cast<QFocusEvent*>(event));
      return true;
   }
   if ( event->type() == QEvent::MouseButtonPress )
   {
      mousePressEvent(dynamic_cast<QMouseEvent*>(event));
      return true;
   }
   if ( event->type() == QEvent::MouseButtonRelease )
   {
      mouseReleaseEvent(dynamic_cast<QMouseEvent*>(event));
      return true;
   }
   if ( event->type() == QEvent::MouseButtonDblClick )
   {
      mouseDoubleClickEvent(dynamic_cast<QMouseEvent*>(event));
      return true;
   }
   if ( event->type() == QEvent::MouseMove )
   {
      mouseMoveEvent(dynamic_cast<QMouseEvent*>(event));
      return true;
   }
   if ( event->type() == QEvent::Wheel )
   {
      wheelEvent(dynamic_cast<QWheelEvent*>(event));
      return true;
   }
   if ( event->type() == QEvent::Resize )
   {
      resizeEvent(dynamic_cast<QResizeEvent*>(event));
      return true;
   }
   if ( event->type() == QEvent::KeyPress )
   {
      keyPressEvent(dynamic_cast<QKeyEvent*>(event));
      return true;
   }
   if ( event->type() == QEvent::KeyRelease )
   {
      keyReleaseEvent(dynamic_cast<QKeyEvent*>(event));
      return true;
   }
//   qDebug("eventFilter: unhandled %d object %s", event->type(), object->objectName().toAscii().constData());
   return false;
}

void CLockedEdit::mouseDoubleClickEvent(QMouseEvent *event)
{
   CPoint point(event->pos());
   unsigned int flags = 0;
   if ( event->modifiers()&Qt::ControlModifier )
   {
      flags |= MK_CONTROL;
   }
   if ( event->modifiers()&Qt::ShiftModifier )
   {
      flags |= MK_SHIFT;
   }
   if ( event->buttons()&Qt::LeftButton )
   {
      flags |= MK_LBUTTON;
   }
   if ( event->buttons()&Qt::MiddleButton )
   {
      flags |= MK_MBUTTON;
   }
   if ( event->buttons()&Qt::RightButton )
   {
      flags |= MK_RBUTTON;            
   }
   if ( event->button() == Qt::LeftButton )
   {
      OnLButtonDblClk(flags,point);
   }
}

void CLockedEdit::focusInEvent(QFocusEvent *)
{
   OnSetFocus(GetFocus());
}

void CLockedEdit::focusOutEvent(QFocusEvent *)
{
   OnKillFocus(NULL);
}

bool CLockedEdit::IsEditable() const
{
	return !((GetWindowLong(m_hWnd, GWL_STYLE) & ES_READONLY) == ES_READONLY);
}

bool CLockedEdit::Update()
{
	bool ret_val(m_bUpdate);
	m_bUpdate = false;
	return ret_val;
}

int CLockedEdit::GetValue() const
{
	return m_iValue;
}

void CLockedEdit::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	m_bUpdate = false;
	if (IsEditable())
		SetSel(0, -1);	// select all
	else {
		SendMessage(EM_SETREADONLY, FALSE);
		SetFocus();
		SetSel(0, -1);
	}
}

void CLockedEdit::OnSetFocus(CWnd* pOldWnd)
{
	CEdit::OnSetFocus(pOldWnd);

	if (!IsEditable())
		CFamiTrackerView::GetView()->SetFocus();
}

void CLockedEdit::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);
	CString Text;
	if (!IsEditable())
		return;
	GetWindowText(Text);
	m_iValue = _ttoi(Text);
	m_bUpdate = true;
	SendMessage(EM_SETREADONLY, TRUE);
}

BOOL CLockedEdit::PreTranslateMessage(MSG* pMsg)
{
	// For some reason OnKeyDown won't work
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) {
		CFamiTrackerView::GetView()->SetFocus();
		return TRUE;
	}

	return CEdit::PreTranslateMessage(pMsg);
}
