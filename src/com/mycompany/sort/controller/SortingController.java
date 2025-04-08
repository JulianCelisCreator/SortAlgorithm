package com.mycompany.sort.controller;

import com.mycompany.sort.model.SortingStrategy.*;
import com.mycompany.sort.model.datachain.DataGeneratorChain;
import com.mycompany.sort.model.politico.Politico;
import com.mycompany.sort.model.politico.PoliticoComparator;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Controlador encargado de dirigir los procesos internos
 * de ordenamiento en listas y matrices
 */
public class SortingController {
    private final DataGeneratorChain dataGenerator;
    private final List<SortingStrategy> strategies;
    private final List<SortResult> results;

    /**
     * Constructor del controlador de ordenamient
     * Instancia cadena para generar datos
     * Instancia estrategias en una lista
     */
    public SortingController() {
        this.dataGenerator = new DataGeneratorChain();
        this.strategies = List.of(
                new BubbleSortingStrategy(),
                new SelectionSortingStrategy(),
                new InsertionSortingStrategy(),
                new MergeSortingStrategy(),
                new QuickSortingStrategy()
        );
        this.results = new ArrayList<>();
    }

    /**
     *
     * Método que ejecuta el analisis del algoritmo
     * @param initialSize Población inicial
     * @param growthFactor Factor de crecimiento de la población
     */
    public void runAnalysis(int initialSize, double growthFactor) {
        int currentSize = initialSize;
        try {
            while (true) {
                Politico[] data = dataGenerator.generateData("RANDOM", currentSize);
                System.out.println("Tamaño: " + currentSize);
                for (SortingStrategy strategy : strategies) {
                    Politico[] copy = Arrays.copyOf(data, data.length);
                    SortResult result = strategy.sort(copy, PoliticoComparator.porDinero());
                    results.add(result);
                    System.out.println(strategy.getClass().getSimpleName() + " -> " +
                            "Iteraciones: " + result.getIterations() + ", Tiempo: " + result.getTimeElapsedMinutes() + "s");
                }
                System.out.println("-------------");
                currentSize = (int) (currentSize * growthFactor);
            }
        } catch (OutOfMemoryError e) {
            System.out.println("Memoria llena en tamaño: " + currentSize);
        }
    }


    public void exportResultsToPDF() {
        // Implementación usando iText o similar
    }
}

