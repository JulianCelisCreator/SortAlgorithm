# Añadir un combobox para seleccionar criterio de ordenamiento
import tkinter as tk
from tkinter import ttk, messagebox
from controller.OrdenadorController import OrdenadorController

""" clase InterfazApp se encarga de hacer de vista dentro del modelo
    MVC llamando a un controlador y sirviendo de GUI para la recepcion
    de los datos tamaño inicial y el factor de crecimiento
    
    elaborado por: Juan Esteban Jurado Martinez
"""
class InterfazApp:
    """ metodo __init__ para inicializar el root, controller y
        configurar la GUI
    """
    def __init__(self, root):
        self.root = root
        self.controller = OrdenadorController()
        self._configurar_ui()
    """ metodo _configurar_ui se encarga de creat la GUI 
    """
    def _configurar_ui(self):
        self.root.title("Pruebas de Rendimiento APOCO")
        self.root.geometry("600x400")

        ttk.Label(self.root, text="Tamaño inicial (n):").grid(row=0, column=0, padx=5, pady=5)
        self.entry_n = ttk.Entry(self.root)
        self.entry_n.grid(row=0, column=1, padx=5, pady=5)
        self.entry_n.insert(0, "")

        ttk.Label(self.root, text="Factor de crecimiento:").grid(row=1, column=0, padx=5, pady=5)
        self.entry_factor = ttk.Entry(self.root)
        self.entry_factor.grid(row=1, column=1, padx=5, pady=5)
        self.entry_factor.insert(0, "2")

        ttk.Button(self.root, text="Ejecutar Pruebas", command=self.ejecutar_pruebas).grid(row=3, columnspan=2, pady=10)

        self.text_resultados = tk.Text(self.root, height=15, width=70)
        self.text_resultados.grid(row=4, columnspan=2, padx=10, pady=10)

        scrollbar = ttk.Scrollbar(self.root, command=self.text_resultados.yview)
        scrollbar.grid(row=4, column=2, sticky='nsew')
        self.text_resultados['yscrollcommand'] = scrollbar.set

    """ metodo ejecutar_pruebas se encarga de realizar la ejecucion de
        la prueba llamando al objeto controller de tipo OrdenadorController
        y muestre los resultados del programa
    """
    def ejecutar_pruebas(self):
        try:
            n_inicial = int (self.entry_n.get())
            factor = float(self.entry_factor.get())

            self.text_resultados.delete(1.0, tk.END)
            self.text_resultados.insert(tk.END, "Iniciando pruebas...\n")
            self.root.update()

            controller = OrdenadorController()
            resultados, archivo_pdf = controller.ejecutar_pruebas_continuas(n_inicial, factor,)

            self.text_resultados.insert(tk.END, "\nResultados promediados:\n")
            self.text_resultados.insert(tk.END, "-" * 50 + "\n")

            for alg, datos in resultados.items():
                self.text_resultados.insert(tk.END,
                                            f"{alg}:\n"
                                            f"  Iteraciones promedio: {datos['iteraciones_promedio']:.2f}\n"
                                            f"  Tiempo promedio: {datos['tiempo_promedio']:.4f} seg\n"
                                            f"  Ejecuciones: {datos['total_ejecuciones']}\n"
                                            f"-" * 50 + "\n"
                                            )

            self.text_resultados.insert(tk.END, f"\nPDF generado: {archivo_pdf}\n")
            if messagebox.askyesno("PDF Generado", "¿Desea abrir el archivo PDF con los resultados?"):
                import os
                os.startfile(archivo_pdf)
        except ValueError:
            messagebox.showerror("Error", "Ingrese valores numéricos válidos")
        except Exception as e:
            messagebox.showerror("Error", f"Ocurrió un error: {str(e)}")

