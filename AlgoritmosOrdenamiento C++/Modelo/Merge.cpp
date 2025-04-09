#include <iostream>
#include <vector>
#include "Politico.cpp"
#include "ISortStrategy.cpp"
using namespace std;

/**
 * @class Merge
 * @brief Implementaci�n del algoritmo de ordenamiento Merge Sort de forma iterativa.
 *
 * Esta clase implementa ISortStrategy y proporciona una implementaci�n del algoritmo
 * Merge Sort iterativo para ordenar un vector de Politicos en orden
 * descendente seg�n el  dinero robado.
 */

class Merge : public ISortStrategy {
public:

    /**
     * @brief Ordena un vector de Politicos utilizando Merge Sort iterativo.
     *
     * @param arr Vector de Politicos a ordenar.
     * @return N�mero de iteraciones realizadas durante el ordenamiento.
     */

    double sortArreglo(vector<Politico>& arr) override {
        double iteraciones = 0;
        if (!arr.empty()) {
            iterativeMergeSort(arr, iteraciones);
        }
        return iteraciones;
    }

private:

    /**
     * @brief Implementaci�n iterativa del algoritmo Merge Sort.
     *
     * Divide el vector en subarrays de tama�o creciente y los combina ordenadamente.
     *
     * @param arr Vector de Politico a ordenar.
     * @param iteraciones realizadas en la funcion.
     */

    void iterativeMergeSort(vector<Politico>& arr, double& iteraciones) {
        int n = arr.size();
        vector<Politico> tempArr(n);

        // Comenzamos con subarrays de tama�o 1 y vamos duplicando
        for (int currSize = 1; currSize <= n - 1; currSize = 2 * currSize) {
            // Escogemos puntos de inicio de los subarrays
            for (int leftStart = 0; leftStart < n - 1; leftStart += 2 * currSize) {
                iteraciones++;

                // Encontramos los puntos finales de los subarrays
                int mid = min(leftStart + currSize - 1, n - 1);
                int rightEnd = min(leftStart + 2 * currSize - 1, n - 1);

                // Combinamos los subarrays arr[leftStart...mid] y arr[mid+1...rightEnd]
                merge(arr, tempArr, leftStart, mid, rightEnd, iteraciones);
            }
        }
    }

    /**
     * @brief Mezcla dos subarrays ordenados dentro del arreglo original.
     *
     * @param arr Vector original de Politicos.
     * @param tempArr Vector temporal usado para la combinaci�n.
     * @param left �ndice inicial del primer subarray.
     * @param mid �ndice final del primer subarray.
     * @param right �ndice final del segundo subarray.
     * @param Numero de iteraciones realizadas.
     */

    void merge(vector<Politico>& arr, vector<Politico>& tempArr,
        int left, int mid, int right, double& iteraciones) {
        int i = left;       // �ndice para el subarray izquierdo
        int j = mid + 1;    // �ndice para el subarray derecho
        int k = left;       // �ndice para el array temporal

        // Combinamos los subarrays ordenados
        while (i <= mid && j <= right) {
            iteraciones++;
            if (arr[i].getDineroRobado() >= arr[j].getDineroRobado()) {
                tempArr[k++] = arr[i++];
            }
            else {
                tempArr[k++] = arr[j++];
            }
        }

        // Copiamos los elementos restantes del subarray izquierdo
        while (i <= mid) {
            tempArr[k++] = arr[i++];
        }

        // Copiamos los elementos restantes del subarray derecho
        while (j <= right) {
            tempArr[k++] = arr[j++];
        }

        // Copiamos el array temporal de vuelta al original
        for (int l = left; l <= right; l++) {
            arr[l] = tempArr[l];
        }
    }
};