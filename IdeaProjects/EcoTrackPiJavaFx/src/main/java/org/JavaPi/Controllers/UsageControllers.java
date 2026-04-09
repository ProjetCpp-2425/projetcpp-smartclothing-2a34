package org.JavaPi.Controllers;

import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import org.JavaPi.Models.Usage;
import org.JavaPi.Services.UsageServices;

public class UsageControllers {

    @FXML
    ComboBox<String> categoryField;

    @FXML
    DatePicker dateField;

    @FXML
    TableView<Usage> usageTable;

    @FXML
    TableColumn<Usage, Integer> idCol;

    @FXML
    TableColumn<Usage, String> categoryCol;

    @FXML
    TableColumn<Usage, String> dateCol;

    UsageServices service = new UsageServices();

    @FXML
    public void initialize() {
        // Remplir le ComboBox
        categoryField.setItems(FXCollections.observableArrayList("Déchets", "Eau", "Énergie"));

        // Lier les colonnes aux attributs de Usage
        idCol.setCellValueFactory(new PropertyValueFactory<>("id"));
        categoryCol.setCellValueFactory(new PropertyValueFactory<>("category"));
        dateCol.setCellValueFactory(new PropertyValueFactory<>("date"));

        // Afficher la liste au démarrage
        afficherUsages();

        // Remplir les champs quand on clique sur une ligne
        usageTable.getSelectionModel().selectedItemProperty().addListener(
                (obs, oldVal, newVal) -> {
                    if (newVal != null) {
                        categoryField.setValue(newVal.getCategory());
                        dateField.setValue(newVal.getDate());
                    }
                }
        );
    }

    @FXML
    void ajouter() {
        Usage u = new Usage();
        u.setCategory(categoryField.getValue());
        u.setDate(dateField.getValue());
        service.add(u);
        afficherUsages();
        viderChamps();
    }

    @FXML
    void modifier() {
        Usage selected = usageTable.getSelectionModel().getSelectedItem();
        if (selected != null) {
            selected.setCategory(categoryField.getValue());
            selected.setDate(dateField.getValue());
            service.update(selected);
            afficherUsages();
            viderChamps();
        }
    }

    @FXML
    void supprimer() {
        Usage selected = usageTable.getSelectionModel().getSelectedItem();
        if (selected != null) {
            service.delete(selected);
            afficherUsages();
            viderChamps();
        }
    }

    void afficherUsages() {
        usageTable.setItems(FXCollections.observableArrayList(service.getAll()));
    }

    void viderChamps() {
        categoryField.setValue(null);
        dateField.setValue(null);
    }
}