package com.mycompany.sort.model;

import java.util.Date;

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
    private Date fecha;

    public Politico(int dinero, Date fecha) {
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
}


