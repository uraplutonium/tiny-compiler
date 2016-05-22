// LexicalAnalyzer.cpp : 实现文件
//

#include "stdafx.h"
#include "LexicalAnalyzer.h"
#pragma warning(disable: 4996)

bool LexicalAnalyzer::isLetter(char ch)
{
	bool ret_value;
	if((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		ret_value = true;
	else
		ret_value = false;
	return ret_value;
}

bool LexicalAnalyzer::isDigit(char ch)
{
	bool ret_value;
	if(ch >= '0' && ch <= '9')
		ret_value = true;
	else
		ret_value = false;
	return ret_value;
}

Code LexicalAnalyzer::isReserved(char ch[])
{
	Code code_reserved;
	if(strcmp(ch, "if") == 0)
		code_reserved = IF;
	else if(strcmp(ch, "then") == 0)
		code_reserved = THEN;
	else if(strcmp(ch, "else") == 0)
		code_reserved = ELSE;
	else if(strcmp(ch, "end") == 0)
		code_reserved = END;
	else if(strcmp(ch, "repeat") == 0)
		code_reserved = REPEAT;
	else if(strcmp(ch, "until") == 0)
		code_reserved = UNTIL;
	else if(strcmp(ch, "read") == 0)
		code_reserved = READ;
	else if(strcmp(ch, "write") == 0)
		code_reserved = WRITE;
	else
		code_reserved = WRITE+1;
	return code_reserved;
}

int LexicalAnalyzer::GetNum(char ch[])
{
	int num, i;
	for(i = 0, num = 0 ; ch[i] != '\0' ; i++)
		num = num*10+(ch[i] - '0');
	return num;
}

void LexicalAnalyzer::InsertWordNode(Code code, int linage, int value)
{
	WordNode *p_Wnode, *new_Wnode;
	for(p_Wnode = word_list ; p_Wnode->next != NULL ; )
		p_Wnode = p_Wnode->next;
	new_Wnode = new(WordNode);
	new_Wnode->code = code;
	new_Wnode->linage = linage;
	new_Wnode->value = value;
	new_Wnode->next = NULL;
	p_Wnode->next = new_Wnode;
}

void LexicalAnalyzer::BuildSymbolTable()
{
	int len_symbol_list, i, j;
	SymbolNode *p_node;
	for(p_node = symbol_list, len_symbol_list = 0 ; p_node->next != NULL ; p_node = p_node->next)
		len_symbol_list++;

	*symbol_table = new SymbolTable[len_symbol_list + CURLY_BRACKET_R + 1];
	*Llength=len_symbol_list + CURLY_BRACKET_R + 1;

	(*symbol_table)[0].symbol = new char[3];
	(*symbol_table)[1].symbol = new char[5];
	(*symbol_table)[2].symbol = new char[5];
	(*symbol_table)[3].symbol = new char[4];
	(*symbol_table)[4].symbol = new char[7];
	(*symbol_table)[5].symbol = new char[6];
	(*symbol_table)[6].symbol = new char[5];
	(*symbol_table)[7].symbol = new char[6];
	for(i = 8 ; i < 18 ; i++)
	{
		if(i != 9)
			(*symbol_table)[i].symbol = new char[2];
		else			
			(*symbol_table)[17].symbol = new char[3];
	}	
	(*symbol_table)[18].symbol = NULL;
	(*symbol_table)[19].symbol = NULL;
	for(i = 21 ; i < 33 ; i++)
		(*symbol_table)[i].symbol = NULL;
	(*symbol_table)[20].symbol = new char[2];
	(*symbol_table)[33].symbol = new char[2];
	(*symbol_table)[34].symbol = new char[2];

	(*symbol_table)[0].symbol = "if";
	(*symbol_table)[1].symbol = "then";
	(*symbol_table)[2].symbol = "else";
	(*symbol_table)[3].symbol = "end";
	(*symbol_table)[4].symbol = "repeat";
	(*symbol_table)[5].symbol = "until";
	(*symbol_table)[6].symbol = "read";
	(*symbol_table)[7].symbol = "write";
	(*symbol_table)[8].symbol = ";";
	(*symbol_table)[9].symbol = ":=";
	(*symbol_table)[10].symbol = "<";
	(*symbol_table)[11].symbol = "=";
	(*symbol_table)[12].symbol = "+";
	(*symbol_table)[13].symbol = "-";
	(*symbol_table)[14].symbol = "*";
	(*symbol_table)[15].symbol = "/";
	(*symbol_table)[16].symbol = "(";
	(*symbol_table)[17].symbol = ")";
	(*symbol_table)[20].symbol = "#";
	(*symbol_table)[33].symbol = "{";
	(*symbol_table)[34].symbol = "}";	
	for(p_node = symbol_list->next, i = CURLY_BRACKET_R ; p_node != NULL ; p_node = p_node->next)
	{
		i++;
		for(j = 0 ; p_node->symbol[j] != '\0' ; )
			j++;
		(*symbol_table)[i].symbol = new char[j+1];
		for(j = 0 ; p_node->symbol[j] != '\0' ; j++)
			(*symbol_table)[i].symbol[j] = p_node->symbol[j];
		(*symbol_table)[i].symbol[j] = '\0';
	}
}

void LexicalAnalyzer::Initialize(CString str_input, SymbolTable **p_symbol_table, WordList *p_word_list, int *p_length_list)
{
	USES_CONVERSION;
	length = str_input.GetLength();
	input = new char[length];
	LPTSTR Lstr = str_input.GetBuffer();
	const char* p_buf = T2A(Lstr);
	strcpy(input, p_buf);
	symbol_table = p_symbol_table;
	word_list = p_word_list;
	Llength = p_length_list;
}

int LexicalAnalyzer::LexicalAnalyze()
{
	int i, j, linage, n_start, n_end;
	char *symbol_buf;
	linage = 1;
	for(i = 0 ; i < length ; i++)
	{
		if(input[i] == '\n')
			linage++;
		while(input[i] == ' ' || input[i] == '\r' || input[i] == '\n' || input[i] == '\t')
		{
			i++;
			if(input[i] == '\n')
				linage++;
		}
		if(isLetter(input[i]) == true)
		{
			SymbolNode *p_Snode, *new_Snode;
			int location;
			Code CodeReserved;
			n_start = i;
			while(i < length && isLetter(input[i]))
			{
				n_end = i;
				i++;
				if(input[i] == '\n')
					linage++;
			}
			i--;
			symbol_buf = new char[n_end-n_start+2];
			for(j = n_start ; j <= n_end ; j++)
				symbol_buf[j-n_start] = input[j];
			symbol_buf[n_end-n_start+1] = '\0';
			CodeReserved = isReserved(symbol_buf);

			if(CodeReserved > WRITE)
			{
				bool exist;
				for(p_Snode = symbol_list, location = 0 , exist = false; p_Snode->next != NULL ; p_Snode = p_Snode->next)
				{
					location++;
					if(strcmp(p_Snode->next->symbol, symbol_buf) == 0)
					{
						exist = true;
						break;
					}
				}
				if(exist == false)
				{
					new_Snode = new(SymbolNode);
					new_Snode->symbol = new char[n_end-n_start+2];
					for(j = 0 ; j < n_end-n_start+1 ; j++)
						new_Snode->symbol[j] = symbol_buf[j];
					new_Snode->symbol[n_end-n_start+1] = '\0';
					new_Snode->next = NULL;
					p_Snode->next = new_Snode;
					location++;
				}
				InsertWordNode(INDENTIFIER, linage, CURLY_BRACKET_R+location);
				free(symbol_buf);
				n_start = 0;
				n_end = 0;
			}
			else
			{
				InsertWordNode(CodeReserved, linage, CodeReserved);
				free(symbol_buf);
			}
		}
		else if(isDigit(input[i]) == true)
		{
			n_start = i;
			while(i < length && isDigit(input[i]))
			{
				n_end = i;
				i++;
			}
			i--;
			symbol_buf = new char[n_end-n_start+2];
			for(j = n_start ; j <= n_end ; j++)
				symbol_buf[j-n_start] = input[j];
			symbol_buf[n_end-n_start+1] = '\0';
			InsertWordNode(INTEGER, linage, GetNum(symbol_buf));
			free(symbol_buf);
			n_start = 0;
			n_end = 0;
		}
		else if(input[i] == '+')
			InsertWordNode(ADD, linage, ADD);
		else if(input[i] == '-')
			InsertWordNode(SUBTRACT, linage, SUBTRACT);
		else if(input[i] == '*')
			InsertWordNode(MULTIPLY, linage, MULTIPLY);
		else if(input[i] == '/')
			InsertWordNode(DIVIDE, linage, DIVIDE);
		else if(input[i] == '=')
			InsertWordNode(EQUAL, linage, EQUAL);
		else if(input[i] == '<')
			InsertWordNode(LESS, linage, LESS);
		else if(input[i] == '(')
			InsertWordNode(BRACKET_L, linage, BRACKET_L);
		else if(input[i] == ')')
			InsertWordNode(BRACKET_R, linage, BRACKET_R);
		else if(input[i] == ';')
			InsertWordNode(SEMICOLON, linage, SEMICOLON);
		else if(input[i] == ':')
		{
			i++;
			if(input[i] == '=')
				InsertWordNode(ASSIGN, linage, ASSIGN);
			else
				return linage;
		}
		else if(input[i] == '{')
		{
			int flag;
			int num;
			flag = 0;
			num = linage;
			i++;
			while(i < length && flag != 1)
			{
				if(input[i] == '}')
					flag = 1;
				else if(input[i] == '{')
					return num;
				else
				{
					flag = 2;
					if(input[i] == '\n')
					{
						linage++;
						i++;
					}
					else
						i++;
				}
			}
		}
		else if(input[i] == '}')
			return linage;
		else
			return linage;
	}
	InsertWordNode(SIGN_OFF, linage+1, SIGN_OFF);
	BuildSymbolTable();
	return 0;
}