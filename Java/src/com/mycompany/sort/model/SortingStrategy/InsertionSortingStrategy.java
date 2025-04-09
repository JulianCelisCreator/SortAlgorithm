package com.mycompany.sort.model.SortingStrategy;

import java.util.Comparator;

import com.mycompany.sort.model.politico.Politico;

/**
 * Implementación del algoritmo de ordenamiento Insertion Sort.
 * Este algoritmo construye el arreglo ordenado de izquierda a derecha,
 * insertando cada nuevo elemento en la posición correcta respecto a los anteriores.
 */
public class InsertionSortingStrategy implements SortingStrategy {

    /**
     * Ordena un arreglo de objetos {@link Politico} usando el algoritmo Insertion Sort
     * y un comparador definido por el usuario.
     *
     * @param arr         el arreglo de políticos a ordenar
     * @param comparator  el comparador que define el criterio de ordenamiento
     * @return objeto {@link SortResult} que contiene el número de iteraciones y el tiempo de ejecución
     */
    @Override
    public SortResult sort(Politico[] arr, Comparator<Politico> comparator) {
        long iterations = 0;
        double start = System.nanoTime();
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

            // Si salió del while sin entrar, igual cuenta como una comparación
            if (j >= 0) iterations++;

            arr[j + 1] = key;
        }

        double end = System.nanoTime() - start;
        double elapsedMillis = end / 1_000_000;

        return new SortResult(iterations, elapsedMillis);
    }

    /**
     * Devuelve el nombre legible del algoritmo de ordenamiento.
     *
     * @return el nombre "Insertion Sort"
     */
    @Override
    public String getName() {
        return "Insertion Sort";
    }
}
