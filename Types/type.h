typedef struct Type {
        char *name;
        void *(*descr)(void *this);
        void *(*add)(void *this, void *operand);
        void *(*subtract)(void *this, void *operand);
        void *(*multiply)(void *this, void *operand);
        void *(*divide)(void *this, void *operand);
} Type;
