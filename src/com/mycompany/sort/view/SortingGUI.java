package com.mycompany.sort.view;

import com.mycompany.sort.controller.SortingController;
import com.mycompany.sort.controller.accumulator.AccumulatorValue;
import com.mycompany.sort.model.SortingStrategy.SortingStrategy;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.util.List;
import java.util.Map;

public class SortingGUI extends JFrame {
    private final SortingController controller;
    private final JTabbedPane tabbedPane;
    private final DefaultTableModel arrayTableModel;
    private final DefaultTableModel matrixTableModel;

    public SortingGUI(SortingController controller) {
        super("Analizador de Estrategias de Ordenamiento");
        this.controller = controller;

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(1200, 600);
        setLocationRelativeTo(null);
        setLayout(new BorderLayout());

        // Panel superior
        JPanel controlPanel = new JPanel();
        JTextField initialSizeField = new JTextField("1000", 10);
        JTextField growthFactorField = new JTextField("1.5", 10);
        JButton startButton = new JButton("Iniciar");
        JButton stopButton = new JButton("Detener");

        controlPanel.add(new JLabel("Tamaño inicial:"));
        controlPanel.add(initialSizeField);
        controlPanel.add(new JLabel("Factor crecimiento:"));
        controlPanel.add(growthFactorField);
        controlPanel.add(startButton);
        controlPanel.add(stopButton);
        add(controlPanel, BorderLayout.NORTH);

        // Tablas
        tabbedPane = new JTabbedPane();
        arrayTableModel = createTableModel();
        matrixTableModel = createTableModel();

        tabbedPane.addTab("Arreglos", new JScrollPane(new JTable(arrayTableModel)));
        tabbedPane.addTab("Matrices", new JScrollPane(new JTable(matrixTableModel)));

        add(tabbedPane, BorderLayout.CENTER);

        // Listeners
        startButton.addActionListener(e -> {
            try {
                int initialSize = Integer.parseInt(initialSizeField.getText());
                double growthFactor = Double.parseDouble(growthFactorField.getText());

                new Thread(() -> {
                    controller.runAnalysis(initialSize, growthFactor);
                    SwingUtilities.invokeLater(this::updateTables);
                }).start();

            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(this, "Valores inválidos", "Error", JOptionPane.ERROR_MESSAGE);
            }
        });

        stopButton.addActionListener(e -> updateTables());
    }

    private DefaultTableModel createTableModel() {
        List<SortingStrategy> strategies = controller.getStrategies();
        String[] columns = new String[1 + strategies.size() * 2];
        columns[0] = "Caso";

        int index = 1;
        for (SortingStrategy strategy : strategies) {
            columns[index++] = strategy.getName() + " (Iter)";
            columns[index++] = strategy.getName() + " (ms)";
        }

        return new DefaultTableModel(columns, 0) {
            @Override
            public boolean isCellEditable(int row, int column) {
                return false;
            }
        };
    }

    private void updateTables() {
        updateTableModel(arrayTableModel, controller.getAccumulatedResults("ARRAY"));
        updateTableModel(matrixTableModel, controller.getAccumulatedResults("MATRIX"));
    }

    private void updateTableModel(DefaultTableModel model, Map<String, Map<String, AccumulatorValue>> data) {
        model.setRowCount(0);
        List<String> cases = List.of("SORTED", "INVERSE", "RANDOM");
        List<SortingStrategy> strategies = controller.getStrategies();

        for (String dataCase : cases) {
            Object[] row = new Object[model.getColumnCount()];
            row[0] = dataCase;

            Map<String, AccumulatorValue> strategyData = data.get(dataCase);
            if (strategyData == null) continue;

            int colIndex = 1;
            for (SortingStrategy strategy : strategies) {
                AccumulatorValue value = strategyData.get(strategy.getName());
                if (value != null) {
                    row[colIndex++] = String.format("%.2f", value.getAverageIterations());
                    row[colIndex++] = String.format("%.2f", value.getAverageTime());
                } else {
                    colIndex += 2;
                }
            }
            model.addRow(row);
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            SortingController controller = new SortingController();
            SortingGUI gui = new SortingGUI(controller);
            gui.setVisible(true);
        });
    }
}