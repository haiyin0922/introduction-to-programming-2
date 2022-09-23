#include<stdio.h>
int board[15][15] = {0};
int M, N;
int total;

int main()
{
    scanf("%d%d", &M, &N);
    total = 0;
    place(0, 0, 0);
    printf("%d\n", total);
    return 0;
}

void place(int m, int n, int row)
{
    int col, i;
    int status, ok;
    
    if(m==M && n==N){
        total++;
    } 
    else if(row<(M+N) && m<=M && n<=N){
        for(col=0; col<(M+N); col++){
            for(status=1; status<=2; status++){
                if(status==1){
                    ok=1;
                    board[row][col]=1;/*�����d��﨤�u�B�C-�欰�w��(=row-col),�ƹ﨤�u�C+�欰�w��(row+col)*/
                    for(i=0; i<row; i++){/*�ˬd�O�_�|�Q���e�񪺴Ѥl����*/
                        if(board[i][col]!=0 || board[i][col-row+i]!=0 || board[i][col+row-i]!=0){
                            board[row][col]=0;
                            ok=0;
                            break;/*�Y�|�Q����,�h������m*/
                        }
                    }
                    if(ok==1){                    	
                        place(m+1, n, row+1);/*��U�@���ӦZ*/
                        board[row][col]=0;/*��^��*/
                    }
                }
                else{
                    ok=1;
                    board[row][col]=2;
                    for(i=0; i<row; i++){
                        if(board[i][col]!=0 || board[i][col-row+i]==1 || board[i][col+row-i]==1){/*�D�ƹ﨤�u�B���ӦZ*/
                            board[row][col]=0;
                            ok=0;
                            break;
                        }
                    }
                    if(ok==1){
                        place(m, n+1, row+1);
                        board[row][col]=0;
                    }
                }
            }
        }
    }
}
