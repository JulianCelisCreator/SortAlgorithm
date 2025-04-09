#include <iostream>
#include <vector>
#include "Politico.cpp"
#include "ISortStrategy.cpp"

using namespace std;

/**
 * @class Selection
 * @brief Implementaci�n del algoritmo de ordenamiento Selection Sort (modo descendente).
 *
 * Esta clase implementa el patr�n de estrategia ISortStrategy para ordenar un vector de objetos
 * Politico de acuerdo al dinero robado, de mayor a menor.
 */

class Selection : public ISortStrategy {

public:

    /**
     * @brief Ordena un vector de pol�ticos utilizando el algoritmo Selection Sort.
     *
     * El criterio de ordenamiento es el dinero robado, de mayor a menor.
     * Se realiza una b�squeda del m�ximo en cada iteraci�n y se coloca en la posici�n correspondiente.
     *
     * @param arr Vector de objetos Politico a ordenar.
     * @return N�mero de iteraciones realizadas durante el ordenamiento.
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
