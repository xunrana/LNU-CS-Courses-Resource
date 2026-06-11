package com.xun.dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class BaseDao 
{
    // 数据库连接URL，这里使用的是MySQL数据库，连接的数据库是movies
    private static final String URL = "jdbc:mysql://localhost:3306/movies";
    // 数据库用户名
    private static final String USER = "root";
    // 数据库密码
    private static final String PASSWORD = "2003oyXL";

    // 获取数据库连接的方法
    protected Connection getConnection() {
        Connection connection = null;
        try {
            // 使用DriverManager获取数据库连接
            connection = DriverManager.getConnection(URL, USER, PASSWORD);
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return connection;
    }

    // 关闭数据库连接的方法
    protected void closeConnection(Connection connection) {
        if (connection != null) {
            try {
                // 关闭数据库连接
                connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
}
