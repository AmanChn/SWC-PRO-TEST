int minMovesToEvenFollowedByOdd(vector<int> arr) {
	int res = 0, left = 0, right = arr.size() - 1;
	// two-pointer approach
	while(left < right) {
		if(arr[left] % 2 != 0) {
			while(right > left && arr[right] % 2 != 0) {
				// Find the first occurrence on the righthand side that can be swapped
				right--;
			}

			if(right > left) {
				// if we're already in the midpoint and the left pointer is odd then there is no swap
				res++;
				// handled this rightmost occurrence that was even => adjust to account for this
				right--;
			}
		}

		left++;
	}

	return res;
}