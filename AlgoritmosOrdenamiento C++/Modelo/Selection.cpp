#include <iostream>
#include <vector>
#include "Politico.cpp"
#include "ISortStrategy.cpp"

using namespace std;

/**
 * @class Selection
 * @brief Implementación del algoritmo de ordenamiento Selection Sort (modo descendente).
 *
 * Esta clase implementa el patrón de estrategia ISortStrategy para ordenar un vector de objetos
 * Politico de acuerdo al dinero robado, de mayor a menor.
 */

class Selection : public ISortStrategy {

public:

    /**
     * @brief Ordena un vector de políticos utilizando el algoritmo Selection Sort.
     *
     * El criterio de ordenamiento es el dinero robado, de mayor a menor.
     * Se realiza una búsqueda del máximo en cada iteración y se coloca en la posición correspondiente.
     *
     * @param arr Vector de objetos Politico a ordenar.
     * @return Número de iteraciones realizadas durante el ordenamiento.
     */

    double sortArreglo(vector<Politico>& arr) override {
        double iteraciones = 0;
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            int minIndex = i;
            for (int j = i + 1; j < n; j++) {
                iteraciones++;
                if (arr[j].getDineroRobado() > arr[minIndex].getDineroRobado()) {
                    minIndex = j;
                }
            }
            swap(arr[i], arr[minIndex]);
        }
        return iteraciones;
    }

};
