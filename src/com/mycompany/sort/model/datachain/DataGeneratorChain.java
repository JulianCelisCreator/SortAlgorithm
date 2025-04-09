package com.mycompany.sort.model.datachain;

import com.mycompany.sort.model.datahandler.*;
import com.mycompany.sort.model.politico.Politico;

public class DataGeneratorChain {
    private DataGeneratorHandler chain;

    public DataGeneratorChain() {
        // Configurar la cadena correctamente: Sorted -> Reverse -> Random
        DataGeneratorHandler sorted = new SortedOrderHandler();
        DataGeneratorHandler reverse = new ReverseOrderHandler();
        DataGeneratorHandler random = new RandomOrderHandler();

        sorted.setNextHandler(reverse);
        reverse.setNextHandler(random);

        this.chain = sorted; // La cadena empieza con "sorted"
    }

    public Politico[] generateData(String type, int size) {
        return chain.generateData(type, size);
    }
}