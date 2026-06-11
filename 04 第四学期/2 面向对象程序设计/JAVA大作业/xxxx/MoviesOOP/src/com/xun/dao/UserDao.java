package com.xun.dao;


import com.xun.model.User;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class UserDao extends BaseDao {
	

	
	public void addUser(int userId, String username, String password) {
	    String sql = "INSERT INTO users (user_id, username, password) VALUES (?, ?, ?)";
	    try (Connection connection = getConnection();
	         PreparedStatement statement = connection.prepareStatement(sql)) {
	        statement.setInt(1, userId);
	        statement.setString(2, username);
	        statement.setString(3, password);
	        statement.executeUpdate();
	    } catch (SQLException e) {
	        e.printStackTrace();
	        // Handle exception appropriately, e.g., show error message
	    }
	}





    public void updateUser(User user) {
        String sql = "UPDATE Users SET username = ?, password = ? WHERE user_id = ?";
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setString(1, user.getUsername());
            statement.setString(2, user.getPassword());
            statement.setInt(3, user.getUserId());
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void deleteUser(int userId) {
        String sql = "DELETE FROM Users WHERE user_id = ?";
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, userId);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public User getUserById(int userId) {
        String sql = "SELECT * FROM Users WHERE user_id = ?";
        User user = null;
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, userId);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                user = new User();
                user.setUserId(resultSet.getInt("user_id"));
                user.setUsername(resultSet.getString("username"));
                user.setPassword(resultSet.getString("password"));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return user;
    }

    public List<User> getAllUsers() {
        String sql = "SELECT * FROM Users";
        List<User> users = new ArrayList<>();
        try (Connection connection = getConnection(); Statement statement = connection.createStatement(); ResultSet resultSet = statement.executeQuery(sql)) {
            while (resultSet.next()) {
                User user = new User();
                user.setUserId(resultSet.getInt("user_id"));
                user.setUsername(resultSet.getString("username"));
                user.setPassword(resultSet.getString("password"));
                users.add(user);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return users;
    }




	
}
