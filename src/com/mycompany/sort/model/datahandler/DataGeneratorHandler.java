package com.mycompany.sort.model.datahandler;

import com.mycompany.sort.model.politico.Politico;

public abstract class DataGeneratorHandler {
    protected DataGeneratorHandler nextHandler;

    public void setNextHandler(DataGeneratorHandler nextHandler) {
        this.nextHandler = nextHandler;
    }

    public abstract Politico[] generateData(String type, int size);
}