from model.AlgoritmoOrdenamiento import AlgoritmoOrdenamiento

""" Clase InsertionSort realiza el ordenamiento de datos mediante el metodo de insercion
"""
class InsertionSort(AlgoritmoOrdenamiento):
    """ metodo ordenar hereda de AlgoritmoOrdenamiento aplicando
        el metodo de ordenamiento de insercion y retorna la cantidad de iteraciones"""
    def ordenar(self, politicos, criterio='dinero'):
        iteraciones = 0
        for i in range(1, len(politicos)):
            key = politicos[i]
            j = i - 1

            if criterio == 'dinero':
                while j >= 0 and key.dinero < politicos[j].dinero:
                    iteraciones += 1  # Comparación + Desplazamiento
                    politicos[j + 1] = politicos[j]
                    j -= 1
            else:  # 'fecha'
                while j >= 0 and key.fecha_nacimiento < politicos[j].fecha_nacimiento:
                    iteraciones += 1  # Comparación + Desplazamiento
                    politicos[j + 1] = politicos[j]
                    j -= 1

            politicos[j + 1] = key
            iteraciones += 1  # Intercambio final
        return iteraciones

