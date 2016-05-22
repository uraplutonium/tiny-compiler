// SemanticAnalyzer.h : 头文件
//

#pragma once
#include "Table.h"

//	1 .数字
//	2 .代码段地址
//	3 .符号表地址

// 语义分析器类
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

	int TreeHight(ASTreeNode *p);		// 返回树的高度
	void ThrAdrCod(ASTreeNode *p);		// 得到三地址代码
	void Init();						// 初始化三地址代码
	CString GetOperator(Code op_code);	// 由操作符代码得到操作符内容

public:
	inline SemanticAnalyzer()	// 构造函数
	{
		Head=NULL;
		StackIp=0;
		TempTop=-1;
		symbol_table = NULL;
	};

	// 初始化函数，传入参数为抽象语法树根结点指针，符号表指针
	void Initialize(ASTreeNode *p, SymbolTable *p_symbol_table);

	// 语义分析函数，执行语义分析过程
	void SemanticAnalyze();

	// 返回所要显示的三地址代码内容
	CString GetOutput();
};