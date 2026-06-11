from scapy.all import sniff
from parser import parse_packet

class PacketSniffer:
    def __init__(self, callback):
        self.callback = callback  # 用于通知 GUI 更新数据
        self.running = False      # 抓包状态标志

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

        # 启动抓包，使用回调函数处理每个抓到的数据包
        sniff(
            prn=sniff_packet,                    # 每个包触发的函数
            store=0,                             # 不存储抓到的数据包
            stop_filter=lambda x: not self.running,  # 动态停止条件
            filter=filter_map.get(protocol_filter)   # 应用过滤器
        )

    def stop_sniffing(self):
        # 修改状态标志以停止抓包
        self.running = False