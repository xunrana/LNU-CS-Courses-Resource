package com.xun.dao;


import com.xun.model.Actor;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class ActorDao extends BaseDao {
	public void addActor(Actor actor) {
	    String sql = "INSERT INTO Actors (actor_id, actor_name, birth_date) VALUES (?, ?, ?)";
	    try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
	        statement.setInt(1, actor.getActorId());
	        statement.setString(2, actor.getActorName());
	        
	        // Handle null birthDate case
	        Date birthDate = actor.getBirthDate() != null ? new Date(actor.getBirthDate().getTime()) : null;
	        statement.setDate(3, birthDate);
	        
	        statement.executeUpdate();
	    } catch (SQLException e) {
	        e.printStackTrace();
	    }
	}



    public void updateActor(Actor actor) {
        String sql = "UPDATE Actors SET actor_name = ?, birth_date = ? WHERE actor_id = ?";
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setString(1, actor.getActorName());
            statement.setDate(2, new Date(actor.getBirthDate().getTime()));
            statement.setInt(3, actor.getActorId());
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void deleteActor(int actorId) {
        String sql = "DELETE FROM Actors WHERE actor_id = ?";
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, actorId);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public Actor getActorById(int actorId) {
        String sql = "SELECT * FROM Actors WHERE actor_id = ?";
        Actor actor = null;
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, actorId);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                actor = new Actor();
                actor.setActorId(resultSet.getInt("actor_id"));
                actor.setActorName(resultSet.getString("actor_name"));
                actor.setBirthDate(resultSet.getDate("birth_date"));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return actor;
    }

    public List<Actor> getAllActors() {
        String sql = "SELECT * FROM Actors";
        List<Actor> actors = new ArrayList<>();
        try (Connection connection = getConnection(); Statement statement = connection.createStatement(); ResultSet resultSet = statement.executeQuery(sql)) {
            while (resultSet.next()) {
                Actor actor = new Actor();
                actor.setActorId(resultSet.getInt("actor_id"));
                actor.setActorName(resultSet.getString("actor_name"));
                actor.setBirthDate(resultSet.getDate("birth_date"));
                actors.add(actor);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return actors;
    }
}
