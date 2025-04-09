#include <iostream>
#include <vector>
#include "Politico.cpp"
#include "ISortStrategy.cpp"

using namespace std;

/**
 * @class Sorter
 * @brief Contexto que permite aplicar diferentes estrategias de ordenamiento a un arreglo de Politicos.
 *
 * Esta clase actúa como un contenedor del patrón Strategy. Permite cambiar dinámicamente el algoritmo de ordenamiento
 * que se aplicará a un arreglo de Politicos.
 */

class Sorter {
private:

    /// Estrategia actual de ordenamiento a usar.
    ISortStrategy* strategy;
public:

    /**
     * @brief Constructor que recibe una estrategia de ordenamiento.
     * @param strat Puntero a una implementación concreta de ISortMatrizStrategy.
     */

    Sorter(ISortStrategy* strat) : strategy(strat) {}

    /**
     * @brief Establece una nueva estrategia de ordenamiento para usar.
     * @param strat Puntero a una nueva implementación de ISortMatrizStrategy.
     */

    void setStrategy(ISortStrategy* strat) {
        strategy = strat;
    }

    /**
     * @brief Ordena la matriz de Politicos usando la estrategia actual.
     *
     * @param arr Arreglo de Politicos que se desea ordenar.
     * @return Numero de iteraciones realizadas por el algoritmo de ordenamiento.
     */

    double executeSort(vector<Politico>& arr) {
        double iteraciones = strategy->sortArreglo(arr);
        return iteraciones;
    }
};
