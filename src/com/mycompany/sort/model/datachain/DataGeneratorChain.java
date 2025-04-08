package com.mycompany.sort.model.datachain;

import com.mycompany.sort.model.datahandler.*;
import com.mycompany.sort.model.politico.Politico;

public class DataGeneratorChain {
    private DataGeneratorHandler chain;

    public DataGeneratorChain() {
        this.chain = new SortedOrderHandler();
        DataGeneratorHandler sorted = new SortedOrderHandler();
        DataGeneratorHandler reverse = new ReverseOrderHandler();
        DataGeneratorHandler random = new RandomOrderHandler(); // Nuevo manejador

        chain.setNextHandler(sorted);
        sorted.setNextHandler(reverse);
        reverse.setNextHandler(random); // Agregar al final de la cadena
    }

    public Politico[] generateData(String type, int size) {
        return chain.generateData(type, size);
    }
}
