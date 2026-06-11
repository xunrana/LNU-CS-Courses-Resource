# 图形化网络抓包工具（Packet Sniffer with GUI）

这是一个基于 Python 编写的图形化网络抓包工具，结合了 `Scapy` 用于抓包，`Tkinter` 用于构建 GUI 界面，能够实时捕获并展示 TCP、UDP、ICMP 等网络数据包的信息。

---

## 📌 项目功能

- 实时抓取网络数据包
- 支持协议过滤（ALL / TCP / UDP / ICMP）
- 表格展示源 IP、目标 IP、协议类型和包长度
- 选择任意数据包可查看其详细内容（`scapy` 分析结果）
- 友好的图形用户界面（GUI）

---

## 🧰 环境要求

- Python 3.7 及以上
- 操作系统：Windows / Linux / macOS（需 root/管理员权限）

### 依赖模块

| 模块        | 用途            |
|-------------|-----------------|
| `scapy`     | 网络数据包抓取与解析 |
| `tkinter`   | GUI 构建（Python 标准库） |

---

## 📦 安装依赖

建议使用虚拟环境：

```bash
python -m venv venv
source venv/bin/activate  # Windows 使用 venv\Scripts\activate
