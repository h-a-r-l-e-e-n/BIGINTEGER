#include"BigInteger.h"
struct Node *createNode(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}
void display(struct BigInteger big_int) {
    struct Node *current = big_int.L;
    struct Node *copy = NULL;

    while (current != NULL) {
        struct Node *newNode = createNode(current->data);
        newNode->next = copy;
        copy = newNode;
        current = current->next;
    }

    current = copy;
if (big_int.sign == -1)
    {
        printf("-");
    }
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }

    while (copy != NULL) {
        struct Node *temp = copy;
        copy = copy->next;
        free(temp);
    }

    printf("\n");
}

struct BigInteger initialize(char *s) {
    struct BigInteger p;
    p.L = NULL;
    p.sign=1;
    int length = strlen(s);
    p.length=length;
    for (int i = 0; i < length; i++) {
        int digit = s[i] - '0'; 
        struct Node *newNode = createNode(digit);

        newNode->next = p.L;
        p.L = newNode;
    }

    struct BigInteger copy = p;
    return p;
}
int compare(struct BigInteger a,struct  BigInteger b)
{
    if (a.length > b.length)
    {
        return 1;  // a is greater
    }
    else if (a.length < b.length)
    {
        return -1; // b is greater
    }
    else
    {
        // Compare digit by digit
        struct Node* i1 = a.L;
        struct Node* i2 = b.L;
        while (i1 && i2)
        {
            if (i1->data > i2->data) return 1;
            if (i1->data < i2->data) return -1;
            i1 = i1->next;
            i2 = i2->next;
        }
        return 0; // They are equal
    }
}
struct BigInteger add(struct BigInteger a, struct BigInteger b) {
    struct Node *head1 = a.L;
    struct Node *head2 = b.L;
    struct BigInteger result;
    result.L = NULL;
    struct Node *temp = NULL;
    int carry = 0;

    while (head1 != NULL || head2 != NULL || carry) {
        int sum = carry;

        if (head1 != NULL) {
            sum += head1->data;
            head1 = head1->next;
        }

        if (head2 != NULL) {
            sum += head2->data;
            head2 = head2->next;
        }

        carry = sum / 10;
        sum %= 10;

        struct Node *newNode = createNode(sum);

        if (result.L == NULL) {
            result.L = newNode;
            temp = result.L;
        } else {
            temp->next = newNode;
            temp = newNode;
        }
    }

    return result;
}

struct BigInteger sub(struct BigInteger a, struct BigInteger b) {

    struct BigInteger result;
    result.L = NULL;
    struct Node *temp = NULL;
    int borrow = 0;

     if(compare(a,b)==0)
    {
        struct BigInteger t;
        t.L=createNode(0);
        t.sign=1;
        return t;
    }
    int sign = 0;
    if (compare(a, b) < 0)
    {
        sign = -1;
        // Swap a and b for proper subtraction
        struct BigInteger temp = a;
        a = b;
        b = temp;
    }
    struct Node *head1 = a.L;
    struct Node *head2 = b.L;

    while (head1 != NULL || head2 != NULL) {
        int num1 = 0, num2 = 0;
        if (head1 != NULL) {
            num1 = head1->data;
        }
        if (head2 != NULL) {
            num2 = head2->data;
        }

        int diff = num1 - num2 - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        struct Node *newNode = createNode(diff);

        if (result.L == NULL) {
            result.L = newNode;
            temp = result.L;
        } else {
            temp->next = newNode;
            temp = newNode;
        }

        if (head1 != NULL) {
            head1 = head1->next;
        }
        if (head2 != NULL) {
            head2 = head2->next;
        }
        if (sign == -1)
    {
        result.sign = -1;
    }
    else
    {
        result.sign = 1;
    }
   
    }
    return result;
}

struct BigInteger mul(struct BigInteger a, struct BigInteger b) {
    struct Node *head1 = a.L;
    struct Node *head2 = b.L;
    struct BigInteger result;
    result.L = NULL;
    struct Node *temp1 = head1;
    int position = 0;

    while (temp1 != NULL) {
        int carry = 0;
        struct Node *temp2 = head2;
        struct BigInteger partialResult;
        partialResult.L = NULL;
        struct Node *partialTemp = NULL;

        for (int i = 0; i < position; i++) {
            struct Node *zero = createNode(0);

            if (partialResult.L == NULL) {
                partialResult.L = zero;
                partialTemp = zero;
            } else {
                partialTemp->next = zero;
                partialTemp = zero;
            }
        }

        while (temp2 != NULL) {
            int product = (temp1->data) * (temp2->data) + carry;
            carry = product / 10;
            product = product % 10;

            struct Node *newNode = createNode(product);

            if (partialResult.L == NULL) {
                partialResult.L = newNode;
                partialTemp = newNode;
            } else {
                partialTemp->next = newNode;
                partialTemp = newNode;
            }

            temp2 = temp2->next;
        }

        if (carry > 0) {
            struct Node *carryNode = createNode(carry);
            partialTemp->next = carryNode;
        }

        result = add(result, partialResult);
        position++;
        temp1 = temp1->next;
    }

    return result;
}
// Function to perform division on BigInteger numbers
struct BigInteger div1(struct BigInteger num1, struct BigInteger num2) {
    struct BigInteger res;
    res.L = NULL;
    res.sign = 1;
    res.length = 0;
    if (num2.L == NULL) {
        printf("Division by zero error\n");
        return res;
    }
    if (num1.L == NULL) {
        return res;
    }
    if (compare(num1, num2) == -1) {
        return res;
    }

    // Perform division of two big integers by repeated subtraction
    struct BigInteger temp = num1;
    while (compare(temp, num2) != -1) {
        temp = sub(temp, num2);
        res = add(res, initialize("1"));
    }
    return res;
}

