package com.mycompany.sort.model.SortingStrategy;

import com.mycompany.sort.model.politico.Politico;

import java.util.Comparator;


public class QuickSortingStrategy implements SortingStrategy{
    private long iterations;

    @Override
    public SortResult sort(Politico[] arr, Comparator<Politico> comparator) {
        iterations = 0;
        long start = System.currentTimeMillis();

        quickSort(arr, 0, arr.length - 1, comparator);

        long end = System.currentTimeMillis();
        return new SortResult(iterations, end - start);
    }

    private void quickSort(Politico[] arr, int low, int high, Comparator<Politico> comparator) {
        if (low < high) {
            int pi = partition(arr, low, high, comparator);
            quickSort(arr, low, pi - 1, comparator);
            quickSort(arr, pi + 1, high, comparator);
        }
    }

    private int partition(Politico[] arr, int low, int high, Comparator<Politico> comparator) {
        Politico pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            iterations++;
            if (comparator.compare(arr[j], pivot) <= 0) {
                i++;
                swap(arr, i, j);
            }
        }

        swap(arr, i + 1, high);
        return i + 1;
    }

    private void swap(Politico[] arr, int i, int j) {
        Politico temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    @Override
    public String getName() {
        return "Quick Sorting"; // Nombre legible del algoritmo
    }
}
