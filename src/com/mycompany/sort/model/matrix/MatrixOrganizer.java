package com.mycompany.sort.model.matrix;

import com.mycompany.sort.model.SortingStrategy.SortResult;
import com.mycompany.sort.model.SortingStrategy.SortingStrategy;
import com.mycompany.sort.model.politico.Politico;
import com.mycompany.sort.model.politico.PoliticoComparator;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;

public class MatrixOrganizer {

    // Método actualizado para recibir filas y columnas
    public SortResult organizeMatrix(
            Politico[] data,
            int rows,
            int cols,
            SortingStrategy strategy
    ) {
        // 1. Ordenar el array original por dinero
        SortResult moneySortResult = strategy.sort(data, PoliticoComparator.porDinero());

        // 2. Crear matriz con las dimensiones especificadas
        Politico[][] matrix = createMatrix(data, rows, cols);

        // 3. Ordenar cada fila por edad y acumular métricas
        long totalIterations = moneySortResult.getIterations();
        long totalTime = moneySortResult.getTimeElapsedMillis();

        for(Politico[] fila : matrix) {
            SortResult rowResult = strategy.sort(fila, PoliticoComparator.porEdad());
            totalIterations += rowResult.getIterations();
            totalTime += rowResult.getTimeElapsedMillis();
        }

        return new SortResult(
                "MATRIX",
                data.length,
                strategy.getName(),
                totalIterations,
                totalTime
        );
    }

    public Politico[][] createMatrix(Politico[] data, int rows, int cols) {
        Politico[][] matrix = new Politico[rows][cols];
        int index = 0;

        // Rellenar con copias de los últimos elementos si es necesario
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = (index < data.length)
                        ? data[index++]
                        : data[data.length - 1]; // Repetir último elemento
            }
        }
        return matrix;
    }
}
