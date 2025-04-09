from model.AlgoritmoOrdenamiento import AlgoritmoOrdenamiento

""" Clase SelectionSort realiza el ordenamiento de datos mediante el metodo de seleccion
"""
class SelectionSort(AlgoritmoOrdenamiento):
    """ metodo ordenar hereda de AlgoritmoOrdenamiento aplicando
        el metodo de ordenamiento de seleccion y retorna la cantidad de iteraciones """
    def ordenar(self, politicos, criterio='dinero'):
        iteraciones = 0
        n = len(politicos)
        for i in range(n):
            min_idx = i
            for j in range(i + 1, n):
                iteraciones += 1  # Comparación

                if criterio == 'dinero':
                    condicion = politicos[j].dinero < politicos[min_idx].dinero
                else:  # 'fecha'
                    condicion = politicos[j].fecha_nacimiento < politicos[min_idx].fecha_nacimiento

                if condicion:
                    min_idx = j

            politicos[i], politicos[min_idx] = politicos[min_idx], politicos[i]
            iteraciones += 1  # Intercambio
        return iteraciones

