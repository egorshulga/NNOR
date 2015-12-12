
// NNORGUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NNORGUI.h"
#include "NNORGUIDlg.h"
#include "afxdialogex.h"

#include <string>
#include <iostream>
#include "../NNORDLL/ITextImageNN.h"
using namespace std;
using namespace nnor;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


void CNNORGUIDlg::drawMatOnControl(cv::Mat cvImg, UINT ID)
{
	cvtColor(cvImg, cvImg, CV_GRAY2RGB);

	// Get the HDC handle information from the ID passed
	CDC *pDC = GetDlgItem(ID)->GetDC();
	HDC hDCDst = pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	cv::Size winSize(rect.right, rect.bottom);

	// Resize the source to the size of the destination image if necessary
	cv::Mat cvImgTmp(winSize, CV_8UC3);
	if (cvImg.size() != winSize)
	{
		double xScale = (double)winSize.width / cvImg.cols;
		double yScale = (double)winSize.height / cvImg.rows;
		double scale = (xScale > yScale) ? yScale : xScale;
		cv::resize(cvImg, cvImgTmp, Size(0,0), scale, scale);
		int left = (winSize.width - cvImgTmp.cols) / 2;
		int right = winSize.width - left - cvImgTmp.cols;
		int top = (winSize.height - cvImgTmp.rows) / 2;
		int bottom = winSize.height - top - cvImgTmp.rows;
		copyMakeBorder(cvImgTmp, cvImgTmp, top, bottom, left, right, BORDER_CONSTANT, Scalar(255,255,255));
	}
	else
	{
		cvImgTmp = cvImg;
	}

	// Rotate the image
	cv::flip(cvImgTmp, cvImgTmp, 0);

	// Initialize the BITMAPINFO structure
	BITMAPINFO bitInfo;
	bitInfo.bmiHeader.biBitCount = 24;
	bitInfo.bmiHeader.biWidth = winSize.width;
	bitInfo.bmiHeader.biHeight = winSize.height;
	bitInfo.bmiHeader.biPlanes = 1;
	bitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitInfo.bmiHeader.biCompression = BI_RGB;
	bitInfo.bmiHeader.biClrImportant = 0;
	bitInfo.bmiHeader.biClrUsed = 0;
	bitInfo.bmiHeader.biSizeImage = 0;
	bitInfo.bmiHeader.biXPelsPerMeter = 0;
	bitInfo.bmiHeader.biYPelsPerMeter = 0;

	// Add header and OPENCV image's data to the HDC
	StretchDIBits(hDCDst, 0, 0,
		winSize.width, winSize.height, 0, 0,
		winSize.width, winSize.height,
		cvImgTmp.data, &bitInfo, DIB_RGB_COLORS, SRCCOPY);

	ReleaseDC(pDC);
}



ITextImageNN *textImageNN = nullptr;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CNNORGUIDlg dialog



CNNORGUIDlg::CNNORGUIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NNORGUI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNNORGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ANGLE, angleSlider);
}

BEGIN_MESSAGE_MAP(CNNORGUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_CBN_SELCHANGE(BLUR_TYPE, &CNNORGUIDlg::OnCbnSelchangeType)
ON_BN_CLICKED(OPEN_FILE, &CNNORGUIDlg::OnBnClickedFile)
ON_WM_CLOSE()
ON_BN_CLICKED(AUTOMATIC_ROTATION, &CNNORGUIDlg::OnBnClickedRotation)
ON_NOTIFY(TRBN_THUMBPOSCHANGING, ANGLE, &CNNORGUIDlg::OnTRBNThumbPosChangingAngle)
ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CNNORGUIDlg message handlers

BOOL CNNORGUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	//DLL loading
	wstring dllPath = L"NNORDLL.dll";
	HINSTANCE dllHandle = LoadLibrary(dllPath.c_str());
	if (!dllHandle)
	{
		wcerr << L"Dll could not be loaded!" << endl;
		return FALSE;
	}
	ITextImageNNFactory factory = (ITextImageNNFactory)GetProcAddress(dllHandle, "createInstance");
	if (!factory)
	{
		wcerr << L"CreateInstance function could not be found!" << endl;
		return FALSE;
	}
	textImageNN = factory();

	//Slider init
	angleSlider.SetRange(0, 360);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNNORGUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNNORGUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNNORGUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CNNORGUIDlg::OnBnClickedFile()
{
	// TODO: Add your control notification handler code here
	OPENFILENAME ofn = { 0 };
	ofn.lStructSize = sizeof(ofn);
	wchar_t *filePath = new wchar_t[MAX_PATH];
	filePath[0] = 0;
	ofn.lpstrFile = filePath;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = L"Portable Network Graphics (*.png)\0*.png\0Windows bitmaps (*.bmp)\0*.bmp\0JPEG files (*.jpg)\0*.jpg\0\0";

	if (GetOpenFileName(&ofn))
	{
		wstring imagePath(ofn.lpstrFile);
		CopyFile(imagePath.c_str(), L"c:/temp/tempImage", FALSE);
		textImageNN->setImage("c:/temp/tempImage");
		
		drawMatOnControl(textImageNN->getImage(), IMAGE_BOX);
	}
}


void CNNORGUIDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	textImageNN->destroy();
	CDialogEx::OnClose();
}


void CNNORGUIDlg::OnBnClickedRotation()
{
	textImageNN->performAutomaticRotation();
	drawMatOnControl(textImageNN->getImage(), IMAGE_BOX);
}


void CNNORGUIDlg::OnTRBNThumbPosChangingAngle(NMHDR *pNMHDR, LRESULT *pResult)
{
	// This feature requires Windows Vista or greater.
	// The symbol _WIN32_WINNT must be >= 0x0600.
	NMTRBTHUMBPOSCHANGING *pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING *>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;


}


void CNNORGUIDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	int angle = angleSlider.GetPos();
	textImageNN->setRotationAngle(angle);
	drawMatOnControl(textImageNN->getImage(), IMAGE_BOX);

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
