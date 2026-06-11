package com.xun.dao;


import com.xun.model.UserFavorite;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class UserFavoriteDao extends BaseDao {
    public void addUserFavorite(UserFavorite userFavorite) {
        String sql = "INSERT INTO UserFavorites (user_id, movie_id, date_added) VALUES (?, ?, ?)";
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, userFavorite.getUserId());
            statement.setInt(2, userFavorite.getMovieId());
            statement.setTimestamp(3, new Timestamp(userFavorite.getDateAdded().getTime()));
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void deleteUserFavorite(int userId, int movieId) {
        String sql = "DELETE FROM UserFavorites WHERE user_id = ? AND movie_id = ?";
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, userId);
            statement.setInt(2, movieId);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public List<UserFavorite> getFavoritesByUserId(int userId) {
        String sql = "SELECT * FROM UserFavorites WHERE user_id = ?";
        List<UserFavorite> userFavorites = new ArrayList<>();
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, userId);
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                UserFavorite userFavorite = new UserFavorite();
                // Fetch user and movie details by their IDs (not implemented here)
                userFavorites.add(userFavorite);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return userFavorites;
    }

    public List<UserFavorite> getUsersByMovieId(int movieId) {
        String sql = "SELECT * FROM UserFavorites WHERE movie_id = ?";
        List<UserFavorite> userFavorites = new ArrayList<>();
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, movieId);
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                UserFavorite userFavorite = new UserFavorite();
                // Fetch user and movie details by their IDs (not implemented here)
                userFavorites.add(userFavorite);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return userFavorites;
    }
}
