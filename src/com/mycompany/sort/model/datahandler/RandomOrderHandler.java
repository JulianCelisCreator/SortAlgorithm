package com.mycompany.sort.model.datahandler;

import com.mycompany.sort.model.politico.Politico;

import java.util.Random;

public class RandomOrderHandler extends DataGeneratorHandler{
    public Politico[] generateData(String type, int n) {
        if(!type.equalsIgnoreCase("random") && nextHandler != null) {
            return nextHandler.generateData(type, n);
        }
        Politico[] politicos = new Politico[n];
        Random rand = new Random();
        for (int i = 0; i < n; i++) {
            politicos[i] = new Politico (rand.nextInt(990000) + 100, RandomDateGenerator.generateRandomDate());
        }
        return politicos;
    }
}
