from abc import ABC, abstractmethod
""" Clase AlgoritmoOrdenamiento se encarga de crear el metodo ordenar
    para aplicarlo en los tipos de ordenamiento disponibles"""

class AlgoritmoOrdenamiento(ABC):
    @abstractmethod
    def ordenar(self, politicos, criterio='dinero'):
        pass
