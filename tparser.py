from tokenizer import TokenType


class IntegerNode:
    def __init__(self, value=None):
        self.value = value

    def __repr__(self):
        return '(IntegerNode(%r))' % self.value


class FloatNode:
    def __init__(self, value=None):
        self.value = None

    def __repr__(self):
        return '(FloatNode(%r))' % self.value


class UnaryOperationNode:
    def __init__(self, operator=None, operand=None):
        self.operator = operator
        self.operand = operand

    def __repr__(self):
        return '(UnaryOperationNode(%r, %r))' % (
            self.operator,
            self.operand
        )


class BinaryOperationNode:
    def __init__(self, left=None, operator=None, right=None):
        self.left = left
        self.operator = operator
        self.right = right

    def __repr__(self):
        return '(BinaryOperationNode(%r, %r, %r))' % (
            self.left,
            self.operator,
            self.right
        )


class TypedNameNode:
    def __init__(self, name=None, name_type=None):
        self.name = name
        self.name_type = name_type


class AssignmentNode(TypedNameNode):
    def __init__(self, name=None, name_type=None, value=None):
        super().__init__(name, name_type)
        self.value = value


class Parser:
    def __init__(self, tokens):
        self.tokens = tokens
        self.position = -1

    def gett(self):
        self.position += 1
        return self.tokens[self.position]

    def parse_integer(self):
        token = self.gett()
        if token.type == TokenType.INTEGER:
            return IntegerNode(token.value)

    def parse_float(self):
        token = self.gett()
        if token.type == TokenType.FLOAT:
            return FloatNode(token.value)

    def parse_number(self):
        number = self.parse_float()
        if number is None:
            self.position -= 1
            number = self.parse_integer()
            if number is None:
                self.position -= 1
        return number

    def parse_factor(self):
        number = self.parse_number()
        if number is not None:
            return number

        token = self.gett()
        root = node = UnaryOperationNode(token.type)
        while True:
            token = self.gett()
            if token.type in (TokenType.PLUS, TokenType.MINUS):
                new_node = UnaryOperationNode(token.type)
                node.operand = new_node
                node = new_node
            else:
                self.position -= 1
                node.operand = self.parse_number()
                return root

    def parse_term(self):
        left = self.parse_factor()

        while True:
            token = self.gett()
            if token.type in (TokenType.FSLASH, TokenType.STAR):
                right = self.parse_factor()
                left = BinaryOperationNode(left, token.type, right)
            else:
                self.position -= 1
                return left

    def parse_expr(self):
        left = self.parse_term()

        while True:
            token = self.gett()
            if token.type in (TokenType.PLUS, TokenType.MINUS):
                right = self.parse_term()
                left = BinaryOperationNode(left, token.type, right)
            else:
                self.position -= 1
                return left
