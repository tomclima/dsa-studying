#include <stdio.h>

int main()
{
	int n_chocolates;
	
	scanf("%d", &n_chocolates);
	
	int chocolate_prices[n_chocolates];
	
	for(int i = 0; i < n_chocolates; i++){
		scanf("%d", &chocolate_prices[i]);

	}
	for(int i = 0; i < n_chocolates; i++){
		printf("%d", chocolate_prices[i]);
	}
}
