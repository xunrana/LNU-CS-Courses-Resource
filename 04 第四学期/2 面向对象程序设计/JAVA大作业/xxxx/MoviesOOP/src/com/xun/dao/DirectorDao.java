package com.xun.dao;


import com.xun.model.Director;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DirectorDao extends BaseDao {
	public void addDirector(Director director) {
	    String sql = "INSERT INTO Directors (director_id, director_name, birth_date) VALUES (?, ?, ?)";
	    try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
	        statement.setInt(1, director.getDirectorId());
	        statement.setString(2, director.getDirectorName());
	        statement.setDate(3, new Date(director.getBirthDate().getTime()));
	        statement.executeUpdate();
	    } catch (SQLException e) {
	        e.printStackTrace();
	    }
	}


    public void updateDirector(Director director) {
        String sql = "UPDATE Directors SET director_name = ?, birth_date = ? WHERE director_id = ?";
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setString(1, director.getDirectorName());
            statement.setDate(2, new Date(director.getBirthDate().getTime()));
            statement.setInt(3, director.getDirectorId());
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void deleteDirector(int directorId) {
        String sql = "DELETE FROM Directors WHERE director_id = ?";
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, directorId);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public Director getDirectorById(int directorId) {
        String sql = "SELECT * FROM Directors WHERE director_id = ?";
        Director director = null;
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, directorId);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                director = new Director();
                director.setDirectorId(resultSet.getInt("director_id"));
                director.setDirectorName(resultSet.getString("director_name"));
                director.setBirthDate(resultSet.getDate("birth_date"));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return director;
    }

    public List<Director> getAllDirectors() {
        String sql = "SELECT * FROM Directors";
        List<Director> directors = new ArrayList<>();
        try (Connection connection = getConnection(); Statement statement = connection.createStatement(); ResultSet resultSet = statement.executeQuery(sql)) {
            while (resultSet.next()) {
                Director director = new Director();
                director.setDirectorId(resultSet.getInt("director_id"));
                director.setDirectorName(resultSet.getString("director_name"));
                director.setBirthDate(resultSet.getDate("birth_date"));
                directors.add(director);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return directors;
    }
}
