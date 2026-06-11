# main.py

from spider import MovieSpider
from database import MovieDatabase
from analysis import RatingAnalyzer

class DoubanMovieApp:
    """
    豆瓣电影数据采集与评分分析应用程序。

    Attributes:
        tags (List[str]): 要抓取的电影类型标签列表。
        total (int): 每个标签下抓取的电影总数。
    """
    def __init__(self, tags, total):
        """
        初始化应用程序实例。

        Args:
            tags (List[str]): 电影类型标签列表。
            total (int): 每个标签下抓取的电影数量。
        """
        self.tags = tags
        self.total = total

    def run(self):
        """
        运行整个数据采集、存储与评分分析流程：
        1. 从豆瓣抓取电影数据；
        2. 存入本地数据库；
        3. 获取所有评分数据；
        4. 分析并可视化评分分布。
        """
        # Step 1: 抓取电影数据
        spider = MovieSpider(self.tags, self.total)
        movies = spider.fetch()

        # Step 2: 将电影数据存入数据库
        db = MovieDatabase()
        db.save_movies(movies)

        # Step 3: 获取所有评分数据用于分析
        ratings = db.get_all_ratings()
        db.close()

        # Step 4: 可视化评分分析结果
        analyzer = RatingAnalyzer(ratings)
        analyzer.plot()

# 程序入口
if __name__ == "__main__":
    # 要抓取的电影类型标签列表（来源：豆瓣分类）
    tags = [
        "剧情", "喜剧", "动作", "爱情", "科幻",
        "动画", "悬疑", "惊悚", "恐怖", "情色",
        "音乐", "歌舞", "家庭", "传记", "历史",
        "战争", "犯罪", "奇幻", "冒险", "灾难"
    ]

    # 实例化并运行应用程序，总共每个标签抓取 200 部电影
    app = DoubanMovieApp(tags, total=200)
    app.run()


