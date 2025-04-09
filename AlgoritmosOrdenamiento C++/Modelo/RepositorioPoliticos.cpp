#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <cstddef>
#include <algorithm>
#include "Politico.cpp"

/**
 * @class RepositorioPoliticos
 * @brief Clase que permite generar y organizar datos de objetos Politico.
 *
 * Ofrece m�todos para crear arreglos y matrices de pol�ticos con datos aleatorios,
 * ordenados o invertidos, y funciones para ordenarlos seg�n su fecha de nacimiento.
 */

class RepositorioPoliticos {

public:

    /**
     * @brief Genera una fecha aleatoria entre los a�os 1925 y 2007.
     * @return Una estructura std::tm con la fecha aleatoria.
     */

    std::tm generarFechaAleatoria() {
        std::tm fecha = {};

        fecha.tm_year = rand() % (2007 - 1925 + 1) + 1925 - 1900;
        fecha.tm_mon = rand() % 12;
        fecha.tm_mday = 1 + rand() % 31;
        return fecha;
    }

    /**
     * @brief Genera un arreglo de Politicos con valores aleatorios.
     * @param tamano Cantidad de pol�ticos a generar.
     * @return Vector de Politicos.
     */

    vector<Politico> arregloAleatorio(int tamano) {

        vector<Politico> politicos;
        for (int i = 0; i < tamano; ++i) {
            int id = i + 1;
            int dineroRobado = 100 + rand() % (1000000 - 100 + 1);
            std::tm fechaNacimiento = generarFechaAleatoria();
            politicos.push_back(Politico(id, dineroRobado, fechaNacimiento));
        }
        return politicos;
    }

    /**
     * @brief Genera un arreglo de pol�ticos con dinero robado en orden creciente.
     * @param tamano Cantidad de pol�ticos a generar.
     * @return Vector de Politicos.
     */

    vector<Politico> arregloInvetido(int tamano) {

        vector<Politico> politicos;
        for (int i = 0; i < tamano; ++i) {
            int id = i + 1;
            int dineroRobado = 100 + i;
            std::tm fechaNacimiento = generarFechaAleatoria();
            politicos.push_back(Politico(id, dineroRobado, fechaNacimiento));
        }
        return politicos;
    }

    /**
     * @brief Genera un arreglo de pol�ticos con dinero robado en orden decreciente.
     * @param tamano Cantidad de pol�ticos a generar.
     * @return Vector de Politicos.
     */

    vector<Politico> arregloOrdenado(int tamano) {

        vector<Politico> politicos;
        for (int i = 0; i < tamano; ++i) {
            int id = i + 1;
            int dineroRobado = 100000000 - i;
            std::tm fechaNacimiento = generarFechaAleatoria();
            politicos.push_back(Politico(id, dineroRobado, fechaNacimiento));
        }
        return politicos;
    }

    /**
     * @brief Divide un vector de pol�ticos en una matriz sin orden espec�fico.
     * @param politicos Vector de objetos Politico.
     * @return Matriz de pol�ticos.
     */

    vector<vector<Politico>> generarMatrizAleatoria(vector<Politico>& politicos) {
        try {
            int n = politicos.size();
            if (n == 0) return {};

            int k = ceil(sqrt(n));
            int m = ceil((double)n / k);

            vector<vector<Politico>> matriz;
            matriz.resize(k);

            int index = 0;
            for (int i = 0; i < k && index < n; ++i) {
                try {
                    matriz[i].reserve(m);  // Reservamos espacio para cada fila
                }
                catch (const bad_alloc& e) {
                    cerr << "Error de memoria al reservar una fila: " << e.what() << endl;
                    throw;
                }

                for (int j = 0; j < m && index < n; ++j) {
                    matriz[i].push_back(politicos[index++]);
                }
            }

            return matriz;

        }
        catch (const bad_alloc& e) {
            cerr << "Error de asignaci�n de memoria en generarMatrizInvertida: " << e.what() << endl;
            return {}; // Devolver una matriz vac�a si falla la asignaci�n de memoria
        }
        catch (const exception& e) {
            cerr << "Error inesperado en generarMatrizInvertida: " << e.what() << endl;
            return {};
        }
    }

    /**
     * @brief Genera una matriz ordenada de menor a mayor por fecha de nacimiento.
     * @param politicos Vector de objetos Politico.
     * @return Matriz de pol�ticos ordenada por fecha.
     */

    vector<vector<Politico>> generarMatrizOrdenada(vector<Politico>& politicos) {
        try {
            int n = politicos.size();
            if (n == 0) return {};

            int k = ceil(sqrt(n));
            int m = ceil((double)n / k);

            vector<vector<Politico>> matriz;
            matriz.resize(k);

            int index = 0;
            for (int i = 0; i < k && index < n; ++i) {
                try {
                    matriz[i].reserve(m);  // Reservamos espacio para cada fila
                }
                catch (const bad_alloc& e) {
                    cerr << "Error de memoria al reservar una fila: " << e.what() << endl;
                    throw;
                }

                for (int j = 0; j < m && index < n; ++j) {
                    matriz[i].push_back(politicos[index++]);
                }
            }

            ordenarMatrizPorFechaNacimientoMenorMayor(matriz);
            return matriz;

        }
        catch (const bad_alloc& e) {
            cerr << "Error de asignaci�n de memoria en generarMatrizInvertida: " << e.what() << endl;
            return {}; // Devolver una matriz vac�a si falla la asignaci�n de memoria
        }
        catch (const exception& e) {
            cerr << "Error inesperado en generarMatrizInvertida: " << e.what() << endl;
            return {};
        }
    }

    /**
     * @brief Genera una matriz ordenada de mayor a menor por fecha de nacimiento.
     * @param politicos Vector de objetos Politico.
     * @return Matriz de pol�ticos ordenada de forma inversa por fecha.
     */

    vector<vector<Politico>> generarMatrizInvertida(vector<Politico>& politicos) {
        try {
            int n = politicos.size();
            if (n == 0) return {};

            int k = ceil(sqrt(n));
            int m = ceil((double)n / k);

            vector<vector<Politico>> matriz;
            matriz.resize(k);

            int index = 0;
            for (int i = 0; i < k && index < n; ++i) {
                try {
                    matriz[i].reserve(m);  // Reservamos espacio para cada fila
                }
                catch (const bad_alloc& e) {
                    cerr << "Error de memoria al reservar una fila: " << e.what() << endl;
                    throw;
                }

                for (int j = 0; j < m && index < n; ++j) {
                    matriz[i].push_back(politicos[index++]);
                }
            }

            ordenarMatrizPorFechaNacimientoMayorMenor(matriz);
            return matriz;

        }
        catch (const bad_alloc& e) {
            cerr << "Error de asignaci�n de memoria en generarMatrizInvertida: " << e.what() << endl;
            return {}; // Devolver una matriz vac�a si falla la asignaci�n de memoria
        }
        catch (const exception& e) {
            cerr << "Error inesperado en generarMatrizInvertida: " << e.what() << endl;
            return {};
        }
    }

    /**
     * @brief Ordena una matriz de pol�ticos de menor a mayor por fecha de nacimiento.
     * @param matriz Matriz de pol�ticos a ordenar.
     */

    void ordenarMatrizPorFechaNacimientoMenorMayor(vector<vector<Politico>>& matriz) {
        for (auto& fila : matriz) {
            sort(fila.begin(), fila.end(), [](const Politico& a, const Politico& b) {
                if (a.getAnio() != b.getAnio()) return a.getAnio() < b.getAnio();
                if (a.getMes() != b.getMes()) return a.getMes() < b.getMes();
                return a.getDia() < b.getDia();
                });
        }
    }

    /**
     * @brief Ordena una matriz de pol�ticos de mayor a menor por fecha de nacimiento.
     * @param matriz Matriz de pol�ticos a ordenar.
     */

    void ordenarMatrizPorFechaNacimientoMayorMenor(vector<vector<Politico>>& matriz) {
        for (auto& fila : matriz) {
            sort(fila.begin(), fila.end(), [](const Politico& a, const Politico& b) {
                if (a.getAnio() != b.getAnio()) return a.getAnio() > b.getAnio();
                if (a.getMes() != b.getMes()) return a.getMes() > b.getMes();
                return a.getDia() > b.getDia();
                });
        }
    }

};
