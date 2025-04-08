package com.mycompany.sort.model.datachain;

import com.mycompany.sort.model.datahandler.DataGeneratorHandler;
import com.mycompany.sort.model.datahandler.PartialOrderHandler;
import com.mycompany.sort.model.datahandler.RandomOrderHandler;
import com.mycompany.sort.model.datahandler.ReverseOrderHandler;
import com.mycompany.sort.model.politico.Politico;

public class DataGeneratorChain {
    private DataGeneratorHandler chain;

    public DataGeneratorChain() {
        this.chain = new RandomOrderHandler();
        PartialOrderHandler partial = new PartialOrderHandler();
        ReverseOrderHandler reverse = new ReverseOrderHandler();
        chain.setNextHandler(partial);
        partial.setNextHandler(reverse);
    }

    public Politico[] generateData(String type, int size) {
        return chain.generateData(type, size);
    }
}

