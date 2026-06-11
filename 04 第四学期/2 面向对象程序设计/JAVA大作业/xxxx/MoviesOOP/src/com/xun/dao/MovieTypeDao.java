package com.xun.dao;

import com.xun.model.MovieType;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class MovieTypeDao extends BaseDao {
    public void addMovieType(MovieType movieType) {
        String sql = "INSERT INTO MovieTypes (type_name) VALUES (?)";
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setString(1, movieType.getTypeName());
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void updateMovieType(MovieType movieType) {
        String sql = "UPDATE MovieTypes SET type_name = ? WHERE type_id = ?";
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setString(1, movieType.getTypeName());
            statement.setInt(2, movieType.getTypeId());
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void deleteMovieType(int typeId) {
        String sql = "DELETE FROM MovieTypes WHERE type_id = ?";
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, typeId);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public MovieType getMovieTypeById(int typeId) {
        String sql = "SELECT * FROM MovieTypes WHERE type_id = ?";
        MovieType movieType = null;
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, typeId);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                movieType = new MovieType();
                movieType.setTypeId(resultSet.getInt("type_id"));
                movieType.setTypeName(resultSet.getString("type_name"));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return movieType;
    }

    public List<MovieType> getAllMovieTypes() {
        String sql = "SELECT * FROM MovieTypes";
        List<MovieType> movieTypes = new ArrayList<>();
        try (Connection connection = getConnection(); Statement statement = connection.createStatement(); ResultSet resultSet = statement.executeQuery(sql)) {
            while (resultSet.next()) {
                MovieType movieType = new MovieType();
                movieType.setTypeId(resultSet.getInt("type_id"));
                movieType.setTypeName(resultSet.getString("type_name"));
                movieTypes.add(movieType);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return movieTypes;
    }
}
