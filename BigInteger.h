#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 struct Node {
    int data;
    struct Node *next;
};
struct BigInteger{
    struct Node *L;
    int length;
    int sign;
};
struct Node *createNode(int data );
void display(struct BigInteger a);
struct BigInteger initialize(char *s);
int compare(struct BigInteger a,struct  BigInteger b );
struct BigInteger add(struct BigInteger a, struct BigInteger b);
struct BigInteger sub(struct BigInteger a , struct BigInteger b);
struct BigInteger mul(struct BigInteger a , struct BigInteger b);
struct BigInteger div1(struct BigInteger a,struct BigInteger b);
struct BigInteger mod(struct BigInteger a ,struct BigInteger b);