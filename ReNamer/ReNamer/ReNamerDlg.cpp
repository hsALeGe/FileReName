
// ReNamerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ReNamer.h"
#include "ReNamerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CReNamerDlg 对话框



CReNamerDlg::CReNamerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RENAMER_DIALOG, pParent)
	, m_strFileFormat(_T(""))
	, m_strBeginIndex(_T(""))
	, m_strEndIndex(_T(""))
	, m_strFileExtName(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReNamerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FILEFORMATE, m_strFileFormat);
	DDX_Text(pDX, IDC_EDIT_FILE_BEGININDEX, m_strBeginIndex);
	DDX_Text(pDX, IDC_EDIT_FILE_ENDINDEX, m_strEndIndex);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strFileExtName);
}

BEGIN_MESSAGE_MAP(CReNamerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SELFILES, &CReNamerDlg::OnBnClickedBtnSelfiles)
	ON_BN_CLICKED(IDC_BTN_RENAME, &CReNamerDlg::OnBnClickedBtnRename)
	ON_BN_CLICKED(IDC_BTN_JSONTOEXCEL, &CReNamerDlg::OnBnClickedBtnJsontoexcel)
END_MESSAGE_MAP()


// CReNamerDlg 消息处理程序

BOOL CReNamerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CReNamerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CReNamerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CReNamerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


static int CALLBACK SHBrowseInfoCallBackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lPdata) {
	switch (uMsg)
	{
	case BFFM_INITIALIZED:
		::SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lPdata);   //传递默认打开路径 break;  
	case BFFM_SELCHANGED:    //选择路径变化，BFFM_SELCHANGED  
	{
		char curr[MAX_PATH];
		SHGetPathFromIDList((LPCITEMIDLIST)lParam, (LPWSTR)(LPCTSTR)curr);
		::SendMessage(hwnd, BFFM_SETSTATUSTEXT, 0, (LPARAM)&curr[0]);
	}
	break;
	default:
		break;
	}
	return 0;
}

void CReNamerDlg::OnBnClickedBtnSelfiles()
{
	m_strPathName=TEXT("");
	m_strVFileName.clear();
	m_strFileFormat = TEXT("");
	m_strBeginIndex = TEXT("");
	m_strEndIndex = TEXT("");
	m_strFileExtName = TEXT("");

	UpdateData(TRUE);
	if (m_strFileExtName == "")
	{
		MessageBox(TEXT("请输入文件扩展名，例如：jpg"));
		return;
	}
	TCHAR szDisplayName[MAX_PATH] = TEXT("");

	ITEMIDLIST * ppid;
	SHGetSpecialFolderLocation(m_hWnd, CSIDL_DRIVES, &ppid);

	//定义浏览文件夹结构体
	BROWSEINFO info;
	info.hwndOwner = this->GetSafeHwnd();
	info.pszDisplayName = szDisplayName;
	info.lpszTitle = TEXT("请选择要重命名文件夹");
	info.lpfn = SHBrowseInfoCallBackProc;
	info.lParam = (LPARAM)TEXT("C:\\");
	info.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	info.pidlRoot = ppid;


	LPITEMIDLIST pIDList = SHBrowseForFolder(&info);
	TCHAR szPathName[MAX_PATH] = TEXT("");
	if (pIDList)
	{
		SHGetPathFromIDList(pIDList, szPathName);
	}
	m_strPathName.Format(TEXT("%s"), szPathName);

	SetDlgItemText(IDC_EDIT_FILEPATH, m_strPathName);
	LoadFile();


}

std::vector<CString> vec_str_filename;
std::vector<CString> vec_str_beginindex;
std::vector<CString> vec_str_endIndex;
void CReNamerDlg::OnBnClickedBtnRename()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strBeginIndex = TEXT("");
	m_strEndIndex = TEXT("");
	m_strFileExtName = TEXT("");
	vec_str_filename.clear();
	vec_str_beginindex.clear();
	vec_str_endIndex.clear();

	UpdateData(TRUE);
	if (m_strPathName == "")
	{
		MessageBox(TEXT("请选择文件夹")); 
		return;
	}
	if(m_strFileFormat=="")
	{
		MessageBox(TEXT("请输入文件名格式。例如：file_#_#,其中#为数字代号"));
	return;
	}
	if(m_strBeginIndex == "")
	{
		MessageBox(TEXT("请输入编号。例如：00,000.00为第一个#位置开始编号，000为第二个#位置开始编号"));
		return;
	}
	if (m_strEndIndex == "")
	{
		MessageBox(TEXT("请输入编号。例如：99,999.99为第一个#位置结束编号，999为第二个#位置结束编号"));
		return;
	}
	

	OnSubStr(m_strFileFormat,TEXT("#"), vec_str_filename);
	OnSubStr(m_strBeginIndex, TEXT(","), vec_str_beginindex);
	OnSubStr(m_strEndIndex, TEXT(","), vec_str_endIndex);
	OnRenameFile();
	CRect rect;
}

//递归取值

void CReNamerDlg::OnSubStr(CString strInfo, CString strSign, std::vector<CString> &str) {
	if (strInfo == "") return;
	int index = strInfo.Find(strSign);
	if (index != -1) {
		str.push_back(strInfo.Left(index));
		int length = strInfo.GetLength();
		CString cstr = strInfo.Right(length - index - 1);
		OnSubStr(cstr, strSign, str);
	}else if (strInfo != TEXT("") && (strInfo.Find(strSign) == -1))
		str.push_back(strInfo);
	return;

}

void CReNamerDlg::OnRenameFile() {
	std::vector<char*> vec_char_begin;
	std::vector<char*> vec_char_end;

	for (size_t i = 0; i < vec_str_beginindex.size(); i++)
	{
		char * ch1, *ch2;
		int len1, len2;
		len1 = WideCharToMultiByte(CP_UTF8, 0, vec_str_beginindex[i], -1, NULL, 0, NULL, NULL);
		ch1 = new char[len1 + 1];
		ZeroMemory(ch1, sizeof(char)*(len1 + 1));
		WideCharToMultiByte(CP_UTF8, 0, vec_str_beginindex[i], -1, ch1, len1, NULL, NULL);
		vec_char_begin.push_back(ch1);

		len2 = WideCharToMultiByte(CP_UTF8, 0, vec_str_endIndex[i], -1, NULL, 0, NULL, NULL);
		ch2 = new char[len2 + 1];
		ZeroMemory(ch2, sizeof(char)*(len2 + 1));
		WideCharToMultiByte(CP_UTF8, 0, vec_str_endIndex[i], -1, ch2, len2, NULL, NULL);
		vec_char_end.push_back(ch2);
	}
	
	std::vector<CString> vec_new_fileName;
	std::vector<CString> vec_new_fileName2;
	for (int i = 0; i < vec_char_begin.size(); ++i) {
		vec_new_fileName2.clear();
		vec_new_fileName2 = vec_new_fileName;
		vec_new_fileName.clear();
		GetNewFileName(vec_str_filename[i], atoi(vec_char_begin[i]), atoi(vec_char_end[i]), vec_new_fileName, vec_new_fileName2);
	}

	for (int i = 0; i < m_strVFileName.size(); ++i) {
		CString str = m_strPathName + TEXT("\\") + vec_new_fileName[i] + (vec_str_filename.size() == vec_char_begin.size() ? TEXT("") : vec_str_filename[vec_str_filename.size() - 1]) + TEXT(".png");
		CFile::Rename(m_strVFileName[i],str);
	}
	LoadFile();
	MessageBox(TEXT("重命名成功"));
}

CString CReNamerDlg::GetNewFileName(CString strFormat, int beginIndex, int endIndex, std::vector<CString> &vec_new_fileName, std::vector<CString> vec_new_fileName2) {
	CString tmpStr = TEXT("");
	static int i = 0;
	if (beginIndex >= endIndex || beginIndex >= m_strVFileName.size()) return strFormat;	
	if(vec_new_fileName2.size() ==0)
		tmpStr.Format(TEXT("%s%s%d"), strFormat, BinarySearch(beginIndex,endIndex), beginIndex);
	else {
		if (i >= vec_new_fileName2.size()) return strFormat;
		tmpStr.Format(TEXT("%s%s%s%d"), vec_new_fileName2[i++] ,strFormat, BinarySearch(beginIndex, endIndex), beginIndex);
	}
	vec_new_fileName.push_back(tmpStr);
	GetNewFileName(strFormat, ++beginIndex, endIndex, vec_new_fileName, vec_new_fileName2);
	i = 0;
	return tmpStr;
	
}

void CReNamerDlg::LoadFile() {
	// TODO: 在此添加控件通知处理程序代码

	m_strVFileName.clear();
	WIN32_FIND_DATA data;
	ZeroMemory(&data, sizeof(WIN32_FIND_DATA));
	CString str = m_strPathName + TEXT("\\*.") + m_strFileExtName;
	HANDLE file = FindFirstFile(str.GetBuffer(), &data);
	if (StrCmp(data.cFileName, TEXT("")))
		if (data.cFileName != TEXT(".") || data.cFileName != TEXT(".."))
			m_strVFileName.push_back(m_strPathName + TEXT("\\") + data.cFileName);

	while (FindNextFile(file, &data)) {
		if (data.cFileName != TEXT(".") || data.cFileName != TEXT(".."))
			m_strVFileName.push_back(m_strPathName + TEXT("\\") + data.cFileName);
	}
}

static int SearchByIndex(int index) {
	int arr[] = { 0,10,100,1000,10000,100000 };
	if (index >= arr[0] && index < arr[1])
		return 1;
	else if (index >= arr[1] && index < arr[2])
		return 2;
	else if (index >= arr[2] && index < arr[3])
		return 3;
	else if (index >= arr[3] && index < arr[4])
		return 4;
	else if (index >= arr[4] && index < arr[5])
		return 5;
}

CString CReNamerDlg::BinarySearch(int begin, int end) {
	CString str = TEXT("");

	for (int i = SearchByIndex(begin); i < SearchByIndex(end); ++i)
		str += TEXT("0");
	return str;
}



void CReNamerDlg::OnBnClickedBtnJsontoexcel()
{
	// TODO: 在此添加控件通知处理程序代码
}
