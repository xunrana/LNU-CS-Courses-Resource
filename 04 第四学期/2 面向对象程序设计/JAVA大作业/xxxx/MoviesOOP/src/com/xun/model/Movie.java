package com.xun.model;

import java.util.Date;
import java.util.List;

public class Movie {
    private int movieId;
    private String title;
    private Date releaseDate;
    private int duration;
    private double rating;
    private String plotSummary;
    private MovieType type;
    private Region region;
    private Director director;
    private List<Actor> actors;

    // Constructor
    public Movie() {}

    // Getters and Setters
    public int getMovieId() {
        return movieId;
    }

    public void setMovieId(int movieId) {
        this.movieId = movieId;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public Date getReleaseDate() {
        return releaseDate;
    }

    public void setReleaseDate(Date releaseDate) {
        this.releaseDate = releaseDate;
    }

    public int getDuration() {
        return duration;
    }

    public void setDuration(int duration) {
        this.duration = duration;
    }

    public double getRating() {
        return rating;
    }

    public void setRating(double rating) {
        this.rating = rating;
    }

    public String getPlotSummary() {
        return plotSummary;
    }

    public void setPlotSummary(String plotSummary) {
        this.plotSummary = plotSummary;
    }

    public MovieType getType() {
        return type;
    }

    public void setType(MovieType type) {
        this.type = type;
    }

    public Region getRegion() {
        return region;
    }

    public void setRegion(Region region) {
        this.region = region;
    }

    public Director getDirector() {
        return director;
    }

    public void setDirector(Director director) {
        this.director = director;
    }

    public List<Actor> getActors() {
        return actors;
    }

    public void setActors(List<Actor> actors) {
        this.actors = actors;
    }

    
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Title: ").append(title).append("\n");
        sb.append("Release Date: ").append(releaseDate).append("\n");
        sb.append("Duration: ").append(duration).append(" minutes\n");
        sb.append("Rating: ").append(rating).append("\n");
        sb.append("Plot Summary: ").append(plotSummary).append("\n");

        if (type != null) sb.append("Type: ").append(type.getTypeName()).append("\n");
        if (region != null) sb.append("Region: ").append(region.getRegionName()).append("\n");
        if (director != null) sb.append("Director: ").append(director.getDirectorName()).append("\n");
        if (actors != null && !actors.isEmpty()) {
            sb.append("Actors: ");
            for (Actor actor : actors) {
                sb.append(actor.getActorName()).append(", ");
            }
            sb.delete(sb.length() - 2, sb.length()); // Remove the last comma and space
            sb.append("\n");
        }

        return sb.toString();
    }


    // Add method to set type by id
    public void setTypeId(int typeId) {
        if (this.type == null) {
            this.type = new MovieType();
        }
        this.type.setTypeId(typeId);
    }

    // Add method to set region by id
    public void setRegionId(int regionId) {
        if (this.region == null) {
            this.region = new Region();
        }
        this.region.setRegionId(regionId);
    }

    // Add method to set director by id
    public void setDirectorId(int directorId) {
        if (this.director == null) {
            this.director = new Director();
            
        }
        this.director.setDirectorId(directorId);
    }
}
