package com.mycompany.sort.controller;

import com.mycompany.sort.model.SortingStrategy.*;
import com.mycompany.sort.model.datachain.DataGeneratorChain;
import com.mycompany.sort.model.politico.Politico;
import com.mycompany.sort.model.politico.PoliticoComparator;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class SortingController {
    private final DataGeneratorChain dataGenerator;
    private final List<SortingStrategy> strategies;
    private final List<SortResult> results;

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

    public void runAnalysis(int initialSize, double growthFactor) {
        int currentSize = initialSize;
        try {
            while (true) {
                Politico[] data = dataGenerator.generateData("RANDOM", currentSize);
                for (SortingStrategy strategy : strategies) {
                    Politico[] copy = Arrays.copyOf(data, data.length);
                    SortResult result = strategy.sort(copy, PoliticoComparator.porDinero());
                    results.add(result);
                }
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

