#include <cstdio>

#include <algorithm>
using std::sort;


int binary_search(const int *array, int left, int right, const int number) {
	int middle;

	while(left <= right) {
		middle = (left + right) / 2;

		if(number == array[middle]) {
			while(number == array[middle -1]) middle--;
			return middle;
		} else {
			if(number < array[middle]) right = middle - 1;
   			if(number > array[middle]) left = middle + 1;
		}
 	}

	if(left > right)
		return -1;
}

int main(void) {
	int N, Q;
	int *marbles = new int[10000];
	int num_case = 0;

	while(scanf("%d %d", &N, &Q) == 2) {
		
		if(N + Q == 0)
			break;

		for(int i = 0; i < N; ++i)
			scanf("%d", &marbles[i]);
		
		sort(&marbles[0], &marbles[0] + N);

		printf("CASE# %d:\n", ++num_case);

		int target_num;

		for(int i = 0; i < Q; ++i) {
			scanf("%d", &target_num);

			int res = binary_search(marbles,0,N,target_num);

			if(res < 0)
				printf("%d not found\n", target_num);
			else
				printf("%d found at %d\n", target_num, res+1);
		}
	}

	return 0;
}
