// ObjectCodeGenerator.cpp : 实现文件
//

#include "stdafx.h"
#include "ObjectCodeGenerator.h"

void ObjectCodeGenerator::Initialize(ASTreeNode *p_as_tree, SymbolTable *p_symbol_table, int length_list)
{
	Head = p_as_tree;
	Llength = length_list;
	STHead = p_symbol_table;
	ObjectCode = _T("");
}

int ObjectCodeGenerator::TreeHight(ASTreeNode *p)
{
	int ht;
	int k;
	if(p==NULL)
		return 0;
	k=p->operator_code;
	if(k==3)
	{
		ht=(TreeHight(p->child1)>TreeHight(p->child2)?TreeHight(p->child1):TreeHight(p->child2));
		ht=(ht>TreeHight(p->child3)?ht:TreeHight(p->child3));
		ht++;
	}
	else if(k==6||k==7)
	{
		ht=TreeHight(p->child1)+1;
	}
	else if(k==1)
	{
		ht=(TreeHight(p->child1)>TreeHight(p->child2)?TreeHight(p->child1):TreeHight(p->child2));
		ht++;
	}
	else if(k==0)
	{
		ht=0;
	}
	else
	{
		ht=(TreeHight(p->child1)>TreeHight(p->child2)?TreeHight(p->child1):TreeHight(p->child2));
		ht++;
	}
	return ht;
}

void ObjectCodeGenerator::GenerateObjectCode()
{
	int TTop=-1;
	int Ti=1;
	ASTList p;
	int *Sta;
	THight=TreeHight(Head);
	int i,j,k,l,m,n,v;

	CString code,buf;
	code=_T("");
	buf=_T("");

	code=code+_T("#include <iostream>")+_T("\r\n")+_T("using namespace std;")+_T("\r\n");
	code=code+_T("void main()")+_T("\r\n")+_T("{")+_T("\r\n");
	for(v=0;v<Ti;v++)
		code=code+_T("\t");
	code=code+_T("int ");

	for(i=35;i<Llength-1;i++)
	{
		buf=STHead[i].symbol;
		code=code+buf;
		code=code+_T(", ");
	}
	buf=STHead[i].symbol;
	code=code+buf+_T(";\r\n");

	TNodeStack = new ASTList[THight+30];
	Sta =new int[THight+30];
	for(i=0;i<THight+10;i++)
	{
		Sta[i]=0;
	}
	TTop=0;
	TNodeStack[TTop]=Head;
	p=Head;
	while(TTop>=0)
	{
		p=TNodeStack[TTop];
		if(p==NULL)
		{
			TTop--;
			Sta[TTop]++;
			continue;
		}
		if(p->operator_code==0)
		{
			if(Sta[TTop]==0)
			{
				i=p->word->code;
				j=p->word->value;
				if(i==18)
				{
					buf.Format(_T("%d"),j);
					code=code+buf;
				}
				else
				{
					buf=STHead[j].symbol;
					code=code+buf;
				}

			}
		}
		else if(p->operator_code==2)
		{
			if(Sta[TTop]==0)
			{
				for(v=0;v<Ti;v++)
					code=code+_T("\t");
				code=code+_T("if(");
			}
			else if(Sta[TTop]==1)
			{
				code=code+_T(")")+_T(" \r\n");
				for(v=0;v<Ti;v++)
					code=code+_T("\t");
				code=code+_T("{")+_T(" \r\n");
				Ti++;
			}
			else if(Sta[TTop]==2)
			{
				Ti--;
				for(v=0;v<Ti;v++)
					code=code+_T("\t");
				code=code+_T("}\r\n");
			}
		}
		else if(p->operator_code==3)
		{
			if(Sta[TTop]==0)
			{
				for(v=0;v<Ti;v++)
					code=code+_T("\t");
				code=code+_T("if(");
			}
			else if(Sta[TTop]==1)
			{
				for(v=0;v<Ti;v++)
					code=code+_T("\t");
				code=code+_T(")")+_T(" \r\n");
				for(v=0;v<Ti;v++)
					code=code+_T("\t");
				code=code+_T("{")+_T(" \r\n");
				Ti++;
			}
			else if(Sta[TTop]==2)
			{
				Ti--;
				for(v=0;v<Ti;v++)
					code=code+_T("\t");
				code=code+_T("}\r\n");
				for(v=0;v<Ti;v++)
					code=code+_T("\t");
				code+=_T("else\r\n");
				for(v=0;v<Ti;v++)
					code=code+_T("\t");
				code+=_T("{\r\n");
				Ti++;
			}
			else if(Sta[TTop]==3)
			{
				Ti--;
				for(v=0;v<Ti;v++)
					code=code+_T("\t");
				code=code+_T("}\r\n");
			}
		}
		else if(p->operator_code==4)
		{
			if(Sta[TTop]==0)
			{
				for(v=0;v<Ti;v++)
					code=code+_T("\t");
				code=code+_T("do")+_T("\r\n");
				for(v=0;v<Ti;v++)
					code=code+_T("\t");
				code=code+_T("{")+_T("\r\n");
				Ti++;
			}
			else if(Sta[TTop]==1)
			{
				Ti--;
				for(v=0;v<Ti;v++)
					code=code+_T("\t");
				code=code+_T("}")+_T("\r\n");
				for(v=0;v<Ti;v++)
					code=code+_T("\t");
				code=code+_T("while(!(");
			}
			else if(Sta[TTop]==2)
				code=code+_T("));")+_T("\r\n");
		}
		else if(p->operator_code==5)
		{
			if(Sta[TTop]==0)
			{
				for(v=0;v<Ti;v++)
					code=code+_T("\t");
				i=p->word->value;
				buf=STHead[i].symbol;
				code=code+buf+_T("=");
			}
			else if(Sta[TTop]==1)
			{
				code=code+_T(";\r\n");
			}
		}
		else if(p->operator_code==6)
		{
			if(Sta[TTop]==0)
			{
				for(v=0;v<Ti;v++)
					code=code+_T("\t");
				i=p->word->value;
				code=code+_T("cin>>");
				buf=STHead[i].symbol;
				code=code+buf+_T(";\r\n");
			}
		}
		else if(p->operator_code==7)
		{
			if(Sta[TTop]==0)
			{
				i=p->word->value;
				if((p->child1->operator_code)!=0)
				{
					for(v=0;v<Ti;v++)
						code=code+_T("\t");
					code=code+_T("cout<<(");
				}
				else
				{
					for(v=0;v<Ti;v++)
						code=code+_T("\t");
					code=code+_T("cout<<");
				}
			}
			else if(Sta[TTop]==1)
			{
				i=p->word->value;
				if((p->child1->operator_code)!=0)
				{
					code=code+_T(");")+_T("\r\n");
				}
				else
					code=code+_T(";")+_T("\r\n");
			}
		}
		else if(p->operator_code!=1)
		{
			i=p->operator_code;
			j=p->child1->operator_code;
			k=p->child2->operator_code;
			l=(i+1)/2;
			m=(j+1)/2;
			n=(k+1)/2;
			if(Sta[TTop]==0&&(l>m)&&(j!=0))
			{
					code=code+_T("(");
			}
			else if(Sta[TTop]==1)
			{
				if((l>m)&&(j!=0))
					code=code+_T(")");
				switch(i)
				{
				case 8:
					code=code+_T("<");
					break;
				case 9:
					code=code+_T("==");
					break;
				case 10:
					code=code+_T("+");
					break;
				case 11:
					code=code+_T("-");
					break;
				case 12:
					code=code+_T("*");
					break;;
				case 13:
					code=code+_T("/");
					break;
				}
				if((l>=n)&&(k!=0))
					code=code+_T("(");

			}
			else if((Sta[TTop]==2)&&(l>=n)&&(k!=0))
			{
				code=code+_T("(");
			}
		}
		if(Sta[TTop]==0)
		{
			TTop++;
			TNodeStack[TTop]=p->child1;
			Sta[TTop]=0;
		}
		else if(Sta[TTop]==1)
		{
			TTop++;
			TNodeStack[TTop]=p->child2;
			Sta[TTop]=0;
		}
		else if(Sta[TTop]==2)
		{
			TTop++;
			TNodeStack[TTop]=p->child3;
			Sta[TTop]=0;
		}
		else if(Sta[TTop]==3)
		{
			Sta[TTop]=0;
			TTop--;
			Sta[TTop]++;
		}

	}
	code=code+_T("\r\n")+_T("}");
	ObjectCode = code;
}

CString ObjectCodeGenerator::GetOutput()
{
	return ObjectCode;
}