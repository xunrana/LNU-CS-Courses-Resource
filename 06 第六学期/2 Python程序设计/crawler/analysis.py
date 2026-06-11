# analysis.py

import matplotlib.pyplot as plt
from collections import defaultdict

# 设置 Matplotlib 支持中文显示与负号正常显示
plt.rcParams["font.sans-serif"] = ["SimHei"]  # 使用黑体显示中文
plt.rcParams["axes.unicode_minus"] = False   # 正常显示负号

class RatingAnalyzer:
    """
    用于分析电影评分数据并绘制评分分布图。

    Attributes:
        ratings (List[str]): 所有电影的评分（字符串形式）。
        bins (defaultdict[int]): 存储每个评分区间的数量。
        no_rating (int): 统计无评分电影的数量。
    """

    def __init__(self, ratings):
        """
        初始化分析器。

        Args:
            ratings (List[str]): 从数据库读取的评分列表。
        """
        self.ratings = ratings
        self.bins = defaultdict(int)  # 每个整数评分区间的数量
        self.no_rating = 0            # 无评分的数量

    def analyze(self):
        """
        对评分数据进行分析，统计每个整数区间（0-1, 1-2, ..., 9-10）内的评分数量。
        """
        for rate in self.ratings:
            try:
                r = float(rate)               # 将评分转换为浮点数
                key = min(int(r), 9)          # 将评分归类到对应区间（最多为9-10）
                self.bins[key] += 1
            except:
                self.no_rating += 1           # 不能转换为数字的视为“无评分”

    def plot(self, save_path="ratings_distribution.png"):
        """
        绘制评分分布直方图，并保存为图像文件。

        Args:
            save_path (str): 保存图像的路径（默认：ratings_distribution.png）
        """
        self.analyze()  # 先进行评分统计分析

        # 构造横坐标标签和对应数据
        labels = [f"{i}-{i+1}" for i in range(10)] + ["无评分"]
        counts = [self.bins[i] for i in range(10)] + [self.no_rating]

        # 设置画布大小
        plt.figure(figsize=(10, 6))
        bars = plt.bar(labels, counts, color='skyblue')  # 绘制柱状图
        plt.title("豆瓣电影评分分布")
        plt.xlabel("评分区间")
        plt.ylabel("电影数量")

        # 在每个柱子上添加具体数值标签
        for bar in bars:
            height = bar.get_height()
            plt.text(bar.get_x() + bar.get_width() / 2, height + 1, str(height), ha="center")

        plt.grid(axis="y", linestyle="--", alpha=0.7)  # 添加横向网格线
        plt.tight_layout()
        plt.savefig(save_path)  # 保存图像
        plt.show()              # 显示图像
