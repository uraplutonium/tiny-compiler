// Compiler.cpp : 实现文件
//

#include "stdafx.h"
#include "Compiler.h"

void Compiler::DisplayASTreeNode(ASTreeNode *p_Tnode)
{
	CString name, buf;
	if(p_Tnode->child1 != NULL)
	{
		name = _T("");
		if(p_Tnode->child1->operator_code != NULL_SYM)
		{
			buf = GetOperator(p_Tnode->child1->operator_code);
			name+=buf;
		}
		if(p_Tnode->child1->word != NULL)
		{
			if(p_Tnode->child1->word->code == INTEGER)
				buf.Format(_T("%d"), p_Tnode->child1->word->value);
			else
				buf = symbol_table[p_Tnode->child1->word->value].symbol;
			name = name + _T(" ") + buf;
		}
		p_Tnode->child1->node = p_Tree->InsertItem(name, 0, 0, p_Tnode->node);
		if(p_Tnode->child1->child1 != NULL)
			DisplayASTreeNode(p_Tnode->child1);
	}
	if(p_Tnode->child2 != NULL)
	{
		name = _T("");
		if(p_Tnode->child2->operator_code != NULL_SYM)
		{
			buf = GetOperator(p_Tnode->child2->operator_code);
			name+=buf;
		}
		if(p_Tnode->child2->word != NULL)
		{
			if(p_Tnode->child2->word->code == INTEGER)
				buf.Format(_T("%d"), p_Tnode->child2->word->value);
			else
				buf = symbol_table[p_Tnode->child2->word->value].symbol;
			name = name + _T(" ") + buf;
		}
		p_Tnode->child2->node = p_Tree->InsertItem(name, 0, 0, p_Tnode->node);
		if(p_Tnode->child2->child1 != NULL)
			DisplayASTreeNode(p_Tnode->child2);
	}
	if(p_Tnode->child3 != NULL)
	{
		name = _T("");
		if(p_Tnode->child3->operator_code != NULL_SYM)
		{
			buf = GetOperator(p_Tnode->child3->operator_code);
			name+=buf;
		}
		if(p_Tnode->child3->word != NULL)
		{
			if(p_Tnode->child3->word->code == INTEGER)
				buf.Format(_T("%d"), p_Tnode->child3->word->value);
			else
				buf = symbol_table[p_Tnode->child3->word->value].symbol;
			name = name + _T(" ") + buf;
		}
		p_Tnode->child3->node = p_Tree->InsertItem(name, 0, 0, p_Tnode->node);
		if(p_Tnode->child3->child1 != NULL)
			DisplayASTreeNode(p_Tnode->child3);
	}
}

CString Compiler::GetOperator(Code op_code)
{	
	CString op;
	switch(op_code)
	{
	case SEMICOLON_SYM:
		{
			op = _T(";");
			break;
		}
	case IF_SYM:
		{
			op = _T("if_then_end");
			break;
		}
	case IF_ELSE_SYM:
		{
			op = _T("if_then_else_end");
			break;
		}
	case REPEAT_SYM:
		{
			op = _T("repeat_until");
			break;
		}
	case ASSIGN_SYM:
		{
			op = _T(":=");
			break;
		}
	case READ_SYM:
		{
			op = _T("read");
			break;
		}
	case WRITE_SYM:
		{
			op = _T("write");
			break;
		}
	case LESS_SYM:
		{
			op = _T("<");
			break;
		}
	case EQUAL_SYM:
		{
			op = _T("=");
			break;
		}
	case ADD_SYM:
		{
			op = _T("+");
			break;
		}
	case SUBTRACT_SYM:
		{
			op = _T("-");
			break;
		}
	case MULTIPLAY_SYM:
		{
			op = _T("*");
			break;
		}
	case DIVIDE_SYM:
		{
			op = _T("/");
			break;
		}
	}
	return op;
}

void Compiler::Initialize(CListBox *m_List_Word, CTreeCtrl *m_Tree)
{
	p_List_Word = m_List_Word;
	p_Tree = m_Tree;
	symbol_table = new(SymbolTable);
	word_list = new(WordList);
	word_list->next = NULL;
	abstract_syntax_tree = new(ASTree);
	abstract_syntax_tree->child1 = NULL;
	abstract_syntax_tree->child2 = NULL;
	abstract_syntax_tree->child3 = NULL;
	abstract_syntax_tree->word = NULL;
	ListLength=0;
}

bool Compiler::Compile(CString input)
{
	int error;
	CString str_linage;
	lexical_analyzer.Initialize(input, &symbol_table, word_list, &ListLength);
	error = lexical_analyzer.LexicalAnalyze();
	if(error != 0)
	{
		str_linage.Format(_T("词法分析第%d行出错！"), error);
		AfxMessageBox(str_linage);
		return false;
	}

	syntax_analyzer.Initialize(_T("Tiny.action"), _T("Tiny.goto"), word_list, abstract_syntax_tree);
	error = syntax_analyzer.SyntaxAnalyze();
	if(error != 0)
	{
		str_linage.Format(_T("语法分析第%d行出错！"), error);
		AfxMessageBox(str_linage);
		return false;
	}

	semantic_analyzer.Initialize(abstract_syntax_tree->child1, symbol_table);
	semantic_analyzer.SemanticAnalyze();

	objectcode_generator.Initialize(abstract_syntax_tree->child1, symbol_table, ListLength);
	objectcode_generator.GenerateObjectCode();
	return true;
}

void Compiler::DisplayWordList()
{
	WordNode *p_node;
	CString str_output, str_buf;
	p_List_Word->ResetContent();
	for(p_node = word_list->next ; p_node != NULL ; p_node = p_node->next)
	{
		str_output.Format(_T("第%d行  "), p_node->linage);
		if((p_node->code >= IF && p_node->code <= BRACKET_R) || (p_node->code == INDENTIFIER) || (p_node->code >= CURLY_BRACKET_L && p_node->code <= CURLY_BRACKET_R))
		{
			if(p_node->code <= WRITE && p_node->code >= IF)
				str_buf.Format(_T("保留字   "));
			else if(p_node->code <= BRACKET_R && p_node->code >= SEMICOLON)
				str_buf.Format(_T("操作符   "));
			else
				str_buf.Format(_T("标识符   "));
			str_output+=str_buf;
			str_buf = symbol_table[p_node->value].symbol;
			str_output+=str_buf;
			p_List_Word->AddString(str_output);
		}
		else if(p_node->code == INTEGER)
		{
			str_buf.Format(_T("数字     "));
			str_output+=str_buf;
			str_buf.Format(_T("%d"), p_node->value);
			str_output+=str_buf;
			p_List_Word->AddString(str_output);
		}
	}
}

void Compiler::DisplayASTree()
{
	p_Tree->DeleteAllItems();
	abstract_syntax_tree->node = p_Tree->InsertItem(_T("Program"), 0, 0);
	DisplayASTreeNode(abstract_syntax_tree);
	p_Tree->Expand(abstract_syntax_tree->node, TVE_EXPAND);
}

CString Compiler::GetTernaryFormula()
{
	CString str;
	str = semantic_analyzer.GetOutput();
	return str;
}

CString Compiler::GetCCode()
{
	CString str;
	str = objectcode_generator.GetOutput();
	return str;
}