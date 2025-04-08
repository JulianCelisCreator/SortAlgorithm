package com.mycompany.sort.model.datahandler;

import com.mycompany.sort.model.politico.Politico;
import java.util.Random;

public class PartialOrderHandler extends DataGeneratorHandler {
    @Override
    public Politico[] generateData(String type, int n) {
        if (!type.equalsIgnoreCase("PARTIAL") && nextHandler != null) {
            return nextHandler.generateData(type, n);
        }
        Politico[] politicos = new Politico[n];
        Random rand = new Random();
        // Primera mitad ordenada
        for (int i = 0; i < n; i++) {
            politicos[i] = new Politico(100 + i * 100, RandomDateGenerator.generateRandomDate());
        }
        // Segunda mitad aleatoria
        for (int i = n/2; i < n; i++) {
            politicos[i] = new Politico(rand.nextInt(990000) + 100, RandomDateGenerator.generateRandomDate());
        }
        return politicos;
    }
}
