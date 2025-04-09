#pragma once
#include <iostream>
#include <vector>
#include "Politico.cpp"

/**
 * @class ISortMatrizStrategy
 * @brief Interfaz para la ejecucion del patron strategy para los algoritmos.
 *
 * Define los metodos que deben seguir todas las clases que implementen un algoritmo de ordenamiento
 * sobre una matriz de Politico. 
 * Utiliza el patr�n de dise�o Strategy para permitir el uso intercambiable de algoritmos.
 */

class ISortMatrizStrategy {
public:

    /**
     * @brief Ordena una matriz de objetos Politico.
     *
     * Este m�todo debe ser implementado por cualquier clase derivada.
     *
     * @param matriz: Matriz de Politico a ordenar.
     * @return Numero de iteraciones realizadas.
     */

    virtual double sortMatriz(std::vector<std::vector<Politico>>& matriz) = 0;

    /**
     * @brief Destructor virtual por defecto.
     *
     * Se declara virtual para asegurar una destrucci�n correcta en caso de herencia.
     */
    virtual ~ISortMatrizStrategy() = default;
};