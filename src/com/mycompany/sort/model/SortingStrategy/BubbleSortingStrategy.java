package com.mycompany.sort.model.SortingStrategy;

import com.mycompany.sort.model.politico.Politico;

import java.util.Comparator;
import java.util.Timer;

public class BubbleSortingStrategy implements SortingStrategy {
    @Override
    public SortResult sort(Politico[] arr, Comparator<Politico> comparator) {
        long iterations = 0;
        long start = System.nanoTime();
        boolean swapped;
        int n = arr.length;

        for (int i = 0; i < n-1; i++) {
            swapped = false;
            for (int j = 0; j < n-i-1; j++) { // Corrección aquí
                iterations++;
                if (comparator.compare(arr[j], arr[j+1]) > 0) {
                    Politico temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                    swapped = true;
                }
            }
            if (!swapped) break; // Mover fuera del bucle interno
        }
        long end = System.nanoTime() - start;
        long elapsedMillis = end / 1_000_000; //
        return new SortResult(iterations, elapsedMillis);
    }

    @Override
    public String getName() {
        return "Bubble Sort"; // Nombre legible del algoritmo
    }
}

