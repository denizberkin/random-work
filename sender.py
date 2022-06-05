from vidstream import ScreenShareClient
import threading

sender = ScreenShareClient('192.168.1.104', 9999, x_res=1920, y_res=1080)

t = threading.Thread(target=sender.start_stream)

t.start()

while input() != 'stop':
    continue

sender.stop_stream()

