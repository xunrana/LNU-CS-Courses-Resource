# config.py

"""
本文件用于集中管理项目配置，包括数据库连接参数、请求头和目标 API 地址。
"""

# 数据库连接配置
DB_CONFIG = {
    'host': 'localhost',        # 数据库主机地址（本地数据库）
    'user': 'root',             # 数据库用户名
    'password': '2003David',     # 数据库密码（注意不要泄露到公网）
    'database': 'douban',       # 要连接的数据库名称
    'charset': 'utf8mb4'        # 使用支持中文和特殊字符的字符集
}

# HTTP 请求头部，模拟浏览器请求，避免被目标网站屏蔽
HEADERS = {
    "User-Agent": "Mozilla/5.0"
}

# 豆瓣电影数据接口的基础 URL（用于获取电影 JSON 数据）
BASE_URL = "https://movie.douban.com/j/search_subjects"

