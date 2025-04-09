#include <iostream>
#include <algorithm> 
#include <vector>
#include <ctime>
#include "Politico.cpp"
#include "ISortMatrizStrategy.cpp"

/**
 * @class QuickMatriz
 * @brief Implementaci�n del algoritmo QuickSort para ordenar filas de una matriz de Politicos.
 *
 * Esta clase implementa la interfaz ISortMatrizStrategy. Aplica QuickSort de forma recursiva
 * a cada fila de la matriz, ordenando los objetos Politico por edad (de menor a mayor).
 */

class QuickMatriz : public ISortMatrizStrategy {

private:

    /**
     * @brief Funci�n de partici�n para QuickSort.
     *
     * Selecciona el primer elemento de la fila como pivote y reorganiza la fila
     * de modo que los elementos menores al pivote (seg�n edad) queden a su izquierda,
     * y los mayores o iguales a su derecha.
     *
     * @param fila Vector de Politicos que representa una fila de la matriz.
     * @param inicio �ndice de inicio del subarreglo a particionar.
     * @param fin �ndice final del subarreglo a particionar.
     * @return �ndice final del pivote despu�s de la partici�n.
     */

    int particion(std::vector<Politico>& fila, int inicio, int fin) {
        Politico pivote = fila[inicio];
        int i = inicio + 1;
        for (int j = i; j <= fin; j++) {
            if (fila[j].calcularEdad() < pivote.calcularEdad()) {
                swap(fila[i], fila[j]);
                i++;
            }
        }
        swap(fila[inicio], fila[i - 1]);
        return i - 1;
    }

    /**
     * @brief Funci�n recursiva de QuickSort.
     *
     * Ordena una fila de la matriz utilizando el algoritmo QuickSort basado en la edad del pol�tico.
     * @param fila Vector de Politicos a ordenar.
     * @param inicio �ndice inicial del segmento a ordenar.
     * @param fin �ndice final del segmento a ordenar.
     * @param Numero de iteraciones realizadas.
     */

    void quickSort(std::vector<Politico>& fila, int inicio, int fin, double& iteraciones) {
        if (inicio < fin) {
            iteraciones++;
            int pivote = particion(fila, inicio, fin);
            quickSort(fila, inicio, pivote - 1, iteraciones);
            quickSort(fila, pivote + 1, fin, iteraciones);
        }
    }

public:

    /**
     * @brief Ordena cada fila de una matriz de Politicos usando QuickSort.
     *
     * Aplica el algoritmo de ordenamiento QuickSort sobre cada fila individualmente,
     * ordenando por edad (de menor a mayor).
     *
     * @param matriz Matriz de Politicos a ordenar.
     * @return N�mero total de iteraciones realizadas durante todo el proceso.
     */

    double sortMatriz(std::vector<std::vector<Politico>>& matriz) override {
        double iteraciones = 0;
        for (auto& fila : matriz) {
            quickSort(fila, 0, fila.size() - 1, iteraciones);
        }
        return iteraciones;
    }


};