#include <stdio.h>
int coins, coin[5], charge, amount[5];

int main()
{
	int i;
	
	scanf("%d", &coins);

	for (i=0; i<coins; i++)
		scanf("%d", &coin[i]);
	
	scanf("%d", &charge);
		
	Find(0);
}

void Find(int now)
{
	int i, buffer;
	
	if (charge == 0) {
		printf("(");
		for (i=0; i<coins; i++) {
			if (i>0)
				printf(",");
			printf("%d", amount[i]);
		}
		printf(")\n");
	}
	
	if (now == coins)
		return;
	
	if (charge < coin[now])
		return;
	
	buffer = charge/coin[now];
	
	for (i=0; i<=buffer; i++) {
		amount[now] = i;
		charge -= (i*coin[now]);
		Find(now+1);
		amount[now] = 0;
		charge += (i*coin[now]);
	}
}
