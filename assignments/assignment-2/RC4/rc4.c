#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>


// Taking key as 8 bytes 

int s[256], k[8];

void swap(int *x, int *y){
    *x = *x + *y;
    *y = *x - *y;
    *x = *x - *y;
}

int find_ith_bit(int k, int i){
    int t = 1 << i;
    return t & k != 0;
}

void initiate_premutation(){
    for(int i=0; i<256; i++){
        s[i] = i;
    }
}

void initiate_key(){
    for(int i=0; i<8; i++){
        k[i] = rand() % 256;
    }
}

void generate_permutation(){
    int j = 0;
    for(int i=0; i<256; i++){
        j = (j + s[i] + k[i%8]) % 256;
        swap(&s[i], &s[j]);
    }
}


void key_schedule(){
    initiate_premutation();
    initiate_key();
    generate_permutation();
}

int run_routine(int i, int j){
    swap(&s[i], &s[j]);
    return s[(s[i] + s[j])%256];
}

int main(){
    FILE *fptr;
    fptr = fopen("z1_z2.txt", "w");
    int z1, z2;
    int Z1[256], Z2[256];
    memset(Z1, 0, sizeof(Z1));
    memset(Z2, 0, sizeof(Z2));
    for(int i=0; i<65536; i++){
        key_schedule();
        z1 = run_routine(1, s[1]);
        z2 = run_routine(2, (s[1] + s[2])%256);
        //fprintf(fptr, "%d ----  %d\n", z1, z2);
        Z1[z1]++; Z2[z2]++;
    }
    fprintf(fptr, "s,z1,z2\n");
    for(int i=0; i<256; i++){
        fprintf(fptr, "%d,%f,%f\n", i, Z1[i]/65536.0, Z2[i]/65536.0);
    }
    fclose(fptr);
}