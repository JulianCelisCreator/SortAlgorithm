from model.AlgoritmoOrdenamiento import AlgoritmoOrdenamiento

""" clase QuickSort realiza el ordenamiento de datos mediante el metodo Quick """
class QuickSort(AlgoritmoOrdenamiento):
    def ordenar(self, politicos, criterio='dinero'):
        iteraciones = 0
        pila = [(0, len(politicos) - 1)]

        while pila:
            low, high = pila.pop()
            if low < high:
                pi, iters = self._particion(politicos, low, high, criterio)
                iteraciones += iters
                pila.append((low, pi - 1))
                pila.append((pi + 1, high))

        return iteraciones

    """ metodo _particion es aquel que asigna un pivote y divide el arreglo
        en secciones mas pequeñas hasta llegar al caso tribial"""
    def _particion(self, arr, low, high, criterio):
        iteraciones = 0
        pivot = getattr(arr[high], criterio)
        i = low - 1

        for j in range(low, high):
            iteraciones += 1
            if getattr(arr[j], criterio) <= pivot:
                i += 1
                arr[i], arr[j] = arr[j], arr[i]

        arr[i + 1], arr[high] = arr[high], arr[i + 1]
        return i + 1, iteraciones