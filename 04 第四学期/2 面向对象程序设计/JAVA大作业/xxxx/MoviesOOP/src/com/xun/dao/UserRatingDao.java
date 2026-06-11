package com.xun.dao;


import com.xun.model.UserRating;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class UserRatingDao extends BaseDao {
    public void addUserRating(UserRating userRating) {
        String sql = "INSERT INTO UserRatings (user_id, movie_id, rating, date_rated) VALUES (?, ?, ?, ?)";
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, userRating.getUserId());
            statement.setInt(2, userRating.getMovieId());
            statement.setDouble(3, userRating.getRating());
            statement.setTimestamp(4, new Timestamp(userRating.getDateRated().getTime()));
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void updateUserRating(UserRating userRating) {
        String sql = "UPDATE UserRatings SET rating = ?, date_rated = ? WHERE user_id = ? AND movie_id = ?";
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setDouble(1, userRating.getRating());
            statement.setTimestamp(2, new Timestamp(userRating.getDateRated().getTime()));
            statement.setInt(3, userRating.getUserId());
            statement.setInt(4, userRating.getMovieId());
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void deleteUserRating(int userId, int movieId) {
        String sql = "DELETE FROM UserRatings WHERE user_id = ? AND movie_id = ?";
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, userId);
            statement.setInt(2, movieId);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public List<UserRating> getRatingsByUserId(int userId) {
        String sql = "SELECT * FROM UserRatings WHERE user_id = ?";
        List<UserRating> userRatings = new ArrayList<>();
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, userId);
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                UserRating userRating = new UserRating();
                // Fetch user and movie details by their IDs (not implemented here)
                userRatings.add(userRating);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return userRatings;
    }

    public List<UserRating> getRatingsByMovieId(int movieId) {
        String sql = "SELECT * FROM UserRatings WHERE movie_id = ?";
        List<UserRating> userRatings = new ArrayList<>();
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, movieId);
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                UserRating userRating = new UserRating();
                // Fetch user and movie details by their IDs (not implemented here)
                userRatings.add(userRating);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return userRatings;
    }
}
