// CmfcReplace.cpp: 구현 파일
//

#include "pch.h"
#include "mfcMemo.h"
#include "afxdialogex.h"
#include "CmfcReplace.h"


// CmfcReplace 대화 상자

IMPLEMENT_DYNAMIC(CmfcReplace, CDialogEx)

CmfcReplace::CmfcReplace(CWnd* pParent /*=nullptr*/)				// 클래스추가 후 .h에 정의된 컨트롤을 객체화
	: CDialogEx(IDD_REPLACE_DIALOG, pParent)
{
	mStrFind = "";								// 생성자
	mStrReplace = "";
}

BOOL CmfcReplace::OnInitDialog()						// Dialog의 컨트롤들을 초기화 작업(원하는 구현을 위해 필수)
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

CmfcReplace::~CmfcReplace()
{
}

void CmfcReplace::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CmfcReplace, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_END, &CmfcReplace::OnBnClickedButtonEnd)	
	ON_BN_CLICKED(IDC_BUTTON_END2, &CmfcReplace::OnBnClickedButtonEnd2)
END_MESSAGE_MAP()


// CmfcReplace 메시지 처리기


BOOL CmfcReplace::PreTranslateMessage(MSG* pMsg)				// 클래스 마법사 가상함수에서 추가
{
	switch (pMsg->message)
	{
	case WM_KEYDOWN:
		switch (pMsg->wParam)
		{
		case VK_ESCAPE:
			EndDialog(IDCANCEL);					// End창이 닫히고 종료를 준비한다(함수를 나가지 않는다)
			break;
		case VK_RETURN:
			OnBnClickedButtonEnd();					// 함수로 호출
			// 함수 호출로 중복코드 생략
			//GetDlgItem(IDC_EDIT_FIND1)->GetWindowText(mStrFind);	// mStrFind에 문자열을 저장
			//GetDlgItem(IDC_EDIT_REPLACE1)->GetWindowText(mStrReplace);// mStrReplace에 문자열을 저장
			//EndDialog(IDOK);
			break;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

// 자체가 함수이므로 로컬에서도 호출 가능
// UI BUTTON키 더블클릭시 자동생성. 이벤트큐(OS)에서 호출된다
// 이벤트들은 이벤트 큐에 저장, 프로그램은 큐에서 이벤트를 처리
void CmfcReplace::OnBnClickedButtonEnd()	
{
	GetDlgItem(IDC_EDIT_FIND1)->GetWindowText(mStrFind);		
	GetDlgItem(IDC_EDIT_REPLACE1)->GetWindowText(mStrReplace);	
	EndDialog(IDOK);
}

void CmfcReplace::OnBnClickedButtonEnd2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
