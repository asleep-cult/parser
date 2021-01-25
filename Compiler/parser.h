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

                /*
                typedef struct NameNode
                {
                	char *name_type;
                	char *name;
                } NameNode;

                typedef struct AssignmentNode
                {
                	Node *assignment_name;
                	Node *assignment_value;
                } AssignmentNode;
                */
	};
} Node;

typedef struct Parser {
        int position;
        int node_size;
        Token *tokens;
} Parser;

enum NodeType {
	NUMBER,
	UNARYOP,
	BINOP,
	NAMENODE,
	ASSIGNMENT
};
