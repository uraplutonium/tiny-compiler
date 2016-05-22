// SyntaxAnalyer.h : 头文件
//

#pragma once
#include "Table.h"

// action编码
#define ERROR 0
#define S 1
#define R 2
#define ACC 3

// 栈结点/栈
struct StackNode
{
	Code state;
	WordNode *word;
	ASTreeNode *p_tree_node;
	StackNode *next;
};
typedef StackNode Stack;

// 语法分析器类
class SyntaxAnalyzer
{
private:
	Code Action[49][21];	// Action表
	int Goto[49][33];		// Goto表
	Code Production[26];	// 产生式数组
	WordList *word_list;	// 单词表头结点指针
	ASTree *as_tree;		// 抽象语法树根节点指针
	Stack *stack;			// 栈顶指针

	void InitProduction();	// 初始化产生式数组
	void Push(int state, WordNode *p_Wnode, ASTreeNode *p_tree_node);	// 压栈，传入参数为压入栈结点内容
	void Pop();				// 弹栈
	void Reduce(int nProduction, WordNode *p_Wnode);	// 规约函数，传入参数为规约所用产生式编码及当前遇到的字符结点

public:
	inline SyntaxAnalyzer()	// 构造函数
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

	// 初始化函数，传入参数为：Action表文件名，Goto表文件名，单词表头结点指针，抽象语法树根节点指针
	void Initialize(CString ActionFileName, CString GotoFileName, WordList *p_word_list, ASTree *p_as_tree);

	// 语法分析函数，执行语法分析过程
	int SyntaxAnalyze();
};