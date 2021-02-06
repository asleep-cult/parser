import enum
import functools


class TokenType(enum.Enum):
    PLUS = '+'
    MINUS = '-'
    STAR = '*'
    FSLASH = '/'
    PERCENT = '%'
    EQUAL = '='
    CARET = '^'
    EXCLAMATION = '!'
    QUESTION_MARK = '?'
    TILDE = '~'
    GREATER_THAN = '>'
    LESS_THAN = '<'
    VLINE = '|'
    AMPERSAND = '&'
    DOT = '.'
    COMMA = ','
    LPAREN = '('
    RPAREN = ')'
    LBRACE = '{'
    RBRACE = '}'
    LBRACKET = '['
    RBRACKET = ']'
    AT = '@'
    SEMICOLON = ';'
    INTEGER = 'INTEGER'
    FLOAT = 'FLOAT'
    STRING = 'STRING'

    @classmethod
    @functools.lru_cache
    def get_token(cls, value):
        for token in cls.__members__.values():
            if token.value == value:
                return token


class Token:
    def __init__(self, token_type, value=None):
        self.type = token_type
        self.value = value

    def __repr__(self):
        return 'Token(type=%s, value=%r)' % (self.type, self.value)


class TokenizerFailure(Exception):
    def __init__(self, message):
        self.message = message


class Tokenizer:
    def __init__(self, source, name='<string>'):
        self.source = source
        self.name = name
        self.position = -1
        self.lineno = 1
        self.eof = False

    def getc(self):
        self.position += 1
        try:
            c = self.source[self.position]
            if c == '\n':
                self.lineno += 1
        except IndexError:
            raise EOFError
        return c

    def backup(self):
        self.position -= 1

    def expect(self, c):
        try:
            nc = self.getc()
        except EOFError:
            self.backup()
            nc = None
        if nc != c:
            raise TokenizerFailure('Expected %r' % c)
        return nc

    def parse_string(self, terminator):
        token = Token(TokenType.STRING, '')

        c = self.getc()
        while c != terminator:
            token.value += c
            c = self.getc()

        return token

    def parse_integer(self):
        token = Token(TokenType.INTEGER, '')

        c = self.getc()
        while c.isdigit():
            token.value += c
            try:
                c = self.getc()
            except EOFError:
                break

        if not c.isdigit():
            self.backup()

        return token

    def parse_number(self):
        left = self.parse_integer()
        try:
            self.expect('.')
        except TokenizerFailure:
            self.backup()
            return left

        right = self.parse_integer()
        token = Token(TokenType.FLOAT, '%s.%s' % (left.value, right.value))
        return token

    def parse_once(self):
        try:
            c = self.getc()
        except EOFError:
            self.eof = True
            return

        token_type = TokenType.get_token(c)
        if token_type is not None:
            return Token(token_type, c)
        elif c in ('\n', '\t', ' '):
            return
        elif c.isdigit():
            self.backup()
            return self.parse_number()
        elif c in ('\'', '"'):
            return self.parse_string(c)
        else:
            raise TokenizerFailure('Invalid token %r' % c)

    @property
    def signiature(self):
        return '[Tokenizer <position=%s, lineo=%s>] In file %s:' % (
            self.position,
            self.lineno,
            self.name
        )

    def parse(self):
        tokens = []
        failed = False
        while not self.eof:
            try:
                token = self.parse_once()
                if token is not None:
                    tokens.append(token)
            except EOFError:
                failed = True
                print('%s Input unexpectedly ended' % self.signiature)
            except TokenizerFailure as e:
                failed = True
                print('%s %s' % (self.signiature, e.message))

        if failed:
            exit()

        return tokens
