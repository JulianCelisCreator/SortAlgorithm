package com.mycompany.sort.model.SortingStrategy;

public class SortResult {
    private long iterations;
    private long timeElapsedMillis;  // Tiempo en milisegundos

    public SortResult(long iterations, long timeElapsedMillis) {
        this.iterations = iterations;
        this.timeElapsedMillis = timeElapsedMillis;
    }

    // Getters y Setters
    public long getIterations() {
        return iterations;
    }

    public void setIterations(long iterations) {
        this.iterations = iterations;
    }

    public long getTimeElapsedMillis() {
        return timeElapsedMillis;
    }

    public void setTimeElapsedMillis(long timeElapsedMillis) {
        this.timeElapsedMillis = timeElapsedMillis;
    }

    // Conversiones útiles
    public double getTimeElapsedSeconds() {
        return timeElapsedMillis / 1_000.0;
    }

    public double getTimeElapsedMinutes() {
        return timeElapsedMillis / 60_000.0;
    }

    // Formato legible
    public String getFormattedTime() {
        long totalMillis = timeElapsedMillis;
        long minutes = totalMillis / 60_000;
        long seconds = (totalMillis % 60_000) / 1_000;
        long milliseconds = totalMillis % 1_000;
        return String.format("%d min, %d sec, %d ms", minutes, seconds, milliseconds);
    }

    @Override
    public String toString() {
        return String.format(
                "Iteraciones: %,d | Tiempo: %s",
                iterations,
                getFormattedTime()
        );
    }
}