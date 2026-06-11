package com.xun.util;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

/**
 * 数据库连接工具类。
 */
public class DBUtil {
    // 数据库连接的URL
    private static final String URL = "jdbc:mysql://localhost:3306/movies";

    // 数据库用户名
    private static final String USER = "root";

    // 数据库密码
    private static final String PASSWORD = "2003oyXL";

    /**
     * 获取数据库连接对象。
     *
     * @return 表示数据库连接的 Connection 对象
     * @throws SQLException 如果发生数据库访问错误
     */
    public static Connection getConnection() throws SQLException {
        return DriverManager.getConnection(URL, USER, PASSWORD);
    }
}
