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

        // Versión iterativa usando pila
        Stack<Integer> stack = new Stack<>();
        stack.push(0);
        stack.push(arr.length - 1);

        while (!stack.isEmpty()) {
            int high = stack.pop();
            int low = stack.pop();

            if (low < high) {
                int pivotIndex = partition(arr, low, high, comparator);

                // Subarray izquierdo
                stack.push(low);
                stack.push(pivotIndex - 1);

                // Subarray derecho
                stack.push(pivotIndex + 1);
                stack.push(high);
            }
        }

        long elapsedMillis = (System.nanoTime() - start) / 1_000_000;
        return new SortResult(iterations, elapsedMillis);
    }

    private int partition(Politico[] arr, int low, int high, Comparator<Politico> comparator) {
        Politico pivot = arr[high]; // Pivote en último elemento
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