// LexicalAnalyzer.h : 头文件
//

#pragma once
#include "Table.h"

// 符号结点/符号链表结构体
struct SymbolNode
{
	char *symbol;
	SymbolNode *next;
};
typedef SymbolNode SymbolList;

// 词法分析器类
class LexicalAnalyzer
{
private:
	int length;		// 输入字符串长度
	int *Llength;	// 编译器类中存储符号表长度的指针
	char* input;	// 输入字符串的头指针
	SymbolList *symbol_list;	// 符号链表，用来辅助生成符号表
	SymbolTable **symbol_table;	// 符号表二级指针
	WordList *word_list;		// 单词表头结点指针

	bool isLetter(char ch);		// 判断ch是否为字母
	bool isDigit(char ch);		// 判断ch是否为数字
	Code isReserved(char ch[]);	// 判断ch[]是否为保留字
	int GetNum(char ch[]);		// 将字符串ch[]转化为整型数字
	void InsertWordNode(Code code, int linage, int value);	// 向单词表中插入结点，传入参数为插入结点的内容
	void BuildSymbolTable();	// 生成符号表

public:
	inline LexicalAnalyzer()	// 构造函数
	{
		input = NULL;
		symbol_list = new(SymbolList);
		symbol_list->next = NULL;
		symbol_table = NULL;
		word_list = NULL;
		Llength=0;
	};

	// 初始化函数，传入参数为：输入字符串，符号表二级指针，单词表头结点指针，指向存储符号表长度的整型数字的指针
	void Initialize(CString str_input, SymbolTable **p_symbol_table, WordList *p_word_list, int *p_length_list);

	// 词法分析函数，执行词法分析过程
	int LexicalAnalyze();
};