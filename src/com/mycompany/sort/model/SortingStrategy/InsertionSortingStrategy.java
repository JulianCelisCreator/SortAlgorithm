package com.mycompany.sort.model.SortingStrategy;

import java.util.Comparator;

import com.mycompany.sort.model.politico.Politico;

public class InsertionSortingStrategy implements SortingStrategy{
    @Override
    public SortResult sort(Politico[] arr, Comparator<Politico> comparator) {
        long iterations = 0;
        long start = System.nanoTime();
        int n = arr.length;
        for (int i = 1; i < n; i++) {
            Politico key = arr[i];
            int j = i - 1;

            // Mueve los elementos mayores que key una posición adelante
            while (j >= 0 && comparator.compare(arr[j], key) > 0) {
                iterations++;
                arr[j + 1] = arr[j];
                j--;
            }

            // Si salió del while sin entrar, igual se cuenta como una iteración de comparación
            if (j >= 0) iterations++;

            arr[j + 1] = key;
        }
        long end = System.nanoTime() - start;
        long elapsedMillis = end / 1_000_000; //
        return new SortResult(iterations, elapsedMillis);
    }

    @Override
    public String getName() {
        return "Insertion Sort"; // Nombre legible del algoritmo
    }
}
