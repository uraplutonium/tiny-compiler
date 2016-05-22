// SyntaxAnalyer.h : ͷ�ļ�
//

#pragma once
#include "Table.h"

// action����
#define ERROR 0
#define S 1
#define R 2
#define ACC 3

// ջ���/ջ
struct StackNode
{
	Code state;
	WordNode *word;
	ASTreeNode *p_tree_node;
	StackNode *next;
};
typedef StackNode Stack;

// �﷨��������
class SyntaxAnalyzer
{
private:
	Code Action[49][21];	// Action��
	int Goto[49][33];		// Goto��
	Code Production[26];	// ����ʽ����
	WordList *word_list;	// ���ʱ�ͷ���ָ��
	ASTree *as_tree;		// �����﷨�����ڵ�ָ��
	Stack *stack;			// ջ��ָ��

	void InitProduction();	// ��ʼ������ʽ����
	void Push(int state, WordNode *p_Wnode, ASTreeNode *p_tree_node);	// ѹջ���������Ϊѹ��ջ�������
	void Pop();				// ��ջ
	void Reduce(int nProduction, WordNode *p_Wnode);	// ��Լ�������������Ϊ��Լ���ò���ʽ���뼰��ǰ�������ַ����

public:
	inline SyntaxAnalyzer()	// ���캯��
	{
		word_list = NULL;
		as_tree = NULL;
		stack = new(StackNode);
		stack->state = 0;
		stack->word = new(WordNode);
		stack->word->code = SIGN_OFF;
		stack->word->value = SIGN_OFF;
		stack->word->linage = 0;
		stack->word->next = NULL;
		stack->next = NULL;
		stack->p_tree_node = NULL;
	};

	// ��ʼ���������������Ϊ��Action���ļ�����Goto���ļ��������ʱ�ͷ���ָ�룬�����﷨�����ڵ�ָ��
	void Initialize(CString ActionFileName, CString GotoFileName, WordList *p_word_list, ASTree *p_as_tree);

	// �﷨����������ִ���﷨��������
	int SyntaxAnalyze();
};