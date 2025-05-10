package com.mycompany.sort.model.SortingStrategy;

import com.mycompany.sort.model.politico.Politico;

import java.util.Comparator;

/**
 * Implementación del algoritmo de ordenamiento Bubble Sort.
 * Este algoritmo compara pares adyacentes y los intercambia si están en el orden incorrecto,
 * repitiendo el proceso hasta que la lista esté ordenada.
 */
public class BubbleSortingStrategy implements SortingStrategy {

    /**
     * Ordena un arreglo de objetos {@link Politico} usando el algoritmo Bubble Sort
     * y un comparador específico.
     *
     * @param arr         el arreglo de políticos a ordenar
     * @param comparator  el comparador que define el criterio de ordenamiento
     * @return objeto {@link SortResult} con estadísticas del proceso (iteraciones y tiempo)
     */
    @Override
    public SortResult sort(Politico[] arr, Comparator<Politico> comparator) {
        long iterations = 0;
        double start = System.nanoTime();
        boolean swapped;
        int n = arr.length;

        for (int i = 0; i < n - 1; i++) {
            swapped = false;
            for (int j = 0; j < n - i - 1; j++) {
                iterations++;
                if (comparator.compare(arr[j], arr[j + 1]) > 0) {
                    Politico temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                    swapped = true;
                }
            }
            if (!swapped) break; // Optimización: si no hubo intercambios, ya está ordenado
        }

        double elapsedMillis = (System.nanoTime() - start) / 1_000_000;

        return new SortResult(iterations, elapsedMillis);
    }

    /**
     * Devuelve el nombre legible del algoritmo de ordenamiento.
     *
     * @return nombre del algoritmo ("Bubble Sort")
     */
    @Override
    public String getName() {
        return "Bubble Sort";
    }
}