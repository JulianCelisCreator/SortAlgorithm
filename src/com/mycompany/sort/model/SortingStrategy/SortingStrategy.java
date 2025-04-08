package com.mycompany.sort.model.SortingStrategy;

import com.mycompany.sort.model.politico.Politico;

import java.util.Comparator;

public interface SortingStrategy {
    SortResult sort(Politico[] arr, Comparator<Politico> comparator);
}
