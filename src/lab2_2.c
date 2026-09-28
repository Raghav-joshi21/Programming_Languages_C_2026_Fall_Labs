#include <stdio.h>
long long factorial(int n) {
    long long result=1;
for (int i =1;i <=n;i++) {
    result *=i;
}
return result;
}
int main(void) {
    int n;
    printf("enter a non-negative integer n: ");
    if (scanf("%d",&n) !=1) {
    printf("Invalid input.\n");
    return 1;
}
   if (n <0) {
    printf("Error: n must be non-negative.\n");
    return 1;
}
long long result = factorial(n);
printf("%d! = %lld\n", n, result);
    return 0;
}
