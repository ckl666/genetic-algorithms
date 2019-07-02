#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define LEN 10				//��Ⱥ�ĸ���
#define ARRLEN 100;
#define ROW 10
#define COL 10
#define MUTATION 0.15        //����ĸ���

//ѡȡ���������
//
//

int Sum(int *arr,int len,int *yarr)
{
	int sum = 0;
	for(int i = 0; i < len; i++)
	{
		sum += yarr[arr[i]];
	}
	return sum;
}
//��Ӧ���㷨
int Suff(int arr[ROW][COL],int mid,int len,int n,int *yarr,double *suf)
{
	double suff = 0;
	int num = 0;							//������ĺ�
	for(int i = 0; i < n; i++)
	{
		num = Sum(arr[i],len,yarr);			
		num = abs(num-mid);				//������ͼ�ȥԭ����ĺ͵�һ��
		if (num == 0)
		{
			return i;
		}
		suff += (double)1/num;			//�ۼ��ܵ���Ӧ��
		num = 0;						//ѭ�����
	}
	*suf = suff;
	return -1;						//�����ܵ���Ӧ��
}

//ѡ��������� ѡ����һ������
void Subarrs(int arr[ROW][COL],int mid,double suff,int n,int len,int index[LEN],int *yarr)
{
	double corona[LEN] = {0};
	int num = 0;
	for(int i = 0; i < LEN; i++)					//��������
	{
		num = Sum(arr[i],len,yarr);
		num = abs(num-mid);
		if(i > 0)
		{
			corona[i] = corona[i-1] + ((double)1/num)/suff;
		}
		else
		{
			corona[i] = ((double)1/num)/suff;
		}
		//printf("%lf \n",corona[i]);
	}	
	//bool index[LEN] = {false};			//����Ŵ�����һ���ĸ�����±�
	for(int i = 0; i < LEN; i++)		//LEN�����Ŵ�����һ���ĸ���
	{
		float f = rand()%10000;				//���ѡ���Ŵ�����һ��
		f /= 10000;	
		//printf("%f \n",f);
		for(int j = 0; j < LEN; j++)
		{
			if(corona[j] >= f)
			{
				index[j]++;
				break;
			}
		}
	}
}


int Select(int arr[ROW][COL],int row1,int row2,int *sub)
{
	int sub1 = rand()%COL;
	int count = 0;
	for(int j = 0; j < COL; j++)
	{
		if(arr[row1][j] == arr[row2][sub1])
		{
			count++;
			sub1 = rand()%COL;
			j = -1;
		}
		if(count == 20)
		{
			return -1;
		}
	}
	*sub = sub1;
	return 0;
}

//�������� arr[][]���ԭ������±�
void Crossover(int arr[ROW][COL])
{
	//srand(time(0));
	for(int i = 0; i < LEN; i += 2)
	{
		int sub1 = 0; 
		int tag1 = Select(arr,i+1,i,&sub1);
		int sub2 = 0; 
		int tag2 = Select(arr,i,i+1,&sub2);

		if(tag1 == 0 && tag2 == 0)			//���ֵ��������
		{
			int tmp = arr[i][sub1];
			arr[i][sub1] = arr[i+1][sub2];
			arr[i+1][sub2] = tmp;
		}	
	}
}

int MutaIndex(int arr[ROW][COL],int row)
{
	int sub = rand()%(2*COL);
	for(int j = 0; j < COL; j++)
	{
		if(sub == arr[row][j])
		{
			sub = rand()%(2*COL);
		}
	}
	return sub;
}


//��������
void Mutation(int arr[ROW][COL])
{
	for(int i = 0; i < LEN; i++)
	{
		float f = rand()%10000;
		f /= 10000;
		if(f < MUTATION)
		{
			int sub = MutaIndex(arr,i);
			int seat = rand()%COL;
			arr[i][seat] = sub;
			//printf("%d==%d\n",i,seat);
		}
	}
}

//���鸳ֵ
void ArrEva(int *des,int *src,int len)
{
	for(int i = 0; i < len; i++)
	{
		des[i] = src[i];
	}
}

void ArrTwoEva(int arr[ROW][COL],int *index)
{
	for(int i = 0; i < LEN; i++)
	{
		if(index[i] == 0)
		{
			for(int j = 0; j < LEN; j++)
			{
				if(index[j] > 1)
				{
					ArrEva(arr[i],arr[j],COL);
					index[j]--;
					index[i]++;
					break;
				}
			}
		}
	}
}

void Show(int arr[ROW][COL],int row,int col,int *yarr)
{
	int sum = 0;
	for(int i = 0; i < ROW; i++)
	{
		for(int j = 0; j < COL; j++)
		{
			printf("%5d",yarr[arr[i][j]]);
			sum += yarr[arr[i][j]];
		}
		printf("  %d\n",sum);
		sum = 0;
	}
}

void Print(int *arr,int len)
{
	int sum = 0;
	for(int i = 0; i < len; i++)
	{
		sum += arr[i];
		printf("%d ",arr[i]);
	}
	printf("  %d \n",sum);
}

int main()
{
	//1 7 9 2 3 4 5 6 7 8 7 1

	srand(time(0));
	int yarr[100] = {0};
	
	for(int i = 0; i < 100; i++)
	{
		yarr[i] = i;
	}
	//�����м�ֵ
	int mid = 0;
	for(int i = 0; i < 100; i++)
	{
		mid += yarr[i];
	}
	mid /= 10;
	//��ʼ����Ⱥ
	int arr[ROW][COL] = {0};
	
	for(int i = 0; i < ROW; i++)
	{
		for(int j = 0; j < COL; j++)
		{
			arr[i][j] = (i+1)*(j+1)-1;
		}
	}

	//Show(arr,ROW,COL,yarr);

	//printf("%f \n",Suff(arr,mid,COL,ROW,yarr));


	for(int i = 0; i < 30; i++)
	{
		double suff = 0;
		int tag = Suff(arr,mid,COL,ROW,yarr,&suff);
		if(tag != -1)
		{
			Print(arr[tag],COL);
			return 0;
		}
		int index[LEN] = {0};						//�Ŵ���һ���ĸ�������
		//�Ŵ�����һ����ֵ
		Subarrs(arr,mid,suff,ROW,COL,index,yarr);
		ArrTwoEva(arr,index);
		/*
		for(int i = 0; i < LEN; i++)
		{
			if(index[i] != 0)
			{
				printf("[%d][%d] ",i,index[i]);
			}
			printf("\n");
		}
		*/

		

		Crossover(arr);
		Mutation(arr);
		//Show(arr,ROW,COL,yarr);
	}
	Show(arr,ROW,COL,yarr);
	return 0;
}