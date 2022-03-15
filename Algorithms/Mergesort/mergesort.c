
static void mergesort_helper(int array[], int temp[], int leftStart, int rightEnd);

static void merge(int array[], int temp[], int leftStart, int rightEnd);

void mergesort(int array[], int size) {
	int temp[size];
	mergesort_helper(array, temp, 0, size - 1);
}


static void mergesort_helper(int array[], int temp[], int leftStart, int rightEnd) {
	if (leftStart >= rightEnd) return;
	int midpoint = (leftStart + rightEnd) / 2;
	mergesort_helper(array, temp, leftStart, midpoint);	
	mergesort_helper(array, temp, midpoint + 1, rightEnd);	
	merge(array, temp, leftStart, rightEnd);
}

static void merge(int array[], int temp[], int leftStart, int rightEnd) {

	int leftEnd = (leftStart + rightEnd) / 2;
	int rightStart = leftEnd + 1;

	int left = leftStart;
	int right = rightStart;
	int currIndex = leftStart;

	while (left <= leftEnd && right <= rightEnd) {

		if (array[left] >= array[right]) {
			temp[currIndex] = array[left];
			left++;
		} else {
			temp[currIndex] = array[right];
			right++;
		}

		currIndex++;

	}

	while (right <= rightEnd) {
		temp[currIndex++] = array[right++];
	}

	while (left <= leftEnd) {
		temp[currIndex++] = array[left++];
	}

	while (leftStart <= rightEnd) {
		array[leftStart] = temp[leftStart];
		leftStart++;
	}

}
