// Talbe.h : 头文件
//

#pragma once
typedef unsigned char Code;	// Code类型定义

// 终结符与非终结符编码 0至34
#define IF 0
#define THEN 1
#define ELSE 2
#define END 3
#define REPEAT 4
#define UNTIL 5
#define READ 6
#define WRITE 7

#define SEMICOLON 8
#define ASSIGN 9
#define LESS 10
#define EQUAL 11
#define ADD 12
#define SUBTRACT 13
#define MULTIPLY 14
#define DIVIDE 15
#define BRACKET_L 16
#define BRACKET_R 17

#define INTEGER 18
#define INDENTIFIER 19
#define SIGN_OFF 20

#define PRO 21
#define SQ 22
#define ST 23
#define IF_ST 24
#define RP_ST 25
#define AS_ST 26
#define RD 27
#define WR 28
#define EXP 29
#define SIM_EXP 30
#define TERM 31
#define FAC 32

#define CURLY_BRACKET_L 33
#define CURLY_BRACKET_R 34

// 运算符号编码 0至15
#define NULL_SYM 0
#define SEMICOLON_SYM 1
#define IF_SYM 2
#define IF_ELSE_SYM 3
#define REPEAT_SYM 4
#define ASSIGN_SYM 5
#define READ_SYM 6
#define WRITE_SYM 7
#define LESS_SYM 8
#define EQUAL_SYM 9
#define ADD_SYM 10
#define SUBTRACT_SYM 11
#define MULTIPLAY_SYM 12
#define DIVIDE_SYM 13
#define JZ_SYM 14
#define JMP_SYM 15

// 符号表
struct SymbolTable
{
	char *symbol;	// 存储符号内容的字符指针，在初始化符号表时开辟内存空间
};

// 单词表结点
struct WordNode
{
	Code code;	// 终结符的编码，即为保留字编码或标识符或数字
	int linage;	// 该终结符所在行数
	int value;	// 值，保留字为0，标识符为符号表中的位置，数字为其数值
	WordNode *next;
};
typedef WordNode WordList;

// 抽象语法树结点 AbstractSyntaxTreeNode
struct ASTreeNode
{
	WordNode *word;
	Code operator_code;
	ASTreeNode *child1;
	ASTreeNode *child2;
	ASTreeNode *child3;
	HTREEITEM node;
};
typedef ASTreeNode ASTree;
typedef ASTreeNode *ASTList;

