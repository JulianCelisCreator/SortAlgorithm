#include <iostream>
#include <vector>
#include "Politico.cpp"
#include "ISortStrategy.cpp"
using namespace std;

class Insertion : public ISortStrategy {

public:

    /// @brief Realiza el ordenamiento de arreglos por Insertion sort comparando por dinero robado.
/// @param arr: Arreglo de politicos.
/// @return numero de iteracions realizadas.

    double sortArreglo(vector<Politico>& arr) override {
        double iteraciones = 0;
        int n = arr.size();
        for (int i = 1; i < n; i++) {
            iteraciones++;
            Politico  key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j].getDineroRobado() < key.getDineroRobado()) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
        return iteraciones;
    }

};