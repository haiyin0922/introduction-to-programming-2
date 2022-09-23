#include <stdio.h>
int main()
{
    int M, N, P;
    int row = 0, col = 0;
    int dir_r = 0, dir_c = 1;
    int i, j, x, y;
    int s[30][30];

    for(i=0;i<30;i++){
        for(j=0;j<30;j++)
            s[i][j]=-1;
    }

    scanf("%d%d%d", &M, &N, &P);
	
	
    i = 0;
    while(i < M*N){
        s[row][col] = i+1;
        // 向右
        if(dir_c==1 && (col+dir_c==N || s[row][col+dir_c]!=-1)){
            dir_c = 0;
            dir_r = 1;
        	if(row+dir_r==M || s[row+dir_r][col]!=-1)
        	break;
        }
        // 向左
        else if(dir_c==-1 && (col+dir_c<0 || s[row][col+dir_c]!=-1)){
            dir_c = 0;
            dir_r = -1;
        	if(row+dir_r<0 || s[row+dir_r][col]!=-1)
        	break;
        }
        // 向下
        else if(dir_r==1 && (row+dir_r==M || s[row+dir_r][col]!=-1)){
            dir_r = 0;
            dir_c = -1;
        	if(col+dir_c<0 || s[row][col+dir_c]!=-1)
        	break;
        }
        // 向上
        else if(dir_r==-1 && (row+dir_r<0 || s[row+dir_r][col]!=-1)){
            dir_r = 0;
            dir_c = 1;
        	if(col+dir_c==N || s[row][col+dir_c]!=-1)
        	break;
        }
        row = row+dir_r;
        col = col+dir_c;
        i++;
    }
	
	
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			if(s[i][j]==P){
				y = i+1;
				x = j+1;
			}
		} 
	}
	
	printf("%d %d\n", y, x);
	
    return 0;
}
