#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int pages[4500];
	int nPrcsPages;
	int nPages;
	int i=0;
	int j=0;
	int k=0;
	int x;
	int entr = 0;
	char algo[10];
	int found;
	int flag;
	int fault = 0;
	int faultCnt = 0;
	int ptr = 0;
	
	for(i=0; i<4500; i++){
		pages[i] = 0;
	}
	
	scanf("%d", &nPrcsPages);
	int prcsPages[nPrcsPages];
	int cnt[nPrcsPages];
	
	scanf("%s", algo);
	
	i=0;
	for(i=0; i<nPrcsPages; i++){
		prcsPages[i] = 0;
		cnt[i] = 0;
	}
	
	i=0;
	while(1){
		scanf("%d", &x);
		if(x == -1){
			break;
		}
		pages[i] = x;
		i++;
	}
	nPages = i;
	
	if(strcasecmp(algo, "FIFO") == 0){
		printf("Replacement Policy = FIFO\n");
		printf("-------------------------------------\n");
		printf("Page   Content of Frames\n");
		printf("----   -----------------\n");
		i=0;
		while(i < nPages){
			found = 0;
			fault = 0;
			j = 0;
			while(found == 0 && j<nPrcsPages){
				if(prcsPages[j] == pages[i]){
					found = 1;
				}
				j++;
			}
			if(!found){
				fault = 1;
				entr++;
				faultCnt++;
				prcsPages[ptr] = pages[i];
				ptr++;
			}
			if(ptr == nPrcsPages){
				ptr = 0;
			}
			if(fault && entr > nPrcsPages){
				printf("%02d F   ", pages[i]);
			}
			else{
				printf("%02d     ", pages[i]);
			}
			k=0;
			while(k < nPrcsPages){
				if(prcsPages[k] == 0)
					break;
				printf("%02d ", prcsPages[k]);
				k++;
			}
			printf("\n");
			i++;
		}
		printf("-------------------------------------\n");
		printf("Number of page faults = %d\n", faultCnt-nPrcsPages);
	}
	
	else if(strcasecmp(algo, "LRU") == 0){
		printf("Replacement Policy = LRU\n");
		printf("-------------------------------------\n");
		printf("Page   Content of Frames\n");
		printf("----   -----------------\n");
		i=0;
		while(i < nPages){
			found = 0;
			fault = 0;
			j = 0;
			while(found == 0 && j<nPrcsPages){
				if(prcsPages[j] == pages[i]){
					found = 1;
				}
				j++;
			}
			if(!found){
				fault = 1;
				entr++;
				faultCnt++;
				j=0;
				flag = 0;
				for(j=0; j<nPrcsPages; j++){
					if(prcsPages[j] == 0){
						prcsPages[j] = pages[i];
						flag = 1;
						break;
					}
				}
				if(!flag){
					j=0;
					for(j=0; j<nPrcsPages; j++){
						k=i-1;
						for(k=i-1; k>=0; k--){
							if(pages[k] != prcsPages[j]){
								cnt[j]++;
							}
							else
								break;
						}
					}
					int max = cnt[0];
					int maxIndex = 0;
					j=0;
					for(j=0; j<nPrcsPages; j++){
						if(max < cnt[j]){
							max = cnt[j];
							maxIndex = j;
						}
					}
					j=0;
					for(j=0; j<nPrcsPages; j++){
						cnt[j] = 0;
					}
					prcsPages[maxIndex] = pages[i];
					
				}
			}
			if(fault && entr > nPrcsPages){
				printf("%02d F   ", pages[i]);
			}
			else{
				printf("%02d     ", pages[i]);
			}
			k=0;
			while(k < nPrcsPages){
				if(prcsPages[k] == 0)
					break;
				printf("%02d ", prcsPages[k]);
				k++;
			}
			printf("\n");
			i++;
		}
		printf("-------------------------------------\n");
		printf("Number of page faults = %d\n", faultCnt-nPrcsPages);
	}
	
	else if(strcasecmp(algo, "OPTIMAL") == 0){
		printf("Replacement Policy = OPTIMAL\n");
		printf("-------------------------------------\n");
		printf("Page   Content of Frames\n");
		printf("----   -----------------\n");
		i=0;
		while(i < nPages){
			found = 0;
			fault = 0;
			j = 0;
			while(found == 0 && j<nPrcsPages){
				if(prcsPages[j] == pages[i]){
					found = 1;
				}
				j++;
			}
			if(!found){
				fault = 1;
				entr++;
				faultCnt++;
				j=0;
				flag = 0;
				for(j=0; j<nPrcsPages; j++){
					if(prcsPages[j] == 0){
						prcsPages[j] = pages[i];
						flag = 1;
						break;
					}
				}
				if(!flag){
					j=0;
					for(j=0; j<nPrcsPages; j++){
						k=i+1;
						for(k=i+1; k<nPages; k++){
							if(pages[k] != prcsPages[j]){
								cnt[j]++;
							}
							else
								break;
						}
					}
					int max = cnt[0];
					int maxIndex = 0;
					j=0;
					for(j=0; j<nPrcsPages; j++){
						if(max < cnt[j]){
							max = cnt[j];
							maxIndex = j;
						}
					}
					j=0;
					for(j=0; j<nPrcsPages; j++){
						cnt[j] = 0;
					}
					prcsPages[maxIndex] = pages[i];
					
				}
			}
			if(fault && entr > nPrcsPages){
				printf("%02d F   ", pages[i]);
			}
			else{
				printf("%02d     ", pages[i]);
			}
			k=0;
			while(k < nPrcsPages){
				if(prcsPages[k] == 0)
					break;
				printf("%02d ", prcsPages[k]);
				k++;
			}
			printf("\n");
			i++;
		}
		printf("-------------------------------------\n");
		printf("Number of page faults = %d\n", faultCnt-nPrcsPages);
	}
	
	else{
		printf("Replacement Policy = CLOCK\n");
		printf("-------------------------------------\n");
		printf("Page   Content of Frames\n");
		printf("----   -----------------\n");
		int useBit[nPrcsPages];
		i=0;
		for(i=0; i<nPrcsPages; i++){
			useBit[i] = 0;
		}
		i=0;
		while(i < nPages){
			found = 0;
			fault = 0;
			j = 0;
			while(found == 0 && j<nPrcsPages){
				if(prcsPages[j] == pages[i]){
					found = 1;
					useBit[j] = 1;
				}
				j++;
			}
			if(!found){
				fault = 1;
				entr++;
				faultCnt++;
				j=0;
				flag = 0;
				for(j=0; j<nPrcsPages; j++){
					if(prcsPages[j] == 0){
						prcsPages[j] = pages[i];
						useBit[ptr] = 1;
						ptr++;
						flag = 1;
						if(ptr == nPrcsPages){
							ptr = 0;
						}
						break;
					}
				}
				if(!flag){
					while(1){
						if(useBit[ptr] == 0){
							prcsPages[ptr] = pages[i];
							useBit[ptr] = 1;
							ptr++;
							if(ptr == nPrcsPages){
								ptr = 0;
							}
							break;
						}
						else{
							useBit[ptr] = 0;
							ptr++;
							if(ptr == nPrcsPages){
								ptr = 0;
							}
						}
					}
				}
			}
			if(fault && entr > nPrcsPages){
				printf("%02d F   ", pages[i]);
			}
			else{
				printf("%02d     ", pages[i]);
			}
			k=0;
			while(k < nPrcsPages){
				if(prcsPages[k] == 0)
					break;
				printf("%02d ", prcsPages[k]);
				k++;
			}
			printf("\n");
			i++;
		}
		printf("-------------------------------------\n");
		printf("Number of page faults = %d\n", faultCnt-nPrcsPages);
	}
}
