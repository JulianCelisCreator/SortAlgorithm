#pragma once

#define WIN32_LEAN_AND_MEAN
#define _WIN32_DCOM
#include <windows.h>
#include "../Controlador/Controlador.h"
#include <msclr/marshal_cppstd.h>  

namespace CppCLRWinformsProjekt {

	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace msclr::interop;

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			controlador = new Controlador();
			this->WindowState = FormWindowState::Maximized;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
		}

	protected:
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	public : event System::EventHandler^ CalcularClick;
	private: Label^ labelTitulo;
	private: Label^ labelTamanoInicial;
	private: Label^ labelTasaCrecimiento;
	private: Label^ labelTablaArreglos;
	private: Label^ labelTablaMatriz;
	private: TextBox^ TamanoInicialText;
	private: TextBox^ TasaCrecimientoText;
	private: Button^ btnCalcular;
	private: DataGridView^ tablaArreglo;
	private: DataGridView^ tablaMatriz;

	private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->labelTitulo = (gcnew System::Windows::Forms::Label());
			   this->labelTamanoInicial = (gcnew System::Windows::Forms::Label());
			   this->labelTasaCrecimiento = (gcnew System::Windows::Forms::Label());
			   this->TamanoInicialText = (gcnew System::Windows::Forms::TextBox());
			   this->TasaCrecimientoText = (gcnew System::Windows::Forms::TextBox());
			   this->btnCalcular = (gcnew System::Windows::Forms::Button());
			   this->tablaArreglo = (gcnew System::Windows::Forms::DataGridView());
			   this->tablaMatriz = (gcnew System::Windows::Forms::DataGridView());
			   this->labelTablaArreglos = (gcnew System::Windows::Forms::Label());
			   this->labelTablaMatriz = (gcnew System::Windows::Forms::Label());

			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tablaArreglo))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tablaMatriz))->BeginInit();
			   this->SuspendLayout();

			   // Título
			   this->labelTitulo->AutoSize = true;
			   this->labelTitulo->Font = (gcnew System::Drawing::Font(L"Book Antiqua", 16, System::Drawing::FontStyle::Bold));
			   this->labelTitulo->Location = System::Drawing::Point(550, 30);
			   this->labelTitulo->Name = L"labelTitulo";
			   this->labelTitulo->Size = System::Drawing::Size(280, 32);
			   this->labelTitulo->Text = L"Algoritmos de ordenamiento";

			   // Tamaño inicial
			   this->labelTamanoInicial->AutoSize = true;
			   this->labelTamanoInicial->Location = System::Drawing::Point(500, 90);
			   this->labelTamanoInicial->Text = L"Tamaño inicial:";
			   this->TamanoInicialText->Location = System::Drawing::Point(650, 87);
			   this->TamanoInicialText->Size = System::Drawing::Size(120, 20);

			   // Tasa crecimiento
			   this->labelTasaCrecimiento->AutoSize = true;
			   this->labelTasaCrecimiento->Location = System::Drawing::Point(500, 130);
			   this->labelTasaCrecimiento->Text = L"Tasa de crecimiento (%):";
			   this->TasaCrecimientoText->Location = System::Drawing::Point(650, 127);
			   this->TasaCrecimientoText->Size = System::Drawing::Size(120, 20);

			   // Botón
			   this->btnCalcular->Location = System::Drawing::Point(600, 170);
			   this->btnCalcular->Size = System::Drawing::Size(100, 30);
			   this->btnCalcular->Text = L"Calcular";
			   this->btnCalcular->Click += gcnew System::EventHandler(this, &Form1::btnCalcular_Click);

			   // Label tabla 1
			   this->labelTablaArreglos->AutoSize = true;
			   this->labelTablaArreglos->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			   this->labelTablaArreglos->Location = System::Drawing::Point(260, 230);
			   this->labelTablaArreglos->Text = L"Resultados de arreglos";
			   this->labelTablaArreglos->Visible = false;

			   // Label tabla 2
			   this->labelTablaMatriz->AutoSize = true;
			   this->labelTablaMatriz->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			   this->labelTablaMatriz->Location = System::Drawing::Point(870, 230);
			   this->labelTablaMatriz->Text = L"Resultados de matrices";
			   this->labelTablaMatriz->Visible = false;

			   // Tabla 1
			   this->tablaArreglo->Location = System::Drawing::Point(150, 260);
			   this->tablaArreglo->Size = System::Drawing::Size(500, 180);
			   this->tablaArreglo->Visible = false;

			   // Tabla 2
			   this->tablaMatriz->Location = System::Drawing::Point(750, 260);
			   this->tablaMatriz->Size = System::Drawing::Size(500, 180);
			   this->tablaMatriz->Visible = false;

			   // Form1
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1400, 600);
			   this->Controls->Add(this->labelTitulo);
			   this->Controls->Add(this->labelTamanoInicial);
			   this->Controls->Add(this->TamanoInicialText);
			   this->Controls->Add(this->labelTasaCrecimiento);
			   this->Controls->Add(this->TasaCrecimientoText);
			   this->Controls->Add(this->btnCalcular);
			   this->Controls->Add(this->labelTablaArreglos);
			   this->Controls->Add(this->labelTablaMatriz);
			   this->Controls->Add(this->tablaArreglo);
			   this->Controls->Add(this->tablaMatriz);
			   this->Text = L"Algoritmos de ordenamiento";

			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tablaArreglo))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tablaMatriz))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();
		   }
#pragma endregion

		   private:
			   Controlador* controlador;

			   /**
 * @brief Evento que se ejecuta al hacer clic en el botón "Calcular".
 *
 * Este método obtiene los valores de entrada del usuario desde los campos de texto
 * para el tamaño inicial y la tasa de crecimiento. Convierte estos valores a sus
 * respectivos tipos (int y double) y luego llama al método eventoBoton del
 * controlador para realizar cálculos sobre estructuras de datos (arreglo y matriz)
 * de objetos Politico, utilizando diferentes estrategias de ordenamiento.
 *
 * Los resultados del ordenamiento son almacenados en dos vectores y mostrados en la
 * interfaz gráfica mediante el método `mostrarResultados`.
 *
 * @param sender Objeto que genera el evento (no se utiliza).
 * @param e Argumentos del evento (no se utiliza).
 */

	private: System::Void btnCalcular_Click(System::Object^ sender, System::EventArgs^ e) {
		vector<ResultadoOrdenamiento> resultadosArreglo;
		vector<ResultadoOrdenamiento> resultadosMatriz;

		msclr::interop::marshal_context contexto;

		std::string tamanoInicialStr = contexto.marshal_as<std::string>(TamanoInicialText->Text);
		std::string tasaCrecimientoStr = contexto.marshal_as<std::string>(TasaCrecimientoText->Text);
		int tamanoInicial = 0;
		double tasaCrecimiento = 0;
		try {
			tamanoInicial = std::stoi(tamanoInicialStr);
		}
		catch (const std::exception& e) {
			MessageBox::Show("Valor no válido. Por favor, ingresa un número entero.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}

		try {
			tasaCrecimiento = std::stoi(tasaCrecimientoStr);
		}
		catch (const std::exception& e) {
			MessageBox::Show("Valor no válido. Por favor, ingresa un número entero.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}

		if (controlador == nullptr) {
			MessageBox::Show("Controlador no inicializado");
			return;
		}
		
		controlador->eventoBoton(tamanoInicial , tasaCrecimiento, resultadosArreglo, resultadosMatriz);

		if (resultadosArreglo.empty() && resultadosMatriz.empty()) {
			MessageBox::Show("Los vectores están vacíos. Revisa el método del controlador.");
		}
		mostrarResultados(resultadosArreglo, resultadosMatriz);

	}

		   /**
 * @brief Muestra los resultados del ordenamiento en las tablas de la interfaz gráfica.
 *
 * Este método toma dos vectores de ResultadoOrdenamiento, correspondientes a los resultados
 * de ordenamiento sobre estructuras de datos tipo arreglo y matriz. Luego, muestra los datos
 * (tipo, algoritmo, tiempo promedio e iteraciones promedio) en los `DataGridView` respectivos
 * de la vista (`tablaArreglo` y `tablaMatriz`), asegurando además que sus etiquetas asociadas
 * sean visibles.
 *
 * @param arreglo Vector que contiene los resultados del ordenamiento de estructuras tipo arreglo.
 * @param matriz Vector que contiene los resultados del ordenamiento de estructuras tipo matriz.
 */

		   void mostrarResultados(
			   const std::vector<ResultadoOrdenamiento>& arreglo,
			   const std::vector<ResultadoOrdenamiento>& matriz)
		   {
			   this->tablaArreglo->Visible = true;
			   this->tablaMatriz->Visible = true;
			   this->labelTablaArreglos->Visible = true;
			   this->labelTablaMatriz->Visible = true;

			   tablaArreglo->Rows->Clear();
			   tablaArreglo->Columns->Add("TipoDatos", "Tipo de Datos");
			   tablaArreglo->Columns->Add("Algoritmo", "Algoritmo");
			   tablaArreglo->Columns->Add("Tiempo", "Tiempo Promedio (Seg)");
			   tablaArreglo->Columns->Add("Iteraciones", "Iteraciones Promedio");
			   tablaMatriz->Rows->Clear();
			   tablaMatriz->Columns->Add("TipoDatos", "Tipo de Datos");
			   tablaMatriz->Columns->Add("Algoritmo", "Algoritmo");
			   tablaMatriz->Columns->Add("Tiempo", "Tiempo Promedio (Seg)");
			   tablaMatriz->Columns->Add("Iteraciones", "Iteraciones Promedio");

			   for (const auto& r : arreglo) {
				   tablaArreglo->Rows->Add(
					   gcnew String(r.tipoDatos.c_str()),
					   gcnew String(r.algoritmo.c_str()),
					   r.tiempoPromedio,
					   r.iteracionesPromedio
				   );
			   }

			   for (const auto& m : matriz) {
				   tablaMatriz->Rows->Add(
					   gcnew String(m.tipoDatos.c_str()),
					   gcnew String(m.algoritmo.c_str()),
					   m.tiempoPromedio,
					   m.iteracionesPromedio
				   );
			   }
		   }

	};
}

