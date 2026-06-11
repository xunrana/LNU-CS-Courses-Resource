def parse_packet(pkt):
    # 解析数据包信息，返回字典摘要
    summary = {
        "src": pkt[0][1].src if hasattr(pkt[0][1], "src") else "N/A",        # 源 IP
        "dst": pkt[0][1].dst if hasattr(pkt[0][1], "dst") else "N/A",        # 目标 IP
        "proto": pkt[0][1].name if hasattr(pkt[0][1], "name") else pkt.name, # 协议类型
        "len": len(pkt),                                                     # 数据包长度
        "details": pkt.show(dump=True)                                       # 数据包详细内容（字符串形式）
    }
    return summary
