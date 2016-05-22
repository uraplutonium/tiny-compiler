// SyntaxAnalyer.cpp : 实现文件
//

#include "stdafx.h"
#include "SyntaxAnalyzer.h"
#include <fstream>
using namespace std;

void SyntaxAnalyzer::InitProduction()
{
	Production[0] = PRO;
	Production[1] = SQ;
	Production[2] = SQ;
	Production[3] = ST;
	Production[4] = ST;
	Production[5] = ST;
	Production[6] = ST;
	Production[7] = ST;
	Production[8] = IF_ST;
	Production[9] = IF_ST;
	Production[10] = RP_ST;
	Production[11] = AS_ST;
	Production[12] = RD;
	Production[13] = WR;
	Production[14] = EXP;
	Production[15] = EXP;
	Production[16] = EXP;
	Production[17] = SIM_EXP;
	Production[18] = SIM_EXP;
	Production[19] = SIM_EXP;
	Production[20] = TERM;
	Production[21] = TERM;
	Production[22] = TERM;
	Production[23] = FAC;
	Production[24] = FAC;
	Production[25] = FAC;
}

void SyntaxAnalyzer::Push(int state, WordNode *p_Wnode, ASTreeNode *p_tree_node)
{
	StackNode *new_Snode;
	new_Snode = new(StackNode);
	new_Snode->state = state;
	new_Snode->word = p_Wnode;
	new_Snode->p_tree_node = p_tree_node;
	new_Snode->next = stack;
	stack = new_Snode;
}

void SyntaxAnalyzer::Pop()
{
	StackNode *free_node;
	free_node = stack;
	stack = stack->next;
	free(free_node);
}

void SyntaxAnalyzer::Reduce(int nProduction, WordNode *p_Wnode)
{
	ASTreeNode *p_Tnode, *new_Tnode;
	switch(nProduction)
	{
	case 1:
		{
			new_Tnode = new(ASTreeNode);
			new_Tnode->child3 = NULL;
			new_Tnode->child2 = stack->p_tree_node;
			Pop();
			Pop();
			new_Tnode->child1 = stack->p_tree_node;
			Pop();
			new_Tnode->word = NULL;
			new_Tnode->operator_code = SEMICOLON_SYM;
			p_Tnode = new_Tnode;
			break;
		}
	case 8:
		{
			new_Tnode = new(ASTreeNode);
			new_Tnode->child3 = NULL;
			Pop();
			new_Tnode->child2 = stack->p_tree_node;
			Pop();
			Pop();
			new_Tnode->child1 = stack->p_tree_node;
			Pop();
			Pop();
			new_Tnode->word = NULL;
			new_Tnode->operator_code = IF_SYM;
			p_Tnode = new_Tnode;
			break;
		}
	case 9:
		{
			new_Tnode = new(ASTreeNode);
			Pop();
			new_Tnode->child3 = stack->p_tree_node;
			Pop();
			Pop();
			new_Tnode->child2 = stack->p_tree_node;
			Pop();
			Pop();
			new_Tnode->child1 = stack->p_tree_node;
			Pop();
			Pop();
			new_Tnode->word = NULL;
			new_Tnode->operator_code = IF_ELSE_SYM;
			p_Tnode = new_Tnode;
			break;
		}
	case 10:
		{
			new_Tnode = new(ASTreeNode);
			new_Tnode->child3 = NULL;
			new_Tnode->child2 = stack->p_tree_node;
			Pop();
			Pop();
			new_Tnode->child1 = stack->p_tree_node;
			Pop();
			Pop();
			new_Tnode->word = NULL;
			new_Tnode->operator_code = REPEAT_SYM;
			p_Tnode = new_Tnode;
			break;
		}
	case 11:
		{
			new_Tnode = new(ASTreeNode);
			new_Tnode->child3 = NULL;
			new_Tnode->child2 = NULL;
			new_Tnode->child1 = stack->p_tree_node;
			Pop();
			Pop();
			new_Tnode->word = stack->word;
			Pop();
			new_Tnode->operator_code = ASSIGN_SYM;
			p_Tnode = new_Tnode;
			break;
		}
	case 12:
		{
			new_Tnode = new(ASTreeNode);
			new_Tnode->word = stack->word;
			Pop();
			Pop();
			new_Tnode->child3 = NULL;
			new_Tnode->child2 = NULL;
			new_Tnode->child1 = NULL;
			new_Tnode->operator_code = READ_SYM;
			p_Tnode = new_Tnode;
			break;
		}
	case 13:
		{
			new_Tnode = new(ASTreeNode);
			new_Tnode->word = NULL;
			new_Tnode->child3 = NULL;
			new_Tnode->child2 = NULL;
			new_Tnode->child1 = stack->p_tree_node;
			Pop();
			Pop();
			new_Tnode->operator_code = WRITE_SYM;
			p_Tnode = new_Tnode;
			break;
		}
	case 14:
		{
			new_Tnode = new(ASTreeNode);
			new_Tnode->word = NULL;
			new_Tnode->child3 = NULL;
			new_Tnode->child2 = stack->p_tree_node;
			Pop();
			Pop();
			new_Tnode->child1 = stack->p_tree_node;
			Pop();
			new_Tnode->operator_code = LESS_SYM;
			p_Tnode = new_Tnode;
			break;
		}
	case 15:
		{
			new_Tnode = new(ASTreeNode);
			new_Tnode->word = NULL;
			new_Tnode->child3 = NULL;
			new_Tnode->child2 = stack->p_tree_node;
			Pop();
			Pop();
			new_Tnode->child1 = stack->p_tree_node;
			Pop();
			new_Tnode->operator_code = EQUAL_SYM;
			p_Tnode = new_Tnode;
			break;
		}
	case 17:
		{
			new_Tnode = new(ASTreeNode);
			new_Tnode->word = NULL;
			new_Tnode->child3 = NULL;
			new_Tnode->child2 = stack->p_tree_node;
			Pop();
			Pop();
			new_Tnode->child1 = stack->p_tree_node;
			Pop();
			new_Tnode->operator_code = ADD_SYM;
			p_Tnode = new_Tnode;
			break;
		}
	case 18:
		{
			new_Tnode = new(ASTreeNode);
			new_Tnode->word = NULL;
			new_Tnode->child3 = NULL;
			new_Tnode->child2 = stack->p_tree_node;
			Pop();
			Pop();
			new_Tnode->child1 = stack->p_tree_node;
			Pop();
			new_Tnode->operator_code = SUBTRACT_SYM;
			p_Tnode = new_Tnode;
			break;
		}
	case 20:
		{
			new_Tnode = new(ASTreeNode);
			new_Tnode->word = NULL;
			new_Tnode->child3 = NULL;
			new_Tnode->child2 = stack->p_tree_node;
			Pop();
			Pop();
			new_Tnode->child1 = stack->p_tree_node;
			Pop();
			new_Tnode->operator_code = MULTIPLAY_SYM;
			p_Tnode = new_Tnode;
			break;
		}
	case 21:
		{
			new_Tnode = new(ASTreeNode);
			new_Tnode->word = NULL;
			new_Tnode->child3 = NULL;
			new_Tnode->child2 = stack->p_tree_node;
			Pop();
			Pop();
			new_Tnode->child1 = stack->p_tree_node;
			Pop();
			new_Tnode->operator_code = DIVIDE_SYM;
			p_Tnode = new_Tnode;
			break;
		}
	case 23:
		{
			Pop();
			p_Tnode = stack->p_tree_node;
			Pop();
			Pop();
			break;
		}
	case 24:
		{
			new_Tnode = new(ASTreeNode);
			new_Tnode->word = stack->word;
			Pop();
			new_Tnode->child1 = NULL;
			new_Tnode->child2 = NULL;
			new_Tnode->child3 = NULL;
			new_Tnode->operator_code = NULL_SYM;
			p_Tnode = new_Tnode;
			break;
		}
	case 25:
		{
			new_Tnode = new(ASTreeNode);
			new_Tnode->word = stack->word;
			Pop();
			new_Tnode->child1 = NULL;
			new_Tnode->child2 = NULL;
			new_Tnode->child3 = NULL;
			new_Tnode->operator_code = NULL_SYM;
			p_Tnode = new_Tnode;
			break;
		}
	default:
		{
			p_Tnode = stack->p_tree_node;
			Pop();
			break;
		}
	}
	as_tree->child1 = p_Tnode;
	Push(Goto[stack->state][Production[nProduction]], p_Wnode, p_Tnode);
}

void SyntaxAnalyzer::Initialize(CString ActionFileName, CString GotoFileName, WordList *p_word_list, ASTree *p_as_tree)
{
	ifstream *action_file, *goto_file;
	int i, j, buf;
	stack = new(StackNode);
	stack->state = 0;
	stack->word = new(WordNode);
	stack->word->code = SIGN_OFF;
	stack->word->value = SIGN_OFF;
	stack->word->linage = 0;
	stack->word->next = NULL;
	stack->next = NULL;
	stack->p_tree_node = NULL;
	action_file = new(ifstream);
	action_file->open(ActionFileName, ios::in);
	for(i = 0 ; i < 49 ; i++)
		for(j = 0 ; j < 21 ; j++)
		{
			*action_file >>buf;
			Action[i][j] = buf;
		}
	action_file->close();
	free(action_file);
	goto_file = new(ifstream);
	goto_file->open(GotoFileName, ios::in);
	for(i = 0 ; i < 49 ; i++)
		for(j = 0 ; j < 33 ; j++)
		{
			*goto_file >>buf;
			Goto[i][j] = buf;
		}
	goto_file->close();
	free(goto_file);
	word_list = p_word_list;
	as_tree = p_as_tree;
}

int SyntaxAnalyzer::SyntaxAnalyze()
{
	WordNode *p_Wnode;
	int num_goto, num_production;
	p_Wnode = word_list->next;
	bool end;
	InitProduction();
	end = false;
	while(end == false)
	{
		switch(Action[stack->state][p_Wnode->code])
		{
		case S:
			{
				num_goto = Goto[stack->state][p_Wnode->code];
				if(num_goto == 0)
					return p_Wnode->linage;
				Push(num_goto, p_Wnode, NULL);
				p_Wnode = p_Wnode->next;
				break;
			}
		case R:
			{
				num_production = Goto[stack->state][p_Wnode->code];
				Reduce(num_production, p_Wnode);
				break;
			}
		case ACC:
			{
				end = true;
				break;
			}
		case ERROR:
				return p_Wnode->linage;
		}
	}
	return 0;
}