#include <stdio.h>

#define MAX 10

int n; // number of states
int trans[MAX][2][MAX]; // transitions on a,b
int eps[MAX][MAX];      // epsilon transitions
int final[MAX];         // final states

int new_trans[MAX][2][MAX];
int new_final[MAX];

/* Task 1: Read NFA */
void readNFA() {
    int i, j, k;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter epsilon transitions (1 if exists, 0 if not):\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &eps[i][j]);

    printf("Enter transitions for symbol a:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &trans[i][0][j]);

    printf("Enter transitions for symbol b:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &trans[i][1][j]);

    printf("Enter final states (1 final, 0 not):\n");
    for (i = 0; i < n; i++)
        scanf("%d", &final[i]);
}

/* Task 2: ε-closure */
void epsilonClosure(int state, int closure[]) {
    int stack[MAX], top = 0;
    int i;

    for (i = 0; i < n; i++)
        closure[i] = 0;

    stack[top++] = state;
    closure[state] = 1;

    while (top > 0) {
        int s = stack[--top];
        for (i = 0; i < n; i++) {
            if (eps[s][i] && !closure[i]) {
                closure[i] = 1;
                stack[top++] = i;
            }
        }
    }
}

/* Task 3: New transitions */
void computeNewTransitions() {
    int i, j, k, c;
    int closure[MAX], closure2[MAX];

    for (i = 0; i < n; i++)
        for (c = 0; c < 2; c++)
            for (j = 0; j < n; j++)
                new_trans[i][c][j] = 0;

    for (i = 0; i < n; i++) {
        epsilonClosure(i, closure);

        for (c = 0; c < 2; c++) {
            for (j = 0; j < n; j++) {
                if (closure[j]) {
                    for (k = 0; k < n; k++) {
                        if (trans[j][c][k]) {
                            epsilonClosure(k, closure2);
                            for (int x = 0; x < n; x++)
                                if (closure2[x])
                                    new_trans[i][c][x] = 1;
                        }
                    }
                }
            }
        }
    }
}

/* Task 4: New final states */
void computeNewFinalStates() {
    int i, j;
    int closure[MAX];

    for (i = 0; i < n; i++) {
        new_final[i] = 0;
        epsilonClosure(i, closure);
        for (j = 0; j < n; j++) {
            if (closure[j] && final[j])
                new_final[i] = 1;
        }
    }
}

/* Task 5: Display result */
void displayAutomaton() {
    int i, j;

    printf("\nNew transitions (without epsilon):\n");

    printf("Symbol a:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf("%d ", new_trans[i][0][j]);
        printf("\n");
    }

    printf("Symbol b:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf("%d ", new_trans[i][1][j]);
        printf("\n");
    }

    printf("New final states:\n");
    for (i = 0; i < n; i++)
        printf("State %d: %d\n", i, new_final[i]);
}

/* MAIN */
int main() {
    readNFA();
    computeNewTransitions();
    computeNewFinalStates();
    displayAutomaton();
    return 0;
}
