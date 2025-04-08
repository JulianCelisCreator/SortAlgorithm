package com.mycompany.sort.model.politico;

import java.util.Comparator;
public class PoliticoComparator {
    public static Comparator<Politico> porDinero() {
        return Comparator.comparingInt(Politico::getDinero);
    }

    public static Comparator<Politico> porEdad() {
        return Comparator.comparing(Politico::getFecha).reversed();
    }
}
