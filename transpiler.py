import compiler


def isnumeric(string):
    if string.isnumeric():
        return True
    try:
        float(string)
    except ValueError:
        return False
    return True


class Transpiler:
    def __init__(self, code, out='out.asm'):
        self.code = code
        self.out = open(out, 'w')
        self.indentation = 0
        self.position = -1
        self.stack = []

    def getb(self):
        self.position += 1
        return self.code.buffer[self.position]

    def write(self, data):
        self.out.write('\t' * self.indentation)
        self.out.write(data)
        self.out.write('\n')

    def get_literal(self):
        literal = self.code.literals[self.getb()]
        self.stack.append(literal)

    def get_literal_reg(self, reg):
        self.get_literal()
        literal = self.stack.pop()
        self.write(f'mov {reg}, {literal}')
        self.stack.append(reg)

    def add(self):
        right = self.stack.pop()
        left = self.stack.pop()
        if isnumeric(left) and isnumeric(right):
            left = float(left) + float(right)
        else:
            self.write(f'add {left}, {right}')
        self.stack.append(str(left))

    def subtract(self):
        right = self.stack.pop()
        left = self.stack.pop()
        if isnumeric(left) and isnumeric(right):
            left = float(left) - float(right)
        else:
            self.write(f'add {left}, {right}')
        self.stack.append(str(left))

    def multiply(self):
        right = self.stack.pop()
        left = self.stack.pop()
        if isnumeric(left) and isnumeric(right):
            left = float(left) * float(right)
        else:
            self.write(f'mul {left}, {right}')
        self.stack.append(str(left))

    def divide(self):
        right = self.stack.pop()
        left = self.stack.pop()
        if isnumeric(left) and isnumeric(right):
            left = float(left) / float(right)
        else:
            self.write(f'div {left}, {right}')
        self.stack.append(str(left))

    def transpile_arg(self):
        b = self.getb()
        if b == compiler.Opcode.GET_INTEGER:
            self.get_literal()
        elif b == compiler.Opcode.ADD:
            self.add()
        elif b == compiler.Opcode.SUBTRACT:
            self.subtract()
        elif b == compiler.Opcode.MULTIPLY:
            self.multiply()
        elif b == compiler.Opcode.DIVIDE:
            self.divide()

    def transpile(self):
        while True:
            try:
                self.transpile_arg()
            except IndexError:
                break
        self.out.close()
        print(self.stack)  # nice :)
