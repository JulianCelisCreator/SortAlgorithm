package com.mycompany.sort.view;


import com.mycompany.sort.controller.SortingController;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;

public class SortingGUI extends JFrame {
    private final SortingController controller;

    private final JTextField sizeField;
    private final JTextField growthField;
    private final JTextArea outputArea;

    public SortingGUI() {
        controller = new SortingController();

        setTitle("Análisis de Estrategias de Ordenamiento");
        setSize(600, 400);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        // Panel de entrada
        JPanel inputPanel = new JPanel(new GridLayout(2, 2, 10, 10));
        inputPanel.setBorder(BorderFactory.createTitledBorder("Parámetros"));

        inputPanel.add(new JLabel("Tamaño inicial:"));
        sizeField = new JTextField("1000");
        inputPanel.add(sizeField);

        inputPanel.add(new JLabel("Factor de crecimiento:"));
        growthField = new JTextField("1.5");
        inputPanel.add(growthField);

        // Botones
        JButton runButton = new JButton("Ejecutar análisis");
        runButton.addActionListener(this::handleRunAnalysis);

        JButton exportButton = new JButton("Exportar resultados a PDF");
        exportButton.addActionListener(e -> controller.exportResultsToPDF());

        JPanel buttonPanel = new JPanel();
        buttonPanel.add(runButton);
        buttonPanel.add(exportButton);

        // Salida
        outputArea = new JTextArea();
        outputArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(outputArea);

        // Layout principal
        setLayout(new BorderLayout(10, 10));
        add(inputPanel, BorderLayout.NORTH);
        add(buttonPanel, BorderLayout.CENTER);
        add(scrollPane, BorderLayout.SOUTH);
    }

    private void handleRunAnalysis(ActionEvent e) {
        try {
            int size = Integer.parseInt(sizeField.getText());
            double factor = Double.parseDouble(growthField.getText());

            outputArea.setText("Ejecutando análisis...\n");
            controller.runAnalysis(size, factor);
            outputArea.append("¡Análisis completado! Resultados disponibles por consola o PDF.\n");

        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(this, "Por favor ingresa valores válidos.", "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            SortingGUI gui = new SortingGUI();
            gui.setVisible(true);
        });
    }
}
