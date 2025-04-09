import random
from abc import ABC, abstractmethod
from model.Politico import Politico

""" clase GeneradorDatosHandler se encarga de crear los manejadores
    aplicados mediante el patron Chain of Responsability para 
    generar los datos de los politicos aleatoriamente siguiendo el
    tipo de generador (Aleatorio, Parcial e Inverso)
    
    elaborado por: Juan Esteban Jurado Martinez
"""
class GeneradorDatosHandler(ABC):
    """ metodo __init__ para settear el manejador y que no apunte
        hacia ningun lado
    """
    def __init__(self):
        self._next_handler = None
    """ metodo set_next asigna un apuntador al manejador para que
        apunte al siguiente manejador
    """
    def set_next(self, handler):
        self._next_handler = handler
        return handler
    """ metodo generar vacio, debido a que se aplica en otra clase"""
    @abstractmethod
    def generar(self, tipo, n):
        pass
    """ metodo GeneradorAleatorio crea el handler para generar los
        datos de los politicos aleatoriamente
    """
class GeneradorAleatorio(GeneradorDatosHandler):
    def generar(self, tipo, n):
        if tipo != "ALEATORIO" and self._next_handler:
            return self._next_handler.generar(tipo, n)
        return [Politico(random.randint(100, 1000000), Politico.generar_fecha_aleatoria()) for _ in range(n)]
    """ metodo GeneradorParcial crea el handler para generar los
        datos de los politicos parcialmente ordenado
    """
class GeneradorParcial(GeneradorDatosHandler):
    def generar(self, tipo, n):
        if tipo != "PARCIAL" and self._next_handler:
            return self._next_handler.generar(tipo, n)
        data = [Politico(random.randint(100, 1000000), Politico.generar_fecha_aleatoria()) for _ in range(n)]
        data[:n//2] = sorted(data[:n//2], key=lambda x: x.dinero)
        return data
    """ metodo GeneradorInverso crea el handler para generar los
        datos de los politicos ordenado de manera inversa
    """
class GeneradorInverso(GeneradorDatosHandler):
    def generar(self, tipo, n):
        if tipo != "INVERSO" and self._next_handler:
            return self._next_handler.generar(tipo, n)
        data = [Politico(random.randint(100, 1000000), Politico.generar_fecha_aleatoria()) for _ in range(n)]
        return sorted(data, key=lambda x: x.dinero, reverse=True)