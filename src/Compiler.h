// Compiler.h : 头文件
//

#pragma once
#include "Table.h"
#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"
#include "SemanticAnalyzer.h"
#include "ObjectCodeGenerator.h"

// 编译器类
class Compiler
{
private:
	// 指向ListBox和TreeCtrl控件的指针，用于显示单词表和抽象语法树
	CListBox *p_List_Word;
	CTreeCtrl *p_Tree;

	// 编译器的主要资源
	SymbolTable *symbol_table;		// 符号表
	WordList *word_list;			// 单词表
	ASTree *abstract_syntax_tree;	// 抽象语法树
	int ListLength;					// 符号表长度

	// 编译器的组成部分
	LexicalAnalyzer lexical_analyzer;			// 词法分析器
	SyntaxAnalyzer syntax_analyzer;				// 语法分析器
	SemanticAnalyzer semantic_analyzer;			// 语义分析器
	ObjectCodeGenerator objectcode_generator;	// 目标代码生成器

	// 实现函数
	void DisplayASTreeNode(ASTreeNode *p_Tnode);	// 递归调用的生成树结点的函数
	CString GetOperator(Code op_code);				// 由操作符代码得到所需显示的操作符内容

public:
	inline Compiler()	// 构造函数
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

	// 初始化函数，传入单词表及抽象语法树所要显示的控件指针
	void Initialize(CListBox *m_List_Word, CTreeCtrl *m_Tree);

	// 编译函数，执行编译过程
	bool Compile(CString input);

	// 显示函数
	void DisplayWordList();		// 显示单词表
	void DisplayASTree();		// 显示抽象语法树
	CString GetTernaryFormula();// 返回三元式显示内容
	CString GetCCode();			// 返回目标代码显示内容
};