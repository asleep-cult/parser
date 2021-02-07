import compiler


class Transpiler:
    def __init__(self, code, out='out.asm'):
        self.code = code
        self.out = open(out, 'w')
        self.indentation = 0
        self.position = -1

    def getb(self):
        self.position += 1
        return self.code.buffer[self.position]

    def write(self, data):
        self.out.write('\t' * self.indentation)
        self.out.write(data)
        self.out.write('\n')

    def pop(self, reg):
        self.write('pop %s' % reg)

    def push(self, value):
        self.write('push %s' % value)

    def push_literal(self):
        index = self.getb()
        value = self.code.literals[index]
        self.push(value)

    def add(self):
        self.pop('rax')
        self.pop('rcx')
        self.write('add rax, rcx')
        self.push('rax')

    def multiply(self):
        self.pop('rax')
        self.pop('rcx')
        self.write('mul rax, rcx')
        self.push('rax')

    def transpile(self):
        while True:
            try:
                b = self.getb()
            except IndexError:
                break
            if b == compiler.Opcode.GET_INTEGER:
                self.push_literal()
            elif b == compiler.Opcode.ADD:
                self.add()
            elif b == compiler.Opcode.MULTIPLY:
                self.multiply()
        self.out.close()
