package com.mycompany.sort.model.SortingStrategy;

import java.time.temporal.ChronoUnit;
import java.util.Comparator;
import java.util.Currency;

import com.mycompany.sort.model.politico.Politico;
public class MergeSortingStrategy implements SortingStrategy {
    private long iterations;

    @Override
    public SortResult sort(Politico[] arr, Comparator<Politico> comparator) {
        iterations = 0;
        long start = System.nanoTime();

        mergeSort(arr, 0, arr.length - 1, comparator);

        long end = System.nanoTime() - start;
        long elapsedMillis = end / 1_000_000; //
        return new SortResult(iterations, elapsedMillis);
    }

    private void mergeSort(Politico[] arr, int left, int right, Comparator<Politico> comparator) {
        if (left < right) {
            int mid = (left + right) / 2;

            mergeSort(arr, left, mid, comparator);
            mergeSort(arr, mid + 1, right, comparator);

            merge(arr, left, mid, right, comparator);
        }
    }

    private void merge(Politico[] arr, int left, int mid, int right, Comparator<Politico> comparator) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        Politico[] leftArr = new Politico[n1];
        Politico[] rightArr = new Politico[n2];

        System.arraycopy(arr, left, leftArr, 0, n1);
        System.arraycopy(arr, mid + 1, rightArr, 0, n2);

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            iterations++;
            if (comparator.compare(leftArr[i], rightArr[j]) <= 0) {
                arr[k++] = leftArr[i++];
            } else {
                arr[k++] = rightArr[j++];
            }
        }

        while (i < n1) {
            arr[k++] = leftArr[i++];
        }

        while (j < n2) {
            arr[k++] = rightArr[j++];
        }
    }

    @Override
    public String getName() {
        return "Merge Sorting"; // Nombre legible del algoritmo
    }
}
