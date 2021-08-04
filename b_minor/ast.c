/*
declaration:
b: boolean;
s: string = "Hello";
f: function integer(x: integer) = {return x*x};
*/
struct decl{
    char* name;
    struct type* type;
    struct expr* value;
    struct stmt* code;
    struct decl* next;
};