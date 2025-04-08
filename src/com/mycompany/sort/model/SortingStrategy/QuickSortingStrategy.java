package com.mycompany.sort.model.SortingStrategy;

import com.mycompany.sort.model.politico.Politico;
import java.util.Comparator;
import java.util.Stack;

public class QuickSortingStrategy implements SortingStrategy {
    private long iterations;

    @Override
    public SortResult sort(Politico[] arr, Comparator<Politico> comparator) {
        iterations = 0;
        long start = System.nanoTime();

        Stack<Integer> stack = new Stack<>();
        stack.push(0);
        stack.push(arr.length - 1);

        while (!stack.isEmpty()) {
            int high = stack.pop();
            int low = stack.pop();

            if (low < high) {
                int pivotIndex = partition(arr, low, high, comparator);

                stack.push(low);
                stack.push(pivotIndex - 1);
                stack.push(pivotIndex + 1);
                stack.push(high);
            }
        }

        long elapsedMillis = (System.nanoTime() - start) / 1_000_000;
        return new SortResult(iterations, elapsedMillis);
    }

    private int partition(Politico[] arr, int low, int high, Comparator<Politico> comparator) {
        // Paso 1: Selección de pivote con mediana de tres
        int mid = low + (high - low) / 2;

        // Ordenar low, mid, high
        if (comparator.compare(arr[low], arr[mid]) > 0) swap(arr, low, mid);
        if (comparator.compare(arr[low], arr[high]) > 0) swap(arr, low, high);
        if (comparator.compare(arr[mid], arr[high]) > 0) swap(arr, mid, high);

        // Mover el pivote (mediana) a la posición high
        swap(arr, mid, high);
        Politico pivot = arr[high];

        // Paso 2: Partición estándar
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
        return "Quick Sort";
    }
}