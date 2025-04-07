package com.mycompany.sort.model;

import java.util.Comparator;

public class BubbleSortingStrategy implements SortingStrategy {
    @Override
    public SortResult sort(Politico[] arr, Comparator<Politico> comparator) {
        int iterations = 0;
        long start = System.nanoTime();
        boolean changed;
        int n = arr.length;
        for (int i = 0; i < n - 1; i++) {
            changed = false;
            for (int j = 0; j < n - i; j++) {
                iterations++;
                if (comparator.compare(arr[j], arr[j + 1]) > 0) {
                    // Intercambiar arr[j] y arr[j+1]
                    Politico temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                    changed = true;
                }
                if(!changed) {
                    break;
                }
            }
        }
        long end = System.nanoTime();
        return new SortResult(iterations, end - start);
    }
}
