import tkinter as tk
from tkinter import ttk
from tkinter import scrolledtext
import threading
from sniffer import PacketSniffer

class PacketSnifferGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("图形化网络抓包工具")  # 窗口标题
        self.sniffer = PacketSniffer(self.add_packet)  # 初始化抓包器，绑定数据处理函数

        self.protocol = tk.StringVar(value="ALL")  # 协议选择变量
        self.packets = []  # 用于存储抓到的数据包信息

        # ------------------ GUI 组件布局 ------------------

        # 协议过滤标签
        ttk.Label(root, text="协议过滤:").grid(row=0, column=0, padx=5, pady=5, sticky="w")

        # 协议下拉选择框（只读）
        self.protocol_menu = ttk.Combobox(
            root,
            textvariable=self.protocol,
            values=["ALL", "TCP", "UDP", "ICMP"],
            state="readonly"
        )
        self.protocol_menu.grid(row=0, column=1, padx=5, pady=5, sticky="w")

        # 开始抓包按钮
        self.start_button = ttk.Button(root, text="开始抓包", command=self.start_sniffing)
        self.start_button.grid(row=0, column=2, padx=5, pady=5)

        # 停止抓包按钮（初始禁用）
        self.stop_button = ttk.Button(root, text="停止抓包", command=self.stop_sniffing, state="disabled")
        self.stop_button.grid(row=0, column=3, padx=5, pady=5)

        # 数据包列表显示区域（Treeview）
        self.tree = ttk.Treeview(root, columns=("src", "dst", "proto", "len"), show="headings", height=15)
        self.tree.heading("src", text="源 IP")
        self.tree.heading("dst", text="目标 IP")
        self.tree.heading("proto", text="协议")
        self.tree.heading("len", text="长度")
        self.tree.grid(row=1, column=0, columnspan=4, padx=5, pady=5, sticky="nsew")

        # 绑定点击选择事件
        self.tree.bind("<<TreeviewSelect>>", self.on_select)

        # 数据包详细信息区域（带滚动条的多行文本）
        self.details = scrolledtext.ScrolledText(root, height=10)
        self.details.grid(row=2, column=0, columnspan=4, padx=5, pady=5, sticky="nsew")

        # 设置窗口行列自适应扩展
        root.grid_rowconfigure(1, weight=1)
        root.grid_columnconfigure(3, weight=1)

    def start_sniffing(self):
        # 点击“开始抓包”后执行的逻辑
        self.start_button.config(state="disabled")
        self.stop_button.config(state="normal")
        self.details.delete(1.0, tk.END)  # 清空详细信息窗口
        self.packets.clear()              # 清空历史数据
        self.tree.delete(*self.tree.get_children())  # 清空表格
        # 启动后台线程进行抓包，避免阻塞 GUI
        threading.Thread(
            target=self.sniffer.start_sniffing,
            args=(self.protocol.get(),),
            daemon=True
        ).start()

    def stop_sniffing(self):
        # 点击“停止抓包”后执行
        self.sniffer.stop_sniffing()
        self.start_button.config(state="normal")
        self.stop_button.config(state="disabled")

    def add_packet(self, pkt_info):
        # 新抓到一个包时执行，更新 GUI 表格和缓存
        self.packets.append(pkt_info)
        self.tree.insert(
            "", "end",
            values=(pkt_info["src"], pkt_info["dst"], pkt_info["proto"], pkt_info["len"])
        )

    def on_select(self, event):
        # 当用户点击表格中某一行时显示其详细内容
        selected = self.tree.selection()
        if selected:
            index = self.tree.index(selected[0])
            pkt = self.packets[index]
            self.details.delete(1.0, tk.END)
            self.details.insert(tk.END, pkt["details"])
