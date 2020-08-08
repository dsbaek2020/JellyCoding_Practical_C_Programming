#include <stdio.h>
#include <math.h>

#define G     9.8//m/s^2
#define PI    3.14//
#define V     100//m/s
#define TARGET  450//m

int main()
{
    float deg;
    float rad;
    float v_y;
    float T;
    float x;
    float error[10];
    int i=0;
    float sum;	
    float a;
		

    while(i<10)
    {
        printf("각도를 입력하세요[deg]: ");
        scanf("%f", &deg);    // 실수를 입력받아서 변수에 저장
        rad=(PI/180.0)*deg;
        v_y=V*sin(rad);
        T=v_y/G;
        x=V*cos(rad)*T;
        error[i]=TARGET-x;

        printf("수직속도는 %f[m/s]입니다.\n", v_y);    // 변수의 내용을 출력
        printf("비행시간은 %f[s]입니다.\n",T);
        printf("비행거리는 %f[m]입니다.\n",x);
        printf("오차는 %f[m]입니다.\n",error[i]);
        i++;
    }
    i=0;
    sum=0;
    while(i<10)
    {
      sum=sum+error[i];
      i++;
    }
    a=sum/10;
    printf("오차 평균값은 %f[m]입니다.\n",a);	
    if((-10<a)&&(a<10))
    {
    printf("평균오차가 적습니다.\n");
    }

   
    return 0;
}