from model.AlgoritmoOrdenamiento import AlgoritmoOrdenamiento

""" Clase MergeSort realiza el ordenamiento de datos mediante el metodo por mezcla
"""

class MergeSort(AlgoritmoOrdenamiento):
    def ordenar(self, politicos, criterio='dinero'):
        iteraciones = 0
        n = len(politicos)
        tamano = 1

        while tamano < n:
            izquierda = 0
            while izquierda < n:
                medio = min(izquierda + tamano - 1, n - 1)
                derecha = min(izquierda + 2 * tamano - 1, n - 1)

                # Fusionar y contar iteraciones
                iters = self._fusionar(politicos, izquierda, medio, derecha, criterio)
                iteraciones += iters

                izquierda += 2 * tamano
            tamano *= 2

        return iteraciones

    """ metodo _fusionar se encarga de comparar los arreglos tribiales y
        unirlos en un solo arreglo de manera ordenada"""
    def _fusionar(self, arr, izquierda, medio, derecha, criterio):
        iteraciones = 0
        temp = []
        i, j = izquierda, medio + 1

        while i <= medio and j <= derecha:
            iteraciones += 1
            if getattr(arr[i], criterio) <= getattr(arr[j], criterio):
                temp.append(arr[i])
                i += 1
            else:
                temp.append(arr[j])
                j += 1

        temp.extend(arr[i:medio + 1])
        temp.extend(arr[j:derecha + 1])

        for idx in range(len(temp)):
            arr[izquierda + idx] = temp[idx]

        return iteraciones