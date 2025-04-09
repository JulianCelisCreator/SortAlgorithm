#include <vector>
#include <stack>
#include <algorithm>
#include <cstdlib>
#include "Politico.cpp"
#include "ISortStrategy.cpp"

using namespace std;

/**
 * @class Quick
 * @brief Implementaci�n del algoritmo QuickSort iterativo para ordenar un vector de Politicos.
 *
 * Esta clase sigue la estrategia de ordenamiento definida por la interfaz ISortStrategy.
 * Utiliza una variante de QuickSort con optimizaci�n por pivote mediano de tres
 * y una pila para simular la recursividad.
 */

class Quick : public ISortStrategy {
public:

    /**
     * @brief Ordena un vector de pol�ticos en orden descendente seg�n el dinero robado.
     * @param arr Vector de objetos Politico a ordenar.
     * @return N�mero de iteraciones realizadas durante el ordenamiento.
     */

    double sortArreglo(vector<Politico>& arr) override {
        double iteraciones = 0;
        if (!arr.empty()) {
            iterativeQuickSort(arr, 0, arr.size() - 1, iteraciones);
        }
        return iteraciones;
    }

private:

    /**
     * @brief Particiona el arreglo alrededor de un pivote.
     *
     * Utiliza el m�todo del pivote "mediano de tres" y realiza la partici�n en orden descendente.
     * @param arr Vector de pol�ticos.
     * @param low �ndice inferior del subarreglo.
     * @param high �ndice superior del subarreglo.
     * @param iteraciones Contador de iteraciones (se incrementa dentro del m�todo).
     * @return �ndice final del pivote despu�s de la partici�n.
     */

    int partition(vector<Politico>& arr, int low, int high, double& iteraciones) {
        int mid = low + (high - low) / 2;

        if (arr[low].getDineroRobado() < arr[mid].getDineroRobado())
            swap(arr[low], arr[mid]);
        if (arr[low].getDineroRobado() < arr[high].getDineroRobado())
            swap(arr[low], arr[high]);
        if (arr[mid].getDineroRobado() < arr[high].getDineroRobado())
            swap(arr[mid], arr[high]);

        swap(arr[mid], arr[high - 1]);
        Politico pivot = arr[high - 1];

        int i = low;
        int j = high - 1;

        while (true) {
            iteraciones++;
            while (arr[++i].getDineroRobado() > pivot.getDineroRobado()) {}
            while (j > low && arr[--j].getDineroRobado() < pivot.getDineroRobado()) {}

            if (i >= j) break;
            swap(arr[i], arr[j]);
        }

        swap(arr[i], arr[high - 1]);
        return i;
    }

    /**
    * @brief Implementaci�n iterativa de QuickSort.
    *
    * Utiliza una pila para evitar la recursi�n directa y particiona el arreglo en orden descendente.
    * @param arr Vector de pol�ticos a ordenar.
    * @param low �ndice inicial del arreglo.
    * @param high �ndice final del arreglo.
    * @param iteraciones Contador de iteraciones que se va incrementando.
    */

    void iterativeQuickSort(vector<Politico>& arr, int low, int high, double& iteraciones) {
        stack<pair<int, int>> stack;
        stack.push(make_pair(low, high));

        while (!stack.empty()) {
            pair<int, int> current = stack.top();
            stack.pop();

            int currentLow = current.first;
            int currentHigh = current.second;

            if (currentLow >= currentHigh) continue;

            int pivotIdx = partition(arr, currentLow, currentHigh, iteraciones);

            // Push the larger subarray first to minimize stack size
            if (pivotIdx - currentLow > currentHigh - pivotIdx) {
                stack.push(make_pair(currentLow, pivotIdx - 1));
                stack.push(make_pair(pivotIdx + 1, currentHigh));
            }
            else {
                stack.push(make_pair(pivotIdx + 1, currentHigh));
                stack.push(make_pair(currentLow, pivotIdx - 1));
            }
        }
    }
};