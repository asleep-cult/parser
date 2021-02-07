import tokenizer
import tparser
import compiler
import transpiler


def dis(c):
    literals = c.literals
    i = iter(c.buffer)
    for op in i:
        if op == compiler.Opcode.ADD:
            print('ADD (2)')
        elif op == compiler.Opcode.SUBTRACT:
            print('SUBTRACT (2)')
        elif op == compiler.Opcode.DIVIDE:
            print('DIVIDE (2)')
        elif op == compiler.Opcode.MULTIPLY:
            print('MULTIPLY (2)')
        elif op == compiler.Opcode.POSITIVE:
            print('POSITIVE (1)')
        elif op == compiler.Opcode.NEGATIVE:
            print('NEGATIVE (1)')
        elif op == compiler.Opcode.GET_INTEGER:
            x = next(i)
            print('PUSH INTEGER %s' % literals[x])
        elif op == compiler.Opcode.GET_FLOAT:
            x = next(i)
            print('PUSH FLOAT %s' % literals[x])


with open('test.xx') as fp:
    tokenizer = tokenizer.Tokenizer(fp.read(), 'test.xx')
    tokens = tokenizer.parse()
    parser = tparser.Parser(tokens)
    node = parser.parse_expr()
    c = compiler.Code()
    c.visit(node)
    print(c.buffer)
    dis(c)
    t = transpiler.Transpiler(c)
    t.transpile()
