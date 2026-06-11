package com.xun.dao;


import com.xun.model.Admin;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class AdminDao extends BaseDao {

	
    public void addAdmin(Admin admin) {
        String sql = "INSERT INTO Admins (username, password) VALUES (?, ?)";
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setString(1, admin.getUsername());
            statement.setString(2, admin.getPassword());
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void updateAdmin(Admin admin) {
        String sql = "UPDATE Admins SET username = ?, password = ? WHERE admin_id = ?";
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setString(1, admin.getUsername());
            statement.setString(2, admin.getPassword());
            statement.setInt(3, admin.getAdminId());
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void deleteAdmin(int adminId) {
        String sql = "DELETE FROM Admins WHERE admin_id = ?";
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, adminId);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public Admin getAdminById(int adminId) {
        String sql = "SELECT * FROM Admins WHERE admin_id = ?";
        Admin admin = null;
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, adminId);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                admin = new Admin();
                admin.setAdminId(resultSet.getInt("admin_id"));
                admin.setUsername(resultSet.getString("username"));
                admin.setPassword(resultSet.getString("password"));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return admin;
    }

    public List<Admin> getAllAdmins() {
        String sql = "SELECT * FROM Admins";
        List<Admin> admins = new ArrayList<>();
        try (Connection connection = getConnection(); Statement statement = connection.createStatement(); ResultSet resultSet = statement.executeQuery(sql)) {
            while (resultSet.next()) {
                Admin admin = new Admin();
                admin.setAdminId(resultSet.getInt("admin_id"));
                admin.setUsername(resultSet.getString("username"));
                admin.setPassword(resultSet.getString("password"));
                admins.add(admin);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return admins;
    }
}
