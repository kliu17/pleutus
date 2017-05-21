#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int main() {
int i=0,flag1=0,count=0,rem=0,quo=0, result=0, divs=0, divd=0;
int arr[20];
        for (rem=0;rem<20;rem++)
        {arr[rem]=-1;}

printf("Enter dividend and divisor\n");
scanf("%d %d",&divd,&divs);

    quo=divd/divs;
    rem=divd%divs;
    printf("%d.",quo);

while(1) {
rem=rem*10;
quo=rem/divs;

for(i=0;i<=count;i++) {
if(quo==arr[i])
{flag1=1;break;}
}
if(flag1==1) break;

arr[count]=quo; count++;
rem=rem%divs;
}

printf("(");
for(i=0;i<count;i++)
{printf("%d",arr[i]);}
printf(")");
	return 0;
}
