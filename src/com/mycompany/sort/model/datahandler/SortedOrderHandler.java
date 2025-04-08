package com.mycompany.sort.model.datahandler;

import com.mycompany.sort.model.politico.Politico;

import java.time.LocalDate;
import java.util.Arrays;
import java.util.Comparator;

public class SortedOrderHandler extends DataGeneratorHandler {
    @Override
    public Politico[] generateData(String type, int size) {
        if ("SORTED".equalsIgnoreCase(type)) {
            Politico[] data = new Politico[size];
            for (int i = 0; i < size; i++) {
                data[i] = new Politico(i * 1000, LocalDate.now().minusYears(i % 50));
            }
            Arrays.sort(data, Comparator.comparingInt(Politico::getDinero));
            return data;
        } else if (nextHandler != null) {
            return nextHandler.generateData(type, size);
        } else {
            throw new IllegalArgumentException("Tipo no soportado: " + type);
        }
    }
}