package com.xun.model;

import java.util.Date;

public class UserRating {
    private int userId;
    private int movieId;
    private double rating;
    private Date dateRated;

    // Constructor
    public UserRating() {}

    // Getters and Setters
    public int getUserId() {
        return userId;
    }

    public void setUserId(int userId) {
        this.userId = userId;
    }

    public int getMovieId() {
        return movieId;
    }

    public void setMovieId(int movieId) {
        this.movieId = movieId;
    }

    public double getRating() {
        return rating;
    }

    public void setRating(double rating) {
        this.rating = rating;
    }

    public Date getDateRated() {
        return dateRated;
    }

    public void setDateRated(Date dateRated) {
        this.dateRated = dateRated;
    }

}
