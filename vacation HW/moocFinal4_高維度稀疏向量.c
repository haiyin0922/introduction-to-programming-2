#include <stdio.h>

int main ()
{
	int i, j, k, l;
	int sum = 0;
	int dim1[100000], value1[100000], dim2[100000], value2[100000];
	
	for(i=0; ; i++){
		scanf("%d:%d", &dim1[i], &value1[i]);
		if(dim1[i]==0 && value1[i]==0) break;
	}
	
	for(j=0; ; j++){
		scanf("%d:%d", &dim2[j], &value2[j]);
		if(dim2[j]==0 && value2[j]==0) break;
	}
	 
	for(k=0; k<=i; k++){
		for(l=0; l<=j; l++){
			if(dim1[k]==dim2[l])
				sum += value1[k]*value2[l];
		}
	}
	
	printf("%d\n", sum);
	
	return 0;
}
