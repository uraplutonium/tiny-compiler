// TinyCompilerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "Compiler.h"

// CTinyCompilerDlg 对话框
class CTinyCompilerDlg : public CDialog
{
// 构造
public:
	CTinyCompilerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TINYCOMPILER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;			// 图标
	Compiler m_Compiler;	// 编译器
	CEdit m_Edit_Input;		// Tiny语言输入编辑框控件
	CListBox m_List_Word;	// 单词表编辑框控件
	CTreeCtrl m_Tree;		// 抽象语法树控件
	CEdit m_Edit_Ternary;	// 三元式编辑框控件
	CEdit m_Edit_Output;	// C语言输出编辑框控件
	CImageList m_ImageList;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	DECLARE_MESSAGE_MAP()
};
