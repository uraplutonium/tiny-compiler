// TinyCompilerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "Compiler.h"

// CTinyCompilerDlg �Ի���
class CTinyCompilerDlg : public CDialog
{
// ����
public:
	CTinyCompilerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TINYCOMPILER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;			// ͼ��
	Compiler m_Compiler;	// ������
	CEdit m_Edit_Input;		// Tiny��������༭��ؼ�
	CListBox m_List_Word;	// ���ʱ�༭��ؼ�
	CTreeCtrl m_Tree;		// �����﷨���ؼ�
	CEdit m_Edit_Ternary;	// ��Ԫʽ�༭��ؼ�
	CEdit m_Edit_Output;	// C��������༭��ؼ�
	CImageList m_ImageList;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	DECLARE_MESSAGE_MAP()
};
