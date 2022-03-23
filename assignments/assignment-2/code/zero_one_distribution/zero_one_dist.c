#include<stdio.h>
#include<string.h>

int main(){
    FILE *fptr;
    fptr = fopen("../utility/scrape_data/scraped_data.txt", "r");
    char c;
    int z = 0, o = 0, p, tot = 0;
    while((c = fgetc(fptr)) != EOF){
        for(int i=6; i>=0; i--){
            p = (c & (1 << i)) ? o++ : z++;
        }
    }
    printf("zero : %f\none: %f", z/(1.0*(z+o)), o/(1.0*(z+o)));

    //Execution of the code gave
    // Pr[z = 0] = 0.5598
    // Pr[z = 1] = 0.4401
}