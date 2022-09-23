#include<stdio.h>
int main()
{
	int N;
	int i, j, k, l;
	int max = 0;
	int row = 0, col = 0;
	int s[10][10], t[8][8];
	
	scanf("%d", &N);
	
	for(i=0;i<N;i++){
		for(j=0;j<N;j++)
			scanf("%d", &s[i][j]);
	}
		
	for(k=3;k<=N;k++){
		for(l=3;l<=N;l++){ 
			for(i=k-3;i<k;i++){
				for(j=l-3;j<l;j++){ 
					if(s[i][j] >= max)
						max = s[i][j];
				}	 
			}
			t[row][col] = max;
			row = (col==N-3)? row+1 : row;
			col = (col==N-3)? 0 : col+1;
			max = 0;			
		}
		l = 3;
	}
	
	for(i=0;i<N-2;i++){
		for(j=0;j<N-2;j++){
			printf("%d", t[i][j]);
			if(j<N-3)
				printf(" ");
		}
			printf("\n");
	}
	
	return 0;
}
