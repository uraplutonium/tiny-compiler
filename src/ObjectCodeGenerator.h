// ObjectCodeGenerator.h : ͷ�ļ�
//

#pragma once
#include "Table.h"
#include <fstream>
using namespace std;

// Ŀ�������������
class ObjectCodeGenerator
{
private:
	ASTreeNode *Head;		// �����﷨�������ָ��
	SymbolTable * STHead;	// ���ű�ָ��
	int Llength;			// ���ű���
	ASTList *TNodeStack;	// �����﷨�����ָ��ջ
	int THight;				// �����﷨���ĸ߶�
	CString ObjectCode;		// Ŀ�����

	int TreeHight(ASTreeNode *p);	// ���س����﷨���ĸ߶�

public:
	inline ObjectCodeGenerator()	// ���캯��
	{
		Llength=0;
		Head = NULL;
	}

	// ��ʼ���������������Ϊ�����﷨�������ָ�룬���ű�ָ�룬���ű���
	void Initialize(ASTreeNode *p_as_tree, SymbolTable *p_symbol_table, int length_list);

	// ����Ŀ����뺯����ִ������Ŀ��������
	void GenerateObjectCode();

	// ������Ҫ��ʾ��Ŀ���������
	CString GetOutput();
};



	


