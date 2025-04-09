#pragma once
#include <string>

/**
 * @class ResultadoOrdenamiento
 * @brief Representa los resultados obtenidos tras aplicar los algoritmos de ordenamiento.
 *
 * Esta clase encapsula la informaci�n resultante de la ejecuci�n de los algoritmos de ordenamiento
 * sobre una estructura de datos. Contiene el tipo de datos utilizados, el nombre del algoritmo,
 * el tiempo promedio que tom� la ejecuci�n y la cantidad promedio de iteraciones realizadas.
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
     * @brief Tiempo promedio de ejecuci�n del algoritmo en segundos.
     */

    double tiempoPromedio;

    /**
     * @brief N�mero promedio de iteraciones realizadas por el algoritmo.
     */

    double iteracionesPromedio;

    /**
     * @brief Constructor para inicializar todos los campos del resultado.
     *
     * @param tipo Tipo de arreglo o matriz utilizada.
     * @param alg Nombre del algoritmo de ordenamiento aplicado.
     * @param tiempo Tiempo promedio de ejecuci�n en segundos.
     * @param iteraciones N�mero promedio de iteraciones realizadas.
     */

    ResultadoOrdenamiento(std::string tipo, std::string alg, double tiempo, double iteraciones)
        : tipoDatos(tipo), algoritmo(alg), tiempoPromedio(tiempo), iteracionesPromedio(iteraciones) {}
};
