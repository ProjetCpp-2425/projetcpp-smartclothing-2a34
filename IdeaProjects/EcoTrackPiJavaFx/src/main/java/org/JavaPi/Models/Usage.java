package org.JavaPi.Models;

import java.time.LocalDate;

public class Usage {

    private int id;
    private String category;
    private LocalDate date;

    public Usage() {}

    public Usage(String category, LocalDate date) {
        this.category = category;
        this.date = date;
    }

    public int getId() { return id; }
    public void setId(int id) { this.id = id; }

    public String getCategory() { return category; }
    public void setCategory(String category) { this.category = category; }

    public LocalDate getDate() { return date; }
    public void setDate(LocalDate date) { this.date = date; }

    @Override
    public String toString() {
        return "Usage{id=" + id + ", category='" + category + "', date=" + date + "}";
    }
}