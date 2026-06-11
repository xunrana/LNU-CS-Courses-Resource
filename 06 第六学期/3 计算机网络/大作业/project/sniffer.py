from scapy.all import (sniff, conf)  # 增加导入 conf
from parser import parse_packet

class PacketSniffer:
    def __init__(self, callback):
        self.callback = callback  # 用于通知 GUI 更新数据
        self.running = False      # 抓包状态标志

    conf.L3socket = conf.L3socket  # 告诉 Scapy 只能用 Layer 3
    conf.use_pcap = False  # 告诉 Scapy 别去找那个不存在的驱动了
    def start_sniffing(self, protocol_filter):
        self.running = True

        def sniff_packet(pkt):
            # 解析数据包并发送到 GUI 显示
            parsed = parse_packet(pkt)
            self.callback(parsed)

        # 协议过滤器映射（Scapy 支持的格式）
        filter_map = {
            "TCP": "tcp",
            "UDP": "udp",
            "ICMP": "icmp",
            "ALL": None
        }

        # 启动抓包
        sniff(
            prn=sniff_packet,
            store=0,
            stop_filter=lambda x: not self.running,
            filter=filter_map.get(protocol_filter),
            L2socket=conf.L3socket  # <--- 【重点】必须加这一行！
        )

    def stop_sniffing(self):
        # 修改状态标志以停止抓包
        self.running = False
