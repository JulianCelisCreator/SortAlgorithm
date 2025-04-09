package com.mycompany.sort.util;

import com.itextpdf.io.IOException;
import com.itextpdf.kernel.pdf.PdfDocument;
import com.itextpdf.kernel.pdf.PdfWriter;
import com.itextpdf.layout.Document;
import com.itextpdf.layout.element.Paragraph;
import com.itextpdf.layout.element.Table;
import com.itextpdf.layout.property.TextAlignment;
import com.mycompany.sort.controller.accumulator.AccumulatorKey;
import com.mycompany.sort.controller.accumulator.AccumulatorValue;

import java.util.Map;

public class PdfExporter {

    public static void exportToPdf(Map<AccumulatorKey, AccumulatorValue> accumulator, String filePath) {
        try (PdfWriter writer = new PdfWriter(filePath);
             PdfDocument pdf = new PdfDocument(writer);
             Document document = new Document(pdf)) {

            // Título del documento
            document.add(new Paragraph("Reporte de Resultados de Ordenamiento")
                    .setTextAlignment(TextAlignment.CENTER)
                    .setBold()
                    .setFontSize(16));

            // Tabla de resultados
            Table table = new Table(5);
            table.setWidth(500);

            // Encabezados de la tabla
            table.addHeaderCell("Caso");
            table.addHeaderCell("Tipo");
            table.addHeaderCell("Estrategia");
            table.addHeaderCell("Iter. Promedio");
            table.addHeaderCell("Tiempo Prom. (ms)");

            // Llenar datos
            for (Map.Entry<AccumulatorKey, AccumulatorValue> entry : accumulator.entrySet()) {
                AccumulatorKey key = entry.getKey();
                AccumulatorValue value = entry.getValue();

                table.addCell(key.dataCase());
                table.addCell(key.dataType());
                table.addCell(key.strategyName());
                table.addCell(String.format("%.2f", value.getAverageIterations()));
                table.addCell(String.format("%.2f", value.getAverageTime()));
            }

            document.add(table);

        } catch (IOException | java.io.IOException e) {
            e.printStackTrace();
        }
    }
}