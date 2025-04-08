package com.mycompany.sort.model.SortingStrategy;

import com.mycompany.sort.model.politico.Politico;

import java.util.Comparator;

public class SelectionSortingStrategy implements SortingStrategy {
    @Override
    public SortResult sort (Politico[] arr, Comparator<Politico> comparator){
        long iterations = 0;
        long start = System.nanoTime();
        int n = arr.length;
        for (int i = 0; i < n - 1; i++) {
            int minIndex = i;

            for (int j = i + 1; j < n; j++) {
                iterations++;
                if (comparator.compare(arr[j], arr[minIndex]) < 0) {
                    minIndex = j;
                }
            }

            // Intercambia el mínimo encontrado con la posición actual
            if (minIndex != i) {
                Politico temp = arr[i];
                arr[i] = arr[minIndex];
                arr[minIndex] = temp;
            }
        }
        long end = System.nanoTime() - start;
        long elapsedMillis = end / 1_000_000; //
        return new SortResult(iterations, elapsedMillis);
    }

    @Override
    public String getName() {
        return "Selection sort"; // Nombre legible del algoritmo
    }
}
