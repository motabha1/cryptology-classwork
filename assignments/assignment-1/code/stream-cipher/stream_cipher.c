#include<stdio.h>
#include "../utility/lfsr.h"

struct lfsr{
    int ff;
    int state;
    int poly;
};

struct lfsr l7, l11, l13;

void initiate_lfsr(){
    l7.ff = 7; l7.poly = 131; l7.state = 1;
    l11.ff = 11; l11.poly = 2053; l11.state = 1;
    l13.ff = 13; l13.poly = 8219; l13.state = 1;
}

int get_bit(struct lfsr *L){
    int b = get_removed_bit(L->state, L->ff);
    L->state = get_new_state(L->state, L->poly, L->ff);
    return b;
}

int get_key_bit(){
    int x = get_bit(&l13);
    int y = get_bit(&l7);
    int z = get_bit(&l11);
    return (x==1)*y + (x==0)*z; 
}

char get_char(int arr[]){
    int temp = 0;
    for(int i=0; i<8; i++){
        temp = 2*temp + arr[i];
    }
    char c = temp;
    return c;
}

int main(){
    initiate_lfsr();
    FILE *fc, *fm;
    fc = fopen("cipher.txt", "w");
    fm = fopen("message.txt", "w");
    
    int m, c, ctr = 0;
    char C, M;
    
    for(int i=0; i<1048576; i++){
        m = rand() % 2;
        c = (m + get_key_bit()) % 2;
        fprintf(fm, "%d", m);
        fprintf(fc, "%d", c);
    }
    fclose(fm);
    fclose(fc);
    return 0;
}