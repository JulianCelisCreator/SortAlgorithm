package com.mycompany.sort.model.datahandler;

import com.mycompany.sort.model.politico.Politico;

public class ReverseOrderHandler extends DataGeneratorHandler {
    @Override
    public Politico[] generateData(String type, int n) {
        if (!type.equalsIgnoreCase("REVERSE") && nextHandler != null) {
            return nextHandler.generateData(type, n);
        }
        Politico[] politicians = new Politico[n];
        for (int i = 0; i < n; i++) {
            politicians[i] = new Politico(1000000 - (i * 1000), RandomDateGenerator.generateRandomDate());
        }
        return politicians;
    }
}