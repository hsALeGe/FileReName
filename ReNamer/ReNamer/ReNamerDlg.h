
// ReNamerDlg.h : 头文件
//

#pragma once
#include <vector>

// CReNamerDlg 对话框
class CReNamerDlg : public CDialogEx
{
// 构造
public:
	CReNamerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RENAMER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnSelfiles();

	//变量声明
private:
	CString  m_strPathName;
	std::vector<CString> m_strVFileName;
public:
	CString m_strFileFormat;
	CString m_strBeginIndex;
	CString m_strEndIndex;
	CString m_strFileExtName;

	afx_msg void OnBnClickedBtnRename();

private:
	void OnSubStr(CString strInfo, CString strSign, std::vector<CString> &str);
	void OnRenameFile();
public:
	afx_msg void OnBnClickedBtnJsontoexcel();
	CString GetNewFileName(CString fileFormat, int beginIndex, int endIndex, std::vector<CString> &vec_new_fileName, std::vector<CString> vec_new_fileName2);
	CString BinarySearch(int begin , int end);
	void LoadFile();
};
