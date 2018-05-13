/*
 prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>

int is_prime(int n){
  if (n>1){
    for (int i=2;i<n-1;i++) {
      if (n%i==0){
        return 0;
      }
    }
    return 1;
  } else {
    return 0;
  }
}

int main(void){
  printf("%d\n", is_prime(2));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
}
