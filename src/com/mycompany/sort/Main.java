package com.mycompany.sort;

import com.mycompany.sort.controller.SortingController;
import com.mycompany.sort.view.SortingGUI;

import javax.swing.SwingUtilities;

public class Main {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            SortingController controller = new SortingController(); // Separa lógica
            SortingGUI gui = new SortingGUI(controller);            // Pasa el controlador a la vista
            gui.setVisible(true);
        });
    }
}
