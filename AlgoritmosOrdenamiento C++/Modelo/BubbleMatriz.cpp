#include <iostream>
#include <algorithm> 
#include <vector>
#include <ctime>
#include "Politico.cpp"
#include "ISortMatrizStrategy.cpp"

class BubbleMatriz : public ISortMatrizStrategy {
public:

    /// @brief Realiza el ordenamiento de matrices por Bubble sort comparando por fecha de nacimiento.
/// @param matriz: matriz de politicos.
/// @return numero de iteracions realizadas.

    double sortMatriz(std::vector<std::vector<Politico>>& matriz) {
        double iteraciones = 0;
        for (auto& fila : matriz) {
            int n = fila.size();
            bool swapped;
            for (int i = 0; i < n - 1; i++) {
                swapped = false;
                for (int j = 0; j < n - 1 - i; j++) {
                    iteraciones++;
                    if (Politico::compararEdades(fila[j], fila[j + 1])) {
                        std::swap(fila[j], fila[j + 1]);
                        swapped = true;
                    }
                }
                if (!swapped) break;
            }
        }
        return iteraciones;
    }
};
