package com.xun.dao;



import com.xun.model.MovieActor;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class MovieActorDao extends BaseDao {
    public void addMovieActor(MovieActor movieActor) {
        String sql = "INSERT INTO MovieActors (movie_id, actor_id) VALUES (?, ?)";
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, movieActor.getMovieId());
            statement.setInt(2, movieActor.getActorId());
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void deleteMovieActor(int movieId, int actorId) {
        String sql = "DELETE FROM MovieActors WHERE movie_id = ? AND actor_id = ?";
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, movieId);
            statement.setInt(2, actorId);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public List<MovieActor> getActorsByMovieId(int movieId) {
        String sql = "SELECT * FROM MovieActors WHERE movie_id = ?";
        List<MovieActor> movieActors = new ArrayList<>();
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, movieId);
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                MovieActor movieActor = new MovieActor();
                // Fetch movie and actor details by their IDs (not implemented here)
                movieActors.add(movieActor);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return movieActors;
    }

    public List<MovieActor> getMoviesByActorId(int actorId) {
        String sql = "SELECT * FROM MovieActors WHERE actor_id = ?";
        List<MovieActor> movieActors = new ArrayList<>();
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, actorId);
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                MovieActor movieActor = new MovieActor();
                // Fetch movie and actor details by their IDs (not implemented here)
                movieActors.add(movieActor);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return movieActors;
    }
}
