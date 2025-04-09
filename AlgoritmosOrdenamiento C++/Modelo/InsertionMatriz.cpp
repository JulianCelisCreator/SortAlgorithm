#include <iostream>
#include <algorithm> 
#include <vector>
#include <ctime>
#include "Politico.cpp"
#include "ISortMatrizStrategy.cpp"

class InsertionMatriz : public ISortMatrizStrategy {

public:

    /// @brief Realiza el ordenamiento de matrices por Insertion sort comparando por fecha de nacimiento.
/// @param matriz: matriz de politicos.
/// @return numero de iteracions realizadas.

    double sortMatriz(std::vector<std::vector<Politico>>& matriz) override {
        double iteraciones = 0;
        for (auto& fila : matriz) {
            int n = fila.size();
            for (int i = 1; i < n; i++) {
                iteraciones++;
                Politico key = fila[i];
                int j = i - 1;

                while (j >= 0 && fila[j].calcularEdad() > key.calcularEdad()) {
                    fila[j + 1] = fila[j];
                    j--;
                }
                fila[j + 1] = key;
            }
        }
        return iteraciones;
    }


};