package com.mycompany.sort.controller;

import com.mycompany.sort.controller.accumulator.AccumulatorKey;
import com.mycompany.sort.controller.accumulator.AccumulatorValue;
import com.mycompany.sort.model.SortingStrategy.*;
import com.mycompany.sort.model.datachain.DataGeneratorChain;
import com.mycompany.sort.model.matrix.MatrixOrganizer;
import com.mycompany.sort.model.politico.Politico;
import com.mycompany.sort.model.politico.PoliticoComparator;
import com.mycompany.sort.model.SortingStrategy.SortResult;

import java.util.Arrays;
import java.util.ArrayList;
import java.util.List;
import java.util.HashMap;
import java.util.Map;

public class SortingController {
    private final DataGeneratorChain dataGenerator;
    private final List<SortingStrategy> strategies;
    private final List<SortResult> results;
    private final MatrixOrganizer matrixOrganizer;
    private final Map<AccumulatorKey, AccumulatorValue> accumulator;

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
        this.accumulator = new HashMap<>();
        setupShutdownHook();
    }

    private void setupShutdownHook() {
        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
            displayAccumulatedResults();
        }));
    }

    public void runAnalysis(int initialSize, double growthFactor) {
        List<String> dataCases = List.of("SORTED", "INVERSE", "RANDOM");
        int currentSize = initialSize;

        try {
            while (true) {
                System.out.println("\n===== TAMAÑO ACTUAL: " + currentSize + " =====");

                for (String dataCase : dataCases) {
                    System.out.println("\n=== CASO: " + dataCase + " ===");
                    Politico[] data = dataGenerator.generateData(dataCase, currentSize);

                    analyzeArrayResults(data, currentSize, dataCase);
                    analyzeMatrixResults(data, currentSize, dataCase);
                }

                currentSize = (int) (currentSize * growthFactor);
            }
        } catch (OutOfMemoryError e) {
            System.out.println("Memoria llena en tamaño: " + currentSize);
            displayAccumulatedResults();
        }
    }

    private void analyzeArrayResults(Politico[] data, int size, String dataCase) {
        System.out.println("\n[RESULTADOS DE ARRAYS]");
        for (SortingStrategy strategy : strategies) {
            try {
                Politico[] copy = Arrays.copyOf(data, data.length);
                SortResult result = strategy.sort(copy, PoliticoComparator.porDinero())
                        .withContext("ARRAY", size, strategy.getName());

                results.add(result);
                updateAccumulator(dataCase, "ARRAY", strategy.getName(), result);
                printResult("[Array]", strategy.getName(), result);

            } catch (OutOfMemoryError e) {
                System.out.println("Memoria insuficiente para array en: " + strategy.getName());
            }
        }
    }

    private void analyzeMatrixResults(Politico[] data, int size, String dataCase) {
        System.out.println("\n[RESULTADOS DE MATRICES]");
        for (SortingStrategy strategy : strategies) {
            try {
                Politico[] sortedByMoney = Arrays.copyOf(data, data.length);
                SortResult moneySortResult = strategy.sort(sortedByMoney, PoliticoComparator.porDinero());

                int rows = calculateRows(size);
                int cols = calculateColumns(size, rows);

                SortResult matrixResult = matrixOrganizer.organizeMatrix(sortedByMoney, rows, cols, strategy);

                SortResult combinedResult = new SortResult(
                        "MATRIX",
                        size,
                        strategy.getName(),
                        moneySortResult.getIterations() + matrixResult.getIterations(),
                        moneySortResult.getTimeElapsedMillis() + matrixResult.getTimeElapsedMillis()
                );

                results.add(combinedResult);
                updateAccumulator(dataCase, "MATRIX", strategy.getName(), combinedResult);
                printResult("[Matriz]", strategy.getName(), combinedResult);

            } catch (OutOfMemoryError e) {
                System.out.println("Memoria insuficiente para matriz en: " + strategy.getName());
            }
        }
    }

    private int calculateRows(int size) {
        return Math.max(1, (int) Math.ceil(Math.sqrt(size)));
    }

    private int calculateColumns(int size, int rows) {
        return (int) Math.ceil((double) size / rows);
    }

    private void updateAccumulator(String dataCase, String dataType, String strategyName, SortResult result) {
        AccumulatorKey key = new AccumulatorKey(dataCase, dataType, strategyName);
        accumulator.compute(key, (k, v) -> {
            if (v == null) {
                v = new AccumulatorValue();
            }
            v.add(result.getIterations(), result.getTimeElapsedMillis());
            return v;
        });
    }

    private void displayAccumulatedResults() {
        System.out.println("\n=== Resultados Acumulados por Caso, Tipo y Estrategia ===");
        for (Map.Entry<AccumulatorKey, AccumulatorValue> entry : accumulator.entrySet()) {
            AccumulatorKey key = entry.getKey();
            AccumulatorValue value = entry.getValue();
            System.out.printf(
                    "Caso: %-7s Tipo: %-6s Estrategia: %-18s | Iteraciones Promedio: %10.2f | Tiempo Promedio: %10.2f ms%n",
                    key.dataCase(),
                    key.dataType(),
                    key.strategyName(),
                    value.getAverageIterations(),
                    value.getAverageTime()
            );
        }
    }

    public Map<String, Map<String, AccumulatorValue>> getAccumulatedResults(String dataType) {
        Map<String, Map<String, AccumulatorValue>> results = new HashMap<>();

        for (Map.Entry<AccumulatorKey, AccumulatorValue> entry : accumulator.entrySet()) {
            AccumulatorKey key = entry.getKey();
            if (key.dataType().equals(dataType)) {
                results.computeIfAbsent(key.dataCase(), k -> new HashMap<>())
                        .put(key.strategyName(), entry.getValue());
            }
        }
        return results;
    }

    public List<SortingStrategy> getStrategies() {
        return strategies;
    }

    private void printResult(String type, String strategyName, SortResult result) {
        System.out.printf(
                "%-8s %-15s | Tamaño: %,6d | Iteraciones: %,9d | Tiempo: %s%n",
                type,
                strategyName,
                result.getSize(),
                result.getIterations(),
                result.getFormattedTime()
        );
    }
}