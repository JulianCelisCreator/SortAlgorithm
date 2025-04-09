from model.AlgoritmoOrdenamiento import AlgoritmoOrdenamiento

""" la Clase BubbleSort realiza el ordenamiento de datos mediante el metodo Burbuja
"""
class BubbleSort(AlgoritmoOrdenamiento):
    """ metodo ordenar hereda de AlgoritmoOrdenamiento aplicando
        el metodo de ordenamiento Burbuja y retorna la cantidad de iteraciones
    """
    def ordenar(self, politicos, criterio='dinero'):
        iteraciones = 0
        n = len(politicos)
        for i in range(n):
            for j in range(0, n - i - 1):
                iteraciones += 1  # Comparación
                if criterio == 'dinero':
                    condicion = politicos[j].dinero > politicos[j + 1].dinero
                else:  # 'fecha'
                    condicion = politicos[j].fecha_nacimiento > politicos[j + 1].fecha_nacimiento

                if condicion:
                    politicos[j], politicos[j + 1] = politicos[j + 1], politicos[j]
                    iteraciones += 1  # Intercambio
        return iteraciones