#include<stdio.h>

int solve(int rightBound);
int N, grammar[100][100], sentence[100], grammar_size[100], pos;

int main()
{	
	int M, i, j;
	 
	scanf("%d%d", &N, &M);
	
	for(i=0; i<N; i++){
		j=0;
		while(j==0 || grammar[i][j-1]!=-1){
			scanf("%d", &grammar[i][j]);
			j++;
			if(grammar[i][0]==0 && grammar[i][1]==-1){
            	N--;
            	i--;
            	break;
        	}
		}
		grammar_size[i] = j-1; 
	}

	for(i=0; i<M; i++){
		j = 0;
		while(j==0 || sentence[j-1]!=-1){
			scanf("%d", &sentence[j]);
			j++;
		}
		pos = 0;
		if(solve(j-2)) printf("True\n");
		else printf("False\n");
	}		
}
	 
int solve(int rightBound) 
{ 
    int i, j;
    int temp_pos = pos;

    for(i=0; i<N; i++){
        pos = temp_pos;
        for(j=0; grammar[i][j]!=-1 && pos<=rightBound; j++){
            // construct another spell
            if(grammar[i][j]==0){
                if(!solve(rightBound-(grammar_size[i]-j-1)))
                    break;
            }
            // not match -> turn to test next grammar
            else if(sentence[pos]!=grammar[i][j])
                break;
            // if match, increase position index by 1
            else
                pos++;
        }

        // if whole grammar match spell, return true
        if(grammar[i][j]==-1 && pos==rightBound+1)
            return 1;
    }
    
    return 0;
}
