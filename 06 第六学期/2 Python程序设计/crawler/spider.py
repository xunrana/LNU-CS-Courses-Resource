# spider.py

import requests
import time
from config import BASE_URL, HEADERS

class MovieSpider:
    """
    用于从豆瓣电影API抓取指定标签下的电影数据。

    Attributes:
        tags (List[str]): 要抓取的电影标签。
        total (int): 每个标签下希望抓取的电影总数。
        movies (List[Dict]): 已抓取的电影信息列表。
        seen_urls (Set[str]): 用于去重的已抓取电影链接集合。
    """

    def __init__(self, tags, total):
        """
        初始化抓取器。

        Args:
            tags (List[str]): 电影标签列表。
            total (int): 每个标签下抓取的电影数量。
        """
        self.tags = tags
        self.total = total
        self.movies = []
        self.seen_urls = set()

    def fetch(self):
        """
        执行抓取流程：遍历所有标签，对每个标签分批分页抓取数据。

        Returns:
            List[Dict]: 包含电影标题、评分、链接的电影字典列表。
        """
        for tag in self.tags:
            for start in range(0, self.total, 20):  # 每页抓取20条
                params = {
                    "type": "movie",          # 类型为电影
                    "tag": tag,               # 当前电影标签
                    "sort": "recommend",      # 按推荐排序
                    "page_limit": 20,         # 每页限制数量
                    "page_start": start       # 分页起始位置
                }

                try:
                    # 向豆瓣API发起请求
                    res = requests.get(BASE_URL, headers=HEADERS, params=params, timeout=10)
                    res.raise_for_status()  # 如果响应状态码错误，抛出异常

                    # 获取电影数据列表
                    data = res.json().get("subjects", [])
                    if not data:
                        break  # 如果没有返回数据，结束该标签的抓取

                    for movie in data:
                        # 去重：只加入未抓取过的电影
                        if movie["url"] not in self.seen_urls:
                            self.seen_urls.add(movie["url"])
                            self.movies.append({
                                "title": movie["title"],
                                "rate": movie["rate"],
                                "url": movie["url"]
                            })

                    print(f"[INFO] 正在抓取标签: {tag}, 已抓取: {len(self.movies)}")
                    time.sleep(0.3)  # 避免访问过于频繁导致被封IP

                except Exception as e:
                    print(f"[ERROR] 抓取失败: {e}")
                    break  # 出现错误，跳出当前标签的抓取

        return self.movies

