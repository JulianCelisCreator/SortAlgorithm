#include <iostream>
#include <algorithm> 
#include <vector>
#include <ctime>
#include "Politico.cpp"
#include "ISortMatrizStrategy.cpp"

/**
 * @class QuickMatriz
 * @brief Implementación del algoritmo QuickSort para ordenar filas de una matriz de Politicos.
 *
 * Esta clase implementa la interfaz ISortMatrizStrategy. Aplica QuickSort de forma recursiva
 * a cada fila de la matriz, ordenando los objetos Politico por edad (de menor a mayor).
 */

class QuickMatriz : public ISortMatrizStrategy {

private:

    /**
     * @brief Función de partición para QuickSort.
     *
     * Selecciona el primer elemento de la fila como pivote y reorganiza la fila
     * de modo que los elementos menores al pivote (según edad) queden a su izquierda,
     * y los mayores o iguales a su derecha.
     *
     * @param fila Vector de Politicos que representa una fila de la matriz.
     * @param inicio Índice de inicio del subarreglo a particionar.
     * @param fin Índice final del subarreglo a particionar.
     * @return Índice final del pivote después de la partición.
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
     * @brief Función recursiva de QuickSort.
     *
     * Ordena una fila de la matriz utilizando el algoritmo QuickSort basado en la edad del político.
     * @param fila Vector de Politicos a ordenar.
     * @param inicio Índice inicial del segmento a ordenar.
     * @param fin Índice final del segmento a ordenar.
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
     * @return Número total de iteraciones realizadas durante todo el proceso.
     */

    double sortMatriz(std::vector<std::vector<Politico>>& matriz) override {
        double iteraciones = 0;
        for (auto& fila : matriz) {
            quickSort(fila, 0, fila.size() - 1, iteraciones);
        }
        return iteraciones;
    }


};