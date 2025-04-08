package com.mycompany.sort.model.SortingStrategy;

public class SortResult {
    private long iterations;
    private long timeElapsedMillis; // Tiempo transcurrido en milisegundos

    public SortResult(long iterations, long timeElapsedMillis) {
        this.iterations = iterations;
        this.timeElapsedMillis = timeElapsedMillis;
    }

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

    // Método para obtener el tiempo transcurrido en segundos con decimales
    public double getTimeElapsedSeconds() {
        return timeElapsedMillis / 1000.0;
    }

    // Método para obtener el tiempo transcurrido en minutos con decimales
    public double getTimeElapsedMinutes() {
        return timeElapsedMillis / 60000.0;
    }

    // Método para obtener una representación formateada del tiempo transcurrido
    public String getFormattedTime() {
        long minutes = timeElapsedMillis / 60000;
        long seconds = (timeElapsedMillis % 60000) / 1000;
        long milliseconds = timeElapsedMillis % 1000;
        return String.format("%d min, %d sec, %d ms", minutes, seconds, milliseconds);
    }
}
