
// mfcMemoDlg.cpp: 구현 파일
// 커스텀 헤더파일5

#include "pch.h"
#include "framework.h"
#include "mfcMemo.h"
#include "mfcMemoDlg.h"
#include "CmfcFindDlg.h"
#include "CmfcReplace.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <iostream>
#include <cstring>
#include <fstream>


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();	// 생성자

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonEnd2();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)				// NULL 생성자
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)						// 매크로
	ON_BN_CLICKED(IDC_BUTTON_END2, &CAboutDlg::OnBnClickedButtonEnd2)
END_MESSAGE_MAP()

// CmfcMemoDlg 대화 상자

CmfcMemoDlg::CmfcMemoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCMEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CmfcMemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MEMO, mEditMemo);
}

BEGIN_MESSAGE_MAP(CmfcMemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MENU_OPEN, &CmfcMemoDlg::OnMenuOpen)
	ON_COMMAND(ID_MENU_ABOUT, &CmfcMemoDlg::OnMenuAbout)
	ON_COMMAND(ID_MENU_FIND, &CmfcMemoDlg::OnMenuFind)
	ON_COMMAND(ID_MENU_FIND_MORE, &CmfcMemoDlg::OnMenuFindMore)
	ON_COMMAND(ID_MENU_UTF8, &CmfcMemoDlg::OnMenuUtf8)
	ON_COMMAND(ID_MENU_ANSI, &CmfcMemoDlg::OnMenuAnsi)
	ON_COMMAND(ID_MENU_REPLACE, &CmfcMemoDlg::OnMenuReplace)
	ON_WM_SIZE()
	ON_COMMAND(ID_MENU_FONT, &CmfcMemoDlg::OnMenuFont)
	ON_WM_MOUSEHWHEEL()
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_BUTTON_END2, &CmfcMemoDlg::OnBnClickedButtonEnd2)
END_MESSAGE_MAP()


// CmfcMemoDlg 메시지 처리기

BOOL CmfcMemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	fntSize = 100;
	fntName = "Arial";

	mAccel = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCEL1));	// 단축키 초기화
	mStatusBar.Create(WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, 0);
	// 선언된 변수를 생성해 호출한다. 모든 콘트롤은 window다
	// mStatusBar.Create()=상태 표시줄(Status Bar)을 동적으로 생성하고 초기화
	// WS_CHILD=window 하단에 위치.WS_VISIBLE=window와 동시생성/크기지정 필요x
	// 
	//RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 2);			// StatusBar 위치조정
	//HWND hSB = mStatusBar.GetSafeHwnd();
	//GetDynamicLayout()->AddItem(hSB, 
	//	CMFCDynamicLayout::MoveVertical(90), 
	//	CMFCDynamicLayout::SizeHorizontal(90));
	// 동적 레이아웃 매니저에 새 항목 추가해 다양한 해상도 및 화면 크기에 대응

	int sec[] = { 100, 200 };
	mStatusBar.SetParts(2, sec);
	//mStatusBar.SetText(" Test1", 0, SBT_NOBORDERS);
	//mStatusBar.SetText(" Test2", 1, SBT_NOBORDERS);
	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CmfcMemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CmfcMemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서 이 함수를 호출합니다.
HCURSOR CmfcMemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// MFC를 사용해 Dialog에서 Open 메뉴를 선택시 호출되는 함수
// 파일을 열고 해당 파일의 내용을 읽어와 Edit Control에 표시

void CmfcMemoDlg::OnMenuOpen()						// File Open Menu 처리기
{
	char buf[512];
	CString str;

	char fName[300]="";						// ofn의 filename 저장공간
	OPENFILENAME ofn;						// 구조체
	//ZeroMemory(&ofn, sizeof(ofn));				// 메모리 초기화
	//ZeroMemory(fName, sizeof(fName));
	memset(&ofn, 0, sizeof(OPENFILENAME));	// ZeroMemory 같은 역할


	ofn.lStructSize = sizeof(OPENFILENAME);	// 구조체 크기지정
	ofn.lpstrFile = fName;						// 선택한 파일의 경로 및 이름을 저장할 버퍼를 지정
	ofn.nMaxFile = 100;
	ofn.lpstrDefExt = "";
	if (!GetOpenFileName(&ofn)) return;
	
	str = buf;							// CString <== Wchar, CString <== char 대입가능
	
	// C 언어의 표준함수. ANSI encoding
	if (mEncoding == 0)
	{
		FILE* fp = fopen(fName, "rb");				// fopen = C언어 표준함수/CStringA = ANSI(ASCII) 문자열을 다루는 클래스
		while (fgets(buf, 512, fp))				// 512(최대갯수)만큼 읽어온다, \r\n을 만나면 거기까지 읽는다
		{
			((CEdit*)GetDlgItem(IDC_EDIT1))->GetWindowText(str);
			GetDlgItem(IDC_EDIT1)->SetWindowText(str + buf);
		}
	}
	// C++ stream 표준 .UTF-8(웹에서 표준 문자 인코딩으로 사용) encoding
	// locale = 언어 및 지역별로 특정 기능과 데이터를 다루는 역할
	
	else if (mEncoding == 1)
	{
		wchar_t buf1[512];
		std::locale::global(std::locale(".UTF-8"));		// 전역 로케일을 UTF-8 인코딩으로 설정
		std::wifstream ff(fName);
		//ff.open(fName);					// 지정된 파일을 읽기 위한 wifstream형태의 입력 스트림 ff를 생성
		for (; ff.getline(buf1, 512);)
		{
			str = buf1;
			AddText(str);
			AddText("\r\n");
		}
	}
}

void CmfcMemoDlg::AddText(CString s)
{
	CString str;
	((CEdit*)GetDlgItem(IDC_EDIT1))->GetWindowText(str);
	str += s;	
	GetDlgItem(IDC_EDIT1)->SetWindowText(str);
}

void CmfcMemoDlg::OnMenuAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}

void CmfcMemoDlg::OnMenuFind()
{
	CmfcFindDlg dlg; 						// dlg객체도 변수이다
	if (dlg.DoModal() == IDOK)					// FIND 할 문자열 입력
	{
		CString s;
		mEditMemo.GetWindowText(s);
		Data = dlg.mStr;					// 입력한 문자열을 다른 윈도우로 가져올 변수에 저장 
		int start = s.Find(dlg.mStr);				// s에 담긴 문자열의 위치(시작점)를 가져온다
		int end = start + dlg.mStr.GetLength();			// 시작점부터 찾으려는 길이 = 끝점
		mEditMemo.SetSel(start, end);				// 블록지정
		start_pos = start + 1;					// 실행 후 다음 찾기를 위해 시작점을 이동한다		
	}
}

void CmfcMemoDlg::OnMenuFindMore()
{		
	CString s;
	mEditMemo.GetWindowText(s);	
	start_pos = s.Find(Data, start_pos);				// s에 담긴 문자열의 위치를 새 시작점에서 가져온다
	int end = start_pos + Data.GetLength();
	mEditMemo.SetSel(start_pos, end);
	start_pos++;							// 시작점을 계속 바꿔준다
}

void CmfcMemoDlg::OnMenuReplace()
{
	CmfcReplace dlg; 							
	if (dlg.DoModal() == IDOK)					// FIND & REPLACE 할 문자열 입력
	{
		CString s;
		mEditMemo.GetWindowText(s);
		sFind = dlg.mStrFind;						
		sReplace = dlg.mStrReplace;
		s.Replace(sFind, sReplace);
		mEditMemo.SetWindowText(s);
	}
}



// PreTranslateMessage 메시지처리 전 호출함수
// 결과에 따라 TRUE/FALSE를 반환 메시지를 처리할지 결정

BOOL CmfcMemoDlg::PreTranslateMessage(MSG* pMsg)
{
	if (mAccel)
	{
		if (TranslateAccelerator(m_hWnd, mAccel, pMsg)) return TRUE;	
		// 주어진 메시지를 Accelerator로 해석/작업을 수행
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CmfcMemoDlg::OnMenuUtf8()
{
	CMenu* m = GetMenu();
	m->CheckMenuItem(ID_MENU_UTF8, MF_CHECKED);			// 선택옵션에 체크
	m->CheckMenuItem(ID_MENU_ANSI, MF_UNCHECKED);
	mStatusBar.SetText(" UTF-8", 0, SBT_NOBORDERS);	
	mEncoding = 1;
}

void CmfcMemoDlg::OnMenuAnsi()
{
	CMenu* m = GetMenu();
	m->CheckMenuItem(ID_MENU_UTF8, MF_UNCHECKED);
	m->CheckMenuItem(ID_MENU_ANSI, MF_CHECKED);	
	mStatusBar.SetText(" ANSI", 0, SBT_NOBORDERS);
	mEncoding = 0;
}

void CmfcMemoDlg::OnSize(UINT nType, int cx, int cy)	// 사용자영역의 크기
{
	CDialogEx::OnSize(nType, cx, cy);
	int nSBHeight = 30;
	if (mStatusBar)							// mStatusBar 생성전이면
	{
		mStatusBar.MoveWindow(0, cy - nSBHeight, cx, nSBHeight);
	}
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CmfcMemoDlg::OnMenuFont()
{
	CFontDialog dlg;
	dlg.DoModal();

	fntSize = dlg.GetSize();
	fntName = dlg.GetFaceName();

	CFont font;
	font.CreatePointFont(fntSize, fntName);
	GetDlgItem(IDC_EDIT_MEMO)->SetFont(&font);
	font.Detach();
}

BOOL CmfcMemoDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (nFlags == MK_CONTROL)
	{
		if (zDelta <= 0)fntSize += 5;
		else           fntSize -= 5;
		if (fntSize < 20) fntSize = 20;

		CFont font;
		font.CreatePointFont(fntSize, fntName);
		GetDlgItem(IDC_EDIT_MEMO)->SetFont(&font);
		font.Detach();
	}
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}
