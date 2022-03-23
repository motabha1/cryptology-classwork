#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>


// Taking key as 16 bytes 

int s[256], k[16];
int rout = 2;
int z[2];

void swap(int *x, int *y){
    int z = *x;
    *x = *y;
    *y = z;
}

void initiate_permutation(){
    for(int i=0; i<256; i++){
        s[i] = i;
    }
}

void initiate_key(){
    for(int i=0; i<16; i++){
        k[i] = rand() % 256;
    }
}

void generate_permutation(){
    int j = 0;
    for(int i=0; i<256; i++){
        j = (j + s[i] + k[i%16]) % 256;
        swap(&s[i], &s[j]);
    }
}


void key_schedule(){
    initiate_permutation();
    initiate_key();
    generate_permutation();
}

void run_routine(){
    int i = 0, j = 0;
    while(rout--){
        i = i+1;
        j = (j + s[i]) % 256;
        swap(&s[i], &s[j]);
        int t = (s[i] + s[j]) % 256;
        z[1-rout] = s[t];
    }
}

int main(){
    FILE *fptr;
    fptr = fopen("z1_z2.txt", "w");
    int Z1[256], Z2[256];
    memset(Z1, 0, sizeof(Z1));
    memset(Z2, 0, sizeof(Z2));
    for(int i=0; i<65536; i++){
        key_schedule();
        rout = 2;
        run_routine();
        Z1[z[0]]++; Z2[z[1]]++;
    }
    fprintf(fptr, "s,z1,z2\n");
    for(int i=0; i<256; i++){
        fprintf(fptr, "%d,%f,%f\n", i, Z1[i]/65536.0, Z2[i]/65536.0);
    }
    fclose(fptr);
}