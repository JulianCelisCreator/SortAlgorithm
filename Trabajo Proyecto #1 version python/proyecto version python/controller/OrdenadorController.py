import psutil
from model.GeneradorDatosHandler import GeneradorAleatorio, GeneradorParcial, GeneradorInverso
from model.BubbleSort import BubbleSort
from model.SelectionSort import SelectionSort
from model.InsertionSort import InsertionSort
from model.MergeSort import MergeSort
from model.QuickSort import QuickSort
import time
import numpy as np
from datetime import datetime
from reportlab.lib import colors
from reportlab.lib.pagesizes import letter,inch
from reportlab.platypus import SimpleDocTemplate, Table, TableStyle, Paragraph, Spacer, Image
from reportlab.lib.styles import getSampleStyleSheet, ParagraphStyle
from reportlab.lib.enums import TA_CENTER
import matplotlib.pyplot as plt
import io

""" clase OrdenadorController es aquella que se encarga de hacer el llamado
    a los metodos de ordenamiento y generacion de datos para posteriormente
    ordenarlos, tomar el tiempo de ejecucion e iteraciones y generar un
    documento con dicha informacion
    
    elaborado por: Juan Esteban Jurado Martinez
"""
class OrdenadorController:
    """ metodo _configurar_generadores se encarga de crear los generadores
        de datos aleatorios, parcialmente ordenado e inversamente ordenado
        para posteriormente ser utilizados por los metodos de ordenamiento
    """
    @staticmethod
    def _configurar_generadores():
        aleatorio = GeneradorAleatorio()
        parcial = GeneradorParcial()
        inverso = GeneradorInverso()
        aleatorio.set_next(parcial).set_next(inverso)
        return aleatorio

    """ metodo __init__ para inicializar los generadores y los arlgoritmos
        de ordenamiento
    """
    def __init__(self):
        self.generadores = self._configurar_generadores()
        self.algoritmos = {
            "BubbleSort": BubbleSort(),
            "SelectionSort": SelectionSort(),
            "InsertionSort": InsertionSort(),
            "MergeSort": MergeSort(),
            "QuickSort": QuickSort()
        }
        self.resultados = {alg: {"iteraciones": [], "tiempos": []} for alg in self.algoritmos.keys()}

    """ metodo _generar_grafico crea un grafico de barras dentro del archivo
        pdf generado donde se muestra la diferencia en tiempo de ejecucion
        entre los algoritmos de ordenamiento
    """
    @staticmethod
    def _generar_grafico(datos):
        algoritmos = list(datos.keys())
        tiempos = [sum(datos[alg]["tiempos"]) / len(datos[alg]["tiempos"]) for alg in algoritmos]

        plt.figure(figsize=(8, 4))
        bars = plt.bar(algoritmos, tiempos, color=['#1f77b4', '#ff7f0e', '#2ca02c', '#d62728', '#9467bd'])
        plt.title("Tiempo de ejecución por algoritmo")
        plt.ylabel("Segundos")

        for bar in bars:
            height = bar.get_height()
            plt.text(bar.get_x() + bar.get_width() / 2., height,
                     f'{height:.4f}s',
                     ha='center', va='bottom')

        buf = io.BytesIO()
        plt.savefig(buf, format='png', dpi=150, bbox_inches='tight')
        plt.close()
        buf.seek(0)
        return buf

    """ metodo _crear_reportes se encarga de generar el documento pdf con
        toda la información detallada sobre las iteraciones y tiempos de 
        ejecuciones de los algoritmos de ordenamiento
    """
    def _crear_reporte(self, promedios):
        nombre_archivo = f"Reporte_APOCO_{datetime.now().strftime('%Y%m%d_%H%M')}.pdf"
        doc = SimpleDocTemplate(nombre_archivo, pagesize=letter)

        estilos = getSampleStyleSheet()
        estilo_titulo = ParagraphStyle(
            'Titulo',
            parent=estilos['Heading1'],
            fontSize=16,
            alignment=TA_CENTER,
            spaceAfter=20,
            textColor=colors.HexColor("#003366")
        )

        elementos = [Paragraph("RESULTADOS DE ORDENAMIENTO APOCO", estilo_titulo), Paragraph(
            f"<b>Fecha:</b> {datetime.now().strftime('%d/%m/%Y %H:%M:%S')}<br/>"
            f"<b>Generado por:</b> Sistema de Análisis APOCO",
            estilos["Normal"]
        ), Spacer(1, 20)]

        encabezados = ["Algoritmo", "Iteraciones Promedio", "Tiempo Promedio (s)", "Ejecuciones"]
        datos_tabla = [encabezados]

        for alg, datos in promedios.items():
            datos_tabla.append([
                alg,
                f"{datos['iteraciones_promedio']:.2f}",
                f"{datos['tiempo_promedio']:.4f}",
                datos['total_ejecuciones']
            ])

        tabla = Table(datos_tabla, colWidths=[1.5 * inch, 1.5 * inch, 1.5 * inch, 1 * inch])
        tabla.setStyle(TableStyle([
            ('BACKGROUND', (0, 0), (-1, 0), colors.HexColor("#003366")),
            ('TEXTCOLOR', (0, 0), (-1, 0), colors.whitesmoke),
            ('ALIGN', (0, 0), (-1, -1), 'CENTER'),
            ('FONTNAME', (0, 0), (-1, 0), 'Helvetica-Bold'),
            ('FONTSIZE', (0, 0), (-1, 0), 10),
            ('BOTTOMPADDING', (0, 0), (-1, 0), 12),
            ('BACKGROUND', (0, 1), (-1, -1), colors.HexColor("#f0f0f0")),
            ('GRID', (0, 0), (-1, -1), 1, colors.lightgrey),
        ]))
        elementos.append(tabla)
        elementos.append(Spacer(1, 30))

        # 4. Gráfico
        elementos.append(Paragraph("COMPARACIÓN DE RENDIMIENTO", estilos["Heading2"]))
        img_buffer = self._generar_grafico(promedios)
        elementos.append(Image(img_buffer, width=6 * inch, height=3 * inch))

        # 5. Observaciones
        mejor_algoritmo = min(promedios.items(), key=lambda x: x[1]["tiempo_promedio"])
        peor_algoritmo = max(promedios.items(), key=lambda x: x[1]["tiempo_promedio"])

        elementos.append(Spacer(1, 20))
        elementos.append(Paragraph(
            "<b>Observaciones:</b><br/>"
            f"• <b>{mejor_algoritmo[0]}</b> demostró el mejor rendimiento ({mejor_algoritmo[1]['tiempo_promedio']:.4f}s)<br/>"
            f"• <b>{peor_algoritmo[0]}</b> requiere optimización ({peor_algoritmo[1]['tiempo_promedio']:.4f}s)<br/>"
            "• Los tiempos incluyen ordenamiento por dinero y edad",
            estilos["Normal"]
        ))

        doc.build(elementos)
        return nombre_archivo

    """ metodo _ejecutar_algoritmo se encarga de aplicar los algoritmos y
        transformar los arreglos ordenados en matrices para ordenar
    """
    @staticmethod
    def _ejecutar_algoritmo(algoritmo, datos):
        inicio_arreglo = time.time()
        iteraciones = algoritmo.ordenar(datos, 'dinero')
        tiempo_arreglo = time.time() - inicio_arreglo

        k = int(np.sqrt(len(datos)))
        m = len(datos) // k
        matriz = np.array(datos[:k * m]).reshape(k, m)

        inicio_edad = time.time()
        for col in range(m):
            columna = matriz[:, col].tolist()
            algoritmo.ordenar(columna, 'fecha_nacimiento')
            matriz[:, col] = columna
        for fil in range(m):
            fila = matriz[fil, :].tolist()
            algoritmo.ordenar(fila, 'fecha_nacimiento')
            matriz[:, fil] = fila
        tiempo_arreglo += time.time() - inicio_edad
        return iteraciones, tiempo_arreglo,

    """ metodo ejecutar_pruebas_continuas se encarga de ejecutar el programa 
        continuamente hasta agotar los recursos asignados al programa
    """
    def ejecutar_pruebas_continuas(self, n_inicial= "", factor_crecimiento=2):
        self.resultados = {alg: {"iteraciones": [], "tiempos": []} for alg in self.algoritmos.keys()}
        n = n_inicial

        try:
            while True:
                self._verificar_recursos()
                print(f"Ejecutando con n = {n}", end='\r')

                for tipo in ["ALEATORIO", "PARCIAL", "INVERSO"]:
                    datos = self.generadores.generar(tipo, n)

                    for nombre, algoritmo in self.algoritmos.items():
                        copia = list(datos)
                        iters, tiempo = self._ejecutar_algoritmo(algoritmo, copia)

                        self.resultados[nombre]["iteraciones"].append(iters)
                        self.resultados[nombre]["tiempos"].append(tiempo)

                n = int(n * factor_crecimiento)

        except (MemoryError, self.RecursosAgotadosException) as e:
            print(f"\nDetenido por: {str(e)}")
        finally:
            promedios = self._calcular_resultados_promedio()
            archivo_pdf = self._crear_reporte(promedios)
            return promedios, archivo_pdf

    """ metodo _verificar_recursos se encarga de monitorear los recursos del
        sistema para evitar llegar a fallos en la ejecucion del programa
    """
    def _verificar_recursos(self):
        if psutil.virtual_memory().percent > 90:
            raise self.RecursosAgotadosException("Uso de memoria > 90%")
        if psutil.cpu_percent() > 85:
            raise self.RecursosAgotadosException("Uso de CPU > 85%")

    """ metodo _calcular_resultados_promedio se encarga de recibir las iteraciones
        y los tiempos totales para luego promediarlo entre la cantidad de 
        ejecuciones
    """
    def _calcular_resultados_promedio(self):
        promedios = {}
        for alg, datos in self.resultados.items():
            if datos["iteraciones"]:
                promedios[alg] = {
                    "iteraciones_promedio": sum(datos["iteraciones"]) / len(datos["iteraciones"]),
                    "tiempo_promedio": sum(datos["tiempos"]) / len(datos["tiempos"]),
                    "total_ejecuciones": len(datos["iteraciones"]),
                    "tiempos": datos["tiempos"],  # Guardamos todos los tiempos para el gráfico
                    "iteraciones": datos["iteraciones"]  # Guardamos todas las iteraciones
                }
        return promedios

    """ metodo RecursosAgotadosException se encarga de terminar el programa cuando
        se quede sin recursos disponibles para seguir ejecutandolo
    """
    class RecursosAgotadosException(Exception):
        pass