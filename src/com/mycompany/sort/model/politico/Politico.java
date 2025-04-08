package com.mycompany.sort.model.politico;

import java.time.LocalDate;

/**
 * Clase que modela a un politico de APOCO
 *
 * @author juliancelis
 * @email jdcelis@udistrital.edu.co
 *
 */
public class Politico {
    private static int ultimoID = 1;
    private int id;
    private int dinero;
    private LocalDate fecha;

    public Politico(int dinero, LocalDate fecha) {
        this.id = ultimoID++;
        this.dinero = dinero;
        this.fecha = fecha;
    }

    public int getId() {
        return id;
    }
    public void setId(int id) {
        this.id = id;
    }

    public int getDinero() {
        return dinero;
    }

    public void setDinero(int dinero) {
        this.dinero = dinero;
    }

    public LocalDate getFecha() {
        return fecha;
    }
}


