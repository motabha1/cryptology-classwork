/*

    This utility header is an implementation of LFSR
    new_state Sj = C{0}.S{j-n-1} + C{1}.S{j-n-2} + .... + C{n-1}S{j-n-1}  mod 2
    Connection Polynomial : x^n + C{n-1}.x^(n-1) + C{n-2}.x^(n-2) + .... + C{0} 
*/

int get_new_state(int state, int poly, int n){
    int st[n], conn[n];
    for(int i=0; i<n; i++){
        st[i] = state % 2;
        conn[i] = poly % 2;
        state/=2; poly/=2;
    }
    int new_state = 0;
    for(int i=0; i<n; i++){
        new_state = (new_state + st[n-i-1]*conn[i]) % 2;
    }
    int tmp;
    state = 0;
    for(int i=0; i<n; i++){
        tmp = st[i];
        st[i] = new_state;
        new_state = tmp;
    }
    for(int i=n-1; i>=0; i--){
        state = 2*state + st[i];
    }
    return state;
}   
