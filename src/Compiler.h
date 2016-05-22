// Compiler.h : ͷ�ļ�
//

#pragma once
#include "Table.h"
#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"
#include "SemanticAnalyzer.h"
#include "ObjectCodeGenerator.h"

// ��������
class Compiler
{
private:
	// ָ��ListBox��TreeCtrl�ؼ���ָ�룬������ʾ���ʱ�ͳ����﷨��
	CListBox *p_List_Word;
	CTreeCtrl *p_Tree;

	// ����������Ҫ��Դ
	SymbolTable *symbol_table;		// ���ű�
	WordList *word_list;			// ���ʱ�
	ASTree *abstract_syntax_tree;	// �����﷨��
	int ListLength;					// ���ű���

	// ����������ɲ���
	LexicalAnalyzer lexical_analyzer;			// �ʷ�������
	SyntaxAnalyzer syntax_analyzer;				// �﷨������
	SemanticAnalyzer semantic_analyzer;			// ���������
	ObjectCodeGenerator objectcode_generator;	// Ŀ�����������

	// ʵ�ֺ���
	void DisplayASTreeNode(ASTreeNode *p_Tnode);	// �ݹ���õ����������ĺ���
	CString GetOperator(Code op_code);				// �ɲ���������õ�������ʾ�Ĳ���������

public:
	inline Compiler()	// ���캯��
	{
		p_List_Word = NULL;
		p_Tree = NULL;
		symbol_table = new(SymbolTable);
		word_list = new(WordList);
		word_list->next = NULL;
		abstract_syntax_tree = new(ASTree);
		abstract_syntax_tree->child1 = NULL;
		abstract_syntax_tree->child2 = NULL;
		abstract_syntax_tree->child3 = NULL;
		abstract_syntax_tree->word = NULL;
		ListLength=0;
	};

	// ��ʼ�����������뵥�ʱ������﷨����Ҫ��ʾ�Ŀؼ�ָ��
	void Initialize(CListBox *m_List_Word, CTreeCtrl *m_Tree);

	// ���뺯����ִ�б������
	bool Compile(CString input);

	// ��ʾ����
	void DisplayWordList();		// ��ʾ���ʱ�
	void DisplayASTree();		// ��ʾ�����﷨��
	CString GetTernaryFormula();// ������Ԫʽ��ʾ����
	CString GetCCode();			// ����Ŀ�������ʾ����
};