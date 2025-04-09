#pragma once
#ifndef CONTROLADOR_H
#define CONTROLADOR_H
#include "../Modelo/Politico.cpp"
#include "../modelo/RepositorioPoliticos.cpp"
#include "../Modelo/ResultadosOrdenamiento.h"
#include "../modelo/Bubble.cpp"
#include "../modelo/Quick.cpp"
#include "../modelo/Merge.cpp"
#include "../modelo/Insertion.cpp"
#include "../modelo/Selection.cpp"
#include "../modelo/QuickMatriz.cpp"
#include "../modelo/MergeMatriz.cpp"
#include "../modelo/SelectionMatriz.cpp"
#include "../modelo/InsertionMatriz.cpp"
#include "../modelo/BubbleMatriz.cpp"
#include "../modelo/Sorter.cpp"
#include "../modelo/MatrizSorter.cpp"
#include <vector>

using namespace std;

ref class Form1;

/**
 * @class Controlador
 * @brief Controla la lógica del sistema de ordenamiento de políticos usando diferentes algoritmos.
 *
 * Esta clase coordina el uso de múltiples algoritmos de ordenamiento sobre listas y matrices de objetos Politico.
 * También almacena resultados (tiempos e iteraciones) para cada combinación de algoritmo y tipo de datos.
 */

class Controlador {

private:
    // Instancias de algoritmos para los arreglos
    Bubble bubble;
    Quick quick;
    Insertion insert;
    Merge mergeSort;
    Selection selectSort;
    // Instancias de algoritmos para las matrices
    QuickMatriz quickMatriz;
    MergeMatriz mergeMatriz;
    BubbleMatriz bubbleMatriz;
    InsertionMatriz insertionMatriz;
    SelectionMatriz selectionMatriz;

    // Variables para almacenar tiempos de ejecución e iteraciones por tipo de ordenamiento
    // (aleatorio, ordenado, invertido) y tipo de estructura (arreglo o matriz)
    // Estas variables se agrupan por algoritmo y por tipo de datos

    double tiempoTotalBubbleAleatorio = 0;
    double tiempoTotalQuickAleatorio = 0;
    double tiempoTotalInsertionAleatorio = 0;
    double tiempoTotalMergeAleatorio = 0;
    double tiempoTotalSelectionAleatorio = 0;

    double tiempoTotalBubbleOrdenado = 0;
    double tiempoTotalQuickOrdenado = 0;
    double tiempoTotalInsertionOrdenado = 0;
    double tiempoTotalMergeOrdenado = 0;
    double tiempoTotalSelectionOrdenado = 0;

    double tiempoTotalBubbleInvertido = 0;
    double tiempoTotalQuickInvertido = 0;
    double tiempoTotalInsertionInvertido = 0;
    double tiempoTotalMergeInvertido = 0;
    double tiempoTotalSelectionInvertido = 0;

    double tiempoTotalMatrizQuickOrdenado = 0;
    double tiempoTotalMatrizBubbleOrdenado = 0;
    double tiempoTotalMatrizInsertionOrdenado = 0;
    double tiempoTotalMatrizMergeOrdenado = 0;
    double tiempoTotalMatrizSelectionOrdenado = 0;

    double tiempoTotalMatrizQuickAleatorio = 0;
    double tiempoTotalMatrizBubbleAleatorio = 0;
    double tiempoTotalMatrizInsertionAleatorio = 0;
    double tiempoTotalMatrizMergeAleatorio = 0;
    double tiempoTotalMatrizSelectionAleatorio = 0;

    double tiempoTotalMatrizQuickInvertido = 0;
    double tiempoTotalMatrizBubbleInvertido = 0;
    double tiempoTotalMatrizInsertionInvertido = 0;
    double tiempoTotalMatrizMergeInvertido = 0;
    double tiempoTotalMatrizSelectionInvertido = 0;

    double iteracionesTotalesBubbleAleatorio = 0;
    double iteracionesTotalesQuickAleatorio = 0;
    double iteracionesTotalesInsertionAleatorio = 0;
    double iteracionesTotalesMergeAleatorio = 0;
    double iteracionesTotalesSelectionAleatorio = 0;

    double iteracionesTotalesBubbleOrdenado = 0;
    double iteracionesTotalesQuickOrdenado = 0;
    double iteracionesTotalesInsertionOrdenado = 0;
    double iteracionesTotalesMergeOrdenado = 0;
    double iteracionesTotalesSelectionOrdenado = 0;

    double iteracionesTotalesBubbleInvertido = 0;
    double iteracionesTotalesQuickInvertido = 0;
    double iteracionesTotalesInsertionInvertido = 0;
    double iteracionesTotalesMergeInvertido = 0;
    double iteracionesTotalesSelectionInvertido = 0;

    double iteracionesTotalesMatrizSelectionOrdenado = 0;
    double iteracionesTotalesMatrizBubbleOrdenado = 0;
    double iteracionesTotalesMatrizQuickOrdenado = 0;
    double iteracionesTotalesMatrizMergeOrdenado = 0;
    double iteracionesTotalesMatrizInsertionOrdenado = 0;

    double iteracionesTotalesMatrizSelectionAleatorio = 0;
    double iteracionesTotalesMatrizBubbleAleatorio = 0;
    double iteracionesTotalesMatrizQuickAleatorio = 0;
    double iteracionesTotalesMatrizMergeAleatorio = 0;
    double iteracionesTotalesMatrizInsertionAleatorio = 0;

    double iteracionesTotalesMatrizSelectionInvertido = 0;
    double iteracionesTotalesMatrizBubbleInvertido = 0;
    double iteracionesTotalesMatrizQuickInvertido = 0;
    double iteracionesTotalesMatrizMergeInvertido = 0;
    double iteracionesTotalesMatrizInsertionInvertido = 0;

public:
    Controlador();
	size_t calcularTamanoMaximo(size_t tamanoDato, double porcentajeUso);
	int calcular(int tamano, double crecimiento, int tamanoMaximo);
	void ordenarPoliticosAleatorio(vector<Politico> politicos);
	void ordenarPoliticosOrdenados(vector<Politico> politicos);
	void ordenarPoliticosInvertidos(vector<Politico> politicos);
	void ordenarMatrizPoliticosAleatoria(vector<vector<Politico>> matrizPoliticos);
	void ordenarMatrizPoliticosInvertido(vector<vector<Politico>> matrizPoliticos);
	void ordenarMatrizPoliticosOrdenada(vector<vector<Politico>> matrizPoliticos);
    void eventoBoton(int tamano, double crecimiento, vector<ResultadoOrdenamiento>& resultadosArreglo, vector<ResultadoOrdenamiento>& resultadosMatriz);
    std::vector<ResultadoOrdenamiento> calcularResultadosArreglo(int iteracionesWhile);
    vector<ResultadoOrdenamiento> calcularResultadosMatriz(int iteracionesWhile);

};

#endif

/**
 * @class ResultadoOrdenamiento
 * @brief Representa el resultado de un algoritmo de ordenamiento.
 *
 * Esta clase almacena información relevante sobre un proceso de ordenamiento,
 * como el nombre del algoritmo, el tiempo de ejecución, y el número de comparaciones realizadas.
 */