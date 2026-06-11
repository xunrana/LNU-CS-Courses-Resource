package com.xun.dao;

import com.xun.model.Actor;
import com.xun.model.Director;
import com.xun.model.Movie;
import com.xun.model.MovieType;
import com.xun.model.Region;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class MovieDao extends BaseDao {

	public void addMovie(Movie movie)
	{
	    String sql = "INSERT INTO Movies (movie_id, title, release_date, duration, rating, plot_summary, type_id, region_id, director_id) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)";
	    try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
	        statement.setInt(1, movie.getMovieId()); // Assuming movieId is the first parameter
	        statement.setString(2, movie.getTitle());
	        statement.setDate(3, new Date(movie.getReleaseDate().getTime()));
	        statement.setInt(4, movie.getDuration());
	        statement.setDouble(5, movie.getRating());
	        statement.setString(6, movie.getPlotSummary());
	        statement.setInt(7, movie.getType().getTypeId());
	        statement.setInt(8, movie.getRegion().getRegionId());
	        statement.setInt(9, movie.getDirector().getDirectorId());
	        
	        statement.executeUpdate();
	    } catch (SQLException e) {
	        e.printStackTrace();
	    }
	}


    public void updateMovie(Movie movie) {
        String sql = "UPDATE Movies SET title = ?, release_date = ?, duration = ?, rating = ?, plot_summary = ?, type_id = ?, region_id = ?, director_id = ? WHERE movie_id = ?";
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setString(1, movie.getTitle());
            statement.setDate(2, new Date(movie.getReleaseDate().getTime()));
            statement.setInt(3, movie.getDuration());
            statement.setDouble(4, movie.getRating());
            statement.setString(5, movie.getPlotSummary());
            statement.setInt(6, movie.getType().getTypeId());
            statement.setInt(7, movie.getRegion().getRegionId());
            statement.setInt(8, movie.getDirector().getDirectorId());
            statement.setInt(9, movie.getMovieId());
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void deleteMovie(int movieId) {
        String sql = "DELETE FROM Movies WHERE movie_id = ?";
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, movieId);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public Movie getMovieById(int movieId) {
        String sql = "SELECT m.*, t.type_name, r.region_name, d.director_name " +
                     "FROM Movies m " +
                     "LEFT JOIN types t ON m.type_id = t.type_id " +
                     "LEFT JOIN regions r ON m.region_id = r.region_id " +
                     "LEFT JOIN directors d ON m.director_id = d.director_id " +
                     "WHERE m.movie_id = ?";
        Movie movie = null;
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, movieId);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                movie = extractMovieFromResultSet(resultSet);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return movie;
    }

    public List<Movie> getAllMovies() {
        String sql = "SELECT m.*, t.type_name, r.region_name, d.director_name " +
                     "FROM Movies m " +
                     "LEFT JOIN types t ON m.type_id = t.type_id " +
                     "LEFT JOIN regions r ON m.region_id = r.region_id " +
                     "LEFT JOIN directors d ON m.director_id = d.director_id";
        List<Movie> movies = new ArrayList<>();
        try (Connection connection = getConnection(); Statement statement = connection.createStatement(); ResultSet resultSet = statement.executeQuery(sql)) {
            while (resultSet.next()) {
                movies.add(extractMovieFromResultSet(resultSet));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return movies;
    }

    public List<Movie> searchMovies(String actor, String director, String title, int year) {
        List<Movie> movies = new ArrayList<>();
        String sql = "SELECT m.*, t.type_name, r.region_name, d.director_name " +
                     "FROM Movies m " +
                     "LEFT JOIN MovieActors ma ON m.movie_id = ma.movie_id " +
                     "LEFT JOIN Actors a ON ma.actor_id = a.actor_id " +
                     "LEFT JOIN MovieTypes t ON m.type_id = t.type_id " +
                     "LEFT JOIN Regions r ON m.region_id = r.region_id " +
                     "LEFT JOIN Directors d ON m.director_id = d.director_id " +
                     "WHERE (a.actor_name LIKE ? OR ? IS NULL OR ? = '') " +
                     "AND (d.director_name LIKE ? OR ? IS NULL OR ? = '') " +
                     "AND (m.title LIKE ? OR ? IS NULL OR ? = '') " +
                     "AND (YEAR(m.release_date) = ? OR ? = 0)";
        try (Connection conn = getConnection(); PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, actor != null ? "%" + actor + "%" : "%");
            pstmt.setString(2, actor != null ? "%" + actor + "%" : "%");
            pstmt.setString(3, actor != null ? "%" + actor + "%" : "");
            pstmt.setString(4, director != null ? "%" + director + "%" : "%");
            pstmt.setString(5, director != null ? "%" + director + "%" : "%");
            pstmt.setString(6, director != null ? "%" + director + "%" : "");
            pstmt.setString(7, title != null ? "%" + title + "%" : "%");
            pstmt.setString(8, title != null ? "%" + title + "%" : "%");
            pstmt.setString(9, title != null ? "%" + title + "%" : "");
            pstmt.setInt(10, year);
            pstmt.setInt(11, year);
            ResultSet rs = pstmt.executeQuery();
            while (rs.next()) {
                movies.add(extractMovieFromResultSet(rs));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return movies;
    }


    public List<Movie> searchMoviesByYear(int year) {
        List<Movie> movies = new ArrayList<>();
        String sql = "SELECT m.*, t.type_name, r.region_name, d.director_name " +
                     "FROM Movies m " +
                     "LEFT JOIN MovieTypes t ON m.type_id = t.type_id " +
                     "LEFT JOIN Regions r ON m.region_id = r.region_id " +
                     "LEFT JOIN Directors d ON m.director_id = d.director_id " +
                     "WHERE YEAR(m.release_date) = ?";
        try (Connection connection = getConnection(); PreparedStatement pstmt = connection.prepareStatement(sql)) {
            pstmt.setInt(1, year);
            ResultSet rs = pstmt.executeQuery();
            while (rs.next()) {
                movies.add(extractMovieFromResultSet(rs));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return movies;
    }



    public List<Movie> getDailyRecommendation() {
        List<Movie> movies = new ArrayList<>();
        String sql = "SELECT m.*, t.type_name, r.region_name, d.director_name " +
                     "FROM Movies m " +
                     "LEFT JOIN MovieTypes t ON m.type_id = t.type_id " +
                     "LEFT JOIN Regions r ON m.region_id = r.region_id " +
                     "LEFT JOIN Directors d ON m.director_id = d.director_id " +
                     "ORDER BY RAND() LIMIT 3";
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                movies.add(extractMovieFromResultSet(resultSet));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return movies;
    }


    public List<Movie> getRecentHotRecommendations() {
        List<Movie> movies = new ArrayList<>();
        String sql = "SELECT m.*, t.type_name, r.region_name, d.director_name " +
                     "FROM Movies m " +
                     "LEFT JOIN MovieTypes t ON m.type_id = t.type_id " +
                     "LEFT JOIN Regions r ON m.region_id = r.region_id " +
                     "LEFT JOIN Directors d ON m.director_id = d.director_id " +
                     "ORDER BY m.release_date DESC LIMIT 5";
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                movies.add(extractMovieFromResultSet(resultSet));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return movies;
    }


    private Movie extractMovieFromResultSet(ResultSet rs) throws SQLException {
        Movie movie = new Movie();
        movie.setMovieId(rs.getInt("movie_id"));
        movie.setTitle(rs.getString("title"));
        movie.setReleaseDate(rs.getDate("release_date"));
        movie.setDuration(rs.getInt("duration"));
        movie.setRating(rs.getDouble("rating"));
        movie.setPlotSummary(rs.getString("plot_summary"));
        
        // Set type
        MovieType type = new MovieType();
        type.setTypeId(rs.getInt("type_id"));
        type.setTypeName(rs.getString("type_name"));
        movie.setType(type);

        // Set region
        Region region = new Region();
        region.setRegionId(rs.getInt("region_id"));
        region.setRegionName(rs.getString("region_name"));
        movie.setRegion(region);

        // Set director
        Director director = new Director();
        director.setDirectorId(rs.getInt("director_id"));
        director.setDirectorName(rs.getString("director_name"));
        movie.setDirector(director);

        // Fetch actors
        List<Actor> actors = getActorsByMovieId(rs.getInt("movie_id"));
        movie.setActors(actors);

        return movie;
    }

    private List<Actor> getActorsByMovieId(int movieId) {
        List<Actor> actors = new ArrayList<>();
        String sql = "SELECT a.* FROM Actors a " +
                     "JOIN MovieActors ma ON a.actor_id = ma.actor_id " +
                     "WHERE ma.movie_id = ?";
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, movieId);
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                Actor actor = new Actor();
                actor.setActorId(resultSet.getInt("actor_id"));
                actor.setActorName(resultSet.getString("actor_name"));
                actors.add(actor);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return actors;
    }


}
