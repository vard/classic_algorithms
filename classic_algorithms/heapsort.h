/*
 * Heapsort:
 * - is optimal for time and space
 * - in-place, NlogN
 * - longer inner loop than quicksort's
 * - not stable
 * Heap construction takes <= 2N compares and exchanges
 * Heapsort uses <= 2NlgN compares and exchanges
 */

template <typename K>void exch(K* arr, int i, int j){
    K temp = arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
}

template <typename K>void sink(K* arr, int index, int size){
    while(2*index < size){
        int j = index*2;
        if((j < size-1) && (arr[j]<arr[j+1]))
            j++;
        if(arr[index]<arr[j]){
            exch(arr, index, j);
            index=j;
        } else {
            break;
        }
    }
}

template <typename K>void heapsort(K* arr, int size){
    for(int i = size/2; i > 0; i--){
        sink(arr, i, size);
    }

    while(size>1){
        exch(arr, 1, size-1);
        size--;
        sink(arr, 1, size);
    }

}