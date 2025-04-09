#pragma once
#include <string>

/**
 * @class ResultadoOrdenamiento
 * @brief Representa los resultados obtenidos tras aplicar los algoritmos de ordenamiento.
 *
 * Esta clase encapsula la información resultante de la ejecución de los algoritmos de ordenamiento
 * sobre una estructura de datos. Contiene el tipo de datos utilizados, el nombre del algoritmo,
 * el tiempo promedio que tomó la ejecución y la cantidad promedio de iteraciones realizadas.
 */

class ResultadoOrdenamiento {
public:

    /**
     * @brief Tipo de arreglo o matriz utilizada (Invertido, ordenado, aleatorio)
     */

    std::string tipoDatos;

    /**
     * @brief Nombre del algoritmo de ordenamiento aplicado.
     */

    std::string algoritmo;

    /**
     * @brief Tiempo promedio de ejecución del algoritmo en segundos.
     */

    double tiempoPromedio;

    /**
     * @brief Número promedio de iteraciones realizadas por el algoritmo.
     */

    double iteracionesPromedio;

    /**
     * @brief Constructor para inicializar todos los campos del resultado.
     *
     * @param tipo Tipo de arreglo o matriz utilizada.
     * @param alg Nombre del algoritmo de ordenamiento aplicado.
     * @param tiempo Tiempo promedio de ejecución en segundos.
     * @param iteraciones Número promedio de iteraciones realizadas.
     */

    ResultadoOrdenamiento(std::string tipo, std::string alg, double tiempo, double iteraciones)
        : tipoDatos(tipo), algoritmo(alg), tiempoPromedio(tiempo), iteracionesPromedio(iteraciones) {}
};
