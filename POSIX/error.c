#include<stdio.h>
#include<errno.h>
#include <string.h>
 int main()
 {
    FILE *fp;

    fp = fopen("data.txt", "r");

    printf("The error number is %d\n", errno);
    printf("The error description is %s\n", strerror(errno));

  return (0);
}
