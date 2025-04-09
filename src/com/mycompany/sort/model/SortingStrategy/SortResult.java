package com.mycompany.sort.model.SortingStrategy;

public class SortResult {
    private final String type;     // "ARRAY" o "MATRIX"
    private final int size;       // Tamaño de los datos
    private final String strategy;// Nombre del algoritmo
    private final long iterations; // Iteraciones totales
    private final long timeElapsedMillis; // Tiempo en milisegundos

    // Constructor completo (para resultados con contexto)
    public SortResult(String type,
                      int size,
                      String strategy,
                      long iterations,
                      long timeElapsedMillis) {
        if (iterations < 0 || timeElapsedMillis < 0) {
            throw new IllegalArgumentException("Iteraciones o tiempo no pueden ser negativos");
        }
        this.type = type;
        this.size = size;
        this.strategy = strategy;
        this.iterations = iterations;
        this.timeElapsedMillis = timeElapsedMillis;
    }

    // Constructor para métricas crudas (usado por las estrategias)
    public SortResult(long iterations, long timeElapsedMillis) {
        this(null, -1, null, iterations, timeElapsedMillis);
    }

    // Método para añadir contexto
    public SortResult withContext(String type, int size, String strategy) {
        return new SortResult(
                type,
                size,
                strategy,
                this.iterations,
                this.timeElapsedMillis
        );
    }

    // Getters
    public String getType() { return type; }
    public int getSize() { return size; }
    public String getStrategy() { return strategy; }
    public long getIterations() { return iterations; }
    public long getTimeElapsedMillis() { return timeElapsedMillis; }

    // Conversiones de tiempo
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
        long millis = totalMillis % 1_000;
        return String.format("%02d:%02d.%03d", minutes, seconds, millis);
    }

    @Override
    public String toString() {
        return String.format(
                "[%s] %s | Tamaño: %,d | Iteraciones: %,d | Tiempo: %s",
                type != null ? type : "RAW",
                strategy != null ? strategy : "N/A",
                size,
                iterations,
                getFormattedTime()
        );
    }
}