package com.mycompany.sort.model;

public abstract class DataGeneratorHandler {
    protected DataGeneratorHandler nextHandler;

    public void setNextHandler(DataGeneratorHandler nextHandler) {
        this.nextHandler = nextHandler;
    }

    public abstract Politico[] generateData(String type, int n);
}
