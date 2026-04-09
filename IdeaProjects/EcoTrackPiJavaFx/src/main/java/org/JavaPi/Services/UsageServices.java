package org.JavaPi.Services;

import org.JavaPi.Models.Usage;
import org.JavaPi.Utils.MyDataBase;

import java.sql.*;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class UsageServices {

    private Connection cnx;

    public UsageServices() {
        cnx = MyDataBase.getInstance().getCnx();
    }

    public void add(Usage usage) {
        String qry = "INSERT INTO `eco_usage`(`category`, `date`) VALUES (?, ?)";
        try {
            PreparedStatement pstm = cnx.prepareStatement(qry);
            pstm.setString(1, usage.getCategory());
            pstm.setDate(2, Date.valueOf(usage.getDate()));
            pstm.executeUpdate();
            System.out.println("Usage ajouté avec succès !");
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public List<Usage> getAll() {
        List<Usage> usages = new ArrayList<>();
        String qry = "SELECT * FROM `eco_usage`";
        try {
            Statement stm = cnx.createStatement();
            ResultSet rs = stm.executeQuery(qry);
            while (rs.next()) {
                Usage u = new Usage();
                u.setId(rs.getInt("id"));
                u.setCategory(rs.getString("category"));
                u.setDate(rs.getDate("date").toLocalDate());
                usages.add(u);
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
        return usages;
    }

    public void update(Usage usage) {
        String qry = "UPDATE `eco_usage` SET `category` = ?, `date` = ? WHERE `id` = ?";
        try {
            PreparedStatement pstm = cnx.prepareStatement(qry);
            pstm.setString(1, usage.getCategory());
            pstm.setDate(2, Date.valueOf(usage.getDate()));
            pstm.setInt(3, usage.getId());
            pstm.executeUpdate();
            System.out.println("Usage modifié avec succès !");
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void delete(Usage usage) {
        String qry = "DELETE FROM `eco_usage` WHERE `id` = ?";
        try {
            PreparedStatement pstm = cnx.prepareStatement(qry);
            pstm.setInt(1, usage.getId());
            pstm.executeUpdate();
            System.out.println("Usage supprimé avec succès !");
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }
}