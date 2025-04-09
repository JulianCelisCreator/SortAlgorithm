#include <iostream>
#include <algorithm> 
#include <vector>
#include "Politico.cpp"
#include "ISortStrategy.cpp"

using namespace std;

class Bubble : public ISortStrategy {

public:

    /// @brief Realiza el ordenamiento de arreglos por Bubble sort comparando por dinero robado.
/// @param arr: Arreglo de politicos.
/// @return numero de iteracions realizadas.

    double sortArreglo(vector<Politico>& arr) override {
        double iteraciones = 0;
        int n = arr.size();
        bool swapped;
        for (int i = 0; i < n - 1; i++) {
            swapped = false;
            for (int j = 0; j < n - 1 - i; j++) {
                iteraciones++;
                if (arr[j].getDineroRobado() < arr[j + 1].getDineroRobado()) {
                    swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
        return iteraciones;
    }

};