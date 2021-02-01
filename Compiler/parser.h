typedef struct Node
{
	int type;
	union {
                struct NumberNode {
                	char *number;
                };

                struct UnaryOpNode
                {
                	int unary_operator;
                	struct Node *unary_operand;
                };

                struct BinOpNode
                {
                	int binop_operator;
                	struct Node *binop_left;
                	struct Node *binop_right;
                };
	};
} Node;

typedef struct Parser {
        int position;
        Token *tokens;
} Parser;

enum NodeType {
	NUMBER,
	UNARYOP,
	BINOP,
	NAMENODE,
	ASSIGNMENT
};

Parser Parser_ParseTokens(Token *tokens);
