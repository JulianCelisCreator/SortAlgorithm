package com.mycompany.sort.controller;

import com.mycompany.sort.model.SortingStrategy.*;
import com.mycompany.sort.model.datachain.DataGeneratorChain;
import com.mycompany.sort.model.matrix.MatrixOrganizer;
import com.mycompany.sort.model.politico.Politico;
import com.mycompany.sort.model.politico.PoliticoComparator;
import com.mycompany.sort.model.SortingStrategy.SortResult;

import java.util.Arrays;
import java.util.ArrayList;
import java.util.List;

public class SortingController {
    private final DataGeneratorChain dataGenerator;
    private final List<SortingStrategy> strategies;
    private final List<SortResult> results;
    private final MatrixOrganizer matrixOrganizer;

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
        this.matrixOrganizer = new MatrixOrganizer();
    }

    public void runAnalysis(int initialSize, double growthFactor) {
        List<String> dataCases = List.of("SORTED", "INVERSE", "PARTIAL");
        for (String dataCase : dataCases) {
            analyzeDataCase(dataCase, initialSize, growthFactor);
        }
    }

    private void analyzeDataCase(String dataCase, int initialSize, double growthFactor) {
        int currentSize = initialSize;
        try {
            while (true) {
                Politico[] data = dataGenerator.generateData(dataCase, currentSize);
                System.out.println("\n=== CASO: " + dataCase + " - TAMAÑO: " + currentSize + " ===");

                analyzeArrayResults(data, currentSize);
                analyzeMatrixResults(data, currentSize);

                currentSize = (int) (currentSize * growthFactor);
            }
        } catch (OutOfMemoryError e) {
            System.out.println("Memoria llena en tamaño: " + currentSize + " para caso: " + dataCase);
        }
    }

    private void analyzeArrayResults(Politico[] data, int size) {
        System.out.println("\n[RESULTADOS DE ARRAYS]");
        for (SortingStrategy strategy : strategies) {
            try {
                Politico[] copy = Arrays.copyOf(data, data.length);
                SortResult result = strategy.sort(copy, PoliticoComparator.porDinero())
                        .withContext("ARRAY", size, strategy.getName());

                results.add(result);
                printResult("[Array]", strategy.getName(), result);

            } catch (OutOfMemoryError e) {
                System.out.println("Memoria insuficiente para array en: " + strategy.getName());
            }
        }
    }

    private void analyzeMatrixResults(Politico[] data, int size) {
        System.out.println("\n[RESULTADOS DE MATRICES]");
        for (SortingStrategy strategy : strategies) {
            try {
                // 1. Ordenar por dinero
                Politico[] sortedByMoney = Arrays.copyOf(data, data.length);
                SortResult moneySortResult = strategy.sort(sortedByMoney, PoliticoComparator.porDinero());

                // 2. Crear y ordenar matriz
                int rows = calculateRows(size);
                int cols = calculateColumns(size, rows);
                SortResult matrixResult = matrixOrganizer.organizeMatrix(sortedByMoney, rows, cols, strategy);

                // 3. Combinar resultados
                SortResult combinedResult = new SortResult(
                        "MATRIX",
                        size,
                        strategy.getName(),
                        moneySortResult.getIterations() + matrixResult.getIterations(),
                        moneySortResult.getTimeElapsedMillis() + matrixResult.getTimeElapsedMillis()
                );

                results.add(combinedResult);
                printResult("[Matriz]", strategy.getName(), combinedResult);

            } catch (OutOfMemoryError e) {
                System.out.println("Memoria insuficiente para matriz en: " + strategy.getName());
            }
        }
    }

    private int calculateRows(int size) {
        return Math.max(1, (int) Math.sqrt(size));
    }

    private int calculateColumns(int size, int rows) {
        return rows > 0 ? (int) Math.ceil((double) size / rows) : 0;
    }

    private void printResult(String type, String strategyName, SortResult result) {
        System.out.printf("%-8s %-15s | Tamaño: %,6d | Iteraciones: %,9d | Tiempo: %s%n",
                type,
                strategyName,
                result.getSize(),
                result.getIterations(),
                result.getFormattedTime());
    }

    public void exportResultsToPDF() {
        // Implementación pendiente
    }
}