package com.mycompany.sort.model.matrix;

import com.mycompany.sort.model.politico.Politico;
import com.mycompany.sort.model.politico.PoliticoComparator;

import java.util.Arrays;

public class MatrixOrganizer {
    public Politico[][] createMatrix(Politico[] data, int rows, int cols) {
        Politico[][] matrix = new Politico[rows][cols];

        // 1. Ordenar el array por dinero (de menor a mayor)
        Arrays.sort(data, PoliticoComparator.porDinero());

        // 2. Distribuir los elementos ordenados en la matriz
        int index = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (index < data.length) {
                    matrix[i][j] = data[index++];
                } else {
                    matrix[i][j] = null; // Manejar caso si data es más pequeño que la matriz
                }
            }
        }

        // 3. Ordenar cada fila por edad (de más joven a más viejo)
        for (int i = 0; i < rows; i++) {
            Arrays.sort(matrix[i], PoliticoComparator.porEdad());
        }

        return matrix;
    }
}