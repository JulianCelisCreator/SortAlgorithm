package com.mycompany.sort.model.SortingStrategy;

import com.mycompany.sort.model.politico.Politico;

import java.util.Comparator;

/**
 * Interfaz que define el contrato para estrategias de ordenamiento aplicadas a arreglos de {@link Politico}.
 */
public interface SortingStrategy {

    /**
     * Ordena el arreglo de políticos utilizando un comparador específico.
     *
     * @param data       el arreglo de políticos a ordenar
     * @param comparator el comparador que define el criterio de ordenamiento
     * @return un {@link SortResult} que contiene información sobre el rendimiento del algoritmo
     */
    SortResult sort(Politico[] data, Comparator<Politico> comparator);

    /**
     * Devuelve el nombre del algoritmo de ordenamiento.
     *
     * @return nombre legible del algoritmo
     */
    String getName();
}
