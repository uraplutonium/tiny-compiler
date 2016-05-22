// ObjectCodeGenerator.h : 头文件
//

#pragma once
#include "Table.h"
#include <fstream>
using namespace std;

// 目标代码生成器类
class ObjectCodeGenerator
{
private:
	ASTreeNode *Head;		// 抽象语法树根结点指针
	SymbolTable * STHead;	// 符号表指针
	int Llength;			// 符号表长度
	ASTList *TNodeStack;	// 抽象语法树结点指针栈
	int THight;				// 抽象语法树的高度
	CString ObjectCode;		// 目标代码

	int TreeHight(ASTreeNode *p);	// 返回抽象语法树的高度

public:
	inline ObjectCodeGenerator()	// 构造函数
	{
		Llength=0;
		Head = NULL;
	}

	// 初始化函数，传入参数为抽象语法树根结点指针，符号表指针，符号表长度
	void Initialize(ASTreeNode *p_as_tree, SymbolTable *p_symbol_table, int length_list);

	// 生成目标代码函数，执行生成目标代码过程
	void GenerateObjectCode();

	// 返回所要显示的目标代码内容
	CString GetOutput();
};



	


