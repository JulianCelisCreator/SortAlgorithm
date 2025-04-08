package com.mycompany.sort;

import com.mycompany.sort.view.SortingGUI;

import javax.swing.SwingUtilities;

public class Main {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            SortingGUI gui = new SortingGUI();
            gui.setVisible(true);
        });
    }
}
