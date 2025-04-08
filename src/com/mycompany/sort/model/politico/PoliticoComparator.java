package com.mycompany.sort.model.politico;

import java.time.LocalDate;
import java.time.temporal.ChronoUnit;
import java.util.Comparator;
public class PoliticoComparator {
    public static Comparator<Politico> porDinero() {
        return Comparator.comparingInt(Politico::getDinero);
    }

    public static Comparator<Politico> porEdad() {
        return Comparator.comparing(p -> {
            long years = ChronoUnit.YEARS.between(p.getFecha(), LocalDate.now());
            return (int) years;
        });
    }
}
