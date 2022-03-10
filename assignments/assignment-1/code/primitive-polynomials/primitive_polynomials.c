#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include "../utility/lfsr.h"

FILE *fptr;

void print_polynomial(int x, int degree){
    //fprintf(fptr, "%d\n", x);
    for(int i=0; i<degree; i++){
        if(x % 2){
            i == 0 ? fprintf(fptr, "1 + ") : (i == 1 ? fprintf(fptr, "x + ") : fprintf(fptr, "x^%d + ", i));
        }
        x/=2;
    }
    fprintf(fptr, "x^%d\n", degree);
}

// A polynomial is primitive if it is able to give us all states from 1 to 2^n - 1
int check_primitive(int poly, int seed, int degree){
    int count = 1, new_state;
    int no_of_states = (1 << degree) - 1;
    int is_repeated[no_of_states];
    memset(is_repeated, 0, sizeof(is_repeated));
    is_repeated[seed-1] = 1;
    while(1){
        new_state = get_new_state(seed, poly, degree);
        if(is_repeated[new_state - 1])
            break;
        is_repeated[new_state - 1] = 1;
        seed = new_state;
        count++;
    }
    return count == no_of_states;
}

// We will go through all possible polynomials for a degree and check if they are primitive
void check_for_degree(int seed, int degree){
    int num = 1 << (degree);        
    for(int i=num; i<2*num; i++){
        if(check_primitive(i, seed, degree)){
            print_polynomial(i, degree);
        }
    }
    fprintf(fptr, "\n");
}

// Each iteration will find a polynomial of that degree
void find_polynomials(int seed, int lower, int upper){
    for(int i=lower; i<=upper; i++){
        fprintf(fptr, "%d\n--------------------------------------------\n", i);
        check_for_degree(seed, i);
    }
}

int main(){

    time_t begin = time(NULL);

    fptr = fopen("primitive_polynomials.txt", "w");
    find_polynomials(1, 4, 16);
    fclose(fptr);

    time_t end = time(NULL);

    printf("%f minutes", (end - begin)/60.0);
}