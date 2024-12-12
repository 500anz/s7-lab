#include <stdio.h>
#include <stdlib.h>

#define MAX_STATES 20
#define MAX_ALPHABETS 20

struct Node {
	int state;
	struct Node* next;
};

int numStates, numAlphabets, startState, numFinalStates;
int finalStates[MAX_STATES];
char alphabet[MAX_ALPHABETS];
int epsilonClosure[MAX_STATES][MAX_STATES];
int closureCount[MAX_STATES];
struct Node* transitions[MAX_STATES][MAX_ALPHABETS];
struct Node* newTransitions[MAX_STATES][MAX_ALPHABETS];

void insertTransition(struct Node* transitions[MAX_STATES][MAX_ALPHABETS], int from, char symbol, int to) {
	int index = (symbol == 'e') ? (numAlphabets - 1) : (symbol - 'a');
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->state = to;
	newNode->next = transitions[from][index];
	transitions[from][index] = newNode;
}

void computeEpsilonClosure(int state, int closureIndex) {
	if (closureCount[state]) return;

	epsilonClosure[closureIndex][closureCount[closureIndex]++] = state;
	struct Node* temp = transitions[state][numAlphabets - 1]; // ε-transitions
	while (temp != NULL) {
    	computeEpsilonClosure(temp->state, closureIndex);
    	temp = temp->next;
	}
}

void createNFA() {
	for (int i = 0; i < numStates; i++) {
    	closureCount[i] = 0; // Reset closure count
    	computeEpsilonClosure(i, i);
	}

	// Now create transitions for the equivalent NFA
	for (int i = 0; i < numStates; i++) {
    	for (int j = 0; j < closureCount[i]; j++) {
        	int currentState = epsilonClosure[i][j];

        	for (int k = 0; k < numAlphabets - 1; k++) { // Exclude 'e'
            	struct Node* temp = transitions[currentState][k];
            	while (temp != NULL) {
                	for (int m = 0; m < closureCount[temp->state]; m++) {
                    	insertTransition(newTransitions, i, alphabet[k], epsilonClosure[temp->state][m]);
                	}
                	temp = temp->next;
            	}
        	}
    	}
	}
}

void printNFA() {
	printf("Transitions for the equivalent NFA:\n");
	for (int i = 0; i < numStates; i++) {
    	for (int j = 0; j < numAlphabets - 1; j++) { // Exclude 'e'
        	struct Node* temp = newTransitions[i][j];
        	if (temp != NULL) {
            	printf("From q%d on '%c': ", i, alphabet[j]);
            	while (temp != NULL) {
                	printf("q%d ", temp->state);
                	temp = temp->next;
            	}
            	printf("\n");
        	}
    	}
	}
}

int main() {
	printf("Enter the number of states: ");
	scanf("%d", &numStates);
   
	printf("Enter the number of alphabets (including epsilon as 'e'): ");
	scanf("%d", &numAlphabets);
   
	printf("Enter the alphabets (e must be last): ");
	for (int i = 0; i < numAlphabets; i++) {
    	scanf(" %c", &alphabet[i]);
	}
	printf("Enter the start state: ");
	scanf("%d", &startState);
	printf("Enter the number of final states: ");
	scanf("%d", &numFinalStates);
   
	printf("Enter the final states:\n");
	for (int i = 0; i < numFinalStates; i++) {
    	scanf("%d", &finalStates[i]);
	}
   
	int numTransitions;
	printf("Enter the number of transitions: ");
	scanf("%d", &numTransitions);
   
	printf("Enter transitions in the format: from_state symbol to_state\n");
	for (int i = 0; i < numTransitions; i++) {
    	int fromState, toState;
    	char symbol;
    	scanf("%d %c %d", &fromState, &symbol, &toState);
    	insertTransition(transitions, fromState, symbol, toState);
	}
	for (int i = 0; i < numStates; i++) {
    	closureCount[i] = 0;
	}
   
	createNFA();
   

	printNFA();

	for (int i = 0; i < numStates; i++) {
    	for (int j = 0; j < numAlphabets; j++) {
        	struct Node* temp = transitions[i][j];
        	while (temp) {
            	struct Node* toDelete = temp;
            	temp = temp->next;
            	free(toDelete);
        	}}}
	return 0;}
