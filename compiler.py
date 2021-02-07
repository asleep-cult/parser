import tparser
from tokenizer import TokenType


class Opcode:
    ADD = 0
    SUBTRACT = 1
    DIVIDE = 2
    MULTIPLY = 3
    POSITIVE = 4
    NEGATIVE = 5
    GET_FLOAT = 6
    GET_INTEGER = 7


class Code:
    def __init__(self):
        self.buffer = bytearray()
        self.literals = []

    def add_literal(self, value):
        try:
            return self.literals.index(value)
        except ValueError:
            pass

        self.literals.append(value)
        return len(self.literals) - 1

    def visit_float(self, node):
        self.buffer.append(Opcode.GET_FLOAT)
        self.buffer.append(self.add_literal(node.value))

    def visit_integer(self, node):
        self.buffer.append(Opcode.GET_INTEGER)
        self.buffer.append(self.add_literal(node.value))

    def visit_unary_op(self, node):
        self.visit(node.operand)

        operator = node.operator
        if operator == TokenType.PLUS:
            self.buffer.append(Opcode.POSITIVE)
        elif operator == TokenType.MINUS:
            self.buffer.append(Opcode.NEGATIVE)

    def visit_binary_op(self, node):
        self.visit(node.left)
        self.visit(node.right)

        operator = node.operator
        if operator == TokenType.PLUS:
            self.buffer.append(Opcode.ADD)
        elif operator == TokenType.MINUS:
            self.buffer.append(Opcode.SUBTRACT)
        elif operator == TokenType.FSLASH:
            self.buffer.append(Opcode.DIVIDE)
        elif operator == TokenType.STAR:
            self.buffer.append(Opcode.MULTIPLY)

    def visit(self, node):
        if isinstance(node, tparser.FloatNode):
            self.visit_float(node)
        elif isinstance(node, tparser.IntegerNode):
            self.visit_integer(node)
        elif isinstance(node, tparser.UnaryOperationNode):
            self.visit_unary_op(node)
        elif isinstance(node, tparser.BinaryOperationNode):
            self.visit_binary_op(node)
