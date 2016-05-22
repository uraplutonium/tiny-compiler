// SemanticAnalyzer.cpp : 实现文件
//

#include "stdafx.h"
#include "Table.h"
#include <fstream>
#include "SemanticAnalyzer.h"
using namespace std;

int SemanticAnalyzer::TreeHight(ASTreeNode *p)
{
	int ht;
	int k;
	if(p==NULL)
		return 0;
	k=p->operator_code;
	if(k==3)
	{
		ht=TreeHight(p->child1)+TreeHight(p->child2)+TreeHight(p->child3)+2;
	}
	else if(k==6||k==7)
	{
		ht=TreeHight(p->child1)+1;
	}
	else if(k==1)
	{
		ht=TreeHight(p->child1)+TreeHight(p->child2);
	}
	else if(k==0)
	{
		ht=0;
	}
	else
	{
		ht=TreeHight(p->child1)+TreeHight(p->child2)+1;
	}
	return ht;
}

void SemanticAnalyzer::Init()
{
	Ht=TreeHight(Head);
	OP = new int[Ht+10];
	Ty1 =new int[Ht+10];
	Ty2 = new int[Ht+10];
	Arg1 = new int[Ht+10];
	Arg2 = new int[Ht+10];
}

CString SemanticAnalyzer::GetOperator(Code op_code)
{	
	CString op;
	switch(op_code)
	{
	case SEMICOLON_SYM:
		{
			op = _T("        ;         ");
			break;
		}
	case IF_SYM:
		{
			op = _T("   if_then_end    ");
			break;
		}
	case IF_ELSE_SYM:
		{
			op = _T(" if_then_else_end ");
			break;
		}
	case REPEAT_SYM:
		{
			op = _T("   repeat_until   ");
			break;
		}
	case ASSIGN_SYM:
		{
			op = _T("        :=        ");
			break;
		}
	case READ_SYM:
		{
			op = _T("       read       ");
			break;
		}
	case WRITE_SYM:
		{
			op = _T("       write      ");
			break;
		}
	case LESS_SYM:
		{
			op = _T("         <        ");
			break;
		}
	case EQUAL_SYM:
		{
			op = _T("         =        ");
			break;
		}
	case ADD_SYM:
		{
			op = _T("         +        ");
			break;
		}
	case SUBTRACT_SYM:
		{
			op = _T("         -        ");
			break;
		}
	case MULTIPLAY_SYM:
		{
			op = _T("         *        ");
			break;
		}
	case DIVIDE_SYM:
		{
			op = _T("         /        ");
			break;
		}
	case JZ_SYM:
		{
			op = _T("        jz        ");
			break;
		}
	case JMP_SYM:
		{
			op = _T("       jmp        ");
			break;
		}
	}
	return op;
}

void SemanticAnalyzer::Initialize(ASTreeNode *p, SymbolTable *p_symbol_table)
{
	StackIp=0;
	TempTop=-1;
	Head=p;
	symbol_table = p_symbol_table;
}

void SemanticAnalyzer::ThrAdrCod(ASTreeNode *p)
{
	if(p==NULL)
		return;

	int k1;
	int pop;
	pop=p->operator_code;
	if(pop==1)
	{
		ThrAdrCod(p->child1);
		ThrAdrCod(p->child2);
	}
	else if(pop==2)
	{
		ThrAdrCod(p->child1);
		OP[StackIp]=JZ_SYM;
		Ty1[StackIp]=Type[TempTop];
		Arg1[StackIp]=Temp[TempTop];
		Ty2[StackIp]=2;
		k1=StackIp;
		StackIp++;
		ThrAdrCod(p->child2);
		Arg2[k1]=StackIp;
		TempTop=-1;
	}
	else if(pop==3)
	{
		ThrAdrCod(p->child1);
		OP[StackIp]=JZ_SYM;
		Ty1[StackIp]=Type[TempTop];
		Arg1[StackIp]=Temp[TempTop];
		Ty2[StackIp]=2;
		k1=StackIp;
		StackIp++;
		ThrAdrCod(p->child2);
		Arg2[k1]=StackIp;
		OP[StackIp]=JMP_SYM;
		Ty1[StackIp]=2;
		k1=StackIp;
		StackIp++;
		ThrAdrCod(p->child3);
	    Arg1[k1]=StackIp;
		TempTop=-1;
	}
	else if(pop==4)
	{
		k1=StackIp;
		ThrAdrCod(p->child1);
		ThrAdrCod(p->child2);
		OP[StackIp]=JZ_SYM;
		Ty1[StackIp]=Type[TempTop];
		Arg1[StackIp]=Temp[TempTop];
		Ty2[StackIp]=2;
		Arg2[StackIp]=k1;
		StackIp++;
		TempTop=-1;
	}
	else if(pop==5)
	{
		ThrAdrCod(p->child1);
		OP[StackIp]=5;
		Ty1[StackIp]=3;
		Arg1[StackIp]=(p->word)->value;
		Ty2[StackIp]=Type[TempTop];
		Arg2[StackIp]=Temp[TempTop];
		StackIp++;
		TempTop=-1;
	}
	else if(pop==6)
	{
		OP[StackIp]=6;
		Ty1[StackIp]=3;
		Arg1[StackIp]=(p->word)->value;
		StackIp++;
		TempTop=-1;
	}
	else if(pop==7)
	{
		ThrAdrCod(p->child1);
		OP[StackIp]=7;
		Ty1[StackIp]=Type[TempTop];
		Arg1[StackIp]=Temp[TempTop];
		StackIp++;
		TempTop=-1;
	}
	else if(pop==0)
	{
		TempTop++;
		Temp[TempTop]=(p->word)->value;
		if((p->word)->code==18)
			Type[TempTop]=1;
		else
			Type[TempTop]=3;
	}
	else
	{
		ThrAdrCod(p->child1);
		ThrAdrCod(p->child2);
		OP[StackIp]=pop;
		Ty2[StackIp]=Type[TempTop];
		Arg2[StackIp]=Temp[TempTop];
		TempTop--;
		Ty1[StackIp]=Type[TempTop];
		Arg1[StackIp]=Temp[TempTop];
		Type[TempTop]=2;
		Temp[TempTop]=StackIp;
		StackIp++;
	}
}

void SemanticAnalyzer::SemanticAnalyze()
{
	Init();
	ThrAdrCod(Head);
}

CString SemanticAnalyzer::GetOutput()
{
	int i;
	CString str, buf;
	str = _T("\t\tOP\t\tARG1\t\tARG2\r\n");
	for(i = 0 ; i < StackIp ; i++)
	{
		buf.Format(_T("(%d)\t"), i);
		str  = str + buf + GetOperator(OP[i]);
		if(Ty1[i]==1)
			buf.Format(_T(" %d"), Arg1[i]);
		else if(Ty1[i]==2)
			buf.Format(_T("(%d)"), Arg1[i]);
		else
			buf = symbol_table[Arg1[i]].symbol;
		str = str + _T("\t") + buf + _T("\t");
		if((OP[i]!=6)&&(OP[i]!=7)&&(OP[i]!=15))
		{
			if(Ty2[i]==1)
				buf.Format(_T(" %d"), Arg2[i]);
			else if(Ty2[i]==2)
				buf.Format(_T("(%d)"), Arg2[i]);
			else
				buf = symbol_table[Arg1[i]].symbol;
			str = str + _T("\t") + buf;
		}
		str = str + _T("\r\n");
	}
	return str;
}