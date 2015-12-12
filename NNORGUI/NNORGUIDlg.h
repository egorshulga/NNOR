
// NNORGUIDlg.h : header file
//

#pragma once
#include <opencv2/core/base.hpp>


// CNNORGUIDlg dialog
class CNNORGUIDlg : public CDialogEx
{
// Construction
public:
	void drawMatOnControl(cv::Mat cvImg, UINT ID);
	CNNORGUIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NNORGUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnCbnSelchangeType();
	afx_msg void OnBnClickedFile();
	afx_msg void OnClose();
};
