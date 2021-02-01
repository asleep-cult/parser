#include "runtime.h"

void Runtime_Exec(char *file_path)
{
        Lexer lexer = Lexer_ParseFile(file_path);
        Node *node = Parser_ParseTokens(lexer->tokens);
        Code *code = Compile_AST(node);
}
