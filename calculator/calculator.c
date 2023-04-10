#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100
int err;

typedef char element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

void init_stack(StackType *s) {
	s->top = -1;
}

int is_empty(StackType *s) {
	return (s->top == -1);
}

int is_full(StackType *s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType *s, element item) {
	if (is_full(s)) {
		printf(stderr, "stack full\n");
	}
	else 
		s->data[++(s->top)] = item;
}

element pop(StackType *s) {
	if (is_empty(s)) {
		printf(stderr, "stack empty\n");
		exit(1);
	}
	else 
		return s->data[(s->top)--];
}

void check_error(char exp[]) {
	err = -1;
	int len = strlen(exp);

	// 문자 입력 오류
	for (int i = 0; i < len; i++) {
		if (exp[i] != '+' && exp[i] != '-' && exp[i] != '*' && exp[i] != '/') {
			if (!isdigit(exp[i])) {
				printf("Error: Invalid character\n");
				err = 1;
				return err;
			}
		}
	}
}

int eval(char exp[]) {

	int op1, op2, value, i;
	int len = strlen(exp);
	char ch;
	StackType s;

	init_stack(&s);

	for (i = 0; i < len; i++) {
		ch = exp[i];
		if (ch == ' ')
			value = 0; 
			
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
			value = ch - '0';
			push(&s, value);
		}
		else {
			op2 = pop(&s);
			op1 = pop(&s);
			switch (ch) {
			case '+': push(&s, op1 + op2); break;
			case '-': push(&s, op1 - op2); break;
			case '*': push(&s, op1 * op2); break;
			case '/': push(&s, op1 / op2); break;
			}
		}
	}
	return pop(&s);
}

int main(){
	char postfix[MAX_STACK_SIZE];
	int result;

	printf("Enter an postfix expression: ");
	scanf("%[^\n]s\n", postfix);

	check_error(postfix);

	if (err == -1) {
	result = eval(postfix);
	printf("Result: %d\n", result);
	}

	return 0;
}