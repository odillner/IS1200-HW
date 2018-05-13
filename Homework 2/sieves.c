#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6

void print_number(int const n){
  static int counter=0;
  printf("%10d", n);
  counter++;
  if (counter==COLUMNS){
    counter = 0; 
    printf("\n");
  }
}
int find_next_prime(int* arr, int const p, int const len){
  for (int i=p-1;i<len;i++){
    if (arr[i]==1){
      return i+2;
    }
  }
  return 0;
}
int exclude_multiples(int* arr, int const p, int const len){
  int count = 0;
  for (int i=(p*p)-2;i<len;i++){
    if (((i+2)%p)==0){
      arr[i]=0;
      count++;
    }
  }
  return count;
}
void print_sieves(const int n){
  int const len = n-2;
  int p = 2;
  int *arr = (int*)malloc(sizeof(int) * len);

  for (int i=0;i<len;i++){
    arr[i] = 1;
  }

  while (p!=0){
    if (exclude_multiples(arr,p,len)==0) {
      break;
    }
    p = find_next_prime(arr,p,len);
  }

  for (int i=0;i<len;i++){
    if (arr[i]==1){
      print_number(i+2);
    }
  }
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}

 
