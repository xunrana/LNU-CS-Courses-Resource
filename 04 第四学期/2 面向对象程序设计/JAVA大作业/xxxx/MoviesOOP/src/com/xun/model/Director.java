package com.xun.model;



import java.util.Date;

public class Director {
    private int directorId;
    private String directorName;
    private Date birthDate;

    // Constructor
    public Director() {}

    // Getters and Setters
    public int getDirectorId() {
        return directorId;
    }

    public void setDirectorId(int directorId) {
        this.directorId = directorId;
    }

    public String getDirectorName() {
        return directorName;
    }

    public void setDirectorName(String directorName) {
        this.directorName = directorName;
    }

    public Date getBirthDate() {
        return birthDate;
    }

    public void setBirthDate(Date birthDate) {
        this.birthDate = birthDate;
    }
}
