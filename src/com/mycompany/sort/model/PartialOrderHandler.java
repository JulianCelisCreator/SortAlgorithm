package com.mycompany.sort.model;

import java.util.Random;

public class PartialOrderHandler extends DataGeneratorHandler {
    @Override
    public Politico[] generateData(String type, int n) {
        if (!type.equals("Parcial") && nextHandler != null) {
            return nextHandler.generateData(type, n);
        }
        Politico[] politicos = new Politico[n];
        Random rand = new Random();
        for (int i = 0; i < n; i++) {
            politicos[i] = new Politico(100 + i * 100, RandomDateGenerator.generateRandomDate());
        }
        for (int i = n/2; i < n; i++) {
            politicos[i] = new Politico(rand.nextInt(990000) + 100, RandomDateGenerator.generateRandomDate());
        }
        return politicos;

    }
}
