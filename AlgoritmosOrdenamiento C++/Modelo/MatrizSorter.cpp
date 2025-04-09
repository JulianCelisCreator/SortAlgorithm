#include <iostream>
#include <vector>
#include "Politico.cpp"
#include "ISortMatrizStrategy.cpp"

using namespace std;

/**
 * @class MatrizSorter
 * @brief Contexto que permite aplicar diferentes estrategias de ordenamiento a una matriz de Politico.
 *
 * Esta clase act�a como un contenedor del patr�n Strategy. Permite cambiar din�micamente el algoritmo de ordenamiento
 * que se aplicar� a una matriz de Politicos.
 */

class MatrizSorter {
private:

    /// Estrategia actual de ordenamiento a usar.
    ISortMatrizStrategy* strategy;
public:

    /**
     * @brief Constructor que recibe una estrategia de ordenamiento.
     * @param strat Puntero a una implementaci�n concreta de ISortMatrizStrategy.
     */

    MatrizSorter(ISortMatrizStrategy* strat) : strategy(strat) {}

    /**
     * @brief Establece una nueva estrategia de ordenamiento para usar.
     * @param strat Puntero a una nueva implementaci�n de ISortMatrizStrategy.
     */

    void setStrategy(ISortMatrizStrategy* strat) {
        strategy = strat;
    }

    /**
     * @brief Ordena la matriz de Politicos usando la estrategia actual.
     *
     * @param matriz Matriz de Politicos que se desea ordenar.
     * @return Numero de iteraciones realizadas por el algoritmo de ordenamiento.
     */

    double ordenar(std::vector<std::vector<Politico>>& matriz) {
        double iteraciones = strategy->sortMatriz(matriz);
        return iteraciones;
    }
};
