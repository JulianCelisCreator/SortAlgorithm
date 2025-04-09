package com.mycompany.sort.controller.accumulator;

public class AccumulatorValue {
    private long totalIterations = 0;
    private long totalTime = 0;
    private int count = 0;

    public void add(long iterations, long time) {
        totalIterations += iterations;
        totalTime += time;
        count++;
    }

    public void merge(AccumulatorValue other) {
        this.totalIterations += other.totalIterations;
        this.totalTime += other.totalTime;
        this.count += other.count;
    }

    public double getAverageIterations() {
        return count == 0 ? 0 : (double) totalIterations / count;
    }

    public double getAverageTime() {
        return count == 0 ? 0 : (double) totalTime / count;
    }
}