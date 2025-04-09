#include <iostream>
#include <algorithm> 
#include <vector>
#include <ctime>
#include "Politico.cpp"
#include "ISortMatrizStrategy.cpp"


/**
 * @class MergeMatriz
 * @brief Implementaci�n del algoritmo de ordenamiento Merge Sort.
 *
 * Esta clase implementa ISortStrategy y proporciona una implementaci�n del algoritmo
 * Merge Sort para ordenar una matriz de Politicos en orden
 * ascendente seg�n la fecha de nacimiento.
 */

class MergeMatriz : public ISortMatrizStrategy {

private:

    /**
 * @brief Realiza la mezcla de dos subarrays ordenados de una fila.
 *
 * Combina dos mitades de una fila de Politicos, ordenadas por edad de forma ascendente,
 * en un �nico subarray ordenado dentro del arreglo original.
 *
 * @param fila Referencia a la fila del vector a ordenar.
 * @param inicio �ndice inicial del primer subarray.
 * @param mitad �ndice final del primer subarray.
 * @param final �ndice final del segundo subarray.
 * @param Numero de iteraciones realizadas.
 */

    void merge(vector<Politico>& fila, int inicio, int mitad, int final, double& iteraciones) {
        int i, j, k;
        int elementosIzq = mitad - inicio + 1;
        int elementosDer = final - mitad;

        vector<Politico> izquierda(elementosIzq);
        vector<Politico> derecha(elementosDer);

        for (int i = 0; i < elementosIzq; i++) {
            izquierda[i] = fila[inicio + i];
        }
        for (int j = 0; j < elementosDer; j++) {
            derecha[j] = fila[mitad + 1 + j];
        }

        i = 0;
        j = 0;
        k = inicio;

        while (i < elementosIzq && j < elementosDer) {
            iteraciones++;
            if (izquierda[i].calcularEdad() <= derecha[j].calcularEdad()) {
                fila[k] = izquierda[i];
                i++;
            }
            else {
                fila[k] = derecha[j];
                j++;
            }
            k++;
        }

        while (i < elementosIzq) {
            fila[k] = izquierda[i];
            i++;
            k++;
        }

        while (j < elementosDer) {
            fila[k] = derecha[j];
            j++;
            k++;
        }
    }

    /**
 * @brief Algoritmo recursivo Merge Sort aplicado sobre una fila de pol�ticos.
 *
 * Separa la fila en mitades recursivamente y luego
 * combina los subarrays ordenados usando el m�todo merge.
 *
 * @param fila Fila de pol�ticos a ordenar.
 * @param inicio �ndice inicial del subarray actual.
 * @param final �ndice final del subarray actual.
 * @param Numero de iteraciones realizadas.
 */

    void mergeSort(vector<Politico>& fila, int inicio, int final, double& iteraciones) {
        if (inicio < final) {
            iteraciones++;
            int mitad = inicio + (final - inicio) / 2;
            mergeSort(fila, inicio, mitad, iteraciones);
            mergeSort(fila, mitad + 1, final, iteraciones);
            merge(fila, inicio, mitad, final, iteraciones);
        }
    }

public:

    /**
 * @brief Ordena cada fila de una matriz de pol�ticos usando Merge Sort.
 *
 * Aplica el algoritmo mergeSort recursivo en cada fila de la matriz de Politicos,
 * ordenando cada una por edad de forma ascendente.
 *
 * @param matriz Matriz de Politicos a ordenar por filas.
 * @return N�mero total de iteraciones realizadas durante el ordenamiento.
 */

    double sortMatriz(std::vector<std::vector<Politico>>& matriz) override {
        double iteraciones = 0;
        for (auto& fila : matriz) {
            mergeSort(fila, 0, fila.size() - 1, iteraciones);
        }
        return iteraciones;
    }


};