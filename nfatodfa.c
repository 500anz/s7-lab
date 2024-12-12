#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 100
#define MAX_TRANSITIONS 100
#define MAX_SYMBOLS 26

typedef struct {
    int nfa_states[MAX_STATES];
    int n_states;
} StateSet;

int nfa[MAX_STATES][MAX_SYMBOLS][
MAX_STATES];
int dfa[MAX_STATES][MAX_SYMBOLS];
int nfa_states, symbols;
int start_state, n_end_states;
int nfa_end_states[MAX_STATES];

StateSet dfa_states[MAX_STATES];
int dfa_state_count = 0;
int dfa_end_states[MAX_STATES];
int n_dfa_end_states = 0;

int is_end_state(StateSet set) {
    for (int i = 0; i < set.n_states; i++) {
        for (int j = 0; j < n_end_states; j++) {
            if (set.nfa_states[i] == nfa_end_states[j]) {
                return 1;
            }
        }
    }
    return 0;
}

int set_equals(StateSet a, StateSet b) {
    if (a.n_states != b.n_states) return 0;
    for (int i = 0; i < a.n_states; i++) {
        if (a.nfa_states[i] != b.nfa_states[i]) return 0;
    }
    return 1;
}

int state_exists(StateSet set) {
    for (int i = 0; i < dfa_state_count; i++) {
        if (set_equals(dfa_states[i], set)) {
            return i;
        }
    }
    return -1;
}

void add_state(StateSet set) {
    dfa_states[dfa_state_count] = set;
    dfa_state_count++;
}

StateSet move(StateSet set, int symbol) {
    StateSet result;
    result.n_states = 0;
    int exists[MAX_STATES] = {0};

    for (int i = 0; i < set.n_states; i++) {
        int current_state = set.nfa_states[i];
        for (int j = 0; j < nfa_states; j++) {
            if (nfa[current_state][symbol][j] && !exists[j]) {
                result.nfa_states[result.n_states++] = j;
                exists[j] = 1;
            }
        }
    }
    return result;
}

void convert_nfa_to_dfa() {
    StateSet start_set;
    start_set.n_states = 1;
    start_set.nfa_states[0] = start_state;

    add_state(start_set);
    if (is_end_state(start_set)) {
        dfa_end_states[n_dfa_end_states++] = 0;
    }

    for (int i = 0; i < dfa_state_count; i++) {
        for (int j = 0; j < symbols; j++) {
            StateSet new_set = move(dfa_states[i], j);

            if (new_set.n_states > 0) {
                int state_index = state_exists(new_set);
                if (state_index == -1) {
                    add_state(new_set);
                    state_index = dfa_state_count - 1;
                    if (is_end_state(new_set)) {
                        dfa_end_states[n_dfa_end_states++] = state_index;
                    }
                }
                dfa[i][j] = state_index;
            } else {
                dfa[i][j] = -1;
            }
        }
    }
}

void print_set(StateSet set, int width) {
    char buffer[100] = "{";
    for (int i = 0; i < set.n_states; i++) {
        char temp[10];
        sprintf(temp, "%d", set.nfa_states[i]);
        strcat(buffer, temp);
        if (i < set.n_states - 1) {
            strcat(buffer, ", ");
        }
    }
    strcat(buffer, "}");

    printf("%-*s", width, buffer);  // Fixed width for each state set
}

void print_dfa() {
    int column_width = 15;  // Adjust this for better alignment if necessary
    printf("\nDFA Transition Table:\n");
    printf("State\t\t");
    for (int i = 0; i < symbols; i++) {
        printf("%-*c", column_width, 'a' + i);  // Print 'a', 'b', etc. with fixed width
    }
    printf("\n");

    for (int i = 0; i < dfa_state_count; i++) {
        print_set(dfa_states[i], column_width);  // Print the DFA state
        printf("\t");
        for (int j = 0; j < symbols; j++) {
            if (dfa[i][j] != -1) {
                print_set(dfa_states[dfa[i][j]], column_width);  // Print the next state for symbol
            } else {
                printf("%-*s", column_width, "-");  // Print '-' for no transition
            }
        }
        printf("\n");
    }

    printf("Start state: ");
    print_set(dfa_states[0], column_width);
    printf("\nEnd states: ");
    for (int i = 0; i < n_dfa_end_states; i++) {
        print_set(dfa_states[dfa_end_states[i]], column_width);
       
    }
    printf("\n");
}

int main() {
    int transitions, from, to;
    char symbol;

    // Input NFA details
    printf("Enter number of states in NFA: ");
    scanf("%d", &nfa_states);

    printf("Enter number of symbols: ");
    scanf("%d", &symbols);

    printf("Enter number of transitions: ");
    scanf("%d", &transitions);

    memset(nfa, 0, sizeof(nfa));

    printf("Enter transitions (from_state symbol to_state):\n");
    for (int i = 0; i < transitions; i++) {
        scanf("%d %c %d", &from, &symbol, &to);
        nfa[from][symbol - 'a'][to] = 1;
    }

    printf("Enter start state: ");
    scanf("%d", &start_state);

    printf("Enter number of end states: ");
    scanf("%d", &n_end_states);

    printf("Enter end states: ");
    for (int i = 0; i < n_end_states; i++) {
        scanf("%d", &nfa_end_states[i]);
    }

    // Convert NFA to DFA
    convert_nfa_to_dfa();

    // Print DFA
    print_dfa();

    return 0;
}
