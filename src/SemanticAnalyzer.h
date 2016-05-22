// SemanticAnalyzer.h : ͷ�ļ�
//

#pragma once
#include "Table.h"

//	1 .����
//	2 .����ε�ַ
//	3 .���ű��ַ

// �����������
class SemanticAnalyzer
{
private:
	int Ht;
	int *OP,*Ty1,*Ty2,*Arg1,*Arg2;

	ASTreeNode *Head;
	SymbolTable *symbol_table;
	int StackIp;
	
	int Temp[10];
	int Type[10];
	int TempTop;

	int TreeHight(ASTreeNode *p);		// �������ĸ߶�
	void ThrAdrCod(ASTreeNode *p);		// �õ�����ַ����
	void Init();						// ��ʼ������ַ����
	CString GetOperator(Code op_code);	// �ɲ���������õ�����������

public:
	inline SemanticAnalyzer()	// ���캯��
	{
		Head=NULL;
		StackIp=0;
		TempTop=-1;
		symbol_table = NULL;
	};

	// ��ʼ���������������Ϊ�����﷨�������ָ�룬���ű�ָ��
	void Initialize(ASTreeNode *p, SymbolTable *p_symbol_table);

	// �������������ִ�������������
	void SemanticAnalyze();

	// ������Ҫ��ʾ������ַ��������
	CString GetOutput();
};