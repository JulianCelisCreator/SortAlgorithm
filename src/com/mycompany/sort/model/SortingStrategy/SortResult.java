package com.mycompany.sort.model.SortingStrategy;

public class SortResult {
    private int iterations;
    private long timeElapsed;

    public SortResult(int iterations, long timeElapsed) {
        this.iterations = iterations;
        this.timeElapsed = timeElapsed;
    }

    public int getIterations() {
        return iterations;
    }

    public void setIterations(int iterations) {
        this.iterations = iterations;
    }

    public long getTimeElapsed() {
        return timeElapsed;
    }

    public void setTimeElapsed(long timeElapsed) {
        this.timeElapsed = timeElapsed;
    }
}
