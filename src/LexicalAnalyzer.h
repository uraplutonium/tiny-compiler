// LexicalAnalyzer.h : ͷ�ļ�
//

#pragma once
#include "Table.h"

// ���Ž��/��������ṹ��
struct SymbolNode
{
	char *symbol;
	SymbolNode *next;
};
typedef SymbolNode SymbolList;

// �ʷ���������
class LexicalAnalyzer
{
private:
	int length;		// �����ַ�������
	int *Llength;	// ���������д洢���ű��ȵ�ָ��
	char* input;	// �����ַ�����ͷָ��
	SymbolList *symbol_list;	// �������������������ɷ��ű�
	SymbolTable **symbol_table;	// ���ű����ָ��
	WordList *word_list;		// ���ʱ�ͷ���ָ��

	bool isLetter(char ch);		// �ж�ch�Ƿ�Ϊ��ĸ
	bool isDigit(char ch);		// �ж�ch�Ƿ�Ϊ����
	Code isReserved(char ch[]);	// �ж�ch[]�Ƿ�Ϊ������
	int GetNum(char ch[]);		// ���ַ���ch[]ת��Ϊ��������
	void InsertWordNode(Code code, int linage, int value);	// �򵥴ʱ��в����㣬�������Ϊ�����������
	void BuildSymbolTable();	// ���ɷ��ű�

public:
	inline LexicalAnalyzer()	// ���캯��
	{
		input = NULL;
		symbol_list = new(SymbolList);
		symbol_list->next = NULL;
		symbol_table = NULL;
		word_list = NULL;
		Llength=0;
	};

	// ��ʼ���������������Ϊ�������ַ��������ű����ָ�룬���ʱ�ͷ���ָ�룬ָ��洢���ű��ȵ��������ֵ�ָ��
	void Initialize(CString str_input, SymbolTable **p_symbol_table, WordList *p_word_list, int *p_length_list);

	// �ʷ�����������ִ�дʷ���������
	int LexicalAnalyze();
};