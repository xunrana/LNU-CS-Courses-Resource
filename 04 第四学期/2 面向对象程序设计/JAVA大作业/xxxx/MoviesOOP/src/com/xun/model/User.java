package com.xun.model;

import java.util.List;

public class User {
    private int userId;
    private String username;
    private String password;
    private List<Movie> favoriteMovies;
    private List<UserRating> ratings;

    // Constructors
    public User() {}

    public User(int userId,String username, String password) {
    	this.userId = userId;
        this.username = username;
        this.password = password;
    }


    // Getters and Setters
    public int getUserId() {
        return userId;
    }

    public void setUserId(int userId) {
        this.userId = userId;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public List<Movie> getFavoriteMovies() {
        return favoriteMovies;
    }

    public void setFavoriteMovies(List<Movie> favoriteMovies) {
        this.favoriteMovies = favoriteMovies;
    }

    public List<UserRating> getRatings() {
        return ratings;
    }

    public void setRatings(List<UserRating> ratings) {
        this.ratings = ratings;
    }
}
