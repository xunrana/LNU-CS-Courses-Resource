# database.py

import pymysql
from config import DB_CONFIG

class MovieDatabase:
    """
    管理电影数据库的连接与操作，包括建表、数据存储、评分提取等。

    Attributes:
        conn: 数据库连接对象。
        cursor: 数据库操作游标。
    """

    def __init__(self):
        """
        初始化数据库连接并创建 movies 表（如果尚未存在）。
        """
        self.conn = pymysql.connect(**DB_CONFIG)  # 使用配置文件中的数据库连接参数
        self.cursor = self.conn.cursor()
        self._create_table()

    def _create_table(self):
        """
        创建 movies 表，用于存储电影的标题、评分与链接。
        若表已存在则不重复创建。
        """
        self.cursor.execute("""
            CREATE TABLE IF NOT EXISTS movies (
                id INT AUTO_INCREMENT PRIMARY KEY,  -- 自动递增主键
                title VARCHAR(255),                -- 电影标题
                rate VARCHAR(10),                  -- 评分（以字符串保存，方便存储“暂无评分”等特殊情况）
                url TEXT                           -- 电影详情页链接
            )
        """)

    def save_movies(self, movies):
        """
        将电影信息批量插入数据库。

        Args:
            movies (List[Dict]): 包含 title、rate、url 的电影数据列表。
        """
        for m in movies:
            self.cursor.execute(
                "INSERT INTO movies (title, rate, url) VALUES (%s, %s, %s)",
                (m["title"], m["rate"], m["url"])
            )
        self.conn.commit()  # 提交事务
        print("[INFO] 数据保存成功")

    def get_all_ratings(self):
        """
        获取数据库中所有电影的评分。

        Returns:
            List[str]: 所有电影的评分列表（字符串形式）。
        """
        self.cursor.execute("SELECT rate FROM movies")
        return [r[0] for r in self.cursor.fetchall()]  # 返回评分的第一列

    def close(self):
        """
        关闭数据库连接与游标。
        """
        self.cursor.close()
        self.conn.close()
