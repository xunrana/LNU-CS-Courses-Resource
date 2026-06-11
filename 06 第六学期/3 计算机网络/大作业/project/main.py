import tkinter as tk
from ui_main import PacketSnifferGUI

if __name__ == "__main__":
    # 创建主窗口
    root = tk.Tk()
    # 初始化 GUI 应用
    app = PacketSnifferGUI(root)
    # 启动主事件循环
    root.mainloop()
