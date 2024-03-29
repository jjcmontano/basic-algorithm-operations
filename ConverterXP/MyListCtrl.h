#if !defined(AFX_MYLISTCTRL_H__5F90ECB9_2FE9_464D_A537_7ADE3A95F992__INCLUDED_)
#define AFX_MYLISTCTRL_H__5F90ECB9_2FE9_464D_A537_7ADE3A95F992__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyListCtrl.h : header file
//

#include "LCCFlatHeaderCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl window

class CMyListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CMyListCtrl)
		
		// Construction
public:
	CMyListCtrl();
	
	// Attributes
public:
	virtual CLCCFlatHeaderCtrl& GetHeaderCtrl ()
	{
		return m_wndHeader;
	}
	
	// Mark sorted column by background color
	void EnableMarkSortedColumn (BOOL bMark = TRUE, BOOL bRedraw = TRUE);
	
protected:
	CLCCFlatHeaderCtrl	m_wndHeader;
	int				m_iSortedColumn;
	BOOL			m_bAscending;
	BOOL			m_bMarkSortedColumn;
	COLORREF		m_clrSortedColumn;
	HFONT			m_hOldFont;
	
	// Operations
public:
	
	// Sorting operations:
	virtual void Sort (int iColumn, BOOL bAscending, BOOL bAdd = FALSE);
	void SetSortColumn (int iColumn, BOOL bAscending, BOOL bAdd = FALSE);
	void RemoveSortColumn (int iColumn);
	void EnableMultipleSort (BOOL bEnable = TRUE);
	BOOL IsMultipleSort () const;
	
	// Overrides
	virtual int OnCompareItems (LPARAM lParam1, LPARAM lParam2, int iColumn);
	
	// Support for individual cells text/background colors:
	virtual COLORREF OnGetCellTextColor (int /*nRow*/, int /*nColum*/)
	{
		return GetTextColor ();
	}
	
	virtual COLORREF OnGetCellBkColor (int /*nRow*/, int /*nColum*/)
	{
		return GetBkColor ();
	}
	
	virtual HFONT OnGetCellFont (int /*nRow*/, int /*nColum*/, DWORD /*dwData*/ = 0)
	{
		return NULL;
	}
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPListCtrl)
protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual void Sort(int iColumn);
	virtual ~CMyListCtrl();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPListCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSysColorChange();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	//afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnStyleChanged(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()
		
	static int CALLBACK CompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	BOOL InitList ();
	void InitColors ();
	
	virtual void InitHeader ();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTCTRL_H__5F90ECB9_2FE9_464D_A537_7ADE3A95F992__INCLUDED_)
