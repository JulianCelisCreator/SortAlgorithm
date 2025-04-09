#include <iostream>
#include <algorithm> 
#include <vector>
#include <ctime>
#include "Politico.cpp"
#include "ISortMatrizStrategy.cpp"

/**
 * @class SelectionMatriz
 * @brief Implementaci�n del algoritmo Selection Sort para ordenar matrices de Politicos.
 *
 * Esta clase implementa la interfaz ISortMatrizStrategy y aplica el algoritmo Selection Sort
 * para ordenar cada fila de la matriz de pol�ticos en funci�n de su edad (de menor a mayor).
 */

class SelectionMatriz : public ISortMatrizStrategy {

    /**
     * @brief Ordena cada fila de una matriz de objetos Politico utilizando Selection Sort.
     *
     * El criterio de ordenamiento es la edad de los pol�ticos, de menor a mayor.
     * En cada fila, se busca al pol�tico m�s joven y se coloca al inicio,
     * repitiendo este proceso hasta ordenar la fila completa.
     *
     * @param matriz Matriz de pol�ticos, representada como un vector de vectores.
     * @return N�mero total de iteraciones realizadas durante el ordenamiento.
     */

    double sortMatriz(std::vector<std::vector<Politico>>& matriz) override {
        double iteraciones = 0;
        for (auto& fila : matriz) {
            int n = fila.size();
            for (int i = 0; i < n - 1; i++) {
                int minIndex = i;
                for (int j = i + 1; j < n; j++) {
                    iteraciones++;
                    if (fila[j].calcularEdad() < fila[minIndex].calcularEdad()) {
                        minIndex = j;
                    }
                }
                std::swap(fila[i], fila[minIndex]);
            }
        }
        return iteraciones;
    }


};