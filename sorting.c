#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

long *Load_File(char *Filename, int *Size)
{

	FILE *fp = fopen(Filename, "r");
	char str[12];

	fgets(str, 12, fp);
	*Size = atoi(str);

	long *array = malloc((*Size) * sizeof(long));
	
	int i=0;
	while(i < *Size)
	{
		fgets(str, 12, fp);
		array[i] = atol(str);
		i++;
	}

	fclose(fp);
	
return array;
}	

int Save_File(char *Filename, long *Array, int Size)
{
	FILE *fp = fopen(Filename, "w");
	
	fprintf(fp, "%d\n", Size);

	int i = 0;
	for(i =0; i < Size; i++)
	{
		fprintf(fp, "%ld%c", Array[i], '\n');
	}

	fclose(fp);

return i;
}

void Shell_Insertion_Sort(long *Array, int Size, double *NComp, double *NMove)
{
	int terms = 0;
	int* gaps = Three_Smooth(Size, &terms);
	
	int gap, i, j;
	int k;
	for(k = terms-1; k >= 0; k--)
	{
		gap = gaps[k];
		for(i = gap; i < Size; i++)
		{
			long temp = Array[i];
			(*NMove)++;
			j = i;
			
			while(j >= gap && Array[j-gap] > temp)
			{
				Array[j] = Array[j-gap];
				(*NMove)++;
				j -= gap;
				(*NComp)++;
			}

			if(j >= gap)
			{(*NComp)++;}
			
			Array[j] = temp;
			(*NMove)++;
		}
	}	
	
	free(gaps);

return;
}

void Improved_Bubble_Sort(long *Array, int Size, double *NComp, double *NMove)
{
	int terms = 0;
	int* gaps = Bubble_Seq(Size, &terms);	
	int gap = 0;
	int n;
	
	for(n = terms-1; n >= 0;n--)	
	{

		gap = gaps[n];
		
		int i=0;
		for(i = 0;i < Size - gap;i++)
		{	
			if(Array[i] > Array[i+gap])
			{
				(*NComp)++;
				long temp = Array[i];
				Array[i] = Array[i+gap];
				Array[i+gap] = temp;
				(*NMove)++;			
			}
		}

		int j;
		for(j = Size-gap-1; j > 0; j--)
		{	
			if(Array[j] > Array[j+gap])
			{
				(*NComp)++;
				long temp = Array[j];
				Array[j] = Array[j+gap];
				Array[j+gap] = temp;
				(*NMove)++;
			}
		}
	}
	
	free(gaps);

return;
}

void Save_Seq1(char *Filename, int N)
{
	int terms = 0;
	int* seq = Bubble_Seq(N, &terms);
	
	FILE *fp = fopen(Filename, "w");
	
	fprintf(fp, "%d\n", terms);

	int i = 0;
	for(i =0; i < terms; i++)
	{
		fprintf(fp, "%d%c", seq[i], '\n');
	}

	fclose(fp);

return;
}

void Save_Seq2(char *Filename, int N)
{
	int terms = 0;
	int* seq = Bubble_Seq(N, &terms);
	
	FILE *fp = fopen(Filename, "w");
	
	fprintf(fp, "%d\n", terms);

	int i = 0;
	for(i =0; i < terms; i++)
	{
		fprintf(fp, "%d%c", seq[i], '\n');
	}

	fclose(fp);

return;
}

int* Three_Smooth(int size, int* terms)
{
	int *Smooth_Seq = malloc(sizeof(int) * size);		//3 Smooth Sequence
	Smooth_Seq[0] = 1;
	int p2 = 0, p3 = 0;
	int u2 =0, u3=0;
	int i = 1;

	for(i=1; i < size; i++){
		if (Smooth_Seq[p2]*2 == Smooth_Seq[i-1]){
			p2 += 1;}
		
		if (Smooth_Seq[p3]*3 == Smooth_Seq[i-1]){
			p3 += 1;}

		u2 = Smooth_Seq[p2]*2;
		u3 = Smooth_Seq[p3]*3;
		
		if(u2 < u3){
			p2 += 1;
			Smooth_Seq[i] = u2;}
		else{
			p3 += 1;
			Smooth_Seq[i] = u3;}	
		
		if(Smooth_Seq[i] >= size)	
		{
			break;
		}
	}	
	
	int *Smooth = malloc(sizeof(int) * i);
	int k;
	for(k=0; k < i; k++)
	{
		Smooth[k] = Smooth_Seq[k];
	}

	*terms = i;

	free(Smooth_Seq);

return Smooth;
}

int* Bubble_Seq(int size, int*terms)
{
	int temp = size;
	int counter = 0; 

	while(temp > 1)
	{
		temp /= 1.3;
		if(temp == 9 || temp == 10)
		{
			temp = 11;
		}
		counter++;
	}
	
	int* gaps = malloc(sizeof(int) * counter);	
	int i;
	*terms = counter;
	temp = size;

	for(i = counter-1; i >=0; i--)
	{
		temp = temp/1.3;
		if(temp == 9 || temp == 10)
		{
			temp = 11;
		}
		
		gaps[i] = temp;
	}

return gaps;
}
