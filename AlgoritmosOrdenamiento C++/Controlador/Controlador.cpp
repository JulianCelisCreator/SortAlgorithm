#include <iostream>
#include "Controlador.h"
#include "../Modelo/ResultadosOrdenamiento.h"
#include <list>
#include <ctime>
#include <cstdlib>
#include <iomanip> 
#include <chrono>
#include <windows.h>
#include <vector>

using namespace std;
using namespace std::chrono;

/// @brief Calcula el tamaño maximo del arreglo segun la memoria disponble.
/// @param tamanoDato: Tamano en bytes que ocupa un objeto de la clase Politico en memoria.
/// @param porcentajeUso: Es el porcentaje que se usara de memoria para construir los arreglos.
/// @return Tamano maximo que puede tener el arreglo.

    size_t Controlador::calcularTamanoMaximo(size_t tamanoDato, double porcentajeUso) {
        MEMORYSTATUSEX estado;
        estado.dwLength = sizeof(estado);

        if (GlobalMemoryStatusEx(&estado)) {
            size_t memoriaDisponible = static_cast<size_t>(estado.ullAvailPhys * porcentajeUso);
            return memoriaDisponible / tamanoDato;
        }
        else {
            cerr << "Error al obtener la memoria disponible" << endl;
            return 0;
        }
    }

    /// @brief Es llamado desde la vista al hacer click en el boton para construir los arreglos y matrices,realizar los ordenamientos y calcular los resultados.
/// @param tamano: Tamano inicial del arreglo digitado por el usuario en la interfaz.
/// @param crecimiento: Tasa de crecimiento del arreglo digitado por el usuario en la interfaz.
/// @param resultadosArreglo: vector vacio el cual se modifica y se envian los datos a la vista. 
/// @param resultadosMatriz: vector vacio el cual se modifica y se envian los datos a la vista. 

    void Controlador::eventoBoton(int tamano, double crecimiento, vector<ResultadoOrdenamiento>& resultadosArreglo, vector<ResultadoOrdenamiento>& resultadosMatriz) {
    
        size_t tamanoDato = sizeof(Politico);
        size_t tamanoMaximo = calcularTamanoMaximo(tamanoDato, 0.2);

        int iteraciones = calcular(tamano, crecimiento, 50000);
        resultadosArreglo = calcularResultadosArreglo(iteraciones);
        resultadosMatriz = calcularResultadosMatriz(iteraciones);

    }

    /// @brief Genera los arreglos y mmatrices de las 3 formas, luego ejecuta cada algoritmo de ordenamiento en los 3 casos para arreglo y matriz.
/// @param tamano: Tamano del arreglo.
/// @param crecimiento: Tasa de crecimiento en la que aumentara el tamano del arreglo.
/// @param tamanoMaximo: Tamano maximo que puede tomar el arreglo.
/// @return Numero de iteraciones realizadas en el while.

    int Controlador::calcular(int tamano, double crecimiento, int tamanoMaximo) {
        int iteracionesWhile = 0;
        while (tamano <= tamanoMaximo) {
            iteracionesWhile++;

            MEMORYSTATUSEX estado;
            estado.dwLength = sizeof(estado);
            GlobalMemoryStatusEx(&estado);
            size_t memoriaDisponible = estado.ullAvailPhys;
            size_t memoriaNecesaria = tamano * sizeof(Politico);

            if (memoriaNecesaria >= memoriaDisponible) {
                cout << "Se ha alcanzado el limite seguro de memoria." << endl;
                break;
            }

            vector<Politico> politicosAleatorios;
            try {
                politicosAleatorios.reserve(tamano);
            }
            catch (const bad_alloc& e) {
                cerr << "Error de asignacion de memoria: " << e.what() << endl;
                break;
            }

            vector<Politico> politicosOrdenados;
            try {
                politicosOrdenados.reserve(tamano);
            }
            catch (const bad_alloc& e) {
                cerr << "Error de asignacion de memoria: " << e.what() << endl;
                break;
            }

            vector<Politico> politicosInvertidos;
            try {
                politicosInvertidos.reserve(tamano);
            }
            catch (const bad_alloc& e) {
                cerr << "Error de asignacion de memoria: " << e.what() << endl;
                break;
            }

            RepositorioPoliticos repoPoliticos;
            try {
                politicosAleatorios = repoPoliticos.arregloAleatorio(tamano);
            }
            catch (const bad_alloc& e) {
                cerr << "Error al generar el arreglo: " << e.what() << endl;
                break;
            }

            try {
                politicosOrdenados = repoPoliticos.arregloOrdenado(tamano);
            }
            catch (const bad_alloc& e) {
                cerr << "Error al generar el arreglo: " << e.what() << endl;
                break;
            }


            try {
                politicosInvertidos = repoPoliticos.arregloInvetido(tamano);
            }
            catch (const bad_alloc& e) {
                cerr << "Error al generar el arreglo: " << e.what() << endl;
                break;
            }

            vector<vector<Politico>> matrizPoliticosAleatoria;
            vector<vector<Politico>> matrizPoliticosOrdenada;
            vector<vector<Politico>> matrizPoliticosInvertida;

            try {
                matrizPoliticosAleatoria = repoPoliticos.generarMatrizAleatoria(politicosOrdenados);
                matrizPoliticosOrdenada = repoPoliticos.generarMatrizOrdenada(politicosOrdenados);
                matrizPoliticosInvertida = repoPoliticos.generarMatrizInvertida(politicosOrdenados);
            }
            catch (const bad_alloc& e) {

                cerr << "Excepción en la creación de las matrices: " << e.what() << endl;

            }

            ordenarPoliticosAleatorio(politicosAleatorios);
            ordenarPoliticosOrdenados(politicosOrdenados);
            ordenarPoliticosInvertidos(politicosInvertidos);
            ordenarMatrizPoliticosAleatoria(matrizPoliticosAleatoria);
            ordenarMatrizPoliticosInvertido(matrizPoliticosInvertida);
            ordenarMatrizPoliticosOrdenada(matrizPoliticosOrdenada);

            int nuevoTamano = static_cast<int>(tamano * (1 + crecimiento / 100));
            if (nuevoTamano > tamanoMaximo) {
                cout << "Se ha alcanzado el limite de memoria." << endl;
                break;
            }
            tamano = nuevoTamano;
            cout << "Tamano: " << tamano << endl;
            cout << "Iteraciones: " << iteracionesWhile << endl;
            vector<Politico>().swap(politicosAleatorios);
            vector<Politico>().swap(politicosOrdenados);
            vector<Politico>().swap(politicosInvertidos);
            vector<vector<Politico>>().swap(matrizPoliticosAleatoria);
            vector<vector<Politico>>().swap(matrizPoliticosOrdenada);
            vector<vector<Politico>>().swap(matrizPoliticosInvertida);
        }

        return iteracionesWhile;
    }

    /// @brief Calcula el tiempo promedio y las iteraciones promedio de cada algoritmo en los 3 tipos de arreglos(Aleatorio, ordenado  invertido).
/// @param iteracionesWhile: Numero de iteraciones realizadas en la funcion Calcular.
/// @return Vector con los resultados obtenidos.

    vector<ResultadoOrdenamiento> Controlador::calcularResultadosArreglo(int iteracionesWhile) {
        vector<ResultadoOrdenamiento> resultadosArreglos;
        if (iteracionesWhile > 0) {
        
            double tiempoPromedioBubbleAleatorio = tiempoTotalBubbleAleatorio / iteracionesWhile;

            double tiempoPromedioQuickAleatorio = tiempoTotalQuickAleatorio / iteracionesWhile;

            double tiempoPromedioInsertAleatorio = tiempoTotalInsertionAleatorio / iteracionesWhile;

            double tiempoPromedioMergeAleatorio = tiempoTotalMergeAleatorio / iteracionesWhile;

            double tiempoPromedioSelectionAleatorio = tiempoTotalSelectionAleatorio / iteracionesWhile;

            double tiempoPromedioBubbleOrdenado = tiempoTotalBubbleOrdenado / iteracionesWhile;

            double tiempoPromedioQuickOrdenado = tiempoTotalQuickOrdenado / iteracionesWhile;

            double tiempoPromedioInsertOrdenado = tiempoTotalInsertionOrdenado / iteracionesWhile;

            double tiempoPromedioMergeOrdenado = tiempoTotalMergeOrdenado / iteracionesWhile;

            double tiempoPromedioSelectionOrdenado = tiempoTotalSelectionOrdenado / iteracionesWhile;

            double tiempoPromedioBubbleInvertido = tiempoTotalBubbleInvertido / iteracionesWhile;

            double tiempoPromedioQuickInvertido = tiempoTotalQuickInvertido / iteracionesWhile;

            double tiempoPromedioInsertInvertido = tiempoTotalInsertionInvertido / iteracionesWhile;

            double tiempoPromedioMergeInvertido = tiempoTotalMergeInvertido / iteracionesWhile;

            double tiempoPromedioSelectionInvertido = tiempoTotalSelectionInvertido / iteracionesWhile;

            double iteracionesPromedioBubbleAleatorio = iteracionesTotalesBubbleAleatorio / iteracionesWhile;
            double iteracionesPromedioBubbleOrdenado = iteracionesTotalesBubbleOrdenado / iteracionesWhile;
            double iteracionesPromedioBubbleInvertido = iteracionesTotalesBubbleInvertido / iteracionesWhile;

            double iteracionesPromedioQuickAleatorio = iteracionesTotalesQuickAleatorio / iteracionesWhile;
            double iteracionesPromedioQuickOrdenado = iteracionesTotalesQuickOrdenado / iteracionesWhile;
            double iteracionesPromedioQuickInvertido = iteracionesTotalesQuickInvertido / iteracionesWhile;

            double iteracionesPromedioInsertionAleatorio = iteracionesTotalesInsertionAleatorio / iteracionesWhile;
            double iteracionesPromedioInsertionOrdenado = iteracionesTotalesInsertionOrdenado / iteracionesWhile;
            double iteracionesPromedioInsertionInvertido = iteracionesTotalesInsertionInvertido / iteracionesWhile;

            double iteracionesPromedioMergeAleatorio = iteracionesTotalesMergeAleatorio / iteracionesWhile;
            double iteracionesPromedioMergeOrdenado = iteracionesTotalesMergeOrdenado / iteracionesWhile;
            double iteracionesPromedioMergeInvertido = iteracionesTotalesMergeInvertido / iteracionesWhile;

            double iteracionesPromedioSelectionAleatorio = iteracionesTotalesSelectionAleatorio / iteracionesWhile;
            double iteracionesPromedioSelectionOrdenado = iteracionesTotalesSelectionOrdenado / iteracionesWhile;
            double iteracionesPromedioSelectionInvertido = iteracionesTotalesSelectionInvertido / iteracionesWhile;

            resultadosArreglos.push_back(ResultadoOrdenamiento("Aleatorio", "Bubble", tiempoPromedioBubbleAleatorio, iteracionesPromedioBubbleAleatorio));
            resultadosArreglos.push_back(ResultadoOrdenamiento("Ordenado", "Bubble", tiempoPromedioBubbleOrdenado, iteracionesPromedioBubbleOrdenado));
            resultadosArreglos.push_back(ResultadoOrdenamiento("Invertido", "Bubble", tiempoPromedioBubbleInvertido, iteracionesPromedioBubbleInvertido));

            resultadosArreglos.push_back(ResultadoOrdenamiento("Aleatorio", "Quick", tiempoPromedioQuickAleatorio, iteracionesPromedioQuickAleatorio));
            resultadosArreglos.push_back(ResultadoOrdenamiento("Ordenado", "Quick", tiempoPromedioQuickOrdenado, iteracionesPromedioQuickOrdenado));
            resultadosArreglos.push_back(ResultadoOrdenamiento("Invertido", "Quick", tiempoPromedioQuickInvertido, iteracionesPromedioQuickInvertido));

            resultadosArreglos.push_back(ResultadoOrdenamiento("Aleatorio", "Merge", tiempoPromedioMergeAleatorio, iteracionesPromedioMergeAleatorio));
            resultadosArreglos.push_back(ResultadoOrdenamiento("Ordenado", "Merge", tiempoPromedioMergeOrdenado, iteracionesPromedioMergeOrdenado));
            resultadosArreglos.push_back(ResultadoOrdenamiento("Invertido", "Merge", tiempoPromedioMergeInvertido, iteracionesPromedioMergeInvertido));

            resultadosArreglos.push_back(ResultadoOrdenamiento("Aleatorio", "Selection", tiempoPromedioSelectionAleatorio, iteracionesPromedioSelectionAleatorio));
            resultadosArreglos.push_back(ResultadoOrdenamiento("Ordenado", "Selection", tiempoPromedioSelectionOrdenado, iteracionesPromedioSelectionOrdenado));
            resultadosArreglos.push_back(ResultadoOrdenamiento("Invertido", "Selection", tiempoPromedioSelectionInvertido, iteracionesPromedioSelectionInvertido));

            resultadosArreglos.push_back(ResultadoOrdenamiento("Aleatorio", "Insertion", tiempoPromedioInsertAleatorio, iteracionesPromedioInsertionAleatorio));
            resultadosArreglos.push_back(ResultadoOrdenamiento("Ordenado", "Insertion", tiempoPromedioInsertOrdenado, iteracionesPromedioInsertionOrdenado));
            resultadosArreglos.push_back(ResultadoOrdenamiento("Invertido", "Insertion", tiempoPromedioInsertInvertido, iteracionesPromedioInsertionInvertido));

        }
        return resultadosArreglos;
    }

    /// @brief Calcula el tiempo promedio y las iteraciones promedio de cada algoritmo en los 3 tipos de matrices(Aleatorio, ordenado  invertido).
/// @param iteracionesWhile: Numero de iteraciones realizadas en la funcion Calcular.
/// @return Vector con los resultados obtenidos.

    vector<ResultadoOrdenamiento> Controlador::calcularResultadosMatriz(int iteracionesWhile) {
        vector<ResultadoOrdenamiento> resultadosMatriz;
        if (iteracionesWhile > 0) {

            double tiempoPromedioMatrizBubbleAleatorio = tiempoTotalMatrizBubbleAleatorio / iteracionesWhile;

            double tiempoPromedioMatrizQuickAleatorio = tiempoTotalMatrizQuickAleatorio / iteracionesWhile;

            double tiempoPromedioMatrizInsertAleatorio = tiempoTotalMatrizInsertionAleatorio / iteracionesWhile;

            double tiempoPromedioMatrizMergeAleatorio = tiempoTotalMatrizMergeAleatorio / iteracionesWhile;

            double tiempoPromedioMatrizSelectionAleatorio = tiempoTotalMatrizSelectionAleatorio / iteracionesWhile;

            double tiempoPromedioMatrizBubbleOrdenado = tiempoTotalMatrizBubbleOrdenado / iteracionesWhile;

            double tiempoPromedioMatrizQuickOrdenado = tiempoTotalMatrizQuickOrdenado / iteracionesWhile;

            double tiempoPromedioMatrizInsertOrdenado = tiempoTotalMatrizInsertionOrdenado / iteracionesWhile;

            double tiempoPromedioMatrizMergeOrdenado = tiempoTotalMatrizMergeOrdenado / iteracionesWhile;

            double tiempoPromedioMatrizSelectionOrdenado = tiempoTotalMatrizSelectionOrdenado / iteracionesWhile;

            double tiempoPromedioMatrizBubbleInvertido = tiempoTotalMatrizBubbleInvertido / iteracionesWhile;

            double tiempoPromedioMatrizQuickInvertido = tiempoTotalMatrizQuickInvertido / iteracionesWhile;

            double tiempoPromedioMatrizInsertInvertido = tiempoTotalMatrizInsertionInvertido / iteracionesWhile;

            double tiempoPromedioMatrizMergeInvertido = tiempoTotalMatrizMergeInvertido / iteracionesWhile;

            double tiempoPromedioMatrizSelectionInvertido = tiempoTotalMatrizSelectionInvertido / iteracionesWhile;

            double iteracionesPromedioMatrizBubbleAleatorio = iteracionesTotalesMatrizBubbleAleatorio / iteracionesWhile;
            double iteracionesPromedioMatrizBubbleOrdenado = iteracionesTotalesMatrizBubbleOrdenado / iteracionesWhile;
            double iteracionesPromedioMatrizBubbleInvertido = iteracionesTotalesMatrizBubbleInvertido / iteracionesWhile;

            double iteracionesPromedioMatrizQuickAleatorio = iteracionesTotalesMatrizQuickAleatorio / iteracionesWhile;
            double iteracionesPromedioMatrizQuickOrdenado = iteracionesTotalesMatrizQuickOrdenado / iteracionesWhile;
            double iteracionesPromedioMatrizQuickInvertido = iteracionesTotalesMatrizQuickInvertido / iteracionesWhile;

            double iteracionesPromedioMatrizInsertionAleatorio = iteracionesTotalesMatrizInsertionAleatorio / iteracionesWhile;
            double iteracionesPromedioMatrizInsertionOrdenado = iteracionesTotalesMatrizInsertionOrdenado / iteracionesWhile;
            double iteracionesPromedioMatrizInsertionInvertido = iteracionesTotalesMatrizInsertionInvertido / iteracionesWhile;

            double iteracionesPromedioMatrizMergeAleatorio = iteracionesTotalesMatrizMergeAleatorio / iteracionesWhile;
            double iteracionesPromedioMatrizMergeOrdenado = iteracionesTotalesMatrizMergeOrdenado / iteracionesWhile;
            double iteracionesPromedioMatrizMergeInvertido = iteracionesTotalesMatrizMergeInvertido / iteracionesWhile;

            double iteracionesPromedioMatrizSelectionAleatorio = iteracionesTotalesMatrizSelectionAleatorio / iteracionesWhile;
            double iteracionesPromedioMatrizSelectionOrdenado = iteracionesTotalesMatrizSelectionOrdenado / iteracionesWhile;
            double iteracionesPromedioMatrizSelectionInvertido = iteracionesTotalesMatrizSelectionInvertido / iteracionesWhile;

            resultadosMatriz.push_back(ResultadoOrdenamiento("Aleatorio", "Bubble", tiempoPromedioMatrizBubbleAleatorio, iteracionesPromedioMatrizBubbleAleatorio));
            resultadosMatriz.push_back(ResultadoOrdenamiento("Ordenado", "Bubble", tiempoPromedioMatrizBubbleOrdenado, iteracionesPromedioMatrizBubbleOrdenado));
            resultadosMatriz.push_back(ResultadoOrdenamiento("Invertido", "Bubble", tiempoPromedioMatrizBubbleInvertido, iteracionesPromedioMatrizBubbleInvertido));

            resultadosMatriz.push_back(ResultadoOrdenamiento("Aleatorio", "Quick", tiempoPromedioMatrizQuickAleatorio, iteracionesPromedioMatrizQuickAleatorio));
            resultadosMatriz.push_back(ResultadoOrdenamiento("Ordenado", "Quick", tiempoPromedioMatrizQuickOrdenado, iteracionesPromedioMatrizQuickOrdenado));
            resultadosMatriz.push_back(ResultadoOrdenamiento("Invertido", "Quick", tiempoPromedioMatrizQuickInvertido, iteracionesPromedioMatrizQuickInvertido));

            resultadosMatriz.push_back(ResultadoOrdenamiento("Aleatorio", "Merge", tiempoPromedioMatrizMergeAleatorio, iteracionesPromedioMatrizMergeAleatorio));
            resultadosMatriz.push_back(ResultadoOrdenamiento("Ordenado", "Merge", tiempoPromedioMatrizMergeOrdenado, iteracionesPromedioMatrizMergeOrdenado));
            resultadosMatriz.push_back(ResultadoOrdenamiento("Invertido", "Merge", tiempoPromedioMatrizMergeInvertido, iteracionesPromedioMatrizMergeInvertido));

            resultadosMatriz.push_back(ResultadoOrdenamiento("Aleatorio", "Selection", tiempoPromedioMatrizSelectionAleatorio, iteracionesPromedioMatrizSelectionAleatorio));
            resultadosMatriz.push_back(ResultadoOrdenamiento("Ordenado", "Selection", tiempoPromedioMatrizSelectionOrdenado, iteracionesPromedioMatrizSelectionOrdenado));
            resultadosMatriz.push_back(ResultadoOrdenamiento("Invertido", "Selection", tiempoPromedioMatrizSelectionInvertido, iteracionesPromedioMatrizSelectionInvertido));

            resultadosMatriz.push_back(ResultadoOrdenamiento("Aleatorio", "Insertion", tiempoPromedioMatrizInsertAleatorio, iteracionesPromedioMatrizInsertionAleatorio));
            resultadosMatriz.push_back(ResultadoOrdenamiento("Ordenado", "Insertion", tiempoPromedioMatrizInsertOrdenado, iteracionesPromedioMatrizInsertionOrdenado));
            resultadosMatriz.push_back(ResultadoOrdenamiento("Invertido", "Insertion", tiempoPromedioMatrizInsertInvertido, iteracionesPromedioMatrizInsertionInvertido));

        }
        return resultadosMatriz;
    }

    /// @brief Ejecuta los 5 algoritmos de ordenamiento para los arreglos aleatorios.
/// @param politicos: Arreglo de politicos generado aleatoriamente.

    void Controlador::ordenarPoliticosAleatorio(vector<Politico> politicos) {

        vector<Politico> copiaPoliticos;

        copiaPoliticos = politicos;
        Sorter sorterBubble(&bubble);
        auto inicioBubble = high_resolution_clock::now();
        iteracionesTotalesBubbleAleatorio += sorterBubble.executeSort(copiaPoliticos);
        auto finBubble = high_resolution_clock::now();

        tiempoTotalBubbleAleatorio += duration_cast<duration<double>>(finBubble - inicioBubble).count();

        copiaPoliticos = politicos;
        Sorter sorterQuick(&quick);
        auto inicioQuick = high_resolution_clock::now();
        iteracionesTotalesQuickAleatorio += sorterQuick.executeSort(copiaPoliticos);
        auto finQuick = high_resolution_clock::now();
        tiempoTotalQuickAleatorio += duration_cast<duration<double>>(finQuick - inicioQuick).count();

        copiaPoliticos = politicos;
        Sorter sorterInsert(&insert);
        auto inicioInsert = high_resolution_clock::now();
        iteracionesTotalesInsertionAleatorio += sorterInsert.executeSort(copiaPoliticos);
        auto finInsert = high_resolution_clock::now();
        tiempoTotalInsertionAleatorio += duration_cast<duration<double>>(finInsert - inicioInsert).count();

        copiaPoliticos = politicos;
        Sorter sorterMerge(&mergeSort);
        auto inicioMerge = high_resolution_clock::now();
        iteracionesTotalesMergeAleatorio += sorterMerge.executeSort(copiaPoliticos);
        auto finMerge = high_resolution_clock::now();
        tiempoTotalMergeAleatorio += duration_cast<duration<double>>(finMerge - inicioMerge).count();

        copiaPoliticos = politicos;
        Sorter sorterSelect(&selectSort);
        auto inicioSelect = high_resolution_clock::now();
        iteracionesTotalesSelectionAleatorio += sorterSelect.executeSort(copiaPoliticos);
        auto finSelect = high_resolution_clock::now();
        tiempoTotalSelectionAleatorio += duration_cast<duration<double>>(finSelect - inicioSelect).count();

    }

    /// @brief Ejecuta los 5 algoritmos de ordenamiento para los arreglos ordenados.
/// @param politicos: Arreglo de politicos generado ordenado.

    void Controlador::ordenarPoliticosOrdenados(vector<Politico> politicos) {

        vector<Politico> copiaPoliticos;

        copiaPoliticos = politicos;
        Sorter sorterBubble(&bubble);
        auto inicioBubble = high_resolution_clock::now();
        iteracionesTotalesBubbleOrdenado += sorterBubble.executeSort(copiaPoliticos);
        auto finBubble = high_resolution_clock::now();
        tiempoTotalBubbleOrdenado += duration_cast<duration<double>>(finBubble - inicioBubble).count();

        copiaPoliticos = politicos;
        Sorter sorterQuick(&quick);
        auto inicioQuick = high_resolution_clock::now();
        iteracionesTotalesQuickOrdenado += sorterQuick.executeSort(copiaPoliticos);
        auto finQuick = high_resolution_clock::now();
        tiempoTotalQuickOrdenado += duration_cast<duration<double>>(finQuick - inicioQuick).count();

        copiaPoliticos = politicos;
        Sorter sorterInsert(&insert);
        auto inicioInsert = high_resolution_clock::now();
        iteracionesTotalesInsertionOrdenado += sorterInsert.executeSort(copiaPoliticos);
        auto finInsert = high_resolution_clock::now();
        tiempoTotalInsertionOrdenado += duration_cast<duration<double>>(finInsert - inicioInsert).count();

        copiaPoliticos = politicos;
        Sorter sorterMerge(&mergeSort);
        auto inicioMerge = high_resolution_clock::now();
        iteracionesTotalesMergeOrdenado += sorterMerge.executeSort(copiaPoliticos);
        auto finMerge = high_resolution_clock::now();
        tiempoTotalMergeOrdenado += duration_cast<duration<double>>(finMerge - inicioMerge).count();

        copiaPoliticos = politicos;
        Sorter sorterSelect(&selectSort);
        auto inicioSelect = high_resolution_clock::now();
        iteracionesTotalesSelectionOrdenado += sorterSelect.executeSort(copiaPoliticos);
        auto finSelect = high_resolution_clock::now();
        tiempoTotalSelectionOrdenado += duration_cast<duration<double>>(finSelect - inicioSelect).count();

    }

    /// @brief Ejecuta los 5 algoritmos de ordenamiento para los arreglos invertidos.
/// @param politicos: Arreglo de politicos generado invertido.

    void Controlador::ordenarPoliticosInvertidos(vector<Politico> politicos) {

        vector<Politico> copiaPoliticos;


        copiaPoliticos = politicos;
        Sorter sorterBubble(&bubble);
        auto inicioBubble = high_resolution_clock::now();
        iteracionesTotalesBubbleInvertido += sorterBubble.executeSort(copiaPoliticos);
        auto finBubble = high_resolution_clock::now();
        tiempoTotalBubbleInvertido += duration_cast<duration<double>>(finBubble - inicioBubble).count();

        copiaPoliticos = politicos;
        Sorter sorterQuick(&quick);
        auto inicioQuick = high_resolution_clock::now();
        iteracionesTotalesQuickInvertido += sorterQuick.executeSort(copiaPoliticos);
        auto finQuick = high_resolution_clock::now();
        tiempoTotalQuickInvertido += duration_cast<duration<double>>(finQuick - inicioQuick).count();

        copiaPoliticos = politicos;
        Sorter sorterInsert(&insert);
        auto inicioInsert = high_resolution_clock::now();
        iteracionesTotalesInsertionInvertido += sorterInsert.executeSort(copiaPoliticos);
        auto finInsert = high_resolution_clock::now();
        tiempoTotalInsertionInvertido += duration_cast<duration<double>>(finInsert - inicioInsert).count();

        copiaPoliticos = politicos;
        Sorter sorterMerge(&mergeSort);
        auto inicioMerge = high_resolution_clock::now();
        iteracionesTotalesMergeInvertido += sorterMerge.executeSort(copiaPoliticos);
        auto finMerge = high_resolution_clock::now();
        tiempoTotalMergeInvertido += duration_cast<duration<double>>(finMerge - inicioMerge).count();

        copiaPoliticos = politicos;
        Sorter sorterSelect(&selectSort);
        auto inicioSelect = high_resolution_clock::now();
        iteracionesTotalesSelectionInvertido += sorterSelect.executeSort(copiaPoliticos);
        auto finSelect = high_resolution_clock::now();
        tiempoTotalSelectionInvertido += duration_cast<duration<double>>(finSelect - inicioSelect).count();

    }

    /// @brief Ejecuta los 5 algoritmos de ordenamiento para las matrices aleatorias.
/// @param politicos: Matriz de politicos generado aleatoria.

    void Controlador::ordenarMatrizPoliticosAleatoria(vector<vector<Politico>> matrizPoliticos) {

        vector<vector<Politico>> copiaMatrizPoliticos;

        copiaMatrizPoliticos = matrizPoliticos;
        MatrizSorter MatrizSorterQuick(&quickMatriz);
        auto inicioQuick = high_resolution_clock::now();
        iteracionesTotalesMatrizQuickAleatorio += MatrizSorterQuick.ordenar(copiaMatrizPoliticos);
        auto finQuick = high_resolution_clock::now();
        tiempoTotalMatrizQuickAleatorio += duration_cast<duration<double>>(finQuick - inicioQuick).count();

        copiaMatrizPoliticos = matrizPoliticos;
        MatrizSorter MatrizSorterBubble(&bubbleMatriz);
        auto inicioBubble = high_resolution_clock::now();
        iteracionesTotalesMatrizBubbleAleatorio += MatrizSorterBubble.ordenar(copiaMatrizPoliticos);
        auto finBubble = high_resolution_clock::now();
        tiempoTotalMatrizBubbleAleatorio += duration_cast<duration<double>>(finBubble - inicioBubble).count();

        copiaMatrizPoliticos = matrizPoliticos;
        MatrizSorter MatrizSorterInsertion(&insertionMatriz);
        auto inicioInsertion = high_resolution_clock::now();
        iteracionesTotalesMatrizInsertionAleatorio += MatrizSorterInsertion.ordenar(copiaMatrizPoliticos);
        auto finInsertion = high_resolution_clock::now();
        tiempoTotalMatrizInsertionAleatorio += duration_cast<duration<double>>(finInsertion - inicioInsertion).count();

        copiaMatrizPoliticos = matrizPoliticos;
        MatrizSorter MatrizSorterMerge(&mergeMatriz);
        auto inicioMerge = high_resolution_clock::now();
        iteracionesTotalesMatrizMergeAleatorio += MatrizSorterMerge.ordenar(copiaMatrizPoliticos);
        auto finMerge = high_resolution_clock::now();
        tiempoTotalMatrizMergeAleatorio += duration_cast<duration<double>>(finMerge - inicioMerge).count();

        copiaMatrizPoliticos = matrizPoliticos;
        MatrizSorter MatrizSorterSelection(&selectionMatriz);
        auto inicioSelection = high_resolution_clock::now();
        iteracionesTotalesMatrizSelectionAleatorio += MatrizSorterSelection.ordenar(copiaMatrizPoliticos);
        auto finSelection = high_resolution_clock::now();
        tiempoTotalMatrizSelectionAleatorio += duration_cast<duration<double>>(finSelection - inicioSelection).count();

    }

    /// @brief Ejecuta los 5 algoritmos de ordenamiento para las matrices invertidas.
/// @param politicos: Matriz de politicos generado invertido.

    void Controlador::ordenarMatrizPoliticosInvertido(vector<vector<Politico>> matrizPoliticos) {

        vector<vector<Politico>> copiaMatrizPoliticos;

        copiaMatrizPoliticos = matrizPoliticos;
        MatrizSorter MatrizSorterQuick(&quickMatriz);
        auto inicioQuick = high_resolution_clock::now();
        iteracionesTotalesMatrizQuickInvertido += MatrizSorterQuick.ordenar(copiaMatrizPoliticos);
        auto finQuick = high_resolution_clock::now();
        tiempoTotalMatrizQuickInvertido += duration_cast<duration<double>>(finQuick - inicioQuick).count();

        copiaMatrizPoliticos = matrizPoliticos;
        MatrizSorter MatrizSorterBubble(&bubbleMatriz);
        auto inicioBubble = high_resolution_clock::now();
        iteracionesTotalesMatrizBubbleInvertido += MatrizSorterBubble.ordenar(copiaMatrizPoliticos);
        auto finBubble = high_resolution_clock::now();
        tiempoTotalMatrizBubbleInvertido += duration_cast<duration<double>>(finBubble - inicioBubble).count();

        copiaMatrizPoliticos = matrizPoliticos;
        MatrizSorter MatrizSorterInsertion(&insertionMatriz);
        auto inicioInsertion = high_resolution_clock::now();
        iteracionesTotalesMatrizInsertionInvertido += MatrizSorterInsertion.ordenar(copiaMatrizPoliticos);
        auto finInsertion = high_resolution_clock::now();
        tiempoTotalMatrizInsertionInvertido += duration_cast<duration<double>>(finInsertion - inicioInsertion).count();

        copiaMatrizPoliticos = matrizPoliticos;
        MatrizSorter MatrizSorterMerge(&mergeMatriz);
        auto inicioMerge = high_resolution_clock::now();
        iteracionesTotalesMatrizMergeInvertido += MatrizSorterMerge.ordenar(copiaMatrizPoliticos);
        auto finMerge = high_resolution_clock::now();
        tiempoTotalMatrizMergeInvertido += duration_cast<duration<double>>(finMerge - inicioMerge).count();

        copiaMatrizPoliticos = matrizPoliticos;
        MatrizSorter MatrizSorterSelection(&selectionMatriz);
        auto inicioSelection = high_resolution_clock::now();
        iteracionesTotalesMatrizSelectionInvertido += MatrizSorterSelection.ordenar(copiaMatrizPoliticos);
        auto finSelection = high_resolution_clock::now();
        tiempoTotalMatrizSelectionInvertido += duration_cast<duration<double>>(finSelection - inicioSelection).count();

    }

    /// @brief Ejecuta los 5 algoritmos de ordenamiento para las matrices ordenada.
/// @param politicos: Matriz de politicos generado ordenada.

    void Controlador::ordenarMatrizPoliticosOrdenada(vector<vector<Politico>> matrizPoliticos) {

        vector<vector<Politico>> copiaMatrizPoliticos;

        copiaMatrizPoliticos = matrizPoliticos;
        MatrizSorter MatrizSorterQuick(&quickMatriz);
        auto inicioQuick = high_resolution_clock::now();
        iteracionesTotalesMatrizQuickOrdenado += MatrizSorterQuick.ordenar(copiaMatrizPoliticos);
        auto finQuick = high_resolution_clock::now();
        tiempoTotalMatrizQuickOrdenado += duration_cast<duration<double>>(finQuick - inicioQuick).count();

        copiaMatrizPoliticos = matrizPoliticos;
        MatrizSorter MatrizSorterBubble(&bubbleMatriz);
        auto inicioBubble = high_resolution_clock::now();
        iteracionesTotalesMatrizBubbleOrdenado += MatrizSorterBubble.ordenar(copiaMatrizPoliticos);
        auto finBubble = high_resolution_clock::now();
        tiempoTotalMatrizBubbleOrdenado += duration_cast<duration<double>>(finBubble - inicioBubble).count();

        copiaMatrizPoliticos = matrizPoliticos;
        MatrizSorter MatrizSorterInsertion(&insertionMatriz);
        auto inicioInsertion = high_resolution_clock::now();
        iteracionesTotalesMatrizInsertionOrdenado += MatrizSorterInsertion.ordenar(copiaMatrizPoliticos);
        auto finInsertion = high_resolution_clock::now();
        tiempoTotalMatrizInsertionOrdenado += duration_cast<duration<double>>(finInsertion - inicioInsertion).count();

        copiaMatrizPoliticos = matrizPoliticos;
        MatrizSorter MatrizSorterMerge(&mergeMatriz);
        auto inicioMerge = high_resolution_clock::now();
        iteracionesTotalesMatrizMergeOrdenado += MatrizSorterMerge.ordenar(copiaMatrizPoliticos);
        auto finMerge = high_resolution_clock::now();
        tiempoTotalMatrizMergeOrdenado += duration_cast<duration<double>>(finMerge - inicioMerge).count();

        copiaMatrizPoliticos = matrizPoliticos;
        MatrizSorter MatrizSorterSelection(&selectionMatriz);
        auto inicioSelection = high_resolution_clock::now();
        iteracionesTotalesMatrizSelectionOrdenado += MatrizSorterSelection.ordenar(copiaMatrizPoliticos);
        auto finSelection = high_resolution_clock::now();
        tiempoTotalMatrizSelectionOrdenado += duration_cast<duration<double>>(finSelection - inicioSelection).count();

    }
    /// @brief Constructor vacio.
    Controlador::Controlador() {
    

    }
