package com.mycompany.sort.model;

import java.util.Comparator;

public interface SortingStrategy {
    SortResult sort(Politico[] arr, Comparator<Politico> comparator);
}
