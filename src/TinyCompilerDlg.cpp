// TinyCompilerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TinyCompiler.h"
#include "TinyCompilerDlg.h"
#include <fstream>
#pragma warning(disable: 4996)
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTinyCompilerDlg 对话框

CTinyCompilerDlg::CTinyCompilerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTinyCompilerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTinyCompilerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Edit_Input);
	DDX_Control(pDX, IDC_LIST1, m_List_Word);
	DDX_Control(pDX, IDC_TREE1, m_Tree);
	DDX_Control(pDX, IDC_EDIT3, m_Edit_Ternary);
	DDX_Control(pDX, IDC_EDIT4, m_Edit_Output);
}

BEGIN_MESSAGE_MAP(CTinyCompilerDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTinyCompilerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTinyCompilerDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTinyCompilerDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTinyCompilerDlg::OnBnClickedButton4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// CTinyCompilerDlg 消息处理程序

BOOL CTinyCompilerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_ImageList.Create(32, 32, ILC_COLOR24 | ILC_MASK, 4, 1);
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON1));
	HICON hIcon = ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	m_Tree.SetImageList(&m_ImageList, LVSIL_NORMAL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTinyCompilerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CTinyCompilerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTinyCompilerDlg::OnBnClickedButton1()
{
	CString FileName, str_content, str_buf;
	CFileDialog MyFileDialog(TRUE, _T("*.txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Tiny源文件(*.txt)|*.txt||"), this);
	if (MyFileDialog.DoModal()==IDOK)
	{
		FileName = MyFileDialog.GetPathName();
		ifstream* infile = new(ifstream);
		infile->open(FileName, ios::in);
		char ch;
		while(1)
		{
			infile->get(ch);
			if(infile->eof())
				break;
			if(ch == '\n')
				str_buf.Format(_T("\r\n"));
			else
				str_buf.Format(_T("%c"), ch);
			str_content+=str_buf;
		}
		m_Edit_Input.SetWindowTextW(str_content);
		infile->close();
	}
}

void CTinyCompilerDlg::OnBnClickedButton2()
{
	CString FileName, str_content;
	CFileDialog MyFileDialog(FALSE, _T("*.txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Tiny源文件(*.txt)|*.txt||"), this);
	if (MyFileDialog.DoModal()==IDOK)
	{
		int length, i;
		char *ch_buf;
		m_Edit_Input.GetWindowTextW(str_content);
		USES_CONVERSION;
		length = str_content.GetLength();
		ch_buf = new char[length];
		LPTSTR Lstr = str_content.GetBuffer();
		const char* p_buf = T2A(Lstr);
		strcpy(ch_buf, p_buf);
		FileName = MyFileDialog.GetPathName();
		ofstream* outfile = new(ofstream);
		outfile->open(FileName, ios::out);
		for(i = 0 ; i < length ; i++)
		{
			if(p_buf[i] != '\r')
				*outfile <<p_buf[i];
		}
		outfile->close();
	}
}

void CTinyCompilerDlg::OnBnClickedButton3()
{
	CString str_input;
	bool error;
	m_Compiler.Initialize(&m_List_Word, &m_Tree);
	m_Edit_Input.GetWindowTextW(str_input);
	error = m_Compiler.Compile(str_input);
	if(error == false)
		return;
	m_Compiler.DisplayWordList();
	m_Compiler.DisplayASTree();
	m_Edit_Ternary.SetWindowTextW(m_Compiler.GetTernaryFormula());
	m_Edit_Output.SetWindowTextW(m_Compiler.GetCCode());
}

void CTinyCompilerDlg::OnBnClickedButton4()
{
	CString FileName, str_content;
	CFileDialog MyFileDialog(FALSE, _T("*.c"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("C源文件(*.c)|*.c||"), this);
	if (MyFileDialog.DoModal()==IDOK)
	{
		int length, i;
		char *ch_buf;
		m_Edit_Output.GetWindowTextW(str_content);
		USES_CONVERSION;
		length = str_content.GetLength();
		ch_buf = new char[length];
		LPTSTR Lstr = str_content.GetBuffer();
		const char* p_buf = T2A(Lstr);
		strcpy(ch_buf, p_buf);
		FileName = MyFileDialog.GetPathName();
		ofstream* outfile = new(ofstream);
		outfile->open(FileName, ios::out);
		for(i = 0 ; i < length ; i++)
		{
			if(p_buf[i] != '\r')
				*outfile <<p_buf[i];
		}
		outfile->close();
	}
}