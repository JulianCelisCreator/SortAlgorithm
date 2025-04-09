package com.mycompany.sort.model.matrix;

import com.mycompany.sort.model.SortingStrategy.SortResult;
import com.mycompany.sort.model.SortingStrategy.SortingStrategy;
import com.mycompany.sort.model.politico.Politico;
import com.mycompany.sort.model.politico.PoliticoComparator;

import java.util.Arrays;

public class MatrixOrganizer {
    public SortResult organizeMatrix(Politico[] data, int rows, int cols, SortingStrategy strategy) {
        // 1. Copiar el array para no modificar el original (ya está ordenado por dinero)
        Politico[] copy = Arrays.copyOf(data, data.length);

        // 2. Crear matriz
        Politico[][] matrix = createMatrix(copy, rows, cols);

        // 3. Ordenar filas por edad y acumular métricas
        long totalIterations = 0;
        long totalTime = 0;

        for (Politico[] fila : matrix) {
            SortResult rowResult = strategy.sort(fila, PoliticoComparator.porEdad());
            totalIterations += rowResult.getIterations();
            totalTime += rowResult.getTimeElapsedMillis();
        }

        return new SortResult("MATRIX", data.length, strategy.getName(), totalIterations, totalTime);
    }

    public Politico[][] createMatrix(Politico[] data, int rows, int cols) {
        Politico[][] matrix = new Politico[rows][cols];
        int index = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = (index < data.length)
                        ? data[index++]
                        : data[data.length - 1];
            }
        }
        return matrix;
    }
}