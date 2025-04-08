package com.mycompany.sort.model.politico;

import java.time.LocalDate;

public class Politico {
    private final int dinero;
    private final LocalDate fecha;

    public Politico(int dinero, LocalDate fecha) {
        this.dinero = dinero;
        this.fecha = fecha;
    }

    // Getters (sin setters porque es inmutable)
    public int getDinero() {
        return dinero;
    }

    public LocalDate getFecha() {
        return fecha;
    }

    @Override
    public String toString() {
        return String.format("$%,d - %s", dinero, fecha.toString());
    }
}