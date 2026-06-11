package com.xun.dao;

import com.xun.model.Region;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class RegionDao extends BaseDao {
    public void addRegion(Region region) {
        String sql = "INSERT INTO Regions (region_name) VALUES (?)";
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setString(1, region.getRegionName());
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void updateRegion(Region region) {
        String sql = "UPDATE Regions SET region_name = ? WHERE region_id = ?";
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setString(1, region.getRegionName());
            statement.setInt(2, region.getRegionId());
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void deleteRegion(int regionId) {
        String sql = "DELETE FROM Regions WHERE region_id = ?";
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, regionId);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public Region getRegionById(int regionId) {
        String sql = "SELECT * FROM Regions WHERE region_id = ?";
        Region region = null;
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, regionId);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                region = new Region();
                region.setRegionId(resultSet.getInt("region_id"));
                region.setRegionName(resultSet.getString("region_name"));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return region;
    }

    public List<Region> getAllRegions() {
        String sql = "SELECT * FROM Regions";
        List<Region> regions = new ArrayList<>();
        try (Connection connection = getConnection(); Statement statement = connection.createStatement(); ResultSet resultSet = statement.executeQuery(sql)) {
            while (resultSet.next()) {
                Region region = new Region();
                region.setRegionId(resultSet.getInt("region_id"));
                region.setRegionName(resultSet.getString("region_name"));
                regions.add(region);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return regions;
    }
}
