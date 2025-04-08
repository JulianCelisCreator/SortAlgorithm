package com.mycompany.sort.model.datahandler;

import com.mycompany.sort.model.politico.Politico;

import java.util.Arrays;
import java.util.Collections;

public class ReverseOrderHandler extends DataGeneratorHandler {
    @Override
    public Politico[] generateData(String type, int size) {
        if ("INVERSE".equalsIgnoreCase(type)) {
            // Generar datos ordenados y luego invertirlos
            Politico[] data = new SortedOrderHandler().generateData("SORTED", size);
            Collections.reverse(Arrays.asList(data));
            return data;
        }

        // Delegar al siguiente manejador si no es "INVERSE"
        if (nextHandler != null) {
            return nextHandler.generateData(type, size);
        }

        throw new IllegalArgumentException("Tipo no soportado: " + type);
    }
}