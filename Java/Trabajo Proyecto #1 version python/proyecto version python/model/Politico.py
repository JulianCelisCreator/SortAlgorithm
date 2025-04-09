from datetime import date, timedelta
import random
""" Clase politico es la clase abstracta que permite generar objetos tipo politico
"""
class Politico:
    _next_id = 1
    """ metodo __init__ declara los atributos que tienen los objetos tipo politico"""
    def __init__(self, dinero, fecha_nacimiento):
        self.id = Politico._next_id
        Politico._next_id += 1
        self.dinero = dinero
        self.fecha_nacimiento = fecha_nacimiento
    """ metodo __str__ retorna el objeto tipo politico con los datos asignados"""
    def __str__(self):
        return f"ID: {self.id}, Dinero: {self.dinero}, Nacimiento: {self.fecha_nacimiento.strftime('%d/%m/%Y')}"
    """ metodo generar_fecha_aleatoria se encarga de generar aleatoriamente las
        fechas de los politicos entre 1/01/1950 y 12/31/2000"""
    @classmethod
    def generar_fecha_aleatoria(cls):
        start_date = date(1950, 1, 1)
        end_date = date(2000, 12, 31)
        days_between = (end_date - start_date).days
        random_days = random.randint(0, days_between)
        return start_date + timedelta(days=random_days)