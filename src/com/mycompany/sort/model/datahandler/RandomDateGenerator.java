package com.mycompany.sort.model.datahandler;

import java.time.LocalDate;
import java.util.Random;

public class RandomDateGenerator {
    public static LocalDate generateRandomDate() {
        Random rand = new Random();

        // Calcular el año mínimo y el año máximo
        int currentYear = LocalDate.now().getYear();
        int minYear = currentYear - 100;
        int maxYear = currentYear -20;

        // 2. Generar el año aleatorio en ese rango
        int randomYear = rand.nextInt(maxYear - minYear) + minYear;

        // 3. Generar mes y dia aleatorios ( evitando dias inválidos)
        int randomMonth = rand.nextInt(12) + 1;
        int randomDay = rand.nextInt(28) + 1;

        return LocalDate.of(randomYear, randomMonth, randomDay);
    }

}
