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
pip install scapy
```

如果是在 Linux 上运行，`tkinter` 可能需要通过系统包管理器安装，例如：

```bash
sudo apt install python3-tk
```

---

## ▶️ 运行方式

抓包通常需要管理员或 root 权限。

Windows 下建议以管理员身份打开 PowerShell，然后执行：

```powershell
python main.py
```

Linux / macOS 下可使用：

```bash
sudo python main.py
```

---

## 📁 文件说明

| 文件 | 作用 |
| :--- | :--- |
| `main.py` | 程序入口，创建 Tkinter 主窗口 |
| `ui_main.py` | GUI 界面与交互逻辑 |
| `sniffer.py` | 基于 Scapy 的抓包逻辑 |
| `parser.py` | 数据包摘要与详细信息解析 |

---

## ⚠️ 注意事项

- 运行前请确认已安装 `scapy`。
- 抓包功能依赖系统网络权限，普通终端可能无法捕获数据包。
- 如果协议过滤无法工作，优先确认系统是否支持对应的 BPF 过滤能力。
- 本项目用于课程学习与网络协议分析，请勿用于未授权网络环境。
