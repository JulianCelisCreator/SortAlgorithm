#pragma once
#include <iostream>
#include <ctime>
using namespace std;

/**
 * @class Politico
 * @brief Representa a un pol�tico con informaci�n ID, fecha de nacimiento y dinero robado.
 *
 * La clase proporciona m�todos para acceder y modificar los atributos, calcular la edad
 * y comparar edades
 */

class Politico
{

public:
    /// Identificador �nico del pol�tico
    int id;
    /// Fecha de nacimiento del pol�tico
    std::tm fechaNacimiento;
    /// Cantidad de dinero robado por el pol�tico 
    int dineroRobado;

public:

    /**
     * @brief Constructor por defecto.
     *
     * Inicializa el ID y dinero robado a cero. La fecha de nacimiento se establece a la fecha actual.
     */
    Politico() : id(0), dineroRobado(0) {
        std::time_t t = std::time(NULL);
        tm tmpTime;
        localtime_s(&tmpTime, &t);
        fechaNacimiento = tmpTime;
    }

    /**
     * @brief Constructor con par�metros.
     * @param _id ID del pol�tico.
     * @param _dineroRobado Cantidad de dinero robado.
     * @param _fechaNacimiento Fecha de nacimiento.
     */

    Politico(int _id, int _dineroRobado, std::tm _fechaNacimiento)
        : id(_id), dineroRobado(_dineroRobado), fechaNacimiento(_fechaNacimiento) {}


    /**
     * @brief Operador de comparaci�n por dinero robado.
     * @param otro Otro objeto Politico.
     * @return true si el pol�tico actual ha robado menos dinero que el otro.
     */

    bool operator<(const Politico& otro) const {
        return dineroRobado < otro.dineroRobado;
    }

    /// @return El ID del pol�tico.

    int getId() const
    {
        return id;
    }

    /// @param _id Nuevo ID del pol�tico.
    void setId(int _id)
    {
        id = _id;
    }

    /// @return Fecha de nacimiento del pol�tico.
    std::tm getFechaNacimiento() const
    {
        return fechaNacimiento;
    }
    /// @param _fechaNacimiento Nueva fecha de nacimiento.
    void setFechaNacimiento(std::tm _fechaNacimiento)
    {
        fechaNacimiento = _fechaNacimiento;
    }

    /// @return Cantidad de dinero robado.
    int getDineroRobado() const
    {
        return dineroRobado;
    }

    /// @param _dineroRobado Nueva cantidad de dinero robado.
    void setDineroRobado(int _dineroRobado)
    {
        dineroRobado = _dineroRobado;
    }
    /// @return A�o de nacimiento.
    int getAnio() const { return fechaNacimiento.tm_year + 1900; }
    /// @return Mes de nacimiento.
    int getMes() const { return fechaNacimiento.tm_mon + 1; }
    /// @return Dia de nacimiento.
    int getDia() const { return fechaNacimiento.tm_mday; }

    /**
     * @brief Calcula la edad actual del pol�tico.
     * @return Edad en a�os, calculada a partir de la fecha de nacimiento y la fecha actual.
     */

    int calcularEdad() const {
        std::tm fechaActual = {};
        time_t t = time(0);

        localtime_s(&fechaActual, &t);

        int edad = fechaActual.tm_year + 1900 - (fechaNacimiento.tm_year + 1900);

        if (fechaActual.tm_mon < fechaNacimiento.tm_mon ||
            (fechaActual.tm_mon == fechaNacimiento.tm_mon && fechaActual.tm_mday < fechaNacimiento.tm_mday)) {
            edad--;
        }

        return edad;
    }

    /**
     * @brief Compara la edad entre dos pol�ticos.
     * @param p1 Primer pol�tico.
     * @param p2 Segundo pol�tico.
     * @return true si p1 es menor que p2 en edad.
     */

    static bool compararEdades(const Politico& p1, const Politico& p2) {
        return p1.calcularEdad() < p2.calcularEdad();
    }

};